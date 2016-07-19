#version 120

uniform sampler2D texture;

#define MAX_LIGHTS 3
varying vec3[MAX_LIGHTS] vertex_to_light_vector;
varying vec3 normal;

varying vec4 color;

void main(void)
{
	// Defining The Material Colors
	const vec4 AmbientColor = vec4(0.01, 0.01, 0.01, 1.0);
	vec4 final_color = vec4(0.0);

	float diffuse_term;
	for (int i=0;i<MAX_LIGHTS;i++)
   	{
		float lightAngle = dot(normal, normalize(vec3(vertex_to_light_vector[i])));
		diffuse_term = clamp(lightAngle, 0.0, 1.0) 
			* clamp((1.0 - length(vertex_to_light_vector[i]) * gl_LightSource[i].linearAttenuation), 0.0, 1.0);
		if (gl_LightSource[i].spotCutoff > 0)
		{
			// spotlight
			float cutOff = 1-gl_LightSource[i].spotCosCutoff;
			float fadePoint = 0.1;
			float spotAngle = dot(normalize(-gl_LightSource[i].spotDirection), normalize(vec3(vertex_to_light_vector[i])));
			float ratio = (1-spotAngle) / cutOff;
			float strength = 0;
			if (ratio < (1.0 - fadePoint))
				strength = 1.0;
			else if (ratio > (1.0 - fadePoint) && ratio < (1.0 + fadePoint))
				strength = -(ratio - 1.0 - fadePoint) / fadePoint / 2;
			final_color += gl_LightSource[i].diffuse * (diffuse_term * 0.4 + strength * clamp(lightAngle, 0.0, 1.0));
		}
		else
		{
			final_color += gl_LightSource[i].diffuse * lightAngle * diffuse_term;
		}
	}
	// Calculating The Final Color
	gl_FragColor = AmbientColor + color * texture2D(texture, vec2(gl_TexCoord[0])) * final_color;
}