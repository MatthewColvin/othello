#include "object.h" 
using std::vector;

object::object(vector<point4>& GlobalPoints){mv = mat4();}
object::object(vector<point4>& GlobalPoints,vector<color4>& GlobalColors){mv = mat4();}
object::object(vector<point4>& GlobalPoints,vector<color4>& GlobalColors,vector<color4>& GlobalNormals){mv = mat4();}

void object::draw(){
  glUniformMatrix4fv(model_view, 1, GL_TRUE, mv);
  glDrawArrays(GL_TRIANGLES, StartInVao, NumVertices);
}
void object::triangle(point4& a, point4& b, point4& c, vec4 color){
  colors.push_back(color); points.push_back(a);a.w=0.0;normals.push_back(a);a.w=1.0;
  colors.push_back(color); points.push_back(b);b.w=0.0;normals.push_back(b);b.w=1.0;
  colors.push_back(color); points.push_back(c);c.w=0.0;normals.push_back(c);c.w=1.0;
}
void object::Translate(float xamount,float yamount, float zamount){
  mv *= Angel::Translate(xamount,yamount,zamount);
  x+=xamount; 
  y+=yamount;
  z+=zamount;
}
void object::Rotate(float xradians,float yradians,float zradians){
  mv *=  Angel::RotateX(xradians) * RotateY(yradians) * RotateZ(zradians);
}
void object::Scale(float xamount, float yamount, float zamount){
  mv *= Angel::Scale(zamount,yamount,zamount);
}
float object::distanceToGoal(){
  float xdist = (Goalx-x) * (Goalx-x);
  float ydist = (Goaly-y) * (Goaly-y);
  float zdist = (Goalz-z) * (Goalz-z);

  return(sqrt(xdist + ydist + zdist));
}
vec3 object::get_position(){return vec3(x,y,z);}     
void object::set_position(vec3 newPosition){
  x = newPosition.x;
  y = newPosition.y;
  z = newPosition.z;
  Translate(Goalx-x,Goaly-y,Goalz-z);  
}
vec3 object::get_goal_position(){return vec3(Goalx,Goaly,Goalz);}
void object::set_goal_position(vec3 newPosition){
  if(ismoving){
    std::cerr << "Watch out seting new location while moving may cause weird effect" << std::endl;
  } 
  Goalx = newPosition.x;
  Goaly = newPosition.y;
  Goalz = newPosition.z;
}