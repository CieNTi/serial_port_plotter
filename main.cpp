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
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setOrganizationName("SerialPortPlotter");         // give the folder name to store settings in local home
    a.setApplicationName("SerialPortPlotter");          // give file config name (.conf)


    /* Apply style sheet */
    QFile file(":/serial_port_plotter/styles/style.qss");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
      {
        a.setStyleSheet(file.readAll());
        file.close();
      }

    /* Get the icon for the window corner */
    MainWindow w;
    QIcon appIcon(":/serial_port_plotter/icons/serial_port_icon.icns");
    w.setWindowIcon(appIcon);
    w.setWindowTitle("Serial Port Plotter v1.3.0");
    w.show();

    return a.exec();
}
