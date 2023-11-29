uniform vec2 u_resolution;

float random (vec2 st) {
    return fract(sin(dot(st.xy, vec2(12.9898,78.233)))*43758.5453123);
}

float rectshape(vec2 position, vec2 scale){
    // float rand_x = random(position)
    // float rand_y = random(position)

    scale = vec2(0.5) - scale * 0.5;
    vec2 shaper = vec2(step(scale.x, position.x), step(scale.y, position.y));
    shaper = vec2(step(scale.x, 1.0 - position.x), step(scale.y, 1.0 - position.y));
    return shaper.x shaper.y;
}

void main(){
    vec2 position = gl_FragCoord.xy / u_resolution;
    float rand_w = random(position)
    float rand_h = random(position)

    vec3 color = vec3(0.0);

    float rectangle = rectshape(position, vec2(rand_w, rand_h));

    color = vec3(rectangle);

    gl_FragColor = vec4(color, 1.0);
}