
# include <iostream>
# include "app_window.h"


//==========================================================================
// Main routine
//==========================================================================
int main ( int argc, char** argv )
 {
   // Init freeglut library:
   glutInit ( &argc,argv );
   glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );

   // Now create the window of your application:
   AppWindow* w = new AppWindow ( "Pong!!!!", 300, 300, 640, 480 );

   // Finally start the main loop:
   w->run ();
}
