#include "Vision.h"

CREATE_APPLICATION( "Vision Demo" );

MediaPlayerVLC mediaPlayer, mediaPlayer2;

void setup()
{
  // Local file
  mediaPlayer.load( "test.avi" );
  //mediaPlayer.load( "Video_Bucarest_Urban_Art_DEF_ROMANIA_Sorensen03.flv" );
  println( "Video Res: %d, %d", mediaPlayer.getWidth(), mediaPlayer.getHeight() );
  mediaPlayer.play();

  // Streamed file (just load it for now)
  //mediaPlayer2.load( "http://www.playthemagic.com/videos/buildingmusic/Video_Bucarest_Urban_Art_DEF_ROMANIA_Sorensen03.flv" );
} 

void draw()
{
  // Draw video 1 (local)
  mediaPlayer.update( );
  mediaPlayer.getImage().draw2d( 0, 0 );

  // When video 1 finishes -> start video 2 (online)
  //if ( mediaPlayer.isPlaying() == false )
  //  mediaPlayer2.loop();

  // Draw video 2 (online)
  //mediaPlayer2.update();
  //mediaPlayer2.getImage().draw2d( 0,  mediaPlayer2.getHeight() );
}

void end()
{

}

void mousePressed()
{
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