#ifndef BOARD_H
#define BOARD_H
#include "space.h"
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
        color4 boardcolor = color4(120.0/255.0, 88.0/255.0, 25.0/255.0,1);
        vector<vector<Space*>> spaces;
};

#endif 





