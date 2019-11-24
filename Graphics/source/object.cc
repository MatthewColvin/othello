#include "object.h" 
using std::vector;

object::object(vector<point4>& GlobalPoints){}
object::object(vector<point4>& GlobalPoints,vector<color4>& GlobalColors){}
object::object(vector<point4>& GlobalPoints,vector<color4>& GlobalColors,vector<color4>& GlobalNormals){}

void object::triangle(point4& a, point4& b, point4& c, vec4 color){
  colors.push_back(color); points.push_back(a);a.w=0.0;normals.push_back(a);a.w=1.0;
  colors.push_back(color); points.push_back(b);b.w=0.0;normals.push_back(b);b.w=1.0;
  colors.push_back(color); points.push_back(c);c.w=0.0;normals.push_back(c);c.w=1.0;
}
void object::draw(){
  glUniformMatrix4fv(model_view, 1, GL_TRUE, get_mv());
  glDrawArrays(GL_TRIANGLES, StartInVao, NumVertices);
}

void object::Translate(float xamount,float yamount, float zamount){
  Goalx += xamount;
  Goaly += yamount;
  Goalz += zamount;
  }
  vec3 object::get_position(){return vec3(x,y,z);}     
  void object::set_position(vec3 newPosition){
    x = newPosition.x;
    y = newPosition.y;
    z = newPosition.z;
    translationmatrix = Angel::Translate(x,y,z) * mat4();
  }
  vec3 object::get_goal_position(){return vec3(Goalx,Goaly,Goalz);}
  void object::set_goal_position(vec3 newPosition){
    if(isTraveling()){
      std::cerr << "Watch out seting new location while moving may cause weird effect" << std::endl;
    } 
    Goalx = newPosition.x;
    Goaly = newPosition.y;
    Goalz = newPosition.z;
  }
  float object::distanceToGoal(){
    float xdist = (Goalx-x) * (Goalx-x);
    float ydist = (Goaly-y) * (Goaly-y);
    float zdist = (Goalz-z) * (Goalz-z);

    return(sqrt(xdist + ydist + zdist));
  }
  bool object::isTraveling(){
    if(distanceToGoal() < SNAPTODISTANCEGOAL){
      set_position(get_goal_position());
    }
    if (x==Goalx && y==Goaly && z==Goalz){
      return false;
    }
    return true;
  }


void object::Rotate(float xradians,float yradians,float zradians){
  xRadianGoal += xradians;
  yRadianGoal += yradians;
  zRadianGoal += zradians;
  }
  vec3 object::get_orientation(){return vec3(xRadian,yRadian,zRadian);}
  void object::set_orientation(vec3 newOrientation){
    xRadian = newOrientation.x;
    yRadian = newOrientation.y;
    zRadian = newOrientation.z;
    rotationmatrix = RotateX(xRadian) * RotateY(yRadian) * RotateZ(zRadian);
  }
  vec3 object::get_goal_orientation(){return vec3(xRadianGoal,yRadianGoal,zRadianGoal);}
  void object::set_goal_orientation(vec3 newOrientation){}
  bool object::isRotating(){}
  float object::RadiansToGoal(){}

void object::Scale(float xamount, float yamount, float zamount){
  scalematrix *= Angel::Scale(zamount,yamount,zamount);
}







