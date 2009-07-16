/*
  This source file is part of the Cing project
  For the latest info, see http://www.cing.cc

  Copyright (c) 2006-2009 Julio Obelleiro and Jorge Cano

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software Foundation,
  Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _UserAppFunctionDeclaration_H_
#define _UserAppFunctionDeclaration_H_

/// MAIN FUNCTIONS

/// Starts the application. Called at the start of the application (To initialize data, configure screen...etc)
void setup   ();

/// Called when the application ends (Here you can save screenshots.. etc)
void end     ();

/// Draws the application. Called every frame
void draw    ();

/// Input events
void mousePressed();
void mouseMoved();
void mouseReleased();
void keyPressed();

#endif // _UserAppFunctionDeclaration_H_
