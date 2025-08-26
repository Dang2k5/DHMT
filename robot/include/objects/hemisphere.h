#pragma once

#include "core/openGL.h"
#include "core/shaders.h"

void initHemisphereCylinder();

void drawHemisphereCylinder(const vec3& position, const vec3& rotation, const vec3& scale,
	const color& mainColor,
	engine::shader shader = engine::defaultShader);

mat4 HemispherecylinderTransformMatrix(mat4 matrix);

mat4 HemispherecylinderTransform(const vec3& position, const vec3& rotation, const vec3& scale);

void HemispherecylinderReset();



