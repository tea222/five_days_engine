#extension GL_OES_standard_derivatives : enable

precision lowp float;

uniform float time;
uniform vec2 resolution;

float random(vec2 v) {
	return fract(sin(dot(v, vec2(91.4834, 45.842))) * 48.45873);
}

float noise(vec2 pos) {
	vec2 fl = floor(pos);
	vec2 fr = fract(pos);
	float a = random(fl + vec2(0.0, 0.0));
	float b = random(fl + vec2(1.0, 0.0));
	float c = random(fl + vec2(0.0, 1.0));
	float d = random(fl + vec2(1.0, 1.0));
	vec2 u;
	u.x = pow(fr.x, 2.);
	u.y = pow(fr.y, 2.);
	return mix(a, b, u.x) + (c - a) * u.y * (1.0 - u.x) + (d - b) * u.x * u.y;
}

float fbm(vec2 pos) {
	float v = 0.0;
	float a = 0.5;
	mat2 rot = mat2(cos(0.15), sin(0.15), -sin(0.25), cos(0.5));
	for (int i=0; i < 12; i++) {
		v += a * noise(pos);
		pos = rot * pos * 2.0;
		a *= 0.55;
	}
	return v;
}

void main() {
	vec2 p = (gl_FragCoord.xy - resolution);
	p=p/min(resolution.x, resolution.y);
	float f = fbm(p * 2.0 * vec2(fbm(p - (time / 24.0)), fbm(p / 2.0 - (time / 6.0))));

	vec3 c = vec3(0, 1, 0.5);
	c = f * 1.5 * c;
	gl_FragColor = vec4(c, 0.15);
}