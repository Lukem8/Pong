#ifndef RECTS_H
#define RECTS_H
#include <iostream>
#include <vector>
#include "app_window.h"
using namespace std;
//Class for the paddles and the ball which will be drawn on screen
class Rectangle {
  // (x,y) is top left coordinate
  // (x+w,y) is top right coordinate
  float x,y,w,h,speed, yspeed, fakeSpeed;
  int score;
public:
  ///constructors and destructor
  Rectangle(){
      x = y = w = h = speed = yspeed = fakeSpeed = 0;
      score = 0;
      cout << "default constructor is called" << endl;
  }
  Rectangle(float x, float y, float w, float h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    speed = yspeed = fakeSpeed = 0;
    score = 0;
  }
  ~Rectangle(){
    delete this;
  }

  //getters and setters
  float getHeight(){
      return h;
  }
  float getWidth(){
      return w;
  }
  float getX(){
    return x;
  }
  float getY(){
      return y;
  }
  float getSpeed(){
    return speed;
  }
  int getScore(){
    return score;
  }
  float getYSpeed(){
    return yspeed;
  }
  float getFakeSpeed(){
    return fakeSpeed;
  }
  void setHeight(float h){
    this->h = h;
  }
  void setWidth(float w){
    this->w = w;
  }
  void setX(float x){
    this->x = x;
  }
  void setY(float y){
    this->y = y;
  }
  void setSpeed(float s){
    speed = s;
  }
  void addScore(int s){
    score += s;
  }
  void setYSpeed(float s){
    yspeed = s;
  }
  void setFakeSpeed(float s){
    fakeSpeed = s;
  }
  //Functions to draw objects to screen
  virtual void draw(){
    // Set drawing color to white
    glColor3d ( 1.0, 1.0, 1.0 );
    //cout << "x is" << x << "y is " << y << endl;
    glBegin( GL_POLYGON ); // you may use GL_POLYGON for generic *convex* polygons
    glVertex2d (x+speed,y+yspeed);
    glVertex2d (x+w+speed,y+yspeed);
    glVertex2d (x+w+speed,y+h+yspeed);
    glVertex2d (x+speed,y+h+yspeed);
    glEnd();
    //update the new x position
    x = x+speed;
    y += yspeed;



  }
};




#endif
