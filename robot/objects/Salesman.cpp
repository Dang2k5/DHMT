#include "objects/Salesman.h"

vec3 salesman_rotate(0, 0, 0), salesman_position(0, 0, 0);


void drawSalesman(vec3 position, vec3 rotation, vec3 scale, bool enableInput) {
	if (enableInput) {
		rotation += salesman_rotate;
		position += salesman_position;
	}


	mat4 globalTransformMatrix = sphereTransform(position, rotation, scale);

	color color1 = color(.2, .2, .2, 1);
	color color2 = color(.7, .7, .7, 1);

	drawSphere(vec3(.05, 0, 0), vec3(), vec3(.4, .4, .5), color(color1));

	drawSphere(vec3(.16, .0, -.11), vec3(), vec3(.15, .15, .15), color(color2));

	drawSphere(vec3(.16, .0, .11), vec3(), vec3(.15, .15, .15), color(color2));

	drawSphere(vec3(0, 0, 0), vec3(), vec3(.5, .5, .5), color(color2));

	drawSphere(vec3(0, -.6, 0), vec3(), vec3(.4, .8, .5), color(color1));

	drawSphere(vec3(0, -.6, 0), vec3(), vec3(.45, .75, .55), color(color2));

	sphereReset();
}

void SalesmanKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'a':
		salesman_position.z -= 0.5f;
		break;
	case 'd':
		salesman_position.z += 0.5f;
		break;
	case 's':
		salesman_position.x -= 0.5f;
		break;
	case 'w':
		salesman_position.x += 0.5f;
		break;
	case 'q':
		salesman_rotate.y += 2;
		break;
	case 'e':
		salesman_rotate.y -= 2;
		break;
	default:
		break;
	}
}