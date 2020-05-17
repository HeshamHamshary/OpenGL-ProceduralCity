#version 150
uniform mat4 projection;
uniform mat4 view;
uniform mat4 world;
in vec4 a_position;
in vec3 a_normal;

out vec4 v_color;
out vec4 v_normal;

void main()
{
    gl_Position = projection * view * world * a_position;
	v_color = vec4(0.8,0.4,0.4,1.0);
    v_normal = world * vec4(a_normal, 0.0);
}
