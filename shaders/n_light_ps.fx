#version 120

uniform sampler2D texture;

uniform sampler2D ShadowMap0;
uniform sampler2D ShadowMap1;
uniform sampler2D ShadowMap2;
uniform sampler2D ShadowMap3;
uniform sampler2D ShadowMap4;
uniform sampler2D ShadowMap5;

#define MAX_LIGHTS 3
#define OBJECTS 2
varying vec4[MAX_LIGHTS*OBJECTS] ShadowCoord; 
varying vec3[MAX_LIGHTS] vertex_to_light_vector;
varying vec3 normal;

void main(void)
{
	// Defining The Material Colors
	const vec4 AmbientColor = vec4(0, 0, 0, 1.0);
	vec4 final_color = vec4(0.0);

	vec4[MAX_LIGHTS*OBJECTS] shadowCoordinateWdivide;
	for (int i=0;i<MAX_LIGHTS;i++)
   	{
		shadowCoordinateWdivide[i*OBJECTS] = ShadowCoord[i*OBJECTS] / ShadowCoord[i*OBJECTS].w;
		shadowCoordinateWdivide[i*OBJECTS].z += 0.0005;
		shadowCoordinateWdivide[i*OBJECTS+1] = ShadowCoord[i*OBJECTS+1] / ShadowCoord[i*OBJECTS+1].w;
		shadowCoordinateWdivide[i*OBJECTS+1].z += 0.0005;
	}
	float[MAX_LIGHTS*OBJECTS] distanceFromLight;
	distanceFromLight[0] = texture2D(ShadowMap0,shadowCoordinateWdivide[0].st).z;
	distanceFromLight[1] = texture2D(ShadowMap1,shadowCoordinateWdivide[1].st).z;
	distanceFromLight[2] = texture2D(ShadowMap2,shadowCoordinateWdivide[2].st).z;
	distanceFromLight[3] = texture2D(ShadowMap3,shadowCoordinateWdivide[3].st).z;
	distanceFromLight[4] = texture2D(ShadowMap4,shadowCoordinateWdivide[4].st).z;
	distanceFromLight[5] = texture2D(ShadowMap5,shadowCoordinateWdivide[5].st).z;

	float diffuse_term;
	for (int i=0;i<MAX_LIGHTS;i++)
   	{
		float shadow = 1;
	 	if (ShadowCoord[i*OBJECTS].w > 0.0)
	 		shadow = distanceFromLight[i*OBJECTS] < shadowCoordinateWdivide[i*OBJECTS].z ? 0.5 : 1.0 ;
		if (ShadowCoord[i*OBJECTS+1].w > 0.0)
	 		shadow = min(shadow,distanceFromLight[i*OBJECTS+1] < shadowCoordinateWdivide[i*OBJECTS+1].z ? 0.5 : 1.0);

		float lightAngle = dot(normal, normalize(vec3(vertex_to_light_vector[i])));
		diffuse_term = clamp(lightAngle, 0.0, 1.0) 
			* 2.5 *clamp((1.0 - length(vertex_to_light_vector[i]) * gl_LightSource[i].linearAttenuation), 0.0, 1.0) * shadow;
		if (gl_LightSource[i].spotCutoff > 0)
		{
			// spotlight
			float cutOff = 1-gl_LightSource[i].spotCosCutoff;
			float fadePoint = 0.1;
			float spotAngle = dot(normalize(-gl_LightSource[i].spotDirection), normalize(vec3(vertex_to_light_vector[i])));
			float ratio = (1-spotAngle) / cutOff;
			diffuse_term = diffuse_term * 0.4;
			if (ratio < (1.0 - fadePoint))
				diffuse_term += 1.0 * clamp(lightAngle, 0.0, 1.0);
			else if (ratio > (1.0 - fadePoint) && ratio < (1.0 + fadePoint))
				diffuse_term += -(ratio - 1.0 - fadePoint) / fadePoint / 2 * clamp(lightAngle, 0.0, 1.0);
			final_color += gl_LightSource[i].diffuse * diffuse_term * (shadow - 0.6) * 2;
		}
		else
		{
			final_color += 
			gl_LightSource[i].diffuse 
			* lightAngle 
			* diffuse_term 
			* shadow
			;
		}
	}
	// Calculating The Final Color
	gl_FragColor = AmbientColor + texture2D(texture, vec2(gl_TexCoord[0])) * final_color;
}