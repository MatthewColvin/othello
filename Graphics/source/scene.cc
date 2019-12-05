#include <Angel.h>
#include "cube.h"
#include "cube_door.h"
#include "sphere.h"
#include "camera.h"
#include "scene.h"
#include "shader.h"
#include "piece.h"

void Scene::init(){
  // Create a vertex array object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  // Create and initialize a buffer object
  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);

  string fshaderpath = "./Graphics/shaders/fshader41.glsl";
  string vshaderpath = "./Graphics/shaders/vshader41.glsl";

  shader.init(fshaderpath,vshaderpath);
  
  board = new Board(
    AllVertices,AllColors,AllNormals,
    shader.modelViewMatrix(),AllVertices.size()
  );


  for(int i = 0; i < 64; i++){
    pieces.push_back(new Piece(
      AllVertices,AllColors,AllNormals,
      shader.modelViewMatrix(),AllVertices.size())
    );
  }
 
  // Now send the data to the GPU
    glEnableVertexAttribArray(shader.VertPosition());
    glVertexAttribPointer(
      shader.VertPosition(), 
      4, 
      GL_FLOAT, 
      GL_FALSE, 
      0,
      BUFFER_OFFSET(0)
    );
    glEnableVertexAttribArray(shader.VertColor());
    glVertexAttribPointer(
      shader.VertColor(), 
      4, 
      GL_FLOAT, 
      GL_FALSE, 
      0,
      BUFFER_OFFSET(AllVertices.size()*sizeof(vec4))
    );
    glEnableVertexAttribArray(shader.VertNormal());
    glVertexAttribPointer(
      shader.VertNormal(), 
      4, 
      GL_FLOAT, 
      GL_FALSE, 
      0,
      BUFFER_OFFSET(AllVertices.size()*sizeof(vec4) + AllColors.size()*sizeof(vec4))
    );
    
    glBufferData(
      GL_ARRAY_BUFFER, 
      AllVertices.size()*sizeof(vec4) + AllColors.size()*sizeof(vec4) + AllNormals.size()*sizeof(vec4),
      NULL,
      GL_STATIC_DRAW
    );
    glBufferSubData(
      GL_ARRAY_BUFFER,
      0, 
      AllVertices.size()*sizeof(vec4), AllVertices[0]
    );
    glBufferSubData(
      GL_ARRAY_BUFFER, 
      AllVertices.size()*sizeof(vec4), 
      AllColors.size()*sizeof(vec4), 
      AllColors[0]
    );
    glBufferSubData(
      GL_ARRAY_BUFFER, 
      AllVertices.size()*sizeof(vec4)+ AllColors.size()*sizeof(vec4), 
      AllNormals.size()*sizeof(vec4),
      AllNormals[0]
    );
  //
  
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.4,0.4,0.4, 1.0); 
}
void Scene::draw(){
  //send Camera matrix to gpu
  mat4 cv = camera.generate_view_matrix();
  shader.setcameraViewMatrix(cv);
  
  shader.setlighting(
    camera.get_eye(),
    vec4(0,10,0,0),
    vec4(1,1,1,1),
    0.5,0.5
  );
  
  shader.Shade(true);
  for (auto piece : pieces){
    piece->draw();
  }

  board->draw();
}
void Scene::update(int timefactor){
  for (auto p : pieces){
    p->update(.15,.04);
    //p->updatewithtime(timefactor);
  }
}

void Scene::display_status(bool printTerminalBoard){
  if (printTerminalBoard){
    othello::display_status();// call base class 
  } 
  draw();
}

void Scene::restart(){
  othello::restart();
  
}

void Scene::initailpeiceplacement(){
  
}

vec3 Scene::othelloStrMvToPostition(string move){
  	int coloum, row; // colums are numbers //rows are letters
		//row and coloum will represent the actual array indeces
		if (isalpha(move[0])) { row = toupper(move[0]);     row -= 65;}
		if (isdigit(move[0])) { coloum = move[0];          coloum -= 49;}
		if (isalpha(move[1])) { row = toupper(move[1]);     row -= 65;}
		if (isdigit(move[1])) { coloum = move[1];           coloum -= 49;}

    return(vec3(row,coloum,0));
}

void Scene::updatetonewboard(){};
void Scene::animateupdatetonewboard(){};


