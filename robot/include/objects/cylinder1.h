#pragma once

#include "core/openGL.h"
#include "core/shaders.h"

void initCylinder1();

void drawCylinder1(const vec3& position, const vec3& rotation, const vec3& scale,
	const color& mainColor,
	engine::shader shader = engine::defaultShader);

mat4 cylinder1TransformMatrix(mat4 matrix);

mat4 cylinder1Transform(const vec3& position, const vec3& rotation, const vec3& scale);

void cylinder1Reset();