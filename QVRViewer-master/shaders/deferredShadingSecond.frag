#version 330 core

in vec2 uv;
uniform mat4 view;

// Light properties.
const vec4 WorldSpace_lightPos = vec4(5.0, 5.0, 5.0, 1.0); // world-space light position
const float lightIntensity = 1.0;
const vec3 lightColor = vec3(1.0, 1.0, 1.0);

// Attenuation Properties.
const float attQuadratic = 0.0;
const float attLinear = 0.0;
const float attConstant = 1.0;

// Material properties.
const vec3 color = vec3(1.0, 1.0, 1.0);
const float ambientIntensity = 0.2;
const float shininess = 100;
//const vec3 diffuseColor = vec3(0.4, 1.0, 1.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);

// General scene properties (last val is dropoff).
//const vec4 fog =  vec4(0.3, 0.3, 0.6, 0.5);
const vec4 fog =  vec4(1);

uniform sampler2D NormalAndDiffuse;
uniform sampler2D PosAndSpec;
uniform sampler2D Color;

out vec4 fragColor;

vec3 unpack(vec3 v) {
    if (length(v) > 0){
        return v*vec3(2.0) - vec3(1.0);
    } else {
        return v;
    }
}

void main(){

    // Extract values of position, normal, diffuse, and spec.
    vec4 p = texture(PosAndSpec, uv);
    vec4 pos = vec4(unpack(p.xyz), 1.0);
    float specularIntensity = p.w;
    p = texture(NormalAndDiffuse, uv);
    vec4 norm = vec4(normalize(unpack(p.xyz)), 0.0);
    float diffuseIntensity = p.w ;
    p = texture(Color, uv);
    vec3 diffuseColor = p.xyz;

    // Calculate lighting information.
    vec4 light = WorldSpace_lightPos;
    vec4 L = normalize(light - pos);

    // Typical diffuse calculations, nothing to see here (NB: all in worldspace).
    float diffuseComponent = diffuseIntensity * clamp(dot(norm, L), 0.0, 1.0);
    vec4 camPos = inverse(view) * vec4(0.0, 0.0, 0.0, 1.0);
    vec4 eye = normalize(pos - camPos);
    vec4 reflection = normalize(reflect(L, norm));
    float specComponent = specularIntensity * pow(clamp(dot(eye, reflection), 0.0, 1.0), shininess);
    fragColor = vec4(1.0)*(specComponent);

    // Add in some light attenuation...
    float d = length(light - pos);
    float attFn = (attConstant + attLinear * d + attQuadratic * d*d);
    vec4 diff = diffuseComponent * diffuseColor.xyzz;
    vec4 spec = specComponent* specColor.xyzz;
    vec4 amb = vec4(0.0);

    // If we are on the tree, add ambient.
    if (diffuseIntensity > 0) {
        amb = vec4(diffuseColor, 1.0) * 0.1;
        //    vec4 specAndDiffuse = (diff + spec + amb) * min(lightIntensity / attFn, 1);
        vec4 specAndDiffuse = (diff+ amb) * min(lightIntensity / attFn, 1);
        fragColor = vec4(color * lightColor, 1.0) * specAndDiffuse;

        // Add snow.
        float snow = dot(norm, normalize(vec4(0, 1.0, 0, 0)));
        snow = pow(snow + 0.2, 15);
//        fragColor += snow ;

        // Add fog.
        float fogMix = pow(max((length(pos - camPos) - 3), 0) * fog.w, 0.5) - .6;
        fragColor = mix(fragColor, fog, fogMix);

    } else {
        fragColor = fog;
    }
}
