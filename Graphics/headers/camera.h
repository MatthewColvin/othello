#ifndef CAMERA_H
#define CAMERA_H
#include<Angel.h>

//world coordinates * camera matrix = 

class Camera{
    public:
        
        Camera(){};
        //"walking"
        void moveforward(float amount);
        void moveback(float amount);
        void moveleft(float amount);
        void moveright(float amount);
        //"flying"
        void movedown(float amount);
        void moveup(float amount);
        // "looking around"
        void turnleft(float radians);
        void turnright(float radians);
        void turnup(float radians);
        void turndown(float radians);

        inline mat4 generate_view_matrix(){
            return(GeneratePrespectiveMatrix() * LookAt(eye,eye+at,upvec)*translation);}

        inline mat4 GeneratePrespectiveMatrix(){
            return(Perspective(fovy, aspect,zNear,zFar));
        };
        inline void setAspect(GLfloat newAspect){aspect = newAspect;};
        inline void setZdist(GLfloat zNear,GLfloat zFar){ Camera::zNear = zNear; Camera::zFar = zFar; }

        inline float get_cameraYangel(){return cameraangleiny;};
        inline float get_cameraXangel(){return cameraangleinx;};
        inline vec4 get_eye(){return eye;};
        inline vec4 get_at(){return at;};

    private:
        //prespective viewing parameters
            GLfloat fovy=45;
            GLfloat aspect=1.0;
            GLfloat angle = 0.0;
            GLfloat zNear = 0.1;
            GLfloat zFar = 300.0;	
        //camera pos and viewing direction 
            vec4 eye = vec4(20,21,-26,0);
            vec4 at = vec4(-1.2,-2.4,4.3,0);
            vec3 upvec = vec3(0.0, 1.0, 0.0);

            float cameraangleiny = 0;
            float cameraangleinx = 0;


            mat4 translation = mat4(1.0, 0.0 ,0.0, 0.0,
                                0.0, 1.0 ,0.0, 0.0,
                                0.0, 0.0 ,1.0, 0.0,
                                0.0, 0.0 ,0.0, 1.0);
        
};

#endif