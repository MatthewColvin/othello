#ifndef OBJECT_H
#define OBJECT_H

#include <vector>
#include <Angel.h>

using Angel::vec4;
typedef Angel::vec4 color4;
typedef Angel::vec4 point4;
typedef Angel::vec4 norm4;
using std::vector;
using Angel::mat4;


class object{
    public:
        object(vector<point4>& GlobalPoints);
        object(vector<point4>& GlobalPoints,vector<color4>& GlobalColors);
        object(vector<point4>& GlobalPoints,vector<color4>& GlobalColors,vector<color4>& GlobalNormals);
        void draw(); // Assumes you are drawing triangle soup 
        inline void set_mv(mat4 nmv){mv = nmv;}
        inline mat4 get_mv(){return mv * translationmatrix ;}
        
        void Translate(float xamount,float yamount, float zamount);
        void Rotate(float xradians,float yradians,float zradians);
        void Scale(float xamount,float yamount, float zamount); 

        // Translation /////////////////////
            vec3 get_position();
            void set_position(vec3 newPosition);
            vec3 get_goal_position();
            void set_goal_position(vec3 newPosition);

            inline float XdistToGoal(){return Goalx - x;}
            inline float YdistToGoal(){return Goaly - y;}
            inline float ZdistToGoal(){return Goalz - z;}

            bool isTraveling();
            float distanceToGoal(); 
            inline float translationSpeed(){return translationspeed / 10000;}
            inline void speedUp(int amount){translationspeed += amount;}
            inline void slowDown(int amount){translationspeed -= amount;}
        // End Translation /////////////////

        // Rotation ////////////////////////
            void set_orientation(vec3 newOrientation);
            void set_goal_orientation(vec3 newOrientation);
                        
            vec4 getrotationaxis();
            bool isRotating();
            inline float rotationSpeed(){return rotationspeed / 10000;}
            inline void speedUpRotation(int amount){rotationspeed += amount;}
            inline void slowDownRotation(int amount){rotationspeed -= amount;}
        // End Rotation ////////////////////

    private:
        // Translation 
            float translationspeed = 10;
            // object will go to goal if distance is less than this constant
            float SNAPTODISTANCEGOAL = .000001; 
            float x=0; float y=0; float z=0;
            float Goalx=0; float Goaly=0; float Goalz=0;
            mat4 translationmatrix ;
        // Rotation
            float rotationspeed = 10;
            float SNAPTORADIANGOAL = .000001; 
            vec4 currentQuaternion;
            vec4 goalQuaternion;
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