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
            vec4(0,0,0,1),nmodel_view,nInitial_Point+spheres[0]->GetNumVerts());
}
void Piece::draw(){
    // Everything is drawn in relation to the Piece modelview
    
    spheres[0]->set_mv(
        get_mv() * Angel::Scale(scalefactor));
    spheres[0]->draw();
    
    vec3 sphere1scalefactor = vec3(scalefactor.x,scalefactor.y *1.1,scalefactor.z);  
    spheres[1]->set_mv(
        get_mv() * Angel::Translate(0,.05,0) * Angel::Scale(sphere1scalefactor)  
    );
    spheres[1]->draw();
}

// movement and placement ///////////////
    void Piece::rotatetoblack(){
        set_goal_orientation(vec3(0,0,0));
    }
    void Piece::settoblack(){
        set_goal_orientation(vec3(0,0,0));
        set_orientation(vec3(0,0,0));
    }

    void Piece::rotatetowhite(){
        set_goal_orientation(179.5,0,0);
    }
    void Piece::settowhite(){
        set_goal_orientation(vec3(179.5,0,0));
        set_orientation(vec3(179.5,0,0));
    }

    void Piece::setpostiton(string othelloStrmove,bool placed){
        vec2 newpostion = othelloStrMvToPostition(othelloStrmove);
        float x,y,z = 0;
        x = newpostion.x * 3;
        z = newpostion.y * 3;
        if(placed){
            posOnboard = newpostion;
            y=0;
        }else{
            y=1;
        }
        set_position(z,y,x);
    } 
    void Piece::translatetopostion(string othelloStrmove,bool placed){
        vec2 newpostion = othelloStrMvToPostition(othelloStrmove);
        float x,y,z = 0;
        x = newpostion.x * 3;
        z = newpostion.y * 3;
        if(placed){
            posOnboard = newpostion;
            y=0;
        }else{
            y=1;
        }
        set_goal_position(vec3(z,y,x));
    }
/////////////////////////////////////////

vec2 Piece::othelloStrMvToPostition(string move){
  	int coloum, row; // colums are numbers //rows are letters
		//row and coloum will represent the actual array indeces
		if (isalpha(move[0])) { row = toupper(move[0]);     row -= 65;}
		if (isdigit(move[0])) { coloum = move[0];          coloum -= 49;}
		if (isalpha(move[1])) { row = toupper(move[1]);     row -= 65;}
		if (isdigit(move[1])) { coloum = move[1];           coloum -= 49;}

    return(vec2(row,coloum));
}