#version 430

uniform vec3 camLoc;
uniform vec3 lightLoc;

uniform sampler2D myTexture;

in vec3 Position;
in vec2 UV;
in vec3 Normal;

void main()
{
	vec3 vecToLight = normalize(lightLoc - Position);

	gl_FragColor = texture(myTexture, UV) * 
		(0.1 + 
		.7 * max(dot(vecToLight, Normal), 0.0) + 
		.4 * pow(max(dot(normalize(vecToLight + normalize(camLoc - Position)), Normal), 0.0), 32.0));
}