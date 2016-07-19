#version 120

uniform sampler2D texture;

varying vec3 normal;
varying vec3 vertex_to_light_vector;

void main(void)
{
	const float light_far = 1000.0;
	const vec4 AmbientColor = vec4(0.01, 0.01, 0.01, 1.0);
	vec4 DiffuseColor = texture2D(texture, vec2(gl_TexCoord[0])) * gl_LightSource[0].diffuse;
	vec3 normalized_normal = normalize(normal);
	float DiffuseTerm = clamp(dot(normalized_normal, normalize(vertex_to_light_vector)), 0.0, 1.0) 
		* clamp((1.0 - log(length(vertex_to_light_vector) / light_far)), 0.0, 1.0);
	gl_FragColor = AmbientColor + DiffuseColor * DiffuseTerm;
}