#version 120

#define MAX_LIGHTS 3
#define OBJECTS 2
varying vec3[MAX_LIGHTS] vertex_to_light_vector;
varying vec3 normal;

varying vec4[MAX_LIGHTS * OBJECTS] ShadowCoord; 

void main(void)
{
	// Transforming The Vertex
	gl_Position = ftransform();

	gl_TexCoord[0] = gl_MultiTexCoord0;
	
	// Transforming The Normal To ModelView-Space
	normal = normalize(gl_NormalMatrix * gl_Normal);

	// Transforming The Vertex Position To ModelView-Space
	vec4 vertex_in_modelview_space = gl_ModelViewMatrix * gl_Vertex;

	for (int i=0;i<MAX_LIGHTS;i++)
   	{
		vertex_to_light_vector[i] = vec3(gl_LightSource[i].position - vertex_in_modelview_space);
	}
	ShadowCoord[0] = gl_TextureMatrix[2] * gl_Vertex;
	ShadowCoord[1] = gl_TextureMatrix[3] * gl_Vertex;
	ShadowCoord[2] = gl_TextureMatrix[4] * gl_Vertex;
	ShadowCoord[3] = gl_TextureMatrix[5] * gl_Vertex;
	ShadowCoord[4] = gl_TextureMatrix[6] * gl_Vertex;
	ShadowCoord[5] = gl_TextureMatrix[7] * gl_Vertex;
}