#include "scene.h"
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
using std::string;
using std::stringstream;
using std::setprecision;


Scene scene;
float camrotationamount = 0.01;
float glutaspectratio = 0;
// usedd for mouse look around
int oldx,oldy,deltax,deltay;
float lookaroundsensetivity=0.0008;

// In world movement of objects
  float ligthmovemntamnt = 1;
  float currentpiecemovemntamnt = 1;
  float stepsize = 0.1; 

  enum {Light, CurrentPiece, camera};
  int WASDmoving = camera;
// Controlling parameters in scene with + and - keys
  enum{SpecularLight, DiffuseLight, PieceTranslationSpeed, PieceRotationSpeed};
  int plusminuscontrols = DiffuseLight;
//



extern "C" void display();
extern "C" void idleanimation();
extern "C" void special(int key, int x, int y);
extern "C" void keyboard(unsigned char key, int x, int y);
extern "C" void reshape(int width, int height);
extern "C" void lookaround(int x, int y);
extern "C" void updatemousexy(int x,int y);

void menu(int num){
  switch (num){
    case(0): exit(0); break;
    case(1): scene.restart(); break;
    case(2): scene.display_status(true); break;
  }
}
void objectcontrol(int num){
  switch (num) {
    case (1): WASDmoving = Light;        break;
    case (2): WASDmoving = CurrentPiece; break;
    case (3): WASDmoving = camera;       break;
    case (4): plusminuscontrols = PieceTranslationSpeed; break;
    case (5): plusminuscontrols = PieceRotationSpeed; break;
  }
  glutPostRedisplay();
} 
void lightcontrol(int num){
  switch (num) {
    case (1): scene.changelightcolor(color4(1,1,1,1)); break;
    case (2): scene.changelightcolor(color4(1,0,0,1)); break;
    case (3): scene.changelightcolor(color4(0,1,0,1)); break;
    case (4): scene.changelightcolor(color4(0,0,1,1)); break;
    case (5): scene.changelightcolor(color4(0,1,1,1)); break;
    case (6): scene.changelightcolor(color4(1,1,0,1)); break;
    case (7): scene.changelightcolor(color4(250/255.0,220/255.0,0,1)); break;
    case (100) : plusminuscontrols = SpecularLight; break;
    case (101) : plusminuscontrols = DiffuseLight;  break;
  }

  glutPostRedisplay();
} 
void createMenu(void){  
  int objectcontrolsubmenuid = glutCreateMenu(objectcontrol);
    glutAddMenuEntry("Light", 1);
    glutAddMenuEntry("Current Piece",2);
    glutAddMenuEntry("Camera",3);
    glutAddMenuEntry("+- control piece translation speed",4);
    glutAddMenuEntry("+- control piece rotation speed", 5);
  
  int lightcontolsubmenuid = glutCreateMenu(lightcontrol);
    glutAddMenuEntry("White",1);
    glutAddMenuEntry("Red",2);
    glutAddMenuEntry("Green",3);
    glutAddMenuEntry("Blue",4);
    glutAddMenuEntry("Cyan",5);
    glutAddMenuEntry("Yellow",6);
    glutAddMenuEntry("MellowYellow",7);
    glutAddMenuEntry("+- controls Specular Intensity",100);
    glutAddMenuEntry("+- controls Diffuse Intensity",101);
    //add light speed
  int gameoptions = glutCreateMenu(menu);
    glutAddMenuEntry("Restart Game",1);
    glutAddMenuEntry("Display terminal Board",2);
    
    glutCreateMenu(menu);
    glutAddSubMenu("Object to control", objectcontrolsubmenuid);
    glutAddSubMenu("Light Control",lightcontolsubmenuid);
    glutAddSubMenu("Game options", gameoptions);
    glutAddMenuEntry("Quit", 0);     
  
  glutAttachMenu(GLUT_RIGHT_BUTTON);
} 

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
    string camanglesdebug = cameraangleinx.str() + cameraangleiny.str();
  ///////////////////////////////////////////////
  
  //////Eye At debug/////////////////////////////
    vec4 at= scene.camera.get_at();
    vec4 eye = scene.camera.get_eye();
    stringstream camAt,cameye;
    camAt << "At=" <<  setprecision(2) << "x:" << at.x << "y:" << at.y << "z:" << at.z ;
    cameye << "eye=" <<  setprecision(2) <<"x:" << eye.x << "y:" << eye.y << "z:" << eye.z ;
    string eyeatdebug= camAt.str() + cameye.str();
  ///////////////////////////////////////////////
  
  ///// Peice locations /////////////////////////
    vec4 loc = scene.pieces[0]->get_position();
    stringstream peiceloc;
    peiceloc << "x:" << loc.x << "   y:" << loc.y << "   z:" << loc.z ;
    string piece0locdebug = peiceloc.str();
  ///////////////////////////////////////////////

  ///// Light location //////////////////////////
    stringstream lightloc;
    lightloc << scene.light->get_position() << std::endl;
  ///////////////////////////////////////////////

  // scene.display_message(cameye.str() + lightloc.str());
  // scene.display_message(eyeatdebug);
  // scene.display_message(camanglesdebug);
  // scene.display_message(piece0locdebug);
  
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
  switch (WASDmoving){
    case(camera): switch(key){
      case 'w': scene.camera.moveforward(stepsize); break;
      case 's': scene.camera.moveback(stepsize);    break;
      case 'a': scene.camera.moveright(stepsize); break;
      case 'd': scene.camera.moveleft(stepsize);  break;
      case 'y': scene.camera.movedown(stepsize); break;
      case 'Y': scene.camera.moveup(stepsize); break;
    }break;
    case(Light): switch(key){
      case 'w': scene.light->Translate(0,0,-ligthmovemntamnt); break;
      case 's': scene.light->Translate(0,0,ligthmovemntamnt); break;
      case 'a': scene.light->Translate(ligthmovemntamnt,0,0); break;
      case 'd': scene.light->Translate(-ligthmovemntamnt,0,0); break;
      case 'y': scene.light->Translate(0,-ligthmovemntamnt,0); break;
      case 'Y': scene.light->Translate(0,ligthmovemntamnt,0); break; 
    }break;
    case(CurrentPiece): switch(key){
      case 'w': scene.currentpiece()->Translate(0,0,-currentpiecemovemntamnt); break;
      case 's': scene.currentpiece()->Translate(0,0,currentpiecemovemntamnt); break;
      case 'a': scene.currentpiece()->Translate(currentpiecemovemntamnt,0,0); break;
      case 'd': scene.currentpiece()->Translate(-currentpiecemovemntamnt,0,0); break;
      case 'y': scene.currentpiece()->Translate(0,-currentpiecemovemntamnt,0); break;
      case 'Y': scene.currentpiece()->Translate(0,currentpiecemovemntamnt,0); break;
    }break;
  }
  switch (plusminuscontrols){
    case(DiffuseLight) :switch(key){
      case('+'): scene.changeambiantintensity(0.05);  break;
      case('-'): scene.changeambiantintensity(-0.05); break;
    }break;
    case(SpecularLight):switch(key){
      case('+'): scene.changespecularintenstiy(0.05);  break;
      case('-'): scene.changespecularintenstiy(-0.05); break;
    }break;
    case(PieceTranslationSpeed):switch(key){
      case('+'): scene.changepeicestranslationspeed(10);  break;
      case('-'): scene.changepeicestranslationspeed(-10); break;
    }break;
    case(PieceRotationSpeed):switch(key){
      case('+'): scene.changpiecesrotationspeed(10);  break;
      case('-'): scene.changpiecesrotationspeed(-10); break;
    }break;
  }

  switch(key) {
  //033 escape key
  case 033: exit(EXIT_SUCCESS);break;
  
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
  createMenu();

  glutMainLoop();
  return(EXIT_SUCCESS);
}
