uniform sampler2D u_tex;
uniform vec3 u_lightDir;
uniform vec3 u_lightColor;
uniform vec3 u_ambientLight;

in vec4 v_normal;
in vec2 v_uv1;
out vec4 PixelColor;

void main()
{
    vec3 diffuseLight = u_lightColor * max(0, dot(v_normal.xyz, u_lightDir));
    vec3 diffuseMat = texture(u_tex, v_uv1).rgb;
    PixelColor.rgb = diffuseMat * (u_ambientLight + diffuseLight);
    PixelColor.a = 1.0;
}