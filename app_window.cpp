#include <iostream>
#include "app_window.h"
#include <vector>
#include <string>
#include <sstream>
AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   _markx = 0;
   _marky = 0;
   //addMenuEntry ( "Option 0", evOption0 );
   //addMenuEntry ( "Option 1", evOption1 );
   activeGame = false;
 }

// mouse events are in window coordinates, but your scene is in [0,1]x[0,1],
// so make here the conversion when needed
void AppWindow::windowToScene ( float& x, float &y )
 {
   x = (2.0f*(x/float(_w))) - 1.0f;
   y = 1.0f - (2.0f*(y/float(_h)));
 }

// Called every time there is a window event
void AppWindow::handle ( const Event& e )
 {
   bool rd=true;
//////////////////////////////////////////////////////////////////////////////
  //Here is where we will handle keyboard events.............................
   if ( e.type==Keyboard )
    /////////////////switch for the different keys///////////////////////////
    switch ( e.key )
    { case ' ': // space bar
        if(!activeGame){
	       std::cout << "Space pressed. THE game has STARTED!\n";
         //move the ball left
         ball->setSpeed(-0.025);
         activeGame = true;
         //CALL REDRAW AFTER EVENT TAKES PLACE
         redraw();
         break;
       }

     /////MOVING the PADDLES/////////////////
     case 'w':
      cout << "pressing w" << endl;
      paddle1->setY(paddle1->getY()+0.1);
      paddle1->setFakeSpeed(0.1);
      redraw();
      break;
     case 's':
      cout << "pressing s" << endl;
      paddle1->setY(paddle1->getY()-0.1);
      paddle1->setFakeSpeed(-0.1);
      redraw();
      break;

	  case 27: // Esc was pressed
	   exit(1);
	}

   /////MOVING PADDLES ////////
   if ( e.type==SpecialKey )
    switch ( e.key )
    {
      case GLUT_KEY_UP:
        cout << "pressing up" << endl;
        paddle2->setY(paddle2->getY()+0.1);
        paddle2->setFakeSpeed(0.1);
        redraw();
        break;
      case GLUT_KEY_DOWN:
        paddle2->setY(paddle2->getY()-0.1);
        paddle2->setFakeSpeed(-0.1);
        redraw();
        break;
      default: rd=false; // no redraw
	}

   if (rd) redraw(); // ask the window to be rendered when possible
}

void AppWindow::resize ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }

// here we will redraw the scene according to the current state of the application.
void AppWindow::draw ()
 {
   // Clear the rendering window
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // Clear the trasnformation stack
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   //draw out the start game words on screen
   if (!activeGame){
     glRasterPos2f(-0.10, -0.3);
     string pressSpace = "Press space";
     glutBitmapString(GLUT_BITMAP_HELVETICA_12,
                             (const unsigned char*)pressSpace.c_str());
  }
  //Draw the scores to the screen
  stringstream s;
  s << paddle1->getScore();
  string ss = s.str();
  glRasterPos2f(-0.5, 0.85);
  string output = "Player 1 Score: " + ss;

  glutBitmapString(GLUT_BITMAP_HELVETICA_12,
                       (const unsigned char*)output.c_str());
  stringstream s2;
  s2 << paddle2->getScore();
  string sss = s2.str();
  glRasterPos2f(0.5, 0.85);
  string output2 = "Player 2 Score: " + sss;
  glutBitmapString(GLUT_BITMAP_HELVETICA_12,
                                            (const unsigned char*)output2.c_str());
   // Set drawing color to white
   glColor3d ( 1.0, 1.0, 1.0 );
   //////////////////TODO//////////////////////
   //do a check if the paddle is in motion, then we consider a change in y values, otherwise, shouldnt be affected
   ////////////////////////////////////////////
   //check if there is a collision with the ball and the left paddle
   //collision occuring with ball and paddle1
   if (ball->getX() >= paddle1->getX() && ball->getX() <= paddle1->getX()+paddle1->getWidth()
                                                    && ball->getY() <= paddle1->getY() && ball->getY() >= paddle1->getY()+paddle1->getHeight()){
     cout << "we have a collision" << endl;
     //turn the ball around
     ball->setSpeed(0.025);
     ball->setYSpeed(paddle1->getFakeSpeed()/2);
     //STILL NEED TO IMPLEMENT THE Y VALUES , MAYBE A Y SPEED FOR BALL

   }
   //collision between ball and paddle2
   if (ball->getX() >= paddle2->getX() && ball->getX() <= paddle2->getX()+paddle2->getWidth()
                                                  && ball->getY() <= paddle2->getY() && ball->getY() >= paddle2->getY()+paddle2->getHeight()){
     cout << "we have a collision" << endl;
     //turn the ball around
     ball->setSpeed(-0.025);
     ball->setYSpeed(paddle2->getFakeSpeed()/2);
     //STILL NEED TO IMPLEMENT THE Y VALUES , MAYBE A Y SPEED FOR BALL

   }
   //check if ball hits top or bottom of the window
   if (ball->getY() >= 1.0){
     ball->setYSpeed(ball->getYSpeed()*(-1)); //reverse the y direction
   }
   if (ball->getY() <= -1.0){
     ball->setYSpeed(ball->getYSpeed()*(-1)); //reverse the y direction
   }

   //Updating the balls position on the screen
   if (ball->getX() <= -1.0){
     cout << ball->getX() << endl;
     paddle2->addScore(1);
     ball->setSpeed(0);
     ball->setX(-0.025);
     ball->setY(0.025);
     ball->setWidth(0.05);
     ball->setHeight(-0.05);
     ball->setYSpeed(0);
     paddle1->setFakeSpeed(0);
     paddle2->setFakeSpeed(0);
     activeGame = false;
     redraw();
   }
   if (ball->getX() >= 1.0){
     paddle1->addScore(1);
     ball->setSpeed(0);
     ball->setX(-0.025);
     ball->setY(0.025);
     ball->setWidth(0.05);
     ball->setHeight(-0.05);
     ball->setYSpeed(0);
     paddle1->setFakeSpeed(0);
     paddle2->setFakeSpeed(0);
     activeGame = false;
     redraw();
   }
   //Call the draw function inside the Rectangle class
   paddle1->draw();
   paddle2->draw();
   ball->draw();

   redraw();
   // Swap buffers
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}
