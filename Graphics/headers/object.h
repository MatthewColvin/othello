#ifndef OBJECT_H
#define OBJECT_H

#include<Angel.h>
#include<vector>
typedef Angel::vec4 color4;
typedef Angel::vec4 point4;
typedef Angel::vec4 norm4;
using std::vector;


class object{
    public:
        object(vector<point4>& GlobalPoints);
        object(vector<point4>& GlobalPoints,vector<color4>& GlobalColors);
        object(vector<point4>& GlobalPoints,vector<color4>& GlobalColors,vector<color4>& GlobalNormals);
        void draw(); // Assumes you are drawing triangle soup 

        inline void set_mv(mat4 nmv){mv = nmv;}
        inline mat4 get_mv(){return mv;}

        void Translate(float xamount,float yamount, float zamount);
        void Rotate(float xradians,float yradians,float zradians);
        void Scale(float xamount,float yamount, float zamount); 

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
    private:
        float x=0; float y=0; float z=0;
        float Goalx=0; float Goaly=0; float Goalz=0;
        // object will go to goal if distance is less than this constant
        float SNAPTODISTANCETOGOAL = .000001; 
        float translationspeed = 90;
    protected:
    
        int StartInVao;
        mat4 mv = mat4();
        GLint model_view;
        int NumVertices;

        vector<point4> points; // objects current geoemetery
        vector<color4> colors; // objects current colors 
        vector<norm4> normals;

        // used to put triangles into the vao to be drawn
        void triangle(point4& a, point4& b, point4& c, vec4 color);

        

};

#endif 