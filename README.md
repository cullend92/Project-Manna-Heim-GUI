# Project-Manna-Heim-GUI
Project Manna-Heim is the senior design project untaken by Team Vulcan at Embry-Riddle Aeronautical Universtity, Prescott campus during the Spring 2019 - Fall 2019 semesters.
Project Manna-Heim's goal is to design and construct a remotely operated rover with a deployable debris shelter.
This repository holds the code for the user interface subsystem used to operate the rover.
The interface is written in C++ with the Qt API.

The interface is separated into three modules: command, communication, and display.

The command module is responsible for recording the pilot's commands and forwarding them to the communications module for transmission to the rover.
The keyboard is scanned every 50 ms for each key associated with a command. When a keypress is detected, that command is added to a vector of commands to be transmitted. After all keys have been scanned the vector is passed to the communications module.

The communications module is responsible for transmitting and receiving all data between the rover and interface. A TCP server is hosted that the rover will connect to when powered on. Incoming data from the rover is passed to the display module and data from the command module is transmitted to the rover.

The display module holds the GUI and is responsible for displaying all information to the pilot. Button presses are passed to either the command or communications module depending on the button pressed.
