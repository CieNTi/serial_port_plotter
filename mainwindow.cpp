/***************************************************************************
**  This file is part of Serial Port Plotter                              **
**                                                                        **
**                                                                        **
**  Serial Port Plotter is a program for plotting integer data from       **
**  serial port using Qt and QCustomPlot                                  **
**                                                                        **
**  This program is free software: you can redistribute it and/or modify  **
**  it under the terms of the GNU General Public License as published by  **
**  the Free Software Foundation, either version 3 of the License, or     **
**  (at your option) any later version.                                   **
**                                                                        **
**  This program is distributed in the hope that it will be useful,       **
**  but WITHOUT ANY WARRANTY; without even the implied warranty of        **
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         **
**  GNU General Public License for more details.                          **
**                                                                        **
**  You should have received a copy of the GNU General Public License     **
**  along with this program.  If not, see http://www.gnu.org/licenses/.   **
**                                                                        **
****************************************************************************
**           Author: Borislav                                             **
**           Contact: b.kereziev@gmail.com                                **
**           Date: 29.12.14                                               **
****************************************************************************/

#include "mainwindow.hpp"
#include "ui_mainwindow.h"

/**
 * @brief Constructor
 * @param parent
 */
MainWindow::MainWindow (QWidget *parent) :
    QMainWindow (parent),
    ui (new Ui::MainWindow),

    /* Populate colors */
    line_colors (
      {
        /* For channel data (matlab parula palette) */
        QColor ("#0072bd"), /**< 0: blue */
        QColor ("#d95319"), /**< 1: orange */
        QColor ("#edb120"), /**< 2: yellow */
        QColor ("#7e2f8e"), /**< 3: purple */
        QColor ("#77ac30"), /**< 4: green */
        QColor ("#4dbeee"), /**< 5: light-blue */
        QColor ("#a2142f"), /**< 6: red */
      }),
    gui_colors (
      {
        /* Monochromatic for axes and ui */
        QColor (48,  47,  47,  255), /**<  7: qdark ui dark/background color */
        QColor (80,  80,  80,  255), /**<  8: qdark ui medium/grid color */
        QColor (170, 170, 170, 255)  /**<  9: qdark ui light/text color */
      }),

    /* Main vars */
    connected (false),
    plotting (false),
    dataPointNumber (0),
    serialPort (NULL),
    STATE (WAIT_START),
    NUMBER_OF_POINTS (500)
{
    ui->setupUi (this);

    /* Init UI and populate UI controls */
    createUI();

    /* Setup plot area and connect controls slots */
    setupPlot();
}

/**
 * @brief Destructor
 */
MainWindow::~MainWindow()
{
    if (serialPort != NULL)
      {
        delete serialPort;
      }
    delete ui;
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Create remaining elements and populate the controls
 */
void MainWindow::createUI()
{
    /* Check if there are any ports at all; if not, disable controls and return */
    if (QSerialPortInfo::availablePorts().size() == 0)
      {
        enableControls (false);
        ui->connectButton->setEnabled (false);
        ui->statusBar->showMessage ("No ports detected.");
        ui->savePNGButton->setEnabled (false);
        return;
      }

    /* List all available serial ports and populate ports combo box */
    for (QSerialPortInfo port : QSerialPortInfo::availablePorts())
      {
        ui->comboPort->addItem (port.portName());
      }

    /* Populate baud rate combo box */
    ui->comboBaud->addItem ("1200");
    ui->comboBaud->addItem ("2400");
    ui->comboBaud->addItem ("4800");
    ui->comboBaud->addItem ("9600");
    ui->comboBaud->addItem ("19200");
    ui->comboBaud->addItem ("38400");
    ui->comboBaud->addItem ("57600");
    ui->comboBaud->addItem ("115200");
    /* Select 115200 bits by default */
    ui->comboBaud->setCurrentIndex (7);

    /* Populate data bits combo box */
    ui->comboData->addItem ("8 bits");
    ui->comboData->addItem ("7 bits");

    /* Populate parity combo box */
    ui->comboParity->addItem ("none");
    ui->comboParity->addItem ("odd");
    ui->comboParity->addItem ("even");

    /* Populate stop bits combo box */
    ui->comboStop->addItem ("1 bit");
    ui->comboStop->addItem ("2 bits");
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Setup the plot area
 */
void MainWindow::setupPlot()
{
    /* Remove everything from the plot */
    ui->plot->clearItems();

    /* Background for the plot area */
    ui->plot->setBackground (gui_colors[0]);

    /* Plot button is disabled initially */
    ui->stopPlotButton->setEnabled (false);

    /* Used for higher performance (see QCustomPlot real time example) */
    ui->plot->setNotAntialiasedElements (QCP::aeAll);
    QFont font;
    font.setStyleStrategy (QFont::NoAntialias);
    ui->plot->legend->setFont (font);

    /** See QCustomPlot examples / styled demo **/
    /* X Axis: Style */
    ui->plot->xAxis->grid()->setPen (QPen(gui_colors[2], 1, Qt::DotLine));
    ui->plot->xAxis->grid()->setSubGridPen (QPen(gui_colors[1], 1, Qt::DotLine));
    ui->plot->xAxis->grid()->setSubGridVisible (true);
    ui->plot->xAxis->setBasePen (QPen (gui_colors[2]));
    ui->plot->xAxis->setTickPen (QPen (gui_colors[2]));
    ui->plot->xAxis->setSubTickPen (QPen (gui_colors[2]));
    ui->plot->xAxis->setUpperEnding (QCPLineEnding::esSpikeArrow);
    ui->plot->xAxis->setTickLabelColor (gui_colors[2]);
    ui->plot->xAxis->setTickLabelFont (font);
    /* Range */
    ui->plot->xAxis->setRange (0, NUMBER_OF_POINTS);
    ui->plot->xAxis->setAutoTickCount (12);

    /* Y Axis */
    ui->plot->yAxis->grid()->setPen (QPen(gui_colors[2], 1, Qt::DotLine));
    ui->plot->yAxis->grid()->setSubGridPen (QPen(gui_colors[1], 1, Qt::DotLine));
    ui->plot->yAxis->grid()->setSubGridVisible (true);
    ui->plot->yAxis->setBasePen (QPen (gui_colors[2]));
    ui->plot->yAxis->setTickPen (QPen (gui_colors[2]));
    ui->plot->yAxis->setSubTickPen (QPen (gui_colors[2]));
    ui->plot->yAxis->setUpperEnding (QCPLineEnding::esSpikeArrow);
    ui->plot->yAxis->setTickLabelColor (gui_colors[2]);
    ui->plot->yAxis->setTickLabelFont (font);
    /* Range */
    ui->plot->yAxis->setRange (ui->spinAxesMin->value(), ui->spinAxesMax->value());
    /* User can change Y axis tick step with a spin box */
    ui->plot->yAxis->setAutoTickStep (false);
    ui->plot->yAxis->setTickStep (ui->spinYStep->value());

    /* User interactions Drag and Zoom are allowed only on X axis, Y is fixed manually by UI control */
    ui->plot->setInteraction (QCP::iRangeDrag, true);
    ui->plot->setInteraction (QCP::iRangeZoom, true);
    ui->plot->axisRect()->setRangeDrag (Qt::Horizontal);
    ui->plot->axisRect()->setRangeZoom (Qt::Horizontal);

    /* Slot for printing coordinates */
    connect (ui->plot, SIGNAL (mouseRelease (QMouseEvent*)), this, SLOT (onMouseMoveInPlot (QMouseEvent*)));

    /* Connect update timer to replot slot */
    connect (&updateTimer, SIGNAL (timeout()), this, SLOT (replot()));
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Enable/disable controls
 * @param enable true enable, false disable
 */
void MainWindow::enableControls(bool enable)
{
    ui->comboBaud->setEnabled(enable);                                                    // Disable controls in the GUI
    ui->comboData->setEnabled(enable);
    ui->comboParity->setEnabled(enable);
    ui->comboPort->setEnabled(enable);
    ui->comboStop->setEnabled(enable);
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Open the inside serial port; connect its signals
 * @param portInfo
 * @param baudRate
 * @param dataBits
 * @param parity
 * @param stopBits
 */
void MainWindow::openPort(QSerialPortInfo portInfo, int baudRate, QSerialPort::DataBits dataBits, QSerialPort::Parity parity, QSerialPort::StopBits stopBits)
{
    serialPort = new QSerialPort(portInfo, 0);                                            // Create a new serial port

    connect(this, SIGNAL(portOpenOK()), this, SLOT(portOpenedSuccess()));                 // Connect port signals to GUI slots
    connect(this, SIGNAL(portOpenFail()), this, SLOT(portOpenedFail()));
    connect(this, SIGNAL(portClosed()), this, SLOT(onPortClosed()));
    connect(this, SIGNAL(newData(QStringList)), this, SLOT(onNewDataArrived(QStringList)));
    connect(serialPort, SIGNAL(readyRead()), this, SLOT(readData()));

    if(serialPort->open(QIODevice::ReadWrite) ) {
        serialPort->setBaudRate(baudRate);
        serialPort->setParity(parity);
        serialPort->setDataBits(dataBits);
        serialPort->setStopBits(stopBits);
        emit portOpenOK();
    } else {
        emit portOpenedFail();
        qDebug() << serialPort->errorString();
    }

}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Port Combo Box index changed slot; displays info for selected port when combo box is changed
 * @param arg1
 */
void MainWindow::on_comboPort_currentIndexChanged(const QString &arg1)
{
    QSerialPortInfo selectedPort(arg1);                                                   // Dislplay info for selected port
    ui->statusBar->showMessage(selectedPort.description());
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


/******************************************************************************************************************/
/* Connect Button clicked slot; handles connect and disconnect */
/******************************************************************************************************************/
void MainWindow::on_connectButton_clicked()
{
    if(connected) {                                                                       // If application is connected, disconnect
        serialPort->close();                                                              // Close serial port
        emit portClosed();                                                                // Notify application
        delete serialPort;                                                                // Delete the pointer
        serialPort = NULL;                                                                // Assign NULL to dangling pointer
        ui->connectButton->setText("Connect");                                            // Change Connect button text, to indicate disconnected
        ui->statusBar->showMessage("Disconnected!");                                      // Show message in status bar
        connected = false;                                                                // Set connected status flag to false
        plotting = false;                                                                 // Not plotting anymore
        receivedData.clear();                                                             // Clear received string
        ui->stopPlotButton->setEnabled(false);                                            // Take care of controls
        ui->savePNGButton->setEnabled(false);
        enableControls(true);
    } else {                                                                              // If application is not connected, connect
                                                                                          // Get parameters from controls first
        QSerialPortInfo portInfo(ui->comboPort->currentText());                           // Temporary object, needed to create QSerialPort
        int baudRate = ui->comboBaud->currentText().toInt();                              // Get baud rate from combo box
        int dataBitsIndex = ui->comboData->currentIndex();                                // Get index of data bits combo box
        int parityIndex = ui->comboParity->currentIndex();                                // Get index of parity combo box
        int stopBitsIndex = ui->comboStop->currentIndex();                                // Get index of stop bits combo box
        QSerialPort::DataBits dataBits;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;

        if(dataBitsIndex == 0) {                                                          // Set data bits according to the selected index
            dataBits = QSerialPort::Data8;
        } else {
            dataBits = QSerialPort::Data7;
        }

        if(parityIndex == 0) {                                                            // Set parity according to the selected index
            parity = QSerialPort::NoParity;
        } else if(parityIndex == 1) {
            parity = QSerialPort::OddParity;
        } else {
            parity = QSerialPort::EvenParity;
        }

        if(stopBitsIndex == 0) {                                                          // Set stop bits according to the selected index
             stopBits = QSerialPort::OneStop;
        } else {
            stopBits = QSerialPort::TwoStop;
        }

        serialPort = new QSerialPort(portInfo, 0);                                        // Use local instance of QSerialPort; does not crash
        openPort(portInfo, baudRate, dataBits, parity, stopBits);                         // Open serial port and connect its signals
    }
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Slot for port opened successfully
 */
void MainWindow::portOpenedSuccess()
{
    //qDebug() << "Port opened signal received!";
    setupPlot();                                                                          // Create the QCustomPlot area
    ui->connectButton->setText("Disconnect");                                             // Change buttons
    ui->statusBar->showMessage("Connected!");
    enableControls(false);                                                                // Disable controls if port is open
    ui->stopPlotButton->setText("Stop Plot");                                             // Enable button for stopping plot
    ui->stopPlotButton->setEnabled(true);
    ui->savePNGButton->setEnabled(true);                                                  // Enable button for saving plot
    updateTimer.start(20);                                                                // Slot is refreshed 20 times per second
    connected = true;                                                                     // Set flags
    plotting = true;
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Slot for fail to open the port
 */
void MainWindow::portOpenedFail()
{
    //qDebug() << "Port cannot be open signal received!";
    ui->statusBar->showMessage("Cannot open port!");
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Slot for closing the port
 */
void MainWindow::onPortClosed()
{
    //qDebug() << "Port closed signal received!";
    updateTimer.stop();
    connected = false;
    disconnect(serialPort, SIGNAL(readyRead()), this, SLOT(readData()));
    disconnect(this, SIGNAL(portOpenOK()), this, SLOT(portOpenedSuccess()));             // Disconnect port signals to GUI slots
    disconnect(this, SIGNAL(portOpenFail()), this, SLOT(portOpenedFail()));
    disconnect(this, SIGNAL(portClosed()), this, SLOT(onPortClosed()));
    disconnect(this, SIGNAL(newData(QStringList)), this, SLOT(onNewDataArrived(QStringList)));
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Replot
 */
void MainWindow::replot()
{
    if(connected) {
        ui->plot->xAxis->setRange(dataPointNumber - NUMBER_OF_POINTS, dataPointNumber);
        ui->plot->replot();
    }
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Stop Plot Button
 */
void MainWindow::on_stopPlotButton_clicked()
{
    if(plotting) {                                                                        // Stop plotting
        updateTimer.stop();                                                               // Stop updating plot timer
        plotting = false;
        ui->stopPlotButton->setText("Start Plot");
    } else {                                                                              // Start plotting
        updateTimer.start();                                                              // Start updating plot timer
        plotting = true;
        ui->stopPlotButton->setText("Stop Plot");
    }
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Slot for new data from serial port . Data is comming in QStringList and needs to be parsed
 * @param newData
 */
void MainWindow::onNewDataArrived(QStringList newData)
{
    static int data_members = 0;
    static int channel = 0;
    static int i = 0;

    if (plotting)
      {
        /* Get size of received list */
        data_members = newData.size();

        /* Parse data */
        for (i = 0; i < data_members; i++)
          {
            /* Update number of axes if needed */
            while (ui->plot->graphCount() <= channel)
              {
                /* Add new channel data */
                ui->plot->addGraph();
                ui->plot->graph()->setPen (line_colors[channel % CUSTOM_LINE_COLORS]);
              }

            /* [TODO] Method selection and plotting */
            /* X-Y */
            if (0)
              {

              }
            /* Rolling (v1.0.0 compatible) */
            else
              {
                /* Add data to Graph 0 */
                ui->plot->graph (channel)->addData (dataPointNumber, newData[channel].toInt());
                /* Remove data from graph 0 */
                //ui->plot->graph (0)->removeDataBefore (dataPointNumber - NUMBER_OF_POINTS);
                /* Increment data number and channel */
                channel++;
              }
          }

        /* Post-parsing */
        /* X-Y */
        if (0)
          {

          }
        /* Rolling (v1.0.0 compatible) */
        else
          {
            dataPointNumber++;
            channel = 0;
          }
      }
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Slot for spin box for plot minimum value on y axis
 * @param arg1
 */
void MainWindow::on_spinAxesMin_valueChanged(int arg1)
{
    ui->plot->yAxis->setRangeLower(arg1);
    ui->plot->replot();
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Slot for spin box for plot maximum value on y axis
 * @param arg1
 */
void MainWindow::on_spinAxesMax_valueChanged(int arg1)
{
    ui->plot->yAxis->setRangeUpper(arg1);
    ui->plot->replot();
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Read data for inside serial port
 */
void MainWindow::readData()
{
    if(serialPort->bytesAvailable()) {                                                    // If any bytes are available
        QByteArray data = serialPort->readAll();                                          // Read all data in QByteArray

        if(!data.isEmpty()) {                                                             // If the byte array is not empty
            char *temp = data.data();                                                     // Get a '\0'-terminated char* to the data

            for(int i = 0; temp[i] != '\0'; i++) {                                        // Iterate over the char*
                switch(STATE) {                                                           // Switch the current state of the message
                case WAIT_START:                                                          // If waiting for start [$], examine each char
                    if(temp[i] == START_MSG) {                                            // If the char is $, change STATE to IN_MESSAGE
                        STATE = IN_MESSAGE;
                        receivedData.clear();                                             // Clear temporary QString that holds the message
                        break;                                                            // Break out of the switch
                    }
                    break;
                case IN_MESSAGE:                                                          // If state is IN_MESSAGE
                    if(temp[i] == END_MSG) {                                              // If char examined is ;, switch state to END_MSG
                        STATE = WAIT_START;
                        QStringList incomingData = receivedData.split(' ');               // Split string received from port and put it into list
                        emit newData(incomingData);                                       // Emit signal for data received with the list
                        break;
                    }
                    else if(isdigit(temp[i]) || isspace(temp[i]) ) {                      // If examined char is a digit, and not '$' or ';', append it to temporary string
                        receivedData.append(temp[i]);
                    }
                    break;
                default: break;
                }
            }
        }
    }
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Number of axes combo; when changed, display axes colors in status bar
 * @param index
 */
//void MainWindow::on_comboAxes_currentIndexChanged(int index)
//{
//    if(index == 0) {
//      ui->statusBar->showMessage("Axis 1: Red");
//    } else if(index == 1) {
//        ui->statusBar->showMessage("Axis 1: Red; Axis 2: Yellow");
//    } else {
//        ui->statusBar->showMessage("Axis 1: Red; Axis 2: Yellow; Axis 3: Green");
//    }
//}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Spin box for changing the Y Tick step
 * @param arg1
 */
void MainWindow::on_spinYStep_valueChanged(int arg1)
{
    ui->plot->yAxis->setTickStep(arg1);
    ui->plot->replot();
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Save a PNG image of the plot to current EXE directory
 */
void MainWindow::on_savePNGButton_clicked()
{
    ui->plot->savePng (QString::number(dataPointNumber) + ".png");
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Reset the zoom of the plot to the initial values
 */
void MainWindow::on_resetPlotButton_clicked()
{
    ui->plot->yAxis->setRange(0, 4095);
    ui->plot->xAxis->setRange(dataPointNumber - NUMBER_OF_POINTS, dataPointNumber);
    ui->plot->yAxis->setTickStep(500);
    ui->plot->replot();
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Prints coordinates of mouse pointer in status bar on mouse release
 * @param event
 */
void MainWindow::onMouseMoveInPlot(QMouseEvent *event)
{
    int xx = ui->plot->xAxis->pixelToCoord(event->x());
    int yy = ui->plot->yAxis->pixelToCoord(event->y());
    QString coordinates("X: %1 Y: %2");
    coordinates = coordinates.arg(xx).arg(yy);
    ui->statusBar->showMessage(coordinates);
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Spin box controls how many data points are collected and displayed
 * @param arg1
 */
void MainWindow::on_spinPoints_valueChanged(int arg1)
{
    NUMBER_OF_POINTS = arg1;
    ui->plot->replot();
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

/**
 * @brief Shows a window with instructions
 */
void MainWindow::on_actionHow_to_use_triggered()
{
    helpWindow = new HelpWindow(this);
    helpWindow->setWindowTitle("How to use this application");
    helpWindow->show();
}
/** ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
