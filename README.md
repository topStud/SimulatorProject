# SimulatorProject

## Table of contents
* Background
* Goal
* Preperations
* How to get started
* How does it work?

## Background
This project was done as an assignment for our programming course - Advanced Programming 1. It shows the following skills -
streaming data, parallel programming, client-server Architecture, templates, and so on.

## Goal
The project's purpose is to communicate with a flight simulator by creating a server, so both could exchange data. The outcome (according to out fly.txt file) is a flying plane.

## Preperations
For running our project, you should make the following preparations:
* Download the latest version of FlightGear. You can find the download in the following link - https://www.flightgear.org/
* Add the file named "generic_small.xml" to the protocol folder witch is inside - usr/share/games/flightgear
* The project uses Threads, therefore it is very recommended to use a Linux workspace.
* You need to have a text file that contains the commands for the simulator.
* For allowing the communication between our server and the simulator it is important to do the following - 
  1) Enter the FlightGear
  2) Click on the setting button
  3) Under "Additional Settings" write the following lines :
    
    --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
    --telnet=socket,in,10,127.0.0.1,5402,tcp

## How to get started
After all our preparations are complete, it is time to fly!
First,  we need to create our server so the simulator can connect to it as a client. For that, we need to run our program as follows:
open a terminal and write the command - g++ -std=c++14 *.cpp -o a.out
then the following command will run the program - ./a.out fly.txt
Now, our server is ready and waiting for a client.
The next step will be to open the FlightGear and click on the button "fly!" on the bottom left corner of the screen.
Enjoy the flight :)

## How does it work?
So how our plane ends up in the air flying?
In each minute our program receives data from the simulator 10 times. This data is according to the XML file we inserted to the FlightGear protocol folder. Also, our program receives a text file with commands. These commands are responsible for updating the simulator with the appropriate values. The simulator receives the new values for the appropriate parameters and takes off.
