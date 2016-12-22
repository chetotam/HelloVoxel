#version 450 core

in vec3 frag_Position;
in vec3 frag_Normal;
in vec2 frag_Texture;

out vec4 color;

struct Directional_Light
{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Fog
{
    vec3 color;
    float density;
};

uniform vec3 view_Position;
uniform Directional_Light dir_Light;
uniform Fog fog;

uniform sampler2D texture_diffuse1;


vec3 calc_Dir_Light(Directional_Light light, vec3 frag_Color, vec3 frag_Normal, vec3 view_Dir);
vec3 calc_Fog(Fog fog, vec3 frag_Color, float frag_Distance);


void main()
{
    vec4 default_Color = texture(texture_diffuse1, frag_Texture * 32);
    vec3 norm = normalize(frag_Normal);
    vec3 view_Dir = normalize(view_Position - frag_Position);
    float frag_Distance = length(view_Position - frag_Position);

    vec3 result = vec3(0.0, 0.0, 0.0);
    result += calc_Dir_Light(dir_Light, default_Color.xyz, norm, view_Dir);
    result = calc_Fog(fog, result, frag_Distance);
    color = vec4(result, default_Color.w);
}


vec3 calc_Dir_Light(Directional_Light light, vec3 frag_Color, vec3 frag_Normal, vec3 view_Dir)
{
    vec3 light_Dir = normalize(-light.direction);
    float diff = max(dot(frag_Normal, light_Dir), 0.0);
    vec3 reflect_Dir = reflect(-light.direction, frag_Normal);
    float spec = max(dot(view_Dir, reflect_Dir), 0.0);

    vec3 ambient = light.ambient * frag_Color;
    vec3 diffuse = light.diffuse * diff * frag_Color;
    vec3 specular = light.specular * spec * frag_Color;
    return (ambient + diffuse + specular);
}

vec3 calc_Fog(Fog fog, vec3 frag_Color, float frag_Distance)
{
    float fog_Factor = 1.0 / exp(pow(frag_Distance * fog.density, 4));
    fog_Factor = clamp(fog_Factor, 0.0, 1.0);
    vec3 result = mix(fog.color, frag_Color, fog_Factor);
    return result.xyz;
}