#ifdef GL_ES
precision lowp float;
#endif

varying vec2 v_texCoord;
//uniform sampler2D u_texture;
uniform float rate;
uniform float u_opacity;
void main()
{
	vec4 color=texture2D(CC_Texture0,v_texCoord);
	color += vec4(rate,rate,rate,0);
    color *= u_opacity/255.0;
	gl_FragColor= color;
}