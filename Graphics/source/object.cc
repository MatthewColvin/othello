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
}
void object::Rotate(float xradians,float yradians,float zradians){
  mv *=  Angel::RotateX(xradians) * RotateY(yradians) * RotateZ(zradians);
}
void object::Scale(float xamount, float yamount, float zamount){
  mv *= Angel::Scale(zamount,yamount,zamount);
}