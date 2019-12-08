#include "scene.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
using std::string;
using std::stringstream;
using std::setprecision;

Scene scene;
float stepsize = 0.1; 
float camrotationamount = 0.01;
float glutaspectratio = 0;
// usedd for mouse look around
int oldx,oldy,deltax,deltay;
float lookaroundsensetivity=0.0008;



extern "C" void display();
extern "C" void idleanimation();
extern "C" void special(int key, int x, int y);
extern "C" void keyboard(unsigned char key, int x, int y);
extern "C" void reshape(int width, int height);
extern "C" void lookaround(int x, int y);
extern "C" void updatemousexy(int x,int y);
// Simple animation
GLint lasttime=0;
extern "C" void idleanimation(){
  int time = glutGet(GLUT_ELAPSED_TIME);
  
  //////Debug cam angels ////////////////////////
    // cameras angle about the y axis how you would normally rotate a camera left and right
    stringstream cameraangleiny;
    cameraangleiny  << "CAY: " << setprecision(2) << scene.camera.get_cameraYangel();
    // camera angle about the x axis rotating the camera up and down
    stringstream cameraangleinx;
    cameraangleinx << "CAX: " <<  setprecision(2)  <<  scene.camera.get_cameraXangel();
  ///////////////////////////////////////////////
  
  //////Eye At debug/////////////////////////////
    vec4 at= scene.camera.get_at();
    vec4 eye = scene.camera.get_eye();
    stringstream camAt,cameye;
    camAt << "At=" <<  setprecision(2) << "x:" << at.x << "y:" << at.y << "z:" << at.z ;
    cameye << "eye=" <<  setprecision(2) <<"x:" << eye.x << "y:" << eye.y << "z:" << eye.z ;
  ///////////////////////////////////////////////
  
  ///// Peice locations /////////////////////////
    vec4 loc = scene.pieces[0]->get_position();
    stringstream peiceloc;
    peiceloc << "x:" << loc.x << "   y:" << loc.y << "   z:" << loc.z ;
  ///////////////////////////////////////////////


  string newtitle = camAt.str() + cameye.str() ;
  glutSetWindowTitle(newtitle.c_str());
  
  scene.update(time);


  glutPostRedisplay();
}
extern "C" void special(int key, int x, int y){
  switch(key) { 
  case GLUT_KEY_LEFT: scene.translatepiecetopreviouslegalpostion(); break;
  case GLUT_KEY_RIGHT: scene.translatepiecetonextlegalpostition(); break;
  } 
}
extern "C" void keyboard(unsigned char key, int x, int y){
  switch(key) {
  //033 escape key
  case 033: exit(EXIT_SUCCESS);break;
  
  // standard walking movement
  case 'w': scene.camera.moveforward(stepsize); break;
  case 's': scene.camera.moveback(stepsize);    break;
  case 'a': scene.camera.moveright(stepsize); break;
  case 'd': scene.camera.moveleft(stepsize);  break;

  case 'B':scene.display_status(true); break;

  case ' ':  scene.make_move();  break;
  }

  glutPostRedisplay();
}
extern "C" void reshape(int width, int height){
  glViewport(0, 0, width, height);

  scene.setAspect(GLfloat(width)/height);
}
extern "C" void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  scene.display_status(false);

  glutSwapBuffers();
}
extern "C" void lookaround(int x, int y){
  deltax = oldx-x;
  deltay = oldy-y;
  
  if(deltax <= 0){
    scene.camera.turnleft(deltax*lookaroundsensetivity);
  }else{
    scene.camera.turnright(-deltax*lookaroundsensetivity);
  }
  // Uncomment if you believe you can fly.
  if(deltay <= 0){
    scene.camera.turnup(deltay*lookaroundsensetivity);
  }else{
    scene.camera.turndown(-deltay*lookaroundsensetivity);
  }

  oldx = x;
  oldy = y;
}
extern "C" void updatemousexy(int x,int y){
  oldx = x;
  oldy = y;
}


int main(int argc, char **argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(512, 512);
  glutCreateWindow("");

  glewInit();

  scene.init();
  
  glutDisplayFunc(display);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutIdleFunc(idleanimation);
  glutReshapeFunc(reshape);
  glutMotionFunc(lookaround);
  glutPassiveMotionFunc(updatemousexy);

  glutMainLoop();
  return(EXIT_SUCCESS);
}
