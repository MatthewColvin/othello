#include <Angel.h>
#include "cube.h"
#include "cube_door.h"
#include "sphere.h"
#include "camera.h"
#include "shader.h"
#include "piece.h"
#include "board.h"

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
		void update(int timefactor);
		void display_status(bool printTerminalBoard);
		
		vec3 othelloStrMvToPostition(string move);
		void restart();
			void initailpeiceplacement();
		//

		Camera camera;
			inline void setAspect(GLfloat aspectRatio){camera.setAspect(aspectRatio);}
		// 

		Shader shader;

		vector<Piece*> pieces;

		Board *board;


	private:
		vector<point4> AllVertices;
		vector<color4> AllColors;
		vector<norm4> AllNormals;
		//piece movement 
			void updatetonewboard();
			void animateupdatetonewboard();

	
};