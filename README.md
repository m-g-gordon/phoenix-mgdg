# Phoenix (mgdg)
Phoenix code for custom Hexapod project, built by Mitchell Gordon and Derek Greenaway (mgdg).
Purpose: for Langara College microcontroller class's final term project.

This code is a hard fork of the standard Phoenix Hexapod code repo found at https://github.com/Lynxmotion/3DOF-4DOF-Hex/tree/master/BotBoarduino/3%20DoF%20Ready/BotBoarduino_CH3R_PS2

We (mgdg) have ported the code from BoardBotDuino to Arduino Mega 2560.

While the code is basically/essentially/substantially based on the above repo, we have taken the code into our own  
repo. 

This (core) code permits the following features:

- Basic Robot leg control, Walking, Standing Sitting, Turning, etc. All 18 servos connected to SSC-32 controller card which arduino communicates via Tx/Rx.
- Commanding and Control inputs from a Playstation PS-2 controller communicating remotely over 2.4 GHz link.
- Buzzer so the Phoenix can squawk, beep, and make noise.
- Voltage Sensing on Main Battery.


Aditionally, We (mgdg) have integrated a bunch of extra features into this codebase, these are"

- Pan and Tilt servo system for a FPV 720p camera and 5.8 GHz transmitter, using small servo control card and software library (pololu maestro).
- 4 Channel Untrasonic sensors for proximity and distance monitoring.
- Bluetooth serial monitor for commanding and monitoring.
- Headlights!


Software Structure (files):

hex_cfg.h   - configuration options for Phoenix, arduino pin and serial port assignments, leg coordinates default values and offsets, angles, trig tables

hex_globals.h - extern global variables and functions

inputcontroller.h - a class 'InputController' which represents the PS-2 controller. Also implements the global "State of System" data structure called 'ControlState'.

servodriver.h - a class that represents the SSC-32 controller interface

ps2-controller.cpp - this is the PS-2 Controller library, which (as part of Inputcontroller::ControlInput() listens to user input on the PS-2 Handheld Station, handles button clicks, and joystick movements. Transers information into the global "ControlState" object which is processed by the main control program.

phoenix_driver_ssc32.cpp - this is ssc32 driver library, it is implemented as methods of the ServoDriver class.

sounds.cpp - tone buzzer sound methods, pulled out and made into a separate file

ultrasonic.cpp - library written to handle distance and proximity sensing from the 4 ultrasonic sensors

voltagesensor.cpp - library written to handle reading voltage on main battery.

terminalmonitor.cpp - this is the bluetooth communication module. very little is done to interface to bluetooth module, just send and receive from a serial port. However this code provides a number of commands the user can send from a bluetooth device (e.g phone, tablet, etc.), and a number of monitoring options.

Phoenix.cpp - this is the main arduino control program. It has the setup method and the loop method. 

- In 'setup', all of the subsystems are initialized, pin assignments made, initial leg positions assigned. 

- In 'loop', the ControlState structure is read, then examined and various functions are actuated. Essentially it is a bit of a state machine that needs to handle all input and make all output in a constrained time frame. If the time frame is exceeded, then walking control and and 'gait' quality is affected adversely.

We're learning git a little, check this out http://rogerdudler.github.io/git-guide/
