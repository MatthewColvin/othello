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

#include <stdio.h>
#include <pthread.h>

#include "othello.h"

using std::string;
// struct shapedata{
// 	vector<point4> AllVertices;
// 	vector<color4> AllColors;
// 	vector<norm4> AllNormals;
// };

class Scene : private main_savitch_14::othello{
	public:
		void init();
		void draw();
		void update(int elapsedtime);
		
		
		// Old othello class functions
			void display_status(bool printTerminalBoard);
			void make_move();
			void restart();
				void initailpeiceplacement();
				void animateToinitialplacement();
		//

		Camera camera;
			inline void setAspect(GLfloat aspectRatio){camera.setAspect(aspectRatio);}
		// 
		Shader shader;
		vector<Piece*> pieces;
		Board *board;


		Piece* currentpiece();

		void translatepiecetonextlegalpostition();
		void translatepiecetopreviouslegalpostion();

	private:
		vector<point4> AllVertices;
		vector<color4> AllColors;
		vector<norm4> AllNormals;
		unsigned int lasttime=0; // gets updated everytime update is called
		//piece movement 
			void updatetonewboard();
			void animateupdatetonewboard();
			long unsigned int curwhitepieceindex;
			long unsigned int curblackpieceindex;
			long unsigned int currentpieceindex;
			
			long unsigned int currentmoveindex;
			std::vector<string> currentlegalmoves();
			std::vector<string> legalmoves;
			void setupnextpiece();
			void computermoveifneeded();
			int timesincelastmove;
			
			
};