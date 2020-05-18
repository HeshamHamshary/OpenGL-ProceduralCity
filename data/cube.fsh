#version 150
in vec4 v_color;
in vec4 v_normal;
out vec4 PixelColor;

const vec3 LIGHT_DIR = vec3(0.0,0.707,0.707);
void main()
{
    // PixelColor = vec4(v_normal,1.0);
    PixelColor = v_color * max(0, dot(v_normal.xyz, LIGHT_DIR));
}


