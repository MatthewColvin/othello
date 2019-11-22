#include "piece.h"

Piece::Piece(
    vector<point4>& globalpoints,
    vector<color4>& globalcolors,
    vector<norm4>& globalnormals, 
    GLint nmodel_view ,int nInitial_Point
):object(globalpoints,globalcolors,globalnormals){
    spheres[0] = new sphere(
        globalpoints,globalcolors,globalnormals,
        vec4(1,1,1,0),nmodel_view,nInitial_Point); 

    spheres[1] = new sphere(
        globalpoints,globalcolors,globalnormals,
        vec4(0,0,0,1),nmodel_view,nInitial_Point+spheres[0]->NumVerts());
}

void Piece::draw(){
    
    mat4 squishedmv = Angel::Scale(scalefactor) * mat4();
    spheres[0]->set_mv(squishedmv);
    spheres[0]->draw();
    
    spheres[1]->set_mv(
        spheres[0]->get_mv()*Angel::Translate(0,.2,0) * squishedmv 
    );

    spheres[1]->draw();
}