attribute  vec4 vNormal;
attribute  vec4 vPosition;
attribute  vec4 vColor;

varying vec4 color;
varying vec4 normal;
varying vec4 fragpos;

uniform mat4 model_view;
uniform mat4 camera_view;

void main() 
{
  gl_Position = camera_view*model_view*vPosition;
  color = vColor;
  normal = vNormal;
  fragpos = model_view * vPosition;
}
