
// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include "glut_window.h"
#include "Rectangle.h"
// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
 { private :
    enum MenuEv { evOption0, evOption1 };
    float _markx, _marky;
    int _w, _h;
    bool activeGame;
    //Dynamically create the two paddles
    Rectangle* paddle1 = new Rectangle(-0.9,0.3,0.1,-0.6);
    Rectangle* paddle2 = new Rectangle(0.8,0.3,0.1,-0.6);
    //create the ball (actually a square)
    Rectangle* ball = new Rectangle(-0.025,0.025,0.05,-0.05);
   public :
    AppWindow ( const char* label, int x, int y, int w, int h );
    void windowToScene ( float& x, float &y );

   private : // functions derived from the base class
    virtual void handle ( const Event& e );
    virtual void draw ();
    virtual void resize ( int w, int h );
 };

#endif // APP_WINDOW_H
