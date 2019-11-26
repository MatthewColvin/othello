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
        inline mat4 get_mv(){return mv * translationmatrix * rotationmatrix ;}
        
        void Translate(float xamount,float yamount, float zamount);
        void Rotate(float xdegrees,float ydegrees,float zdegrees);
        void Scale(float xamount,float yamount, float zamount); 

        // Translation /////////////////////s
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
            inline void set_orientation(mat4 newRotationmatrix){rotationmatrix = newRotationmatrix;};
            void set_orientation(vec3 newOrientation);
            void set_goal_orientation(vec3 newOrientation);
            inline vec3 get_goal_orentation(){return goalorientation;}
            void set_orientation(vec4 Quaterian);
            inline mat4 get_rotationmatrix(){return rotationmatrix;};

            inline float xdegreestogoal(){return (goalorientation.x - currentorientation.x);};
            inline float ydegreestogoal(){return (goalorientation.y - currentorientation.y);};
            inline float zdegreestogoal(){return (goalorientation.z - currentorientation.z);};

            inline vec4 getGoalQuaterian(){return(getQuaternian(goalrotationmatrix));}
            inline vec4 getCurrentQuaterian(){return(getQuaternian(rotationmatrix));}

            bool isRotating();
            inline float rotationSpeed(){return rotationspeed / 10000;}
            inline void speedUpRotation(int amount){rotationspeed += amount;}
            inline void slowDownRotation(int amount){rotationspeed -= amount;}
        // End Rotation ////////////////////


        void update(float translationamountpercall,float rotationamountpercall){
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
                float percenttorotate = ;
                if (percenttorotate >= 1.0){
                    set_orientation(get_goal_orentation());
                }else{
                    vec3 nextpos(
                        currentorientation.x + XdistToGoal()*percenttorotate,
                        currentorientation.y + YdistToGoal()*percenttorotate, 
                        currentorientation.z + ZdistToGoal()*percenttorotate);

                    set_position(vec3(nextpos.x,nextpos.y,nextpos.z));
                }
                
                
                mat4 nextrotatation = get_rotationmatrix() +
                RotateX(xdegreestogoal() * rotationSpeed()) * 
                RotateY(ydegreestogoal() * rotationSpeed()) * 
                RotateZ(zdegreestogoal() * rotationSpeed());  
                set_orientation(nextrotatation);
            }
        }
        void updatewithtime(float timeseed){
            float timescale = .005;
            update(timeseed*timescale,timeseed*timescale);
        }

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
            float SNAPTODEGREEGOAL = .000001; 
            mat4 rotationmatrix;
            mat4 goalrotationmatrix;
            vec3 currentorientation;
            vec3 goalorientation;
            bool isUnitQuaterian(vec4 q); // only unit Quaterinas are actually rotations
            vec4 getQuaternian(mat4 &rotationmat)const;
            vec4 getQuaternian(vec3 Rotationaxis,float radians);
            mat4 toMatrix(vec4 Quaternian);            
            vec4 getrotationaxis();
            vec3 rotationMatrixToEulerAngles(mat4 &R);
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