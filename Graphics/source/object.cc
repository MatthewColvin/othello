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

//Animation Code
float mysqrt(float x){
  float squareroot = sqrt(abs(x));
  if(x<0){
    return(-squareroot);
  }
  return(squareroot);
}
// Non-Class helpers ///////////////////////////////
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
//
void object::Translate(float xamount,float yamount, float zamount){
  Goalx += xamount;
  Goaly += yamount;
  Goalz += zamount;
  }
  // public ///////////////////////
    void object::set_goal_position(vec3 newPosition){
      if(isTraveling()){
        std::cerr << "Watch out seting new location while moving may cause weird effect" << std::endl;
      } 
      Goalx = newPosition.x;
      Goaly = newPosition.y;
      Goalz = newPosition.z;
    }
  // private //////////////////////
    bool object::isTraveling(){
      if (x==Goalx && y==Goaly && z==Goalz){
        return false;
      }
      return true;
    }
    float object::distanceToGoal(){
      return(mysqrt(XdistToGoal() + YdistToGoal() + ZdistToGoal()));
    }
    void object::set_position(vec3 newPosition){
      x = newPosition.x;
      y = newPosition.y;
      z = newPosition.z;
      translationmatrix = Angel::Translate(x,y,z) * mat4();
    }
void object::Rotate(float xdegrees,float ydegrees,float zdegrees){
    goalorientation.x += xdegrees;
    goalorientation.y += ydegrees;
    goalorientation.z += zdegrees;
        
    while(goalorientation.x >= 360){goalorientation.x -= 360;}  
    while(goalorientation.y >= 360){goalorientation.y -= 360;}
    while(goalorientation.z >= 360){goalorientation.z -= 360;} 
    
    while(goalorientation.x < 0){goalorientation.x += 360;}  
    while(goalorientation.y < 0){goalorientation.y += 360;}
    while(goalorientation.z < 0){goalorientation.z += 360;}
  }
  // Public Rotation /////////////////////////
    void object::set_goal_orientation(EulerAngles newgoalorientaiton){
        //fix new goal
        while(goalorientation.x >= 360){goalorientation.x -= 360;}  
        while(goalorientation.y >= 360){goalorientation.y -= 360;}
        while(goalorientation.z >= 360){goalorientation.z -= 360;} 
        
        while(goalorientation.x < 0){goalorientation.x += 360;}  
        while(goalorientation.y < 0){goalorientation.y += 360;}
        while(goalorientation.z < 0){goalorientation.z += 360;}
        
        goalorientation = newgoalorientaiton;
    }
  // Private Rotation ////////////////////////
    bool object::isRotating(){
      if(
        currentorientation.x == goalorientation.x &&
        currentorientation.y == goalorientation.y &&
        currentorientation.z == goalorientation.z
      )
      {return false;}else{return true;}
    }

    bool object::isUnitQuaterian(Quaternion q){
      if ((q.x*q.x+q.y*q.y+q.z*q.z+q.w*q.w) != 1){
      std::cerr << "watchout quaternians should sum to 1" << std::endl;
      return false;
      }
      return true;
    }
    Quaternion object::getQuaternian(mat4 &rotmatrix)const{
      mat4 a = rotmatrix;
      float trace = a[0][0] + a[1][1] + a[2][2]; 
      vec4 quat;
      if( trace > 0 ) {
        float s = 0.5f / sqrtf(trace+ 1.0f);
        quat.w = 0.25f / s;
        quat.x = ( a[2][1] - a[1][2] ) * s;
        quat.y = ( a[0][2] - a[2][0] ) * s;
        quat.z = ( a[1][0] - a[0][1] ) * s;
      } else {
        if ( a[0][0] > a[1][1] && a[0][0] > a[2][2] ) {
          float s = 2.0f * sqrtf( 1.0f + a[0][0] - a[1][1] - a[2][2]);
          quat.w = (a[2][1] - a[1][2] ) / s;
          quat.x = 0.25f * s;
          quat.y = (a[0][1] + a[1][0] ) / s;
          quat.z = (a[0][2] + a[2][0] ) / s;
        } else if (a[1][1] > a[2][2]) {
          float s = 2.0f * sqrtf( 1.0f + a[1][1] - a[0][0] - a[2][2]);
          quat.w = (a[0][2] - a[2][0] ) / s;
          quat.x = (a[0][1] + a[1][0] ) / s;
          quat.y = 0.25f * s;
          quat.z = (a[1][2] + a[2][1] ) / s;
        } else {
          float s = 2.0f * sqrtf( 1.0f + a[2][2] - a[0][0] - a[1][1] );
          quat.w = (a[1][0] - a[0][1] ) / s;
          quat.x = (a[0][2] + a[2][0] ) / s;
          quat.y = (a[1][2] + a[2][1] ) / s;
          quat.z = 0.25f * s;
        }
      }
      return quat;
    }
    Quaternion object::getQuaternian(vec3 Rotationaxis,float degrees){
      float radians = degrees * DegreesToRadians;
      vec4 Quat;
      Quat.x = Rotationaxis.x * sin(radians/2);
      Quat.y = Rotationaxis.y * sin(radians/2);
      Quat.z = Rotationaxis.z * sin(radians/2);
      Quat.w = cos(radians/2); 
      if(isUnitQuaterian(Quat)){
        return Quat;
      }
      else{
        std::cerr << "did not create unit quaterian from eulerangles" << std::endl;
        return(vec4(0,0,0,1));
      }
    }
    Quaternion object::getQuaternian(EulerAngles eulerangles){
      float yaw = eulerangles.x * DegreesToRadians; 
      float pitch = eulerangles.y * DegreesToRadians;
      float roll = eulerangles.z * DegreesToRadians;
      
      float qx = sin(roll/2) * cos(pitch/2) * cos(yaw/2) - cos(roll/2) * sin(pitch/2) * sin(yaw/2);
      float qy = cos(roll/2) * sin(pitch/2) * cos(yaw/2) + sin(roll/2) * cos(pitch/2) * sin(yaw/2);
      float qz = cos(roll/2) * cos(pitch/2) * sin(yaw/2) - sin(roll/2) * sin(pitch/2) * cos(yaw/2);
      float qw = cos(roll/2) * cos(pitch/2) * cos(yaw/2) + sin(roll/2) * sin(pitch/2) * sin(yaw/2);
      return vec4(qx,qy,qz,qw);
    }
    Quaternion object::getQuaternian(double yaw, double pitch, double roll){ // yaw (Z), pitch (Y), roll (X)
      // Abbreviations for the various angular functions
      double cy = cos(yaw * 0.5);
      double sy = sin(yaw * 0.5);
      double cp = cos(pitch * 0.5);
      double sp = sin(pitch * 0.5);
      double cr = cos(roll * 0.5);
      double sr = sin(roll * 0.5);

      Quaternion q;
      q.w = cy * cp * cr + sy * sp * sr;
      q.x = cy * cp * sr - sy * sp * cr;
      q.y = sy * cp * sr + cy * sp * cr;
      q.z = sy * cp * cr - cy * sp * sr;

      return q;
    }

    mat4 object::toMatrix(vec4 Quaternian){
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

    EulerAngles object::getEulerAngles(mat4 &R){
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
    EulerAngles object::getEulerAngles(Quaternion q) {
      EulerAngles angles;

      // roll (x-axis rotation)
      double sinr_cosp = 2 * (q.w * q.x + q.y * q.z);
      double cosr_cosp = 1 - 2 * (q.x * q.x + q.y * q.y);
      angles.x = std::atan2(sinr_cosp, cosr_cosp);

      // pitch (y-axis rotation)
      double sinp = 2 * (q.w * q.y - q.z * q.x);
      if (std::abs(sinp) >= 1)
          angles.y = std::copysign(M_PI / 2, sinp); // use 90 degrees if out of range
      else
          angles.y = std::asin(sinp);

      // yaw (z-axis rotation)
      double siny_cosp = 2 * (q.w * q.z + q.x * q.y);
      double cosy_cosp = 1 - 2 * (q.y * q.y + q.z * q.z);
      angles.z = std::atan2(siny_cosp, cosy_cosp);

      return angles;
    }
    
    void object::set_orientation(Quaternion q){
      currentorientation = getEulerAngles(q);
      while(currentorientation.x > 360){currentorientation.x -= 360;}  
      while(currentorientation.y > 360){currentorientation.y -= 360;}
      while(currentorientation.z > 360){currentorientation.z -= 360;} 
      
      while(currentorientation.x < 0){currentorientation.x += 360;}  
      while(currentorientation.y < 0){currentorientation.y += 360;}
      while(currentorientation.z < 0){currentorientation.z += 360;}
    }
    
    void object::set_orientation(EulerAngles neworientaiton){
      currentorientation = neworientaiton;
      while(currentorientation.x > 360){currentorientation.x -= 360;}  
      while(currentorientation.y > 360){currentorientation.y -= 360;}
      while(currentorientation.z > 360){currentorientation.z -= 360;} 
      
      while(currentorientation.x < 0){currentorientation.x += 360;}  
      while(currentorientation.y < 0){currentorientation.y += 360;}
      while(currentorientation.z < 0){currentorientation.z += 360;}

      rotationmatrix = 
        RotateX(currentorientation.x)*
        RotateY(currentorientation.y)*
        RotateZ(currentorientation.z);
    }

    Quaternion object::slerp(Quaternion const &q0, Quaternion const &q1, double t) {
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
void object::Scale(float xamount, float yamount, float zamount){
  scalematrix = Angel::Scale(zamount,yamount,zamount);
}
// TODO update to support speed.
void object::update(float translationamountpercall,float rotationamountpercall){
    if(isTraveling()){
        float percenttotravel = (translationamountpercall/distanceToGoal()) * (translationamountpercall/distanceToGoal());
        if (percenttotravel >= 1.0){
            set_position(get_goal_position());
        }else{
            vec3 nextpos(
                x + XdistToGoal()*percenttotravel,
                y + YdistToGoal()*percenttotravel, 
                z + ZdistToGoal()*percenttotravel);

            set_position(vec3(nextpos.x,nextpos.y,nextpos.z));
        }
    }
    if(isRotating()){
      set_orientation(goalorientation);
    }
}
void object::updatewithtime(float timeseed){
    float timescale = .005;
    update(timeseed*timescale,timeseed*timescale);
}






