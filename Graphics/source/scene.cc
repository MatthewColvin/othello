#include <Angel.h>
#include "cube.h"
#include "cube_door.h"
#include "sphere.h"
#include "camera.h"
#include "scene.h"
#include "shader.h"
#include "piece.h"
#include <unistd.h>
#include <queue>

#include <stdio.h>


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

  restart();

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
void Scene::update(int time){
  float timefactor = time - lasttime;  

  for (auto p : pieces){
    //p->update(.15,.04);
    p->updatewithtime(timefactor*2);
  }

  timesincelastmove += timefactor/1000;
  if (timesincelastmove > rand() % 2 + 2.5 ){computermoveifneeded();}
  

  
  messagequeue.front().displaytimeleft -= timefactor/1000;  
  glutSetWindowTitle(messagequeue.front().message.c_str());
  if(messagequeue.size() > 1 && messagequeue.front().displaytimeleft < 0){
    messagequeue.pop();
  }
  
  lasttime = time;
}


void Scene::display_status(bool printTerminalBoard){
  if (printTerminalBoard){
    othello::display_status();// call base class 
  } 
  draw();
}

void Scene::restart(){
  othello::restart();
  for(auto piece : pieces){
    piece->reset(); // unlinks coordinats from grapical piece
  }
  display_message("Welcome to Othello",7);
  display_message("Use WASD to move around things around",5);
  display_message("Your move use left and right arrows", 2);
  animateToinitialplacement();
  animateupdatetonewboard();
  legalmoves = currentlegalmoves();
}

void Scene::initailpeiceplacement(){
  static int x,y,z =0;
  pieces[0]->setposition("e4",true);pieces[0]->settoblack();
  pieces[1]->setposition("d4",true);pieces[1]->settowhite();
  pieces[2]->setposition("d5",true);pieces[2]->settoblack();
  pieces[3]->setposition("e5",true);pieces[3]->settowhite();

  curblackpieceindex = 4; 
  y = 5;
  for (long unsigned int i=4; i<pieces.size(); i++){
    if(i < ((pieces.size()-4)/2 + 4)){
      z += board->spacesize();
      x = board->spacesize()*-1;
      if(i%8 == 0){ z=0; y -= 1;}  
      pieces[i]->set_position(x,y,z);
    }else{
      if(i == 34){y = 5; currentpieceindex = curwhitepieceindex = i;}
      z += board->spacesize();
      x = board->spacesize()*8;
      if(i%8 == 0){ z=0; y -= 1;}  
      pieces[i]->set_position(x,y,z);
      pieces[i]->settowhite();
    }
  }
}
void Scene::animateToinitialplacement(){
  static int x,y,z =0;
  pieces[0]->translatetopostion("e4",true);pieces[0]->rotatetoblack();
  pieces[1]->translatetopostion("d4",true);pieces[1]->rotatetowhite();
  pieces[2]->translatetopostion("d5",true);pieces[2]->rotatetoblack();
  pieces[3]->translatetopostion("e5",true);pieces[3]->rotatetowhite();

  curblackpieceindex = 4; 
  y = 5;
  for (long unsigned int i=4; i<pieces.size(); i++){
    if(i < ((pieces.size()-4)/2 + 4)){
      z += board->spacesize();
      x = board->spacesize()*-1;
      if(i%8 == 0){ z=0; y -= 1;}  
      pieces[i]->set_goal_position(x,y,z);
      pieces[i]->rotatetoblack();
    }else{
      if(i == 34){y = 5; currentpieceindex = curwhitepieceindex = i;}
      z += board->spacesize();
      x = board->spacesize()*8;
      if(i%8 == 0){ z=0; y -= 1;}  
      pieces[i]->set_goal_position(x,y,z);
      pieces[i]->rotatetowhite();
    }
  }
}
void Scene::updatetonewboard(){
  bool foundpiece = false;
  for(int row=0;row<8;row++){
    for(int col=0;col<8;col++){
      if(othello::board[row][col].is_black()){
        for(auto piece : pieces){
          vec2 currentloc = piece->boardposition();
          if(currentloc.x == row && currentloc.y == col){
            piece->settoblack();
            foundpiece = true;
          }
        }
      }
      else if(othello::board[row][col].is_white()){
        for(auto piece : pieces){
          vec2 currentloc = piece->boardposition();
          if(currentloc.x == row && currentloc.y == col){
            piece->settowhite();
            foundpiece = true;
          }
        }
      }
      else if(othello::board[row][col].is_neutral()){
        foundpiece = true;
      }
      if(!foundpiece){std::cerr << "Board algorithm failed on" << row << "  " << col << std::endl;} 
    }
  }
}
void Scene::animateupdatetonewboard(){
  bool foundpiece = false;
  for(int row=0;row<8;row++){
    for(int col=0;col<8;col++){
      if(othello::board[row][col].is_black()){
        for(auto piece : pieces){
          vec2 currentloc = piece->boardposition();
          if(currentloc.x == row && currentloc.y == col){
            piece->rotatetoblack();
            foundpiece = true;
          }
        }
      }
      else if(othello::board[row][col].is_white()){
        for(auto piece : pieces){
          vec2 currentloc = piece->boardposition();
          if(currentloc.x == row && currentloc.y == col){
            piece->rotatetowhite();
            foundpiece = true;
          }
        }
      }
      else if(othello::board[row][col].is_neutral()){
        foundpiece = true;
      }
      if(!foundpiece){std::cerr << "Board algorithm failed on" << row << "  " << col << std::endl;} 
    }
  }
}
bool Scene::dohavemove(){
  if(legalmoves[0] == "****"){return false;} 
  return true;
}

void Scene::make_move(){
  if(is_game_over()){
    switch(winning()){
      case COMPUTER: display_message("Black wins Press R to replay"); break;
      case HUMAN: display_message("You win Press R to replay");    break;
      case NEUTRAL: display_message("'Twas a draw better press R");  break;
    }
  }else{
    if (last_mover() == COMPUTER){
      othello::make_move(legalmoves[currentmoveindex]);
      if(dohavemove()){
        currentpiece()->translatetopostion(legalmoves[currentmoveindex],true);
        legalmoves = currentlegalmoves();
        setupnextpiece();
        animateupdatetonewboard();
        display_message("Black's move",2);
      }else{
        display_message("Black has no move" , 10);
      }
    }
    else{
      string nextmove = othello::get_computer_move();
      othello::make_move(nextmove); 
      if(dohavemove()){
        currentpiece()->translatetopostion(nextmove,true);
          legalmoves = currentlegalmoves();
          setupnextpiece();
          animateupdatetonewboard();
          display_message("Your move use left and right arrows",2);
      }else{
        display_message("You have no move" , 5);
      }
    }              
    timesincelastmove = 0;
  }
}

void Scene::setupnextpiece(){
  if(currentpieceindex == curwhitepieceindex){
    currentpieceindex = curblackpieceindex;
    curwhitepieceindex ++;
  }else if(currentpieceindex == curblackpieceindex){
    currentpieceindex = curwhitepieceindex;
    curblackpieceindex++;
  }
}

Piece* Scene::currentpiece(){
  return pieces[currentpieceindex];
}
std::vector<string> Scene::currentlegalmoves(){ 
  std::queue<string> legalmoves;
  compute_moves(legalmoves); 
  std::vector<string> legalmovesvec;
  while(!legalmoves.empty()){
    legalmovesvec.push_back(legalmoves.front());
    legalmoves.pop();
  }
  return legalmovesvec;
}

void Scene::translatepiecetonextlegalpostition(){
  if(!dohavemove()){// speical key that means pass
    display_message("Sorry You have no legal moves", 2);
    currentmoveindex = 0;
    make_move();
  }else{
    currentmoveindex++;
    if(currentmoveindex >= legalmoves.size() ){
      currentmoveindex %= legalmoves.size();
    }else if(currentmoveindex < 0 ){ 
      currentmoveindex *= -1;
      currentmoveindex %= legalmoves.size();
    }
    string nextmove = legalmoves[currentmoveindex];
    currentpiece()->translatetopostion(nextmove,false);
  }
}
void Scene::translatepiecetopreviouslegalpostion(){
  if(!dohavemove()){ // speical key that means pass
    display_message("Sorry You have no legal moves", 2);
    currentmoveindex = 0; 
    make_move();
  }else{
    currentmoveindex--;
    if(currentmoveindex > legalmoves.size() ){
      currentmoveindex %= legalmoves.size();
    }else if(currentmoveindex < 0 ){ 
      currentmoveindex *= -1;
      currentmoveindex %= legalmoves.size();
    } 
    string nextmove = legalmoves[currentmoveindex];
    currentpiece()->translatetopostion(nextmove,false);
  }
}
void Scene::computermoveifneeded(){
  if(last_mover() == HUMAN){
    Scene::make_move();
  }
}
void Scene::display_message(std::string newtitle ,float timetodisplay ) {
  gamemessage nextmessage(newtitle,timetodisplay);
  messagequeue.push(nextmessage);
}
void Scene::display_message(std::string newtitle) {
  while(!messagequeue.empty()) messagequeue.pop(); // empty message queue
  gamemessage onlymessage(newtitle,1);
  messagequeue.push(onlymessage);
}
