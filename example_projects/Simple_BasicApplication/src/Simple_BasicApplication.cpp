#include "Cing.h"
CREATE_APPLICATION( "Cing Demo" );

/*
 * This example shows the basic about a Cing application
 * It draws a line from the center of the screen to the mouse.
 * Press the mouse to clear the background.
 */

void setup()
{
	// Set window size and smooth drawing
	size(800, 800);
	smooth();
}

void draw()
{
	// Associate the stroke grayscale value to the vertical position of the mouse
	float value = map(mouseY, 0, height, 0, 255);
	stroke(mouseY);

	// Draw a line from the center of the window to the mouse
	line(width/2, height/2, mouseX, mouseY);
}

void end()
{
}

void mousePressed()
{
	// Clear the background when the mouse is pressed
	background(192, 64, 0);
}

void mouseMoved()
{
}

void mouseReleased()
{
}

void keyPressed()
{
}