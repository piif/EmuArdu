 This repository contains 2 directories which are eclipse projects :

* EmuArdu : a C++ project that contains an Arduino Emulator
* EmuArduExample : a C++ project which contains a single example file
  that compiles from eclipse, but also from Arduino IDE

EmuArdu
=======

 This project consists in a "hardware" directory that can be copied or linked into
Arduino IDE project directory to declare a new set of platforms which are similar
to Arduino ones, but emulated on your computer.

<img src="https://github.com/piif/EmuArdu/blob/master/snapshots/IDE_and_Emulator.png"/>

 See readme inside EmuArdu directory for more informations

EmuArduExample
==============

 This directory contains a single file EmuArduExample.ino (the classical blink program)
that can be loaded in Arduino IDE and compiled for real arduino but also for
"Arduino Uno Emulation" platform, and launched via "EmuArdu Launcher" programmer.

 In this later case, the program will launch on your computer

 See readme inside EmuArduExample directory for more informations

Installation/Requirements
=========================

 See readme inside EmuArdu for detail.
 You will need at least
  * GCC C++ compiler
  * GL, GLU, glut and jpeg, png, gd libraries
  * Arduino 1.5.* version


