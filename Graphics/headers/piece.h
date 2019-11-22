#ifndef SHADER_H
#define SHADER_H
#include "sphere.h"
#include <vector>

class Piece : public object{
    public:
        Piece(
            vector<point4>& globalpoints,
            vector<color4>& globalcolors,
            vector<norm4>& globalnormals, 
            GLint nmodel_view ,int nInitial_Point
        );
        void draw();


    private:
        sphere* spheres[2];
        vec3 scalefactor = vec3(1,.4,1); // used to make the piece look kinda smashed
};

#endif