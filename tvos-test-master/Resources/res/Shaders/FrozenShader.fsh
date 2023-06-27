#ifdef GL_ES
precision lowp float;
#endif

varying vec2 v_texCoord;
//uniform sampler2D u_texture;
uniform float blue;
void main()
{
    vec4 color=texture2D(CC_Texture0,v_texCoord);
    color *= vec4(blue,blue,blue,1);
    color.b += color.a * (1.0 - blue);
    gl_FragColor= color;
}
