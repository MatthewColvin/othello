attribute  vec4 vPosition;
attribute  vec4 vColor;
attribute  vec4 vNormal;
varying vec4 color;

uniform mat4 model_view;
uniform mat4 camera_view;
uniform mat4 projection;
uniform bool shade;


void main() 
{
  vec4 ambiant= vec4(1,1,1,1);
  vec4 lightposition = vec4(0.0,0.8,0.0,1);
  vec4 lightvector = normalize(lightposition);

  gl_Position = projection*camera_view*model_view*vPosition;
  if (shade) {
    color = ambiant * vColor * dot(lightvector,vNormal);
  }else {
    color = vColor;
  }
}
