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
  int timefactor = time - lasttime;
  
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
  
  string newtitle = camAt.str() + "  " + cameye.str() ;
  glutSetWindowTitle(newtitle.c_str());
  
  scene.update(timefactor);

  lasttime=time;
  glutPostRedisplay();
}
extern "C" void special(int key, int x, int y){
  switch(key) {
  // case GLUT_KEY_UP:    scene.camera.turnup(camrotationamount); break;
  // case GLUT_KEY_DOWN:  scene.camera.turndown(camrotationamount);    break;
  // case GLUT_KEY_LEFT:  scene.camera.turnleft(camrotationamount); break;
  // case GLUT_KEY_RIGHT:  scene.camera.turnright(camrotationamount); break;
  case GLUT_KEY_UP:    scene.pieces[0]->Translate(0,1,0);   break;  
  case GLUT_KEY_DOWN:  scene.pieces[0]->Translate(0,-1,0);   break;   
  case GLUT_KEY_LEFT:  scene.pieces[0]->Translate(-1,0,0);   break;   
  case GLUT_KEY_RIGHT: scene.pieces[0]->Translate(1,0,0);   break;   

  }
}
extern "C" void keyboard(unsigned char key, int x, int y){
  switch(key) {
  //033 escape key
  case 033: case 'q': case 'Q': exit(EXIT_SUCCESS);break;


  case 'u':scene.play();


  // I believe i can fly 
  case 'Y': scene.camera.moveup(stepsize);   break;
  case 'y': scene.camera.movedown(stepsize); break;
  //

  case 'b': scene.pieces[0]->Rotate(10,0,0); break;
  case 'B': scene.pieces[0]->Rotate(-10,0,0); break;
  case 'N': scene.pieces[0]->Rotate(0,-10,0); break;
  case 'n': scene.pieces[0]->Rotate(0,10,0); break;
  case 'M': scene.pieces[0]->Rotate(0,0,-10); break;
  case 'm': scene.pieces[0]->Rotate(0,0,10); break;

  // standard walking movement
  case 'w': scene.camera.moveforward(stepsize); break;
  case 's': scene.camera.moveback(stepsize);    break;
  case 'a': scene.camera.moveright(stepsize); break;
  case 'd': scene.camera.moveleft(stepsize);  break;

  case 't':scene.pieces[0]->Tests();

  case 'o': scene.pieces[0]->slowDown(10); break;
  case 'O': scene.pieces[0]->speedUp(10); break;

  case ' ':  // reset values to their defaults

  break;
  
  }

  glutPostRedisplay();
}
extern "C" void reshape(int width, int height){
  glViewport(0, 0, width, height);

  scene.aspect = GLfloat(width)/height;
}
extern "C" void display(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  scene.draw();

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
