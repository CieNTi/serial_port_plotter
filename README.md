# Serial Port Plotter

This is a Windows application that displays real time data from serial port. I had to create it for a project and I would like to put the code here so more people could use it. The application is 32-bit and built with Qt and QCustomPlot library. It can plot up to three axes and 1000 data points. Plot refresh rate is 20 Hz, independent of incoming data frequency. It can also export JPG with the plot.

The application supports zooming and dragging using the mouse wheel. Clicking anywhere in the plot displays the X and Y values of the graph in the status bar.

# Screenshot

![Serial Port Plotter screenshot](gh_assets/screen.jpg)

# How to use the application

Just send your integer data over the serial port. The application expects certain format so it can differentiate between values. Each message you send must start with '$' and end with ';' (semi-colon) and the integers inside need to be space-separated. The Help button displays comprehensive instructions. Example: If you need to plot two values, use this code in your mbed source file:

# Send data over the serial port

```c
pc.printf("$%d %d;", data1, data2);
wait_ms(10);
```

Depending on how much data you want to display, you can adjust the number of data points. For example, if you send data from the serial port of the mbed every 10 ms (100 Hz) and the plotter is set to display 500 points, it will contain information for 5 seconds of data.

# Source

Source and .pro file of the Qt Project are available. A standalone .exe is included for the people who do not want to build the source. Search for it at [releases](https://github.com/CieNTi/serial_port_plotter/releases)

# Credits

* Original programmer: [Borislav K](https://developer.mbed.org/users/borislav/ )
* Source: [Serial Port Plotter at mbed forums](https://developer.mbed.org/users/borislav/notebook/serial-port-plotter/)
