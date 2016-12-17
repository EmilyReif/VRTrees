#version 330 core

in vec2 uv;
uniform mat4 view, projection;



// Attenuation Properties.
const float attQuadratic = 0.0;
const float attLinear = 0.0;
const float attConstant = 1.0;

// Material properties.
const vec3 color = vec3(1.0, 1.0, 1.0);
const float ambientIntensity = 0.2;
const float shininess = 100;
const vec3 ambColor = vec3(1, 1, 1);
//const vec3 diffuseColor = vec3(0.4, 1.0, 1.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);

// General scene properties (last val is dropoff).
// Also some light properties.
const vec4 fog =  vec4(0.4, 0.4, 0.5, 1.0);
const vec4 sunPosWorld = vec4(-5, 0.4, -5, 1);
const vec4 sunColor = vec4(1.0, 0.9, 0.7, 0.0);
const float lightIntensity = 1.0;


uniform sampler2D NormalAndDiffuse;
uniform sampler2D PosAndSpec;
uniform sampler2D Noise;

out vec4 fragColor;

vec3 unpack(vec3 v) {
    if (length(v) > 0){
        return v*vec3(2.0) - vec3(1.0);
    } else {
        return v;
    }
}

float generateNoise(vec2 p) {
    vec4 t = texture(Noise, p/0.25);
    t += texture(Noise, p);
    t += texture(Noise, p/6.0);
    return t.x;

}

void main(){

    // Aspect Ratio.
    float aspect = projection[0][0]/projection[1][1];
    vec2 newUV = uv;
    newUV.y *= aspect;

    // Calculate sun info
    vec4 sunPosScreen = projection * view * sunPosWorld;
    sunPosScreen /= sunPosScreen.w;
    vec2 sunPos = (sunPosScreen.xy + 1)/ 2.0;
    if (sunPosScreen.z > 1) {
        sunPos = vec2(100, 100);
    }

    // Extract values of position, normal, diffuse, and spec.
    vec4 p = texture(PosAndSpec, uv);
    vec4 pos = vec4(p.xyz, 1.0);
    float specularIntensity = p.w;
    p = texture(NormalAndDiffuse, uv);
    vec4 norm = vec4(normalize(unpack(p.xyz)), 0.0);
    float diffuseID = p.w;

    // Calculate lighting information.
    vec4 L = normalize(sunPosWorld - pos);

    // Typical diffuse calculations, nothing to see here (NB: all in worldspace).
    float diffuseComponent = clamp(dot(norm, L), 0.0, 1.0);
    vec4 camPos = inverse(view) * vec4(0.0, 0.0, 0.0, 1.0);
    vec4 eye = normalize(pos - camPos);

    // Add in some light attenuation...
    float d = length(sunPosWorld - pos);
    float attFn = (attConstant + attLinear * d + attQuadratic * d*d);
//    vec4 spec = specComponent* vec4(specColor, 1.0);

    // Overall fog texture depends on screen position.
    float fogTexture = texture(Noise, vec2(uv.x*0.5, uv.y)).y/2.0;

    // If we are on the tree, add ambient.
    if (diffuseID > 0) {

        // Add noise
        vec4 balancedNoise = vec4(
                                generateNoise(pos.xy)*abs(norm.z) +
                                generateNoise(pos.xz)* abs(norm.y) +
                                generateNoise(pos.yz)*abs(norm.x));

        vec4 diffValue = vec4(0.45 * diffuseID, 0.35 * diffuseID, 0.26 * (1 - diffuseID), 1.0) * balancedNoise/2 + 0.5;
        vec4 diff = diffValue * diffuseComponent * min(lightIntensity / attFn, 1);

        vec4 ambient = diffValue/3 * min(lightIntensity / attFn, 1);
        fragColor = sunColor * diff + vec4(ambColor, 1.0) * ambient;

        // Add snow.
        float snow = dot(norm, normalize(vec4(0, 1.0, 0, 0)));
        snow = clamp(pow(snow + 0.2, 15), 0, 1);
//        fragColor += snow;

        // Add fog.
        float fogMix = clamp(pow(max((length(pos - camPos) - 3), 0) * fog.w, 0.7) - .6 + fogTexture, 0, 1);
        fragColor = mix(fragColor, fog, fogMix);

        // Add sun.
        float sunPow = clamp(pow(length(newUV - sunPos), 0.2) * 1.3, 0, 1);
        fragColor = mix(sunColor, fragColor, sunPow);

    } else {
        fragColor = fog;
        float sunPow = clamp(pow(length(newUV - sunPos) - 0.015, 0.2) * 1.3 + fogTexture/7, 0, 1);
        fragColor = mix(sunColor, fragColor, sunPow);
    }


}
