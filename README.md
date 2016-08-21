# Serial Port Plotter

This is a Windows application that displays real time data from serial port. The application is 32-bit and built with Qt and QCustomPlot library.

# Features
- No axes limit: An unknown/new channel data create a new graph and uses it
- No data point limit: All received data is kept and user can look for old data
- Exports to PNG with transparency
- Zooming and dragging using the mouse wheel
- Clicking anywhere in the plot displays the X and Y values of the graph in the status bar.

# Screenshot

![Serial Port Plotter screenshot](res/screen.jpg)

# How to use the application

Just send your integer data over the serial port. The application expects certain format so it can differentiate between values. Each message you send must start with '$' and end with ';' (semi-colon) and the integers inside need to be space-separated. The Help button displays comprehensive instructions. Example: If you need to plot two values, use this code in your mbed source file:

# Send data over the serial port

```c
printf("$%d %d;", data1, data2);
```

Depending on how much data you want to display, you can adjust the number of data points. For example, if you send data from the serial port of the mbed every 10 ms (100 Hz) and the plotter is set to display 500 points, it will contain information for 5 seconds of data.

# Source

Source and .pro file of the Qt Project are available. A standalone .exe is included for the people who do not want to build the source. Search for it at [releases](https://github.com/CieNTi/serial_port_plotter/releases)

# Credits

- [Serial Port Plotter at mbed forums](https://developer.mbed.org/users/borislav/notebook/serial-port-plotter/) by [Borislav K](https://developer.mbed.org/users/borislav/ )
- [Line Icon Set](http://www.flaticon.com/packs/line-icon-set) by [Situ Herrera](http://www.flaticon.com/authors/situ-herrera)

# Changelog

All notable changes to this project will be documented below this line.
This project adheres to [Semantic Versioning](http://semver.org/).

## [Unreleased]
### Added
- Original qdarkstyle resources (icons are now working)
- Manifest and all Windows related/recommended configs
- [Line Icon Set] in 3 colors

### Changed
- Resources structure
- Updated qcustomplot to v1.3.2
- Menubar is replaced by icon toolbar for usability

### Fixed

### Removed

## [1.0.0] - 2014-08-31
### Added
- Original [Boris Kereziev](b.kereziev@gmail.com) work commit

Initial README and commit

[Unreleased]: https://link/to/diff
[1.0.0]: https://developer.mbed.org/users/borislav/notebook/serial-port-plotter/
