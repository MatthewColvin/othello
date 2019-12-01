#ifndef SPACE_H
#define SPACE_H
#include "cube.h"
#include <vector>

class Space : public object{
    public:
        Space(
            vector<point4>& globalpoints,
            vector<color4>& globalcolors,
            vector<norm4>& globalnormals, 
            GLint nmodel_view ,int nInitial_Point
        );
        void draw();
        inline float getsize(){return spacesize;}
    private:
        cube*cubes[4];
        float spacesize = 3;

};

#endif