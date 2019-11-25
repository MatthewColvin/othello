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
  glUniformMatrix4fv(model_view, 1, GL_TRUE,get_mv());
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
  goalQuaternion.x += xradians;
  goalQuaternion.y += yradians;
  goalQuaternion.z += zradians;
  while(goalQuaternion.x > 2 * M_PI){goalQuaternion.x -= 2 * M_PI;}  
  while(goalQuaternion.y > 2 * M_PI){goalQuaternion.y -= 2 * M_PI;}
  while(goalQuaternion.z > 2 * M_PI){goalQuaternion.z -= 2 * M_PI;} 
  
  while(goalQuaternion.x < 0){goalQuaternion.x += 2 * M_PI;}  
  while(goalQuaternion.y < 0){goalQuaternion.y += 2 * M_PI;}
  while(goalQuaternion.z < 0){goalQuaternion.z += 2 * M_PI;}
  }
 


bool isIdentity(mat4 &R){
  //Checks if diagonal elements are equal to 1 and rest of elements are 0 
  for(int i = 0; i < 4; i++){  
      for(int j = 0; j < 4; j++){  
        if(i == j && R[i][j] != 1.0){ 
            return (false);  
            break;  
        } else if(i != j && R[i][j] != 0){  
            return (false);  
            break;  
        }  
      }  
  }  
  return true;
}
bool isRotationMatrix(mat4 &R){
    mat4 Rt = transpose(R);
    mat4 shouldBeIdentity = Rt * R;
    mat4 I; // all vectors are initialized as the identity 
    if(!isIdentity(shouldBeIdentity)){
      // if the matrix * the transpose is not the identity then it is not a rotation matrix
      std::cerr << "Trying to use a non translation matrix as a translation." << std::endl; 
      return false; 
    }
    // to be completly sure of it being a rotation matric
    // would need to check if the determinate == 1 
    return true;  
}
vec3 rotationMatrixToEulerAngles(mat4 &R){
    if(!isRotationMatrix(R)){
      std::cerr<<"Rotation matrix trying to be converted to Euler angel not valid!!"<< std::endl;
    }else{
      float sy = sqrt(R[0][0] * R[0][0] +  R[0][0] * R[0][0] );

      bool singular = sy < 1e-6; // If
  
      float x, y, z;
      if (!singular)
      {
          x = atan2(R[2][1] , R[2][2]);
          y = atan2(-R[2][0], sy);
          z = atan2(R[1][0],R[0][0]);
      }
      else
      {
          x = atan2(-R[1][2], R[1][1]);
          y = atan2(-R[2][0], sy);
          z = 0;
      }
      return vec3(x, y, z);

    }  
    return(vec3(1,1,1));
}
vec4 getQuaternian(vec3 EulerAngles,float radians){
  vec4 Quat;
    Quat.x = EulerAngles.x * sin(radians/2);
    Quat.y = EulerAngles.y * sin(radians/2);
    Quat.z = EulerAngles.z * sin(radians/2);
    Quat.w = cos(radians/2); 
    if ((Quat.x + Quat.y + Quat.z + Quat.w) != 1){
      std::cerr << "watchout quaternians should sum to 1" << std::endl;
    }
    return Quat;
}
vec4 getQuaternian(mat4 &R,float radians){
    vec3 tmp = rotationMatrixToEulerAngles(R);
    return (getQuaternian(vec3(tmp.x,tmp.y,tmp.z),radians));
}
vec4 slerp(vec4 const &v0, vec4 const &v1, double t) {
    // v0 and v1 should be unit length or else
    // something broken will happen.

    // Compute the cosine of the angle between the two vectors.
    double dot = Angel::dot(v0,v1); 

    const double DOT_THRESHOLD = 0.9995;
    if (dot > DOT_THRESHOLD) {
        // If the inputs are too close for comfort, linearly interpolate
        // and normalize the result.

        vec4 result = v0 + t*(v1 - v0);
        result = normalize(result);
        return result;
    }
    
    //std::clamp(dot, -1.0, 1.0);           // Robustness: Stay within domain of acos()
    double theta_0 = acos(dot);  // theta_0 = angle between input vectors
    double theta = theta_0*t;    // theta = angle between v0 and result 

    vec4 v2 = v1 - v0 * dot;
    v2 = normalize(v2);             // { v0, v2 } is now an orthonormal basis

    return v0*cos(theta) + v2*sin(theta);
}



void object::Scale(float xamount, float yamount, float zamount){
  scalematrix *= Angel::Scale(zamount,yamount,zamount);
}







