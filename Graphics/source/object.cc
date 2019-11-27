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
void object::Rotate(float yawdegrees,float pitchdegrees,float rolldegrees){
    goalorientation.x += rolldegrees;
    goalorientation.y += pitchdegrees;
    goalorientation.z += yawdegrees;
    set_goal_orientation(goalorientation);
  }
  // Public Rotation /////////////////////////
    void object::Tests(){
      using std::cout;
      using std::endl;
      static float roll=5;
      static float pitch=0;
      static float yaw=0;
      bool angleconversiontest = true;
      bool slerptest = false;
      if(angleconversiontest){
      cout << "eulerangle -> quaterian -> eulerangle:" << endl;
        EulerAngles EAtest(roll,pitch,yaw);
        cout<< EAtest << endl;
        Quaternion Qtest = getQuaternian(EAtest);
        cout << Qtest << endl;
        EulerAngles EAeq = getEulerAngles(Qtest);
        cout << EAeq << endl;
        roll+=5;
      }
      if(slerptest){
        static float i = .05;
        EulerAngles e1(0,0,10);
        EulerAngles e2(0,0,20);
        Quaternion q1 = getQuaternian(e1);
        Quaternion q2 = getQuaternian(e2);
        Quaternion slerpresult = slerp(q1,q2,i);
        EulerAngles step = getEulerAngles(slerpresult);
        cout << "Euler Angles -> Quaternion then slerp" << endl;
        cout << step << endl;
        i+=.05;
      }
    }
    void object::set_goal_orientation(EulerAngles newgoalorientaiton){
        goalorientation = newgoalorientaiton;
        while(goalorientation.x >= 360){goalorientation.x -= 360;}  
        while(goalorientation.y >= 360){goalorientation.y -= 360;}
        while(goalorientation.z >= 360){goalorientation.z -= 360;} 
        
        while(goalorientation.x < 0){goalorientation.x += 360;}  
        while(goalorientation.y < 0){goalorientation.y += 360;}
        while(goalorientation.z < 0){goalorientation.z += 360;}

        goalori = getQuaternian(goalorientation);
    }
    void object::set_goal_orientation(double roll, double pitch, double yaw){
      set_goal_orientation(EulerAngles(roll,pitch,yaw));
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
    Quaternion object::getQuaternian(EulerAngles EAs){
      if(EAs.y == 90 || EAs.y == -90){
        EAs.y +=.001;
      }
      EAs *= DegreesToRadians;
      return(getQuaternian(EAs.x,EAs.y,EAs.z));
    }
    //Code adapted from http://www.euclideanspace.com/maths/geometry/rotations/conversions/eulerToQuaternion/index.htm
    Quaternion object::getQuaternian(double heading, double attitude, double bank){
      // Assuming the angles are in radians.
      double c1 = cos(heading/2);
      double s1 = sin(heading/2);
      double c2 = cos(attitude/2);
      double s2 = sin(attitude/2);
      double c3 = cos(bank/2);
      double s3 = sin(bank/2);
      double c1c2 = c1*c2;
      double s1s2 = s1*s2;
      Quaternion q;
      q.w =c1c2*c3 - s1s2*s3;
      q.x =c1c2*s3 + s1s2*c3;
      q.y =s1*c2*c3 + c1*s2*s3;
      q.z =c1*s2*c3 - s1*c2*s3;
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
    // adapted from http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToEuler/index.htm
    EulerAngles object::getEulerAngles(Quaternion q1) {
      double heading,attitude,bank;
      double test = q1.x*q1.y + q1.z*q1.w;
      if (test > 0.499) { // singularity at north pole
        heading = 2 * atan2(q1.x,q1.w);
        attitude = M_PI/2;
        bank = 0;
        return(EulerAngles(heading,attitude,bank)/DegreesToRadians);
      }
      if (test < -0.499) { // singularity at south pole
        heading = -2 * atan2(q1.x,q1.w);
        attitude = - M_PI/2;
        bank = 0;
        return(EulerAngles(heading,attitude,bank)/DegreesToRadians);
      }
      double sqx = q1.x*q1.x;
      double sqy = q1.y*q1.y;
      double sqz = q1.z*q1.z;
      heading = atan2(2*q1.y*q1.w-2*q1.x*q1.z , 1 - 2*sqy - 2*sqz);
      attitude = asin(2*test);
      bank = atan2(2*q1.x*q1.w-2*q1.y*q1.z , 1 - 2*sqx - 2*sqz);
      return(EulerAngles(heading,attitude,bank)/DegreesToRadians);
    }
   
    void object::set_orientation(Quaternion q){
      set_orientation(getEulerAngles(q));
    }
    
    void object::set_orientation(EulerAngles neworientaiton){
      currentorientation = neworientaiton;
      while(currentorientation.x > 360){currentorientation.x -= 360;}  
      while(currentorientation.y > 360){currentorientation.y -= 360;}
      while(currentorientation.z > 360){currentorientation.z -= 360;} 
      
      while(currentorientation.x < 0){currentorientation.x += 360;}  
      while(currentorientation.y < 0){currentorientation.y += 360;}
      while(currentorientation.z < 0){currentorientation.z += 360;}

      currentori = getQuaternian(neworientaiton);
      rotationmatrix = 
        RotateX(currentorientation.x)*
        RotateY(currentorientation.y)*
        RotateZ(currentorientation.z);
    }
    Quaternion object::slerp(Quaternion &q1, Quaternion &q2, double lambda) {
      float dotproduct = q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
      float theta, st, sut, sout, coeff1, coeff2;

      if (dotproduct > .99999999){ // if the distance is to close just retun the goal orientation.
        std::cout << "Close to location setting it to goal" << std::endl;
        std::cout << "Goal orienation" << getEulerAngles(q2) << std::endl;
        return q2;
      }

      // algorithm adapted from Shoemake's paper
      lambda=lambda/2.0;

      theta = (float) acos(dotproduct);
      if (theta<0.0) theta=-theta;
      
      st = (float) sin(theta);
      sut = (float) sin(lambda*theta);
      sout = (float) sin((1-lambda)*theta);
      coeff1 = sout/st;
      coeff2 = sut/st;
      Quaternion qr;
      qr.x = coeff1*q1.x + coeff2*q2.x;
      qr.y = coeff1*q1.y + coeff2*q2.y;
      qr.z = coeff1*q1.z + coeff2*q2.z;
      qr.w = coeff1*q1.w + coeff2*q2.w;
      {using std::cout; using std::endl;
        cout << "currentorientation " << currentorientation << endl;
        cout << "goalorientaiton" << goalorientation << endl;

        cout << "old quat->eulerangles" << getEulerAngles(q1) << endl; 
        cout << "goal quat->eulerangles" << getEulerAngles(q2) << endl;
        cout << "slerped eulerangles" << getEulerAngles(qr) << endl << endl;
      }
      return (qr);
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
      if(goalorientation.y==90){
        goalorientation.y -= .001;
        goalori = getQuaternian(goalorientation);
      }
      if(goalorientation.y==-90){
        goalorientation.y += .001;
      }
      Quaternion nextorientaion = slerp(currentori,goalori,rotationamountpercall);
      set_orientation(nextorientaion);
    }
}
void object::updatewithtime(float timeseed){
    float translationtimescale = .005;
    float rotationtimescale = 0.0005;
    update(timeseed*translationtimescale,timeseed*rotationtimescale);
}






