#version 300 es
precision mediump float;
in vec2 texCoord;
uniform sampler2D ourTexture;
out vec4 FragColor;
void main()
{
    vec4 tex = texture(ourTexture, texCoord);
    FragColor = vec4(tex.x, tex.y, tex.z, 1.0);
    // FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}

