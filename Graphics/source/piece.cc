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
    // Everything is drawn in relation to the Piece modelview
    spheres[0]->set_mv(
        mv * Angel::Scale(scalefactor));
    spheres[0]->draw();
    
    vec3 sphere1scalefactor = vec3(scalefactor.x,scalefactor.y *1.1,scalefactor.z);  
    spheres[1]->set_mv(
        mv * Angel::Translate(0,.05,0) * Angel::Scale(sphere1scalefactor)  
    );
    spheres[1]->draw();
}