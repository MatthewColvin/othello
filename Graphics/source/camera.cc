#include "camera.h"
#include <math.h>
void Camera::moveleft(float amount){
    vec4 straifdirection = cross(at,upvec);
    eye += amount * straifdirection;
}
void Camera::moveright(float amount){
    vec4 straifdirection = cross(upvec,at);
    eye += amount * straifdirection;
}
void Camera::moveforward(float amount){
    eye += amount * at;
}
void Camera::moveback(float amount){
    eye += -amount * at;
}


void Camera::turnleft(float radians){  
    cameraangleiny -= radians;
    while(cameraangleiny >= 2*M_PI){cameraangleiny -= 2 * M_PI;} 
    while(cameraangleiny <= 0){cameraangleiny += 2 * M_PI;} 
    at = Rotate(upvec,-radians) * at;
}
void Camera::turnright(float radians){
    cameraangleiny += radians;
    while(cameraangleiny <= 0){cameraangleiny += 2 * M_PI;} 
    while(cameraangleiny >= 2*M_PI){cameraangleiny -= 2 * M_PI;} 
    at = Rotate(upvec,radians) * at;
}
void Camera::turnup(float radians){  
    cameraangleinx += radians;
    while(cameraangleinx >= 2*M_PI){cameraangleinx -= 2 * M_PI;} 
    while(cameraangleinx <= 0){cameraangleinx += 2 * M_PI;} 
    at = Rotate(cross(upvec,at),radians) * at;
}
void Camera::turndown(float radians){
    cameraangleinx -= radians;
    while(cameraangleinx <= 0){cameraangleinx += 2 * M_PI;} 
    while(cameraangleinx >= 2*M_PI){cameraangleinx -= 2 * M_PI;} 
    at = Rotate(cross(at,upvec),radians) * at;
}


void Camera::moveup(float amount){
    eye += amount * upvec;
}
void Camera::movedown(float amount){
    eye += -amount * upvec;
}