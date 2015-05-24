enum class texture_target {
    t1d = underlying_value(gl::GL_TEXTURE_1D),
	t2d = underlying_value(gl::GL_TEXTURE_2D),
	t3d = underlying_value(gl::GL_TEXTURE_3D),
	t1d_array = underlying_value(gl::GL_TEXTURE_1D_ARRAY),
	t2d_array = underlying_value(gl::GL_TEXTURE_2D_ARRAY),
	trectangle = underlying_value(gl::GL_TEXTURE_RECTANGLE),
	tcube_map = underlying_value(gl::GL_TEXTURE_CUBE_MAP),
	tcube_map_array = underlying_value(gl::GL_TEXTURE_CUBE_MAP_ARRAY),
	tbuffer = underlying_value(gl::GL_TEXTURE_BUFFER),
	t2d_multisample = underlying_value(gl::GL_TEXTURE_2D_MULTISAMPLE),
	t2d_multisample_array = underlying_value(gl::GL_TEXTURE_2D_MULTISAMPLE_ARRAY)
};