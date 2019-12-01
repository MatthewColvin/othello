#include"space.h"
Space::Space(
    vector<point4>& globalpoints,
    vector<color4>& globalcolors,
    vector<norm4>& globalnormals, 
    GLint nmodel_view ,int nInitial_Point, color4 spacecolor
):object(globalpoints,globalcolors,globalnormals){
    vector<color4> spacecolors(6,spacecolor);
    int cubesStartpointinvao = nInitial_Point;
    for(int i=0; i<4; i++){
        cubes[i] = new cube(globalpoints,globalcolors,globalnormals,spacecolors,nmodel_view,cubesStartpointinvao);
        cubesStartpointinvao+=cubes[i]->GetNumVerts();
    }
    NumVertices = cubesStartpointinvao - nInitial_Point;
}
void Space::draw(){
    float framepeicelenght = spacesize;
    float framepeicewith = 0.2;
    float framepeicedepth = 0.3; 

    cubes[0]->set_mv(
        get_mv() * 
        Angel::Translate(framepeicelenght/2 - framepeicewith/2,0,0) * 
        Angel::RotateY(90) * 
        Angel::Scale(framepeicelenght,framepeicedepth,framepeicewith));
    cubes[0]->draw();
    
    cubes[1]->set_mv(
        get_mv() * 
        Angel::Translate(-framepeicelenght/2 + framepeicewith/2,0,0) * 
        Angel::RotateY(90) * 
        Angel::Scale(framepeicelenght,framepeicedepth,framepeicewith));
    cubes[1]->draw();
    
    cubes[2]->set_mv(
        get_mv() * 
        Angel::Translate(0,0,framepeicelenght/2 - framepeicewith/2) * 
        Angel::RotateY(0) * 
        Angel::Scale(framepeicelenght,framepeicedepth,framepeicewith));
    cubes[2]->draw();
    
    cubes[3]->set_mv(
        get_mv() * 
        Angel::Translate(0,0,-framepeicelenght/2 + framepeicewith/2) * 
        Angel::RotateY(0) * 
        Angel::Scale(framepeicelenght,framepeicedepth,framepeicewith));
    cubes[3]->draw();
}
    