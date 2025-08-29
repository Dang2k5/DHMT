#pragma once
#include "core/openGL.h"
#include "cube.h"
#include "core/camera.h"
#include "core/lighting.h"
#include "cylinder.h"
#include "sphere.h"
#include "cylinder1.h"



void drawRobot2(const vec3 position, const vec3 rotation, const vec3 scale, bool enableInput = false);

void Robot2Keyboard(unsigned char key, int x, int y);
