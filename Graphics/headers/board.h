#ifndef BOARD_H
#define BOARD_H
#include "cube.h"

class Board : public object{
    public:
        Board(
            vector<point4>& globalpoints,
            vector<color4>& globalcolors,
            vector<norm4>& globalnormals, 
            GLint nmodel_view ,int nInitial_Point
        );
        
        void draw();

    private:
        vector<cube*> cubes; // 18 cubes that will make up the boards shape
        float length, width, depth; 
        color4 boardcolor = color4(120, 88, 25,0);

};

#endif 





