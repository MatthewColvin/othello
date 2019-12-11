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

        inline float spacesize(){ return spaces[0][0]->getsize();}
    private:
        color4 boardcolor = color4(237.0/255.0, 168.0/255.0, 83.0/255.0,1);
        vector<vector<Space*>> spaces;
};

#endif 





