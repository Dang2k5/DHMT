#pragma once

#include "openGL.h"

namespace engine
{
	struct shader
	{
		GLuint model_loc;
		GLuint view_loc;
		GLuint projection_loc;

		GLuint program;

		void initShader(const char* vShaderName, const char* fShaderName)
		{
			program = InitShader(vShaderName, fShaderName);

			model_loc = glGetUniformLocation(program, "model");
			view_loc = glGetUniformLocation(program, "view");
			projection_loc = glGetUniformLocation(program, "projection");
		}
	};

	extern shader defaultShader;
	extern shader emissionShader;


	void initDefaultShaders();
}