#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform float Time;
uniform float AngularStepOY;
uniform float Speed;

out vec2 texcoord;

void main()
{
	float sn = sin(AngularStepOY);
	float xSign = (sn == 0 ? 0 : (sn > 0 ? 1 : -1));
	texcoord = v_texture_coord;

	vec3 newPosition = v_position + vec3(xSign * Time * Speed , 0, Time * Speed);
	gl_Position = Projection * View * Model * vec4(newPosition, 1.0);
}
