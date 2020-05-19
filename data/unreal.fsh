#version 150
uniform sampler2D tex;

in vec4 v_normal;
in vec2 v_uv1;

out vec4 PixelColor;

const vec3 LIGHT_DIR = vec3(0.0,0.707,0.707);

void main()
{
    PixelColor = texture(tex, v_uv1) * max(0, dot(v_normal.xyz, LIGHT_DIR));
}


