#include "objects/robot1.h"

vec3 robot1_rotate(0,0,0), robot1_position(0,0,0);
GLfloat vaiX = 0.0f, vaiZ = 0.0f, dau = 0.0f;
GLfloat khuyuX = 0.0f, khuyuZ = 0.0f;
GLfloat cotay = 0.0f, ngon = 0.0f;
GLfloat armSwing = 0.0f, legSwing = 0.0f;
bool swingForward = true;
bool enableAutoMotion1 = false;


void drawRobot1(vec3 position, vec3 rotation, vec3 scale, bool enableInput) {
	if (enableInput) {
		rotation += robot1_rotate;
		position += robot1_position;
	}
	color bodyColor = color(1.0f, 0.0f, 0.0f, 1); // đỏ
	color jointColor = color(0.0f, 0.0f, 0.0f, 1); // đen
	color eyeColor = color(1.0, 0.2, 0.2, 1);  // xanh ngọc sáng, cho mắt
	color accentColor = color(0.2, 0.2, 0.2, 1); // xám đậm
	color swordColor = color(0.2f, 0.2f, 0.2f, 1); // xám đen

	mat4 globalTransformMatrix = cylinderTransform(position, rotation, scale);
	cylinder1TransformMatrix(globalTransformMatrix);
	sphereTransformMatrix(globalTransformMatrix);
	cubeTransformMatrix(globalTransformMatrix);

	//body
	drawSphere(vec3(0, 0.3, 0), vec3(0, 0, 0), vec3(2.5, 0.6, 1.8), jointColor);
	drawSphere(vec3(0, 0.6, 0), vec3(0, 0, 0), vec3(2.5, 0.6, 1.8), jointColor);
	drawSphere(vec3(0, 0.9, 0), vec3(0, 0, 0), vec3(2.5, 0.6, 1.8), jointColor);
	drawSphere(vec3(0, 1.2, 0), vec3(0, 0, 0), vec3(2.5, 0.6, 1.8), jointColor);
	drawSphere(vec3(0, 1.5, 0), vec3(0, 0, 0), vec3(2.5, 0.6, 1.8), jointColor);
	drawSphere(vec3(0, 0, 0), vec3(0, 0, 0), vec3(2.5, 0.6, 1.8), jointColor);
	drawSphere(vec3(0, -0.3, 0), vec3(0, 0, 0), vec3(2.5, 0.6, 1.8), jointColor);
	drawSphere(vec3(0, -0.6, 0), vec3(0, 0, 0), vec3(2.5, 0.6, 1.8), jointColor);
	drawSphere(vec3(0, -0.9, 0), vec3(0, 0, 0), vec3(2.5, 0.6, 1.8), jointColor);
	

	//neck
	drawCylinder(vec3(0, 1.7, 0), vec3(0, 120, 0), vec3(0.6, 0.4, 1.5), jointColor);
	drawCylinder(vec3(0, 1.7, 0), vec3(0, 0, 0), vec3(0.6, 0.4, 1.5), jointColor);
	drawCylinder(vec3(0, 1.7, 0), vec3(0, -120, 0), vec3(0.6, 0.4, 1.5), jointColor);

	//head
	mat4 head = globalTransformMatrix * TRS(vec3(0, 2.7, 0), vec3(0, 0, 0), vec3(1, 1, 1)) 
		* (enableInput ? Angel::RotateY(dau) : identity()); // quay đầu sang ngang
	cubeTransformMatrix(head);
	sphereTransformMatrix(head);
	cylinderTransformMatrix(head);
	//nón
	drawCylinder(vec3(0, 1, 0), vec3(0,0,0), vec3(1, 0.5, 1), bodyColor);
	drawSphere(vec3(0, 0.6, 0), vec3(0,0,0), vec3(3, 0.4, 1), bodyColor);
	drawSphere(vec3(0, 0, 0), vec3(0, 0, 0), vec3(2, 1, 1), bodyColor);
	drawSphere(vec3(0, 0, 0.48), vec3(0,0,0), vec3(0.2, 0.3, 0.05), color(1.0f, 0.8f, 0.6f, 1.0f));
	drawSphere(vec3(0, 0.2, 0.45), vec3(0, 0, 0), vec3(2, 0.2, 0.05), jointColor);
	// cổ
	drawCylinder(vec3(0, -0.6, 0), vec3(0, 90, 0), vec3(0.8, 0.4, 1), bodyColor);

	// trán
	drawCube(vec3(0, 0.4, 0), vec3(0, 0, 0), vec3(1.5f, 0.2f, 0.8), bodyColor);

	// tai
	drawSphere(vec3(-0.8, 0, 0), vec3(-90, 0, 0), vec3(0.2f, 1, 1), bodyColor);
	drawSphere(vec3(0.8, 0, 0), vec3(90, 0, 0), vec3(0.2f, 1, 1), bodyColor);

	// Mắt - hai hình cầu nhỏ phía trước đầu
	drawSphere(vec3(-0.4, 0.2, 0.3), vec3(0, 0, 0), vec3(0.4f, 0.2f, 0.4f), eyeColor);
	drawSphere(vec3(0.4, 0.2, 0.3), vec3(0, 0, 0), vec3(0.4f, 0.2f, 0.4f), eyeColor);


	// Miệng - hình hộp dẹt
	drawSphere(vec3(0, -0.1, 0.5), vec3(0, 0, 0), vec3(1.0f, 0.2f, 0.02f), accentColor);
	drawCube(vec3(0, -0.1, 0.5), vec3(0, 0, 0), vec3(0.8f, 0.1f, 0.02f), WHITE);

	//left arm
	cylinderTransformMatrix(globalTransformMatrix);
	sphereTransformMatrix(globalTransformMatrix);
	mat4 leftarm = globalTransformMatrix * TRS(vec3(-1.2, 1.5, 0), vec3(0, 0, 0), vec3(1, 1, 1)) 
		* (enableInput ? Angel::RotateX(-armSwing) * RotateZ(-vaiZ) : identity());
		cylinderTransformMatrix(leftarm);
	sphereTransformMatrix(leftarm);
	cubeTransformMatrix(leftarm);
	drawCylinder(vec3(0, -0.75, 0), vec3(0, 0, -30), vec3(1, 1.5, 0.5), bodyColor);
	//khuỷu
	drawSphere(vec3(-0.75 * sin(radians(30.0f)),-0.75 -0.75 * cos(radians(30.0f)), 0),
		vec3(0, 0, 0), vec3(0.4, 0.4, 0.4), jointColor);

	mat4 elbowLeft = leftarm * TRS(vec3(-0.675, -1.4, 0), vec3(0, 0, 0), vec3(1, 1, 1))
		* (enableInput ? Angel::RotateX(khuyuX) * Angel::RotateZ(-khuyuZ) : identity());
	cylinderTransformMatrix(elbowLeft);

	drawCylinder(vec3(0, -0.5, 0), vec3(0, 0, -30), vec3(0.6, 1.2, 0.3), bodyColor);
	

	//hand
	// Cổ tay (khớp nối với cẳng tay)
	mat4 wristLeft = elbowLeft * TRS(vec3(-0.3, -1, 0), vec3(-0, 0, 0), vec3(1, 1, 1))
		* (enableInput ? Angel::RotateX(-cotay) : identity());
	sphereTransformMatrix(wristLeft);
	drawSphere(vec3(0, 0, 0), vec3(0, 0, 30), vec3(0.4, 0.4, 0.4), jointColor);

	// Lòng bàn tay;
	mat4 handLeft = wristLeft * TRS(vec3(-0.1, -0.2, 0), vec3(0, 0, 0), vec3(1, 1, 1));
	cubeTransformMatrix(handLeft);
	drawCube(vec3(0, 0, 0.0), vec3(0, 0, 60), vec3(0.6, 0.2, 1), bodyColor);
	// Ngón tay
	mat4 fingersLeft = handLeft * TRS(vec3(-0.1f, -0.3f, 0), vec3(0, 0, 0), vec3(1, 1, 1))
		* (enableInput ? Angel::RotateZ(ngon) : identity());
	cylinderTransformMatrix(fingersLeft);
	for (int i = 0; i < 5; i++) {
		float zOffset = -0.4 + i * 0.2f;
		drawCylinder(vec3(0, 0, zOffset), vec3(0, 0, 0), vec3(0.2, 0.5, 0.15), jointColor);
		drawCylinder(vec3(0.1, -0.15, zOffset), vec3(0, 0, 90), vec3(0.2, 0.3, 0.15), jointColor);
	}

	mat4 kiem = fingersLeft * TRS(vec3(0, 0, 0), vec3(90, 90, -90), vec3(1, 1, 1));
	cylinderTransformMatrix(kiem);
	sphereTransformMatrix(kiem);
	drawCylinder(vec3(-0.5, 0, 0), vec3(0, 0, 0), vec3(1, 0.2, 0.2), swordColor);
	drawCylinder(vec3(-0.5, 0, 0), vec3(0, 0, 90), vec3(2, 0.2, 0.1), swordColor);
	drawSphere(vec3(-2, 0, 0), vec3(0, 0, 0), vec3(6, 0.5f, 0.05f), swordColor);
	

	//right arm (cánh tay phải)
	mat4 rightarm = globalTransformMatrix * TRS(vec3(1.2, 1.5, 0), vec3(0, 0, 0), vec3(1,1,1))
		* (enableInput ? Angel::RotateX(armSwing) * Angel::RotateZ(vaiZ) : identity());
	cylinderTransformMatrix(rightarm);
	sphereTransformMatrix(rightarm);
	cubeTransformMatrix(rightarm);
	drawCylinder(vec3(0, -0.75, 0), vec3(0, 0, 30), vec3(1, 1.5, 0.5), bodyColor);
	//khuỷu
	drawSphere(vec3(0.75 * sin(radians(30.0f)), -0.75 - 0.75 * cos(radians(30.0f)), 0),
		vec3(0, 0, 0), vec3(0.4, 0.4, 0.4), jointColor);
	mat4 elbowRight = rightarm * TRS(vec3(0.675, -1.4, 0), vec3(0, 0, 0), vec3(1, 1, 1))
		* (enableInput ? Angel::RotateX(khuyuX) * Angel::RotateZ(khuyuZ) : identity());
	cylinderTransformMatrix(elbowRight);
	drawCylinder(vec3(0, -0.5, 0), vec3(0, 0, 30), vec3(0.6, 1.2, 0.3), bodyColor);

	// cổ tay
	mat4 wristRight = elbowRight * TRS(vec3(0.3, -1, 0), vec3(0, 0, 0), vec3(1, 1, 1))
		* (enableInput ? Angel::RotateX(cotay) : identity());
	sphereTransformMatrix(wristRight);
	drawSphere(vec3(0, 0, 0), vec3(0, 0, 30), vec3(0.4, 0.4, 0.4), jointColor);
	// bàn tay
	mat4 handRight = wristRight * TRS(vec3(0.1, -0.2, 0), vec3(0, 0, 0), vec3(1, 1, 1));
	cubeTransformMatrix(handRight);
	drawCube(vec3(0, 0, 0.0f), vec3(0, 0, -60), vec3(0.6, 0.2, 1), bodyColor);
	// ngón tay
	mat4 fingersRight = handRight * TRS(vec3(0.1f, -0.3f, 0), vec3(0, 0, 0), vec3(1, 1, 1))
		* (enableInput ? Angel::RotateZ(ngon) : identity());
	cylinderTransformMatrix(fingersRight);
	for (int i = 0; i < 5; i++) {
		float zOffset = 0.4 - i * 0.2f;
		drawCylinder(vec3(0, 0, zOffset), vec3(0, 0, 0), vec3(0.2, 0.5, 0.15), jointColor);
		drawCylinder(vec3(-0.1, -0.15, zOffset), vec3(0, 0, 90), vec3(0.2, 0.3, 0.15), jointColor);
	}

	cylinderTransformMatrix(globalTransformMatrix);
	sphereTransformMatrix(globalTransformMatrix);

	//hip
	drawSphere(vec3(0, -1.6, 0), vec3(0,0,0), vec3(2, 1, 2), jointColor);
	//right leg
	mat4 rightleg = globalTransformMatrix * (enableInput ? Angel::RotateX(legSwing) : identity())
		* TRS(vec3(0.5, -2.6, 0), vec3(0, 0, 0), vec3(1, 1, 1));
	cylinderTransformMatrix(rightleg);
	sphereTransformMatrix(rightleg);
	cylinder1TransformMatrix(rightleg);
	drawCylinder(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 2, 1), bodyColor);
	drawSphere(vec3(0, -1.1, 0), vec3(90, 0, 0), vec3(0.8, 0.6, 0.6), jointColor);
	drawCylinder(vec3(0, -2.6, 0), vec3(0, 0, 0), vec3(0.6, 3, 0.7), bodyColor);
	//foot
	drawCylinder1(vec3(0, -3.9, 0.5), vec3(0, 0, 0), vec3(0.8, 0.4, 1.5), bodyColor);


	//left leg
	mat4 leftleg = globalTransformMatrix * (enableInput ? Angel::RotateX(-legSwing) : identity())
		* TRS(vec3(-0.5, -2.6, 0), vec3(0, 0, 0), vec3(1, 1, 1));
	cylinderTransformMatrix(leftleg);
	sphereTransformMatrix(leftleg);
	cylinder1TransformMatrix(leftleg);
	drawCylinder(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 2, 1), bodyColor);
	drawSphere(vec3(0, -1.1, 0), vec3(90, 0, 0), vec3(0.8, 0.6, 0.6), jointColor);
	drawCylinder(vec3(0, -2.6, 0), vec3(0, 0, 0), vec3(0.6, 3, 0.7), bodyColor);
	//foot
	drawCylinder1(vec3(0, -3.9, 0.5), vec3(0, 0, 0), vec3(0.8, 0.4, 1.5), bodyColor);

	cylinderReset();
	cylinder1Reset();
	sphereReset();
	cubeReset();
}
void updateRobot1Motion() {
	if (!enableAutoMotion1) return;
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
			khuyuX -= 2;
			if (khuyuX < -30) khuyuX = -30;
			break;
		case 'J':
			khuyuX += 2;
			if (khuyuX > 0) khuyuX = 0;
			break;
		case 'k':
			khuyuZ += 2;
			if (khuyuZ > 30) khuyuZ = 30;
			break;
		case 'K':
			khuyuZ -= 2;
			if (khuyuZ < -30) khuyuZ = -30;
			break;
		case 'h':
			cotay += 2;
			if (cotay > 30) cotay = 30;
			break;
		case 'H':
			cotay -= 2;
			if (cotay < -30) cotay = -30;
			break;
		case 'm':
			vaiZ += 2;
			if (vaiZ > 60) vaiZ = 60;
			break;
		case 'M':
			vaiZ -= 2;
			if (vaiZ < 0) vaiZ = 0;
			break;
		case 'i':
			ngon += 2;
			if (ngon > 45) ngon = 45;
			break;
		case 'I':
			ngon -= 2;
			if (ngon < -45) ngon = -45;
			break;
		case 'n':
			enableAutoMotion1 = !enableAutoMotion1;
			break;
		default:
			break;
	}
}