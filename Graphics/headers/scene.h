#include <Angel.h>
#include "cube.h"
#include "cube_door.h"
#include "sphere.h"
#include "camera.h"
#include "shader.h"
#include "piece.h"
#include "board.h"
#include <queue>
#include <unistd.h>

#include "othello.h"

using std::string;
// struct shapedata{
// 	vector<point4> AllVertices;
// 	vector<color4> AllColors;
// 	vector<norm4> AllNormals;
// };

struct gamemessage{
	float displaytimeleft = 5;
	std::string message;
	gamemessage(std::string message, float timetodisplay){displaytimeleft = timetodisplay;   gamemessage::message = message;}
};

class Scene : private main_savitch_14::othello{
	public:
		void init();
			void sendVertexdata();
		//
		void draw();
		void update(int elapsedtime);
		
		// Old othello class functions
			void display_message(std::string message ,float timetodisplay) ;
			void display_message(std::string newtitle) ;
			void display_status(bool printTerminalBoard);
			void make_move();
			void restart();
				void animateToinitialplacement();
		//

		Camera camera;
			inline void setAspect(GLfloat aspectRatio){camera.setAspect(aspectRatio);}
		// 
		Shader shader;
		vector<Piece*> pieces;
		Board *board;
		
		sphere* light;
			void changelightcolor(color4 newcolor);
			void changeambiantintensity(float amount);
			void changespecularintenstiy(float amount);
		//	

		Piece* currentpiece();
		// Piece movement 
			void translatepiecetonextlegalpostition();
			void translatepiecetopreviouslegalpostion();

			void changepeicestranslationspeed(float amount);
			void changpiecesrotationspeed(float amount);
		//
	private:
		vector<point4> AllVertices;
		vector<color4> AllColors;
		vector<norm4> AllNormals;

		unsigned int lastupdatetime=0; // gets updated everytime update is called
		
		// Light model 
			color4 lightcolor = color4(1,1,1,1);
			float ambiantintenstiy = 0.5;
			float specularintensity = 0.5;
		//
		// Piece movement 
			void updatetonewboard();
			void animateupdatetonewboard();
			void setupnextpiece();
			void computermoveifneeded();
			float timesincelastmove;
			float maxpiecetranslationspeed = 200;
			float minpiecetranslationspeed = 1;
			float maxpiecerotationspeed = 200;
			float minpiecerotationspeed = 1;
		//	

		long unsigned int curwhitepieceindex;
		long unsigned int curblackpieceindex;
		long unsigned int currentpieceindex;
		
		long unsigned int currentmoveindex;
		std::vector<string> currentlegalmoves();
		std::vector<string> legalmoves;
		bool dohavemove();

		std::queue<gamemessage> messagequeue;	
			
};