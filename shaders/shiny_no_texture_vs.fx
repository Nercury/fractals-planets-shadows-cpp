#version 120

varying vec4 color;

#define MAX_LIGHTS 3
varying vec3[MAX_LIGHTS] vertex_to_light_vector;
varying vec3 normal;

void main(void)
{
	gl_TexCoord[0] = gl_MultiTexCoord0;

	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	color = gl_Color;
	normal = normalize(gl_NormalMatrix * gl_Normal);

	// Transforming The Vertex Position To ModelView-Space
	vec4 vertex_in_modelview_space = gl_ModelViewMatrix * gl_Vertex;

	for (int i=0;i<MAX_LIGHTS;i++)
   	{
		vertex_to_light_vector[i] = vec3(gl_LightSource[i].position - vertex_in_modelview_space);
	}
}