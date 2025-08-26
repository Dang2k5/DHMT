#include "objects/robot1.h"

vec3 robot2_rotate, robot2_position;

struct RobotJoint {
	vec3 rotation;  // Xoay quanh X, Y, Z
};

struct Robot2{
	vec3 position;
	vec3 rotation;
	vec3 scale;

	// Các khớp chuyển động
	RobotJoint head;
	RobotJoint leftShoulder, leftElbow, leftWrist;
	RobotJoint rightShoulder, rightElbow, rightWrist;
	RobotJoint leftHip, leftKnee, leftAnkle;
	RobotJoint rightHip, rightKnee, rightAnkle;
};

void drawRobot2(vec3 position, vec3 rotation, vec3 scale, bool enableInput) {

	if (enableInput) {
		rotation += robot2_rotate;
		position += robot2_position;
	}
}

void Robot2Keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
		switch (key)
		{
		case 'a':
			robot2_position.z -= 0.5f;
			break;
		case 'd':
			robot2_position.z += 0.5f;
			break;
		case 's':
			robot2_position.x -= 0.5f;
			break;
		case 'w':
			robot2_position.x += 0.5f;
			break;
		case 'q':
			robot2_rotate.y += 2;
			break;
		case 'e':
			robot2_rotate.y -= 2;
			break;
		default:
			break;
		}
	}
}