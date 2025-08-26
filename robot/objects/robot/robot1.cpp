#include "objects/robot1.h"

vec3 robot1_rotate(0,0,0), robot1_position(0,0,0);
GLfloat vai = 0.0f, dau = 0.0f, hz = 0.0f;
GLfloat khuyu = 0.0f, ly = 0.0f, lz = 0.0f;
GLfloat cotay = 0.0f, ngon = 0.0f, rz = 0.0f;
GLfloat armSwing = 0.0f, legSwing = 0.0f;
bool swingForward = true;


void drawRobot1(vec3 position, vec3 rotation, vec3 scale, bool enableInput) {
	if (enableInput) {
		rotation += robot1_rotate;
		position += robot1_position;
	}
	

	color bodyColor = color(0.7f, 0.7f, 0.75f); // xám kim loại
	color jointColor = color(0.5f, 0.5f, 0.55f); // xám đậm hơn, dùng cho khớp nối
	color eyeColor = color(0.0f, 0.8f, 1.0f);  // xanh ngọc sáng, cho mắt
	color accentColor = color(1.0f, 0.4f, 0.0f);  // cam, cho chi tiết nhỏ hoặc đường viền

	mat4 globalTransformMatrix = cylinderTransform(position, rotation, scale);
	cylinder1TransformMatrix(globalTransformMatrix);
	sphereTransformMatrix(globalTransformMatrix);
	cubeTransformMatrix(globalTransformMatrix);

	//body
	drawCylinder(vec3(0, 0, 0), vec3(0, 0, 0), vec3(2, 3, 1.5), bodyColor);

	//neck
	drawCylinder(vec3(0, 1.7, 0), vec3(0, 120, 0), vec3(0.6, 0.4, 1.5), jointColor);
	drawCylinder(vec3(0, 1.7, 0), vec3(0, 0, 0), vec3(0.6, 0.4, 1.5), jointColor);
	drawCylinder(vec3(0, 1.7, 0), vec3(0, -120, 0), vec3(0.6, 0.4, 1.5), jointColor);

	//head
	mat4 head = globalTransformMatrix * TRS(vec3(0, 2.9, 0), vec3(0, dau, 0), vec3(1, 1, 1)); // quay đầu sang ngang
	cubeTransformMatrix(head);
	sphereTransformMatrix(head);
	cylinderTransformMatrix(head);
	drawCube(vec3(0, 0, 0), vec3(0,0,0), vec3(2, 2, 1.5), bodyColor);

	// Mắt - hai hình cầu nhỏ phía trước đầu
	drawSphere(vec3(-0.4, 0.2, 0.8), vec3(0, 0, 0), vec3(0.4f, 0.2f, 0.4f), eyeColor);
	drawSphere(vec3(0.4, 0.2, 0.8), vec3(0, 0, 0), vec3(0.4f, 0.2f, 0.4f), eyeColor);


	// Miệng - hình hộp dẹt
	drawCube(vec3(0, -0.4, 0.8), vec3(0, 0, 0), vec3(1.0f, 0.2f, 0.1f), accentColor);
	drawCube(vec3(0, -0.6, 0.8), vec3(0, 0, 0), vec3(1.0f, 0.2f, 0.1f), accentColor);

	// Anten - trụ và quả cầu trên đỉnh đầu
	// trái
	
	drawCylinder(vec3(-0.75, 1.1, 0), vec3(0, 0, 0), vec3(0.1f, 0.8f, 0.1f), bodyColor);
	drawSphere(vec3(-0.75, 1.9, 0), vec3(0, 0, 0), vec3(0.25f, 0.25f, 0.25f), eyeColor);
	// phải
	drawCylinder(vec3(0.75, 1.1, 0), vec3(0, 0, 0), vec3(0.1f, 0.8f, 0.1f), bodyColor);
	drawSphere(vec3(0.75, 1.9, 0), vec3(0, 0, 0), vec3(0.25f, 0.25f, 0.25f), eyeColor);

	//left arm
	cylinderTransformMatrix(globalTransformMatrix);
	sphereTransformMatrix(globalTransformMatrix);
	mat4 leftarm = globalTransformMatrix * TRS(vec3(-1.2, 1.5, 0), vec3(-vai, 0, 0), vec3(1,1,1));
	cylinderTransformMatrix(leftarm);
	sphereTransformMatrix(leftarm);
	cubeTransformMatrix(leftarm);
	drawCylinder(vec3(0, -0.75, 0), vec3(0, 0, -30), vec3(0.4, 1.5, 0.4), bodyColor);
	//khuỷu
	drawSphere(vec3(-0.75 * sin(radians(30.0f)),-0.75 -0.75 * cos(radians(30.0f)), 0),
		vec3(0, 0, 0), vec3(0.4, 0.4, 0.4), jointColor);

	mat4 elbowLeft = leftarm * TRS(vec3(-0.675, -1.9, 0), vec3(-khuyu, 0, 0), vec3(1, 1, 1));
	cylinderTransformMatrix(elbowLeft);

	drawCylinder(vec3(0, 0, 0), vec3(0, 0, -30), vec3(0.3, 1, 0.3), bodyColor);
	

	//hand
	// Cổ tay (khớp nối với cẳng tay)
	mat4 wristLeft = elbowLeft * TRS(vec3(-0.3, -0.5, 0), vec3(-cotay, 0, 0), vec3(1, 1, 1));
	sphereTransformMatrix(wristLeft);
	drawSphere(vec3(0, 0, 0), vec3(0, 0, 30), vec3(0.4, 0.4, 0.4), jointColor);

	// Lòng bàn tay;
	mat4 handLeft = wristLeft * TRS(vec3(-0.1, -0.2, 0), vec3(0, 0, 0), vec3(1, 1, 1));
	cubeTransformMatrix(handLeft);
	drawCube(vec3(0, 0, 0.0), vec3(0, 0, 60), vec3(0.6, 0.2, 1), bodyColor);
	// Ngón tay
	mat4 fingersLeft = handLeft * TRS(vec3(-0.1f, -0.3f, 0), vec3(0, 0, 0), vec3(1, 1, 1));
	cylinderTransformMatrix(fingersLeft);
	for (int i = 0; i < 5; i++) {
		float zOffset = -0.4 + i * 0.2f;
		drawCylinder(vec3(0, 0, zOffset), vec3(0, 0, 0), vec3(0.2, 0.5, 0.15), jointColor);
		drawCylinder(vec3(0.1, -0.15, zOffset), vec3(0, 0, 90), vec3(0.2, 0.3, 0.15), jointColor);
	}
	

	//right arm (cánh tay phải)
	mat4 rightarm = globalTransformMatrix * TRS(vec3(1.2, 1.5, 0), vec3(vai, 0, 0), vec3(1,1,1));
	cylinderTransformMatrix(rightarm);
	sphereTransformMatrix(rightarm);
	cubeTransformMatrix(rightarm);
	drawCylinder(vec3(0, -0.75, 0), vec3(0, 0, 30), vec3(0.4, 1.5, 0.4), bodyColor);
	//khuỷu
	drawSphere(vec3(0.75 * sin(radians(30.0f)), -0.75 - 0.75 * cos(radians(30.0f)), 0),
		vec3(0, 0, 0), vec3(0.4, 0.4, 0.4), jointColor);
	mat4 elbowRight = rightarm * TRS(vec3(0.675, -1.9, 0), vec3(-khuyu, 0, 0), vec3(1, 1, 1));
	cylinderTransformMatrix(elbowRight);
	drawCylinder(vec3(0, 0, 0), vec3(0, 0, 30), vec3(0.3, 1, 0.3), bodyColor);

	// cổ tay
	mat4 wristRight = elbowRight * TRS(vec3(0.3, -0.5, 0), vec3(cotay, 0, 0), vec3(1, 1, 1));
	sphereTransformMatrix(wristRight);
	drawSphere(vec3(0, 0, 0), vec3(0, 0, 30), vec3(0.4, 0.4, 0.4), jointColor);
	// bàn tay
	mat4 handRight = wristRight * TRS(vec3(0.1, -0.2, 0), vec3(0, 0, 0), vec3(1, 1, 1));
	cubeTransformMatrix(handRight);
	drawCube(vec3(0, 0, 0.0f), vec3(0, 0, -60), vec3(0.6, 0.2, 1), bodyColor);
	// ngón tay
	mat4 fingersRight = handRight * TRS(vec3(0.1f, -0.3f, 0), vec3(0, 0, 0), vec3(1, 1, 1));
	cylinderTransformMatrix(fingersRight);
	for (int i = 0; i < 5; i++) {
		float zOffset = 0.4 - i * 0.2f;
		drawCylinder(vec3(0, 0, zOffset), vec3(0, 0, 0), vec3(0.2, 0.5, 0.15), jointColor);
		drawCylinder(vec3(-0.1, -0.15, zOffset), vec3(0, 0, 90), vec3(0.2, 0.3, 0.15), jointColor);
	}

	cylinderTransformMatrix(globalTransformMatrix);
	sphereTransformMatrix(globalTransformMatrix);

	//hip
	drawSphere(vec3(0, -1.6, 0), vec3(0,0,0), vec3(2, 1, 1.5), jointColor);
	//right leg
	mat4 rightleg = globalTransformMatrix * TRS(vec3(0.5, -2.6, 0), vec3(legSwing, 0, 0), vec3(1, 1, 1));
	cylinderTransformMatrix(rightleg);
	sphereTransformMatrix(rightleg);
	cylinder1TransformMatrix(rightleg);
	drawCylinder(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 2, 1), bodyColor);
	drawSphere(vec3(0, -0.95, 0), vec3(90, 0, 0), vec3(0.8, 0.6, 0.6), jointColor);
	drawCylinder(vec3(0, -2.6, 0), vec3(0, 0, 0), vec3(0.6, 3, 0.7), bodyColor);
	//foot
	drawCylinder1(vec3(0, -3.9, 0.5), vec3(0, 0, 0), vec3(0.8, 0.4, 1.5), bodyColor);


	//left leg
	mat4 leftleg = globalTransformMatrix * TRS(vec3(-0.5, -2.6, 0), vec3(-legSwing, 0, 0), vec3(1, 1, 1));
	cylinderTransformMatrix(leftleg);
	sphereTransformMatrix(leftleg);
	cylinder1TransformMatrix(leftleg);
	drawCylinder(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 2, 1), bodyColor);
	drawSphere(vec3(0, -0.95, 0), vec3(90, 0, 0), vec3(0.8, 0.6, 0.6), jointColor);
	drawCylinder(vec3(0, -2.6, 0), vec3(0, 0, 0), vec3(0.6, 3, 0.7), bodyColor);
	//foot
	drawCylinder1(vec3(0, -3.9, 0.5), vec3(0, 0, 0), vec3(0.8, 0.4, 1.5), bodyColor);
}
void updateRobotMotion() {
	float speed = 0.5f; // tốc độ vung tay chân
	if (swingForward) {
		armSwing += speed;
		legSwing -= speed;
		if (armSwing > 30.0f) swingForward = false;
	}
	else {
		armSwing -= speed;
		legSwing += speed;
		if (armSwing < -30.0f) swingForward = true;
	}
}
void Robot1Keyboard(unsigned char key, int x, int y) {
	switch (key){
		case 'a':
			robot1_position.z -= 0.5f;
			break;
		case 'd':
			robot1_position.z += 0.5f;
			break;
		case 's':
			robot1_position.x -= 0.5f;
			break;
		case 'w':
			robot1_position.x += 0.5f;
			break;
		case 'q':
			robot1_rotate.y += 2;
			break;
		case 'e':
			robot1_rotate.y -= 2;
			break;
		case 'l':
			dau += 2;
			if (dau > 30) dau = 30;
			break;
		case 'L':
			dau -= 2;
			if (dau < -30) dau = -30;
			break;
		case 'j':
			khuyu += 2;
			if (khuyu > 60) khuyu = 60;
			break;
		case 'J':
			khuyu -= 2;
			if (khuyu < -60) khuyu = -60;
			break;
		case 'k':
			cotay += 2;
			if (cotay > 30) cotay = 30;
			break;
		case 'K':
			cotay -= 2;
			if (cotay < -30) cotay = -30;
			break;
		case 'b':
			vai += 2;
			if (vai > 60) vai = 60;
			break;
		case 'B':
			vai -= 2;
			if (vai < -60) vai = -60;
			break;
		case 'n':
			glutDisplayFunc(updateRobotMotion);
		default:
			break;
	}
}