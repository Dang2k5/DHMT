#include "objects/cabinet1.h"

void drawCabinet1(vec3 position, vec3 rotation, vec3 scale, bool enableInput)
{
	color color1 = color(.8, .8, .8, 1);
	color color2 = color(.5, .5, .5, 1);

	mat4 globalTransformMatrix = cubeTransform(position, rotation, scale);

	drawCube(vec3(), vec3(), vec3(1.2, .05, .5), color1);
	drawCube(vec3(0, .5, 0), vec3(), vec3(1.1, .05, .4), color2);
	drawCube(vec3(0, 1, 0), vec3(), vec3(1.1, .05, .4), color2);
	drawCube(vec3(0, 1.5, 0), vec3(), vec3(1.1, .05, .4), color2);
	drawCube(vec3(0, .8, -0.19), vec3(), vec3(1.16, 1.5, .05), color1);
	drawCube(vec3(-0.6, 0.8, 0.0), vec3(), vec3(.04, 1.5, .42), color1);
	drawCube(vec3(0.6, 0.8, 0.0), vec3(), vec3(.04, 1.5, .42), color1);




	cubeReset();
}
