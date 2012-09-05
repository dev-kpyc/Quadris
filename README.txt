
---------------------------------------------------------------------------------------
                                888         d8b         
                                888         Y8P         
                                888                     
 .d88888 888  888  8888b.   .d88888 888d888 888 .d8888b 
d88  888 888  888     88b  d88  888 888P    888 88K     
888  888 888  888 .d888888 888  888 888     888  Y8888b.
Y88b 888 Y88b 888 888  888 Y88b 888 888     888      X88
  Y88888   Y88888  Y888888   Y88888 888     888  88888P'
     888                                                
     888                                                
     888   
     
By Kevin Pyc & Henry Shi

---------------------------------------------------------------------------------------

Troubleshooting
General: Game does not Work

To begin make sure you are on a Linux platform. This game was created
tested, and designed for Linux. I highly doubt it will work on another OS.

First, install the X11 graphics library. You can do this by typing
sudo apt-get install libx11-dev
in the terminal

Secondly, you may need to recompile the game.
Ideally this would be done by the Eclipse cdt.
Alternatively, I made a quick script to do this. (Use at your own risk, as always)
Type ./recompile from the command line in the quadris folder
(You may need to give permission for this script to run first. Type chmod u+x recompile)
Basically all this does is move all the source folders and headers to the same folder,
then runs the makefile in the main folder. So you could do this yourself if you so desire.

---------------------------------------------------------------------------------------

Commands don't work, Cannot find file sequence.txt ... error messages

Check to see if the sequence.txt and commands.txt are in the same folder as your
executable. These are required by the game to run.

---------------------------------------------------------------------------------------

  Quadris - Stop speed tetris game
    Copyright (C) 2012  Kevin Pyc, Henry Shi

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
