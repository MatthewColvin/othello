#include "board.h"

Board::Board(
            vector<point4>& globalpoints,
            vector<color4>& globalcolors,
            vector<norm4>& globalnormals, 
            GLint nmodel_view ,int nInitial_Point
):object(globalpoints,globalcolors,globalnormals){
    int spacestartinvao = nInitial_Point;
    spaces.resize(8);
    for(int i=0; i<8; i++){ 
        spaces[i].resize(8);
        for(int j=0; j<8; j++){
            spaces[i][j] = (new Space(
                globalpoints,globalcolors,globalnormals,
                nmodel_view,spacestartinvao)
            );
        spacestartinvao += spaces[i][j]->GetNumVerts();
        }
    }
    NumVertices = spacestartinvao + nInitial_Point; // total number of verts to draw a board
}

void Board::draw(){
    float amnt = spaces[0][0]->getsize();
    for(int i=0; i<8; i++){ 
        for(int j=0; j<8; j++){
            spaces[i][j]->set_mv(
                get_mv() * Angel::Translate(j * amnt,0,i * amnt)
            );
            spaces[i][j]->draw();
        }
    }
}


