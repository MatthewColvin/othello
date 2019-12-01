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
            return(LookAt(eye,eye+at,upvec)*translation);}

        inline float get_cameraYangel(){return cameraangleiny;};
        inline float get_cameraXangel(){return cameraangleinx;};
        inline vec4 get_eye(){return eye;};
        inline vec4 get_at(){return at;};

    private:
        vec4 eye = vec4(-30,20,-15,0);
        vec4 at = vec4(4,-2,2.5,0);
        vec3 upvec = vec3(0.0, 1.0, 0.0);

        float cameraangleiny = 0;
        float cameraangleinx = 0;


        mat4 translation = mat4(1.0, 0.0 ,0.0, 0.0,
                                0.0, 1.0 ,0.0, 0.0,
                                0.0, 0.0 ,1.0, 0.0,
                                0.0, 0.0 ,0.0, 1.0);
        
};

#endif