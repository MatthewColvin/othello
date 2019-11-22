#ifndef cube_h
#define cube_h

#include <vector>
#include "object.h"
using std::vector;

// Vertices of a unit cube centered at origin, sides aligned with axes

class cube : public object {
  public:
    cube(
      vector<point4>& globalpoints,
      vector<color4>& globalcolors,
      vector<color4>& wallcolors,
      GLint shader_mv_loc,
      int startinvao
    );
  
  private:
    void makecolorcube(vector<vec4> wallcolors);
    void MyQuad(int a, int b, int c, int d,vec4& color);
    
    point4 vertices[8] = {
      point4(-0.5, -0.5,  0.5, 1.0),
      point4(-0.5,  0.5,  0.5, 1.0),
      point4( 0.5,  0.5,  0.5, 1.0),
      point4( 0.5, -0.5,  0.5, 1.0),
      point4(-0.5, -0.5, -0.5, 1.0),
      point4(-0.5,  0.5, -0.5, 1.0),
      point4( 0.5,  0.5, -0.5, 1.0),
      point4( 0.5, -0.5, -0.5, 1.0)
    };
};
#endif
