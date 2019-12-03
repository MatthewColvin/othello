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

class Scene : public main_savitch_14::othello{
	public:
		void init();
		void draw();
		void update(int timefactor);


		// For perspective camera
		GLfloat fovy=45;
		GLfloat aspect=1.0;
		GLfloat angle = 0.0;

		// Camera and view parameters
		GLfloat zNear = 0.1;
		GLfloat zFar = 300.0;		

		Camera camera;
		Shader shader;

		vector<Piece*> pieces;
		Board *board;



	private:
		vector<point4> AllVertices;
		vector<color4> AllColors;
		vector<norm4> AllNormals;
		
		


};

