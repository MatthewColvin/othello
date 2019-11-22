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

        inline vec3 get_position(){return vec3(x,y,z);}
            inline float getx(){return x;}
            inline float gety(){return y;} 
            inline float getz(){return z;}
        inline void set_position(vec3 newPosition){x = newPosition.x;;;y = newPosition.y;;;z = newPosition.z;}
            inline void setx(float newx){x = newx;}
            inline void sety(float newy){y = newy;} 
            inline void setz(float newz){z = newz;}
    private:
      
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

        float x; float y; float z;

};

#endif 