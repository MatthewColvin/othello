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

bool isUnitQuaterian(vec4 q){
  if ((q.x*q.x+q.y*q.y+q.z*q.z+q.w*q.w) != 1){
   std::cerr << "watchout quaternians should sum to 1" << std::endl;
   return false;
  }
  return true;
}
mat4 toMatrix(vec4 Quaternian){
  if(!isUnitQuaterian(Quaternian)){
    std::cerr<< "could not convert to rotation matrix because not unit quaterian" << std::endl;
    return(mat4());
  }else{
    float x = Quaternian.x; 
    float y = Quaternian.y;
    float z = Quaternian.z;
    float w = Quaternian.w;
    // q0 = w // q1 = z // q2 = y // q3 = x
    mat4 r;
    r[0][0]= w+z-x-y    ;r[0][1]= 2*(z*y-w*y);r[0][2]=2*(w*y+z*x) ;r[0][3]=0;
    r[1][0]= 2*(z*y+w*x);r[1][1]= w-z+y-x    ;r[1][2]=2*(y*x-w*z) ;r[1][3]=0;
    r[2][0]= 2*(z*x-w*y);r[2][1]= 2*(w*z+y*x);r[2][2]=w-z-y+x     ;r[2][3]=0;
    
    r[3][0]= 0 ;r[3][1]= 0 ;r[3][2]= 0 ;       r[3][3]= 1;

    return r;
  }
}
vec4 slerp(vec4 const &q0, vec4 const &q1, double t) {
      // v0 and v1 should be unit length or else
      // something broken will happen.
      normalize(q0);
      normalize(q1);
      // Compute the cosine of the angle between the two vectors.
      double dot = Angel::dot(q0,q1); 

      const double DOT_THRESHOLD = 0.9995;
      if (dot > DOT_THRESHOLD) {
          // If the inputs are too close for comfort, linearly interpolate
          // and normalize the result.

          vec4 result = q0 + t*(q1 - q0);
          result = normalize(result);
          return result;
      }
      
      //std::clamp(dot, -1.0, 1.0);           // Robustness: Stay within domain of acos()
      double theta_0 = acos(dot);  // theta_0 = angle between input vectors
      double theta = theta_0*t;    // theta = angle between v0 and result 

      vec4 v2 = q1 - q0 * dot;
      v2 = normalize(v2);             // { v0, v2 } is now an orthonormal basis

      return q0*cos(theta) + v2*sin(theta);
}

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
  
  // cameras angle about the y axis how you would normally rotate a camera left and right
  stringstream cameraangleiny;
  cameraangleiny  << "CAY: " << setprecision(2) << scene.camera.get_cameraYangel();
  // camera angle about the x axis rotating the camera up and down
  stringstream cameraangleinx;
  cameraangleinx << "CAX: " <<  setprecision(2)  <<  scene.camera.get_cameraXangel();

  string newtitle = cameraangleiny.str() + "  " + cameraangleinx.str() ;
  glutSetWindowTitle(newtitle.c_str());
  
  
  for (auto p : scene.pieces){
    p->update(1,1);
  }

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
  case 033: // Escape Key
  case 'q': case 'Q':
    exit(EXIT_SUCCESS);
    break;

    // Speed up/slow down movements
  
  case '+': scene.incr*=2.0; break;
  case '-': scene.incr/=2.0; break;

  case 'z': scene.zNear  *= 1.1; scene.zFar /= 1.1; break;
  case 'Z': scene.zNear /= 1.1; scene.zFar *= 1.1;  break;
  
  // I believe i can fly 
  case 'Y': scene.camera.moveup(stepsize);   break;
  case 'y': scene.camera.movedown(stepsize); break;
  //

  case 'b': scene.pieces[0]->Rotate(-10,0,0); break;
  case 'B': scene.pieces[0]->Rotate(10,0,0); break;
  case 'N': scene.pieces[0]->Rotate(0,10,0); break;
  case 'n': scene.pieces[0]->Rotate(0,-10,0); break;
  case 'M': scene.pieces[0]->Rotate(0,0,10); break;
  case 'm': scene.pieces[0]->Rotate(0,0,-10); break;

  // standard walking movement
  case 'w': scene.camera.moveforward(stepsize); break;
  case 's': scene.camera.moveback(stepsize);    break;
  case 'a': scene.camera.moveright(stepsize); break;
  case 'd': scene.camera.moveleft(stepsize);  break;


  case 'o': scene.pieces[0]->slowDown(10); break;
  case 'O': scene.pieces[0]->speedUp(10); break;

  case 'v': 
    scene.fovy-=5; 
    if (scene.fovy < 0) {
      // Min angle of view 1 degree
      scene.fovy = 1;
    }
    break;
  case 'V': scene.fovy+=5; break;
    if (scene.fovy > 179) {
      // Max angle of view 179 degrees
      scene.fovy = 179;
    }
    break;

  case ' ':  // reset values to their defaults

    scene.incr=0.1;

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
  //send Camera matrix to gpu
  mat4 cv = scene.camera.generate_view_matrix();
  glUniformMatrix4fv(scene.shader.cameraViewMatrix(), 1, GL_TRUE, cv);
  //send Prespective matrix to gpu
  mat4  p = Perspective(scene.fovy, scene.aspect, scene.zNear, scene.zFar) ;
  glUniformMatrix4fv(scene.shader.projectionMatrix(), 1, GL_TRUE, p);
  
  
  for (auto piece : scene.pieces){
    piece->draw();
  }

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
  glutCreateWindow("Color Cube");

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


