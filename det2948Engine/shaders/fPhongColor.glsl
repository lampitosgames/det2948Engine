#version 430

in vec3 fragPos;
in vec3 outNormal;

uniform vec3 camPos;
uniform vec3 lightPos;
uniform vec3 matColor;

uniform float specularMultiplier;
uniform float ambientIntensity;

void main() {
	vec3 N = normalize(outNormal);
	vec3 L = normalize(lightPos - fragPos);
	vec3 V = normalize(camPos - fragPos);
	vec3 H = normalize(V+L);
	
	float cA = ambientIntensity;
	float cD = max(dot(L, N), 0);
	float cS = pow(max(dot(H, N), 0), specularMultiplier);

	float br = cA + cD + cS;

	gl_FragColor = vec4(matColor * br, 1.0);
}