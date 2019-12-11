uniform bool shade;
uniform vec4 lightPosition;
uniform vec4 cameraPositon;
uniform vec4 lightColor;
uniform float ambiantIntensity;
uniform float specularStrength;

varying vec4 color;
varying vec4 normal;
varying vec4 fragpos;

void main() 
{ 

    vec4 norm = normalize(normal);

    vec4 ambiant = lightColor * ambiantIntensity;

    vec4 lightvector = normalize(lightPosition - fragpos);
    float diff = max(dot(norm,lightvector),0.0);
    vec4 diffuse = diff * lightColor;

    vec4 viewvector = normalize(cameraPositon - fragpos);
    vec4 reflectvector = reflect(-lightvector,norm);
    float spec = pow(max(dot(viewvector,reflectvector),0.0),32.0);
    vec4 specular = specularStrength * spec * lightColor;

    vec4 lightingresult = (ambiant + diffuse + specular) * color;

    if(shade){
        gl_FragColor = lightingresult;
    }else{
        gl_FragColor = color;
    }
} 

