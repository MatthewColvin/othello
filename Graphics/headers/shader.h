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

            shade = glGetUniformLocation(GL_location, "shade");
            cameraPosition = glGetUniformLocation(GL_location,"cameraPositon");
            lightPositon = glGetUniformLocation(GL_location,"lightPosition");
            lightColor = glGetUniformLocation(GL_location,"lightColor");
            ambiantIntensity = glGetUniformLocation(GL_location,"ambiantIntensity");
            specularStrength = glGetUniformLocation(GL_location,"specularStrength");


            vPosition = glGetAttribLocation(GL_location, "vPosition");
            vColor = glGetAttribLocation(GL_location,"vColor");
            vNormal = glGetAttribLocation(GL_location,"vNormal");
            
            
            if (
            ModelViewMatrix == -1 || 
            CameraViewMatrix == -1 ||
            shade == -1 ||
            vPosition == -1 ||
            vColor == -1 ||
            vNormal == -1 ||
            ambiantIntensity == -1 ||
            cameraPosition == -1 ||
            lightPositon == -1 ||
            lightColor == -1 ||
            specularStrength == -1
            ){
                std::cerr << "Error in shader initilization!!";
            }

        };

        inline GLint Location(){return GL_location;};

        inline GLint modelViewMatrix(){return ModelViewMatrix;}
        inline void setcameraViewMatrix(mat4 cv){
            glUniformMatrix4fv(CameraViewMatrix, 1, GL_TRUE, cv);
        }
        
        inline void Shade(bool shadeornoshade){
            if(shadeornoshade){
                glUniform1i(shade,1);
            }else{
                glUniform1i(shade,0);
            }
        }

        inline GLint VertPosition(){return vPosition;}
        inline GLint VertColor() { return vColor;}
        inline GLint VertNormal() { return vNormal;}
        
        
        void setlighting(vec4 cameraposition,vec4 lightpositon,vec4 lightcolor,
        float ambiantintenstiy, float specularstrength){
            glUniform4f(cameraPosition,cameraposition.x,cameraposition.y,cameraposition.z,cameraposition.w);
            glUniform4f(lightPositon,lightpositon.x,lightpositon.y,lightpositon.z,lightpositon.w);
            glUniform4f(lightColor,lightcolor.x,lightcolor.y,lightcolor.z,lightcolor.w);
            glUniform1f(ambiantIntensity,ambiantintenstiy);
            glUniform1f(specularStrength,specularstrength);
        };

    private:
        GLint GL_location; // location of shader program.
        
        //Positioning 
        GLint vPosition; // attribute vertex postionts
            GLint ModelViewMatrix;//mat4
            GLint CameraViewMatrix;//mat4
            
        // Lighting model
            GLint shade; // bool shade or not to shade
            GLint vColor; // attribute vertex colors
            GLint vNormal; // attribute vertex normals
            // uniforms for phong model
                GLint cameraPosition;
                GLint lightPositon;
                GLint lightColor;
                GLint ambiantIntensity;
                GLint specularStrength;

};

#endif