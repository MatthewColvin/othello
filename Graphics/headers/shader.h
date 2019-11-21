#ifndef SHADER_H
#define SHADER_H
#include <Angel.h>
#include <cassert>
#include <string>
using std::string;

class Shader{
    public:
        Shader(){};
        
        void init(string PathToFragShader,string PathToVertexShader){
            GL_location =
            InitShader(PathToVertexShader.c_str(), PathToFragShader.c_str());

            ModelViewMatrix = glGetUniformLocation(GL_location, "model_view");
            CameraViewMatrix = glGetUniformLocation(GL_location, "camera_view");
            ProjectionMatrix = glGetUniformLocation(GL_location, "projection");
            shade = glGetUniformLocation(GL_location, "shade");
            vPosition = glGetAttribLocation(GL_location, "vPosition");
            vColor = glGetAttribLocation(GL_location,"vColor");

            if (
            ModelViewMatrix == -1 || 
            CameraViewMatrix == -1 ||
            ProjectionMatrix == -1 ||
            shade == -1 ||
            vPosition == -1 ||
            vColor == -1
            ){
                assert("Error in shader initilization!!");
            }

        };
        
        inline GLint modelViewMatrix(){return ModelViewMatrix;}
        inline GLint cameraViewMatrix(){return CameraViewMatrix;}
        inline GLint projectionMatrix(){return ProjectionMatrix;}
        inline GLint isShaded(){return shade;}


        inline GLint VertPosition(){return vPosition;}
        inline GLint VertColor() { return vColor;}

        inline GLint Location(){return GL_location;};
    


    private:
        GLint GL_location; // location of shader program.
        
        GLint ModelViewMatrix;
        GLint CameraViewMatrix;
        GLint ProjectionMatrix;
        GLint shade;

        GLint vPosition;
        GLint vColor;
};

#endif