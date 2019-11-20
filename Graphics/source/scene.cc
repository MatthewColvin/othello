#include <Angel.h>
#include "cube.h"
#include "cube_door.h"
#include "sphere.h"
#include "camera.h"
#include "scene.h"

  vector<color4> cubewallcolors1 {
    vec4(1,0,0,1), 
    vec4(0,1,0,1), 
    vec4(0,0,1,1), 
    vec4(1,1,0,1), 
    vec4(1,0,1,1), 
    vec4(0,1,1,1)
  };
  vector<color4> cubewallcolors2{
    vec4(0.5,0.5,0,1), 
    vec4(0,0.5,0,1),
    vec4(0,0,0.5,1),
    vec4(0.5,0.5,0,1), 
    vec4(0.5,0,0.5,1), 
    vec4(0,0.5,0.5,1)
  };
  vector< vector<color4> > cubecolors{cubewallcolors1,cubewallcolors2};

//----------------------------------------------------------------------------
// OpenGL initialization
void Scene::init(){
  // Create a vertex array object
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  // Create and initialize a buffer object
  GLuint buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);

  // Load shaders and use the resulting shader program
  GLuint program = InitShader("./Graphics/shaders/vshader41.glsl", "./Graphics/shaders/fshader41.glsl");
  glUseProgram(program);
  
  model_view_loc = glGetUniformLocation(program, "model_view");
  camera_view_loc = glGetUniformLocation(program, "camera_view");
  projection_loc = glGetUniformLocation(program, "projection");
  shade_loc = glGetUniformLocation(program, "shade");
  
  for (int i=0; i<6; i++){
    rooms.push_back(new cube_door(
    AllVertices,
    AllColors,
    cubecolors[i%2],
    model_view_loc,
    AllVertices.size()));
  }

  // Now send the data to the GPU
  // set up vertex arrays
  GLuint vPosition = glGetAttribLocation(program, "vPosition");
  glEnableVertexAttribArray(vPosition);
  glVertexAttribPointer(
    vPosition, 
    4, 
    GL_FLOAT, 
    GL_FALSE, 
    0,
		BUFFER_OFFSET(0)
  );


  GLuint vColor = glGetAttribLocation(program, "vColor"); 
  glEnableVertexAttribArray(vColor);
  glVertexAttribPointer(
    vColor, 
    4, 
    GL_FLOAT, 
    GL_FALSE, 
    0,
		BUFFER_OFFSET(AllVertices.size()*sizeof(vec4))
  );
  


  glBufferData(
    GL_ARRAY_BUFFER, 
    AllVertices.size()*sizeof(vec4) + AllColors.size()*sizeof(vec4),
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

  
  glEnable(GL_DEPTH_TEST);
  glClearColor(1.0, 1.0, 1.0, 1.0); 
}

//----------------------------------------------------------------------------