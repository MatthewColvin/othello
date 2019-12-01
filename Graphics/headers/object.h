#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#define _USE_MATH_DEFINES
#include <cmath>
#include <Angel.h>

using Angel::vec4;
typedef Angel::vec4 color4;
typedef Angel::vec4 point4;
typedef Angel::vec4 norm4;
typedef Angel::vec4 Quaternion;
typedef Angel::vec3 EulerAngles;
using std::vector;
using Angel::mat4;


class object{
    public:
        object(vector<point4>& GlobalPoints);
        object(vector<point4>& GlobalPoints,vector<color4>& GlobalColors);
        object(vector<point4>& GlobalPoints,vector<color4>& GlobalColors,vector<color4>& GlobalNormals);
        void draw(); // Assumes you are drawing triangle soup 
        inline int GetNumVerts(){return NumVertices;}

        inline void set_mv(mat4 nmv){mv = nmv;}
        inline mat4 get_mv(){return mv * translationmatrix * rotationmatrix ;}
        
        void Translate(float xamount,float yamount, float zamount);
        // Translation /////////////////////
            void set_goal_position(vec3 newPosition);

            inline float translationSpeed(){return translationspeed / 10000;}
            inline void speedUp(int amount){translationspeed += amount;}
            inline void slowDown(int amount){translationspeed -= amount;}
        ////////////////////////////////////

        void Rotate(float xdegrees,float ydegrees,float zdegrees);
        // Rotation ////////////////////////
            void set_goal_orientation(EulerAngles neworientation);
            void set_goal_orientation(double roll, double pitch, double yaw);

            inline float rotationSpeed(){return rotationspeed / 10000;}
            inline void speedUpRotation(int amount){rotationspeed += amount;}
            inline void slowDownRotation(int amount){rotationspeed -= amount;}
            void Tests();
        ////////////////////////////////////

        void Scale(float xamount,float yamount, float zamount); 
        // Scale ///////////////////////////
        ////////////////////////////////////

        void update(float translationamountpercall,float rotationamountpercall);
        void updatewithtime(float timeseed);

    private:
        
        // Translation 
            float translationspeed = 10;
            float x=0; float y=0; float z=0;
            float Goalx=0; float Goaly=0; float Goalz=0;
            mat4 translationmatrix ;
            
            bool isTraveling();
            float distanceToGoal();
            void set_position(vec3 newPosition);
            
            inline vec3 get_position(){return vec3(x,y,z);}     
            inline vec3 get_goal_position(){return vec3(Goalx,Goaly,Goalz);}
            
            inline float XdistToGoal(){return Goalx - x;}
            inline float YdistToGoal(){return Goaly - y;}
            inline float ZdistToGoal(){return Goalz - z;}        
        // Rotation
            float rotationspeed = 10;
            mat4 rotationmatrix;
            
            EulerAngles currentorientation;
            EulerAngles goalorientation;

            Quaternion currentori;
            Quaternion goalori;

            inline float Xdegreestogoal(){return (goalorientation.x - currentorientation.x);};
            inline float Ydegreestogoal(){return (goalorientation.y - currentorientation.y);};
            inline float Zdegreestogoal(){return (goalorientation.z - currentorientation.z);};

            bool isRotating();

            bool isUnitQuaterian(vec4 q); // only unit Quaterinas are actually rotations
            Quaternion getQuaternian(mat4 &rotationmat)const;
            Quaternion getQuaternian(vec3 Rotationaxis,float radians);
            Quaternion getQuaternian(EulerAngles eulerangles);
            Quaternion getQuaternian(double yaw, double pitch, double roll); // yaw (Z), pitch (Y), roll (X)
            
            mat4 toMatrix(Quaternion q);            
            
            EulerAngles getEulerAngles(mat4 &R);
            EulerAngles getEulerAngles(Quaternion q);
            
            void set_orientation(EulerAngles neworientation);
            // ones i will be using internally for animation.
            void set_orientation(Quaternion q);
            
            void set_goal_orientation(Quaternion q);
            
            Quaternion slerp(Quaternion &q0, Quaternion &q1, double t);  
        // Scaling
            mat4 scalematrix;
        // 
        
    protected:
    
        int StartInVao;
        GLint model_view;
        int NumVertices;
        
        vector<point4> points; // objects current geoemetery
        vector<color4> colors; // objects current colors 
        vector<norm4> normals;

        // used to put triangles into the vao to be drawn
        void triangle(point4& a, point4& b, point4& c, vec4 color);
        mat4 mv;
        

};

#endif 