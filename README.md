CPSC 3710 Assignment 2
==============================================

Dependencies
---------------------------------------------
OpenGL library. 
G++ Compiler

Instructions for installation can be found at:
http://www.sumantaguha.com/downloads

Install using:
sudo apt-get install g++ freeglut3 freeglut3-dev libglew-dev libglew1.10 binutils-gold

Available Platforms
---------------------------------------------
Currently compiles on linux using the make function. Probably feasible
to make a working version on other platforms

Description
---------------------------------------------
Simple little 'flight simulator' (For lack of a better term) that utilizes OpenGL's library
to create multiple rotating three dimensional Pentadras. The user uses keys to 'move' around
within the world. The keys are listed below

Controls
------------------------------------------------
Simple controls are as follows

- r -- toggles rotation. If it's already rotating, stop rotation, etc.
- x -- Makes object rotate about the x axis
- y -- Makes object rotate about the y axis
- z -- Makes object rotate about the z axis
- n -- Rolls the screen / camera left
- m -- Rolls the screen / camera right
- space -- Moves the user forward in the world
- b -- Moves the user backwards in the world
- CursorUp -- Moves the camera's pitch upwards
- CursorDown -- Moves the camera's pitch downwards
- CursorLeft -- Moves the camera's yaw to the left
-- CursorRight -- Moves the camera's yaw to the right
- ESC -- Closes program

Execute
-----------------------------------------------------
To execute this, just unpack the tar.gz and type make. The executable
will be located in the bin folder

Notes
-----------------------------------------------------------
This was built using Trusty Tar (AKA Ubuntu 14.04) so compilation may
vary for different flavours of linux. Ultimately, though, it is a working
version of the required assignment. All changes have been documented by
git. Note that the overly convoluted setup with an src, bin, and obj
folder is just a template I use for all my programming to ensure that
organization is maintained.
