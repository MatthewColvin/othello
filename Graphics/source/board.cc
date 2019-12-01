#include "board.h"

Board::Board(
            vector<point4>& globalpoints,
            vector<color4>& globalcolors,
            vector<norm4>& globalnormals, 
            GLint nmodel_view ,int nInitial_Point
):object(globalpoints,globalcolors,globalnormals){
    vector<color4> boardsCubeColors(6,boardcolor);
    int nextstartpointinvao = nInitial_Point;
    for (int i = 0 ; i<=18 ; i++ ){
        cubes.push_back(
            new cube(globalpoints,globalcolors,boardsCubeColors,nmodel_view,nextstartpointinvao)
        );
        nextstartpointinvao += cubes[i]->GetNumVerts();
    }
}

void Board::draw(){
    float SIZEBETWEEN = 20;
    float distfrommiddle = 0;
    for (auto cube : cubes){
        cube->set_mv(
          get_mv()*Angel::Translate(0,0,distfrommiddle)
        );
        distfrommiddle+=SIZEBETWEEN;
        cube->draw();
    }
}
