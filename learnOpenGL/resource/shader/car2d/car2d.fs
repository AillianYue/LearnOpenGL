#version 300 es
precision mediump float;

uniform sampler2D Tex2D;

in vec2 TexCoord;
out vec4 FragColor;

void main()
{
	FragColor = texture(Tex2D, TexCoord).rgba;
}