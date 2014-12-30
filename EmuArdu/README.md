EmuArdu
=======

 This project consists in a "hardware" directory that can be copied or linked into
Arduino IDE project directory to declare a new set of platforms which are similar
to arduino ones, but emulated on your computer.

Current state / TODO
====================

Implemented :
-----------
 * Serial output
 * output pins (digitalWrite and analogWrite)
 * time function (delay, delayMicro, millis, micros)

TODO :
----
 * Serial input
 * digital/analog input pins
 * better pin display (at least arrows to show in/out state)
 * other platforms

Help wanted :
-----------
 * Windows & Mac integration (how to use GL, glut ...)
 * why Micro picture is not displayed ? (I'm a total beginner in GL)

What I (certainly) will NOT implement :
-----------------------------------
 * Registers
 * assembly code
 * Interruptions, low level timers ...
 * shiftIn/Out
 * SPI, I2C ...


Installation/Requirements
=========================

You need :
 * GL, GLU, glut and png, jpeg, gd libraries
   Under Linux Fedora for example, you just need to launch
   yum install mesa-libGL mesa-libGLU freeglut gd libpng libjpeg-turbo
 * Arduino IDE in 1.5.* version (not 1.0.*)
 * GCC C++ compiler (not the avr one included in Arduino IDE, but the "standard" one,
   for your computer)

In Arduino IDE, the menu File, Preferences, Sketchbook location references a directory
where your sketch are by default.
Into this directory, create a subdirectory "hardware" and copy or symbolic link into it the
directory EmuArdu/hardware/piif

Then :
 * launch IDE.
 * In menu Tools, Board a section "piif" with a list of "Arduino ... Emulation" appeared.
   Choose "Arduino Uno Emulation" (the only implemented one for the moment)
 * In Tools, Programmer, choose "EmuArdu Launcher"

Now, you can load your sketches and compile them from the IDE.

The platform.txt file contains everything needed to compile your .ino files, core libraries and
link them into a executable program that shows a photo of the target platform, with colored
squares on each pin.

The Eclipse way
===============

 You can use the Eclipse CDT plugin to compile this project from Eclipse.
 The project contains several configuration, one per arduino platform (for
the moment only Uno and Micro).
 Each configuration will generate a libEmuArdu.so file, into a directory named as the
configuration. 
