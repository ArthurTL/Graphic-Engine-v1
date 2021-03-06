#version 400 core

in vec3 position;
in vec2 vtextureCoords;
in vec3 normals;

out vec2 ftextureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector[5];
out vec3 toCameraVector;
out float visibility;
out vec4 shadowCoords;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition[5];
uniform vec4 plane;
uniform mat4 toShadowMapSpace;

const float density = 0.0025;
const float gradient = 1.5;
const float shadowDistance = 170.0;
const float transitionDistance = 15.0;

void main(void){
	
	
	vec4 worldPosition = transformationMatrix*vec4(position,1.0);
	shadowCoords = toShadowMapSpace * worldPosition;
	shadowCoords = shadowCoords*0.5+0.5;
	vec4 positionRelativeToCam= viewMatrix*worldPosition;
	gl_ClipDistance[0] = dot(worldPosition,plane);
	gl_Position= projectionMatrix*positionRelativeToCam;
	ftextureCoords=vtextureCoords;

	surfaceNormal = (transformationMatrix* vec4(normals,0.0)).xyz;
	for(int i=0; i<5; i++){
		toLightVector[i] = lightPosition[i] - worldPosition.xyz;
	}
	toCameraVector = (inverse(viewMatrix) * vec4(0.0,0.0,0.0,1.0)).xyz - worldPosition.xyz;

	float dist = length(positionRelativeToCam.xyz);
	visibility = exp(-pow((dist*density),gradient));
	visibility = clamp(visibility,0.0,1.0);

	dist = dist - (shadowDistance - transitionDistance);
	dist = dist/transitionDistance;
	shadowCoords.w = clamp(1.0-dist,0.0,1.0);
}