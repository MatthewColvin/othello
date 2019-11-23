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
            inline float X(){return x;}
            inline float Y(){return y;} 
            inline float Z(){return z;}
        void set_position(vec3 newPosition);
            inline void setX(float newx){x = newx; }
            inline void setY(float newy){y = newy; } 
            inline void setZ(float newz){z = newz; }
    
        
        vec3 get_goal_position();
            inline float GoalX(){return Goalx;}
            inline float GoalY(){return Goaly;} 
            inline float GoalZ(){return Goalz;}
        void set_goal_position(vec3 newPosition);
            inline void setGoalx(float newx){x = newx;}
            inline void setGoaly(float newy){y = newy;} 
            inline void setGoalz(float newz){z = newz;}

        float distanceToGoal(); 

        float getamounttraveled();
        void  setamountrtaveled(float amount);

        bool isTraveling(){return ismoving;};
        float percenttraveled(){return amounttraveled;}

    private:
        float x=0; float y=0; float z=0;
        float Goalx=0; float Goaly=0; float Goalz=0;
        float amounttraveled = 0; // value between 0 and 1 used for w in transforms.
        bool ismoving = false;
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