#version 430

uniform mat4 worldViewMat;
uniform mat4 modelWorldMat;
uniform mat4 normalMat;

in vec4 position;1
in vec2 uv;
in vec4 normal;

out vec3 Position;
out vec2 UV;
out vec3 Normal;

void main()
{
	vec4 worldPos = modelWorldMat * position;
	gl_Position = worldViewMat * worldPos;

	Position = vec3(modelWorldMat * position);
	Normal = normalize(vec3(normalMat * normal));
	UV = uv;
}