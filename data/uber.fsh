#ifdef ALBEDO_TEX
uniform sampler2D u_albedoTex;
#else
uniform vec4 u_albedo;
#endif

in vec4 v_normal;
in vec2 v_uv1;

out vec4 PixelColor;

const vec3 LIGHT_DIR = vec3(0.0,0.707,0.707);

void main()
{
    float NoL = max(0, dot(normalize(v_normal.xyz), LIGHT_DIR));
#ifdef ALBEDO_TEX
    PixelColor = texture(u_albedoTex, v_uv1) * NoL;
#else
    PixelColor = u_albedo * vec4(NoL,NoL,NoL,1);
#endif
}


