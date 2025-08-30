#include "objects/robot2.h"

vec3 robot2_rotate(0, 0, 0), robot2_position(0, 0, 0);
GLfloat vai2 = 0.0f, dau2 = 0.0f;
GLfloat cotay2 = 0.0f, ngon2 = 0.0f;
GLfloat armSwing2 = 0.0f, legSwing2 = 0.0f;




void drawRobot2(vec3 position, vec3 rotation, vec3 scale, bool enableInput) {
    if (enableInput) {
        rotation += robot2_rotate;
        position += robot2_position;
    }

    // === Colors (giống hệt robot trong ảnh) ===
    color bodyColor = color(0.19f, 0.84f, 0.78f);  // Xanh ngọc
    color jointColor = color(0.2f, 0.2f, 0.2f);  // Xám khớp
    color eyeColor = color(1.0f, 1.0f, 1.0f);  // Trắng mắt
    color pupilColor = color(0.0f, 0.0f, 0.0f);  // Đen con ngươi
    color blushColor = color(1.0f, 0.6f, 0.7f);  // Hồng má
    color displayColor = color(0.7f, 0.7f, 0.7f);  // Xám màn hình


    // Global transform
    mat4 globalTransformMatrix = cylinderTransform(position, rotation, scale);
    cylinderTransformMatrix(globalTransformMatrix);
    sphereTransformMatrix(globalTransformMatrix);
    cubeTransformMatrix(globalTransformMatrix);

    // === Thân (Body) ===
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1.0f, 1.2f, 1.0f), bodyColor);

    // === Màn hình ngực ===
    mat4 displayTransform = globalTransformMatrix * TRS(vec3(0, 0.1f, 0.5f), vec3(0, 0, 0), vec3(0.6f, 0.4f, 0.1f));
    cubeTransformMatrix(displayTransform);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1), displayColor);



    // === Cổ (Neck) ===

    // === Đầu (Head) ===
    mat4 headTransform = globalTransformMatrix * TRS(vec3(0, 1.1f, 0), vec3(0, 0, 0), vec3(1.4f, 1.2f, 1.2f)) 
        * (enableInput ? Angel::RotateY(dau2) : identity());
    cubeTransformMatrix(headTransform);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1.0f, 1.0f, 1.0f), bodyColor);


    // === Mắt trái ===
    mat4 leftEyeMat = headTransform * TRS(vec3(-0.3f, 0.2f, 0.5f), vec3(0, 0, 0), vec3(1, 1, 1));
    sphereTransformMatrix(leftEyeMat);
    drawSphere(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.2f, 0.2f, 0.05f), eyeColor);
    drawSphere(vec3(0, 0, 0.05f), vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.05f), pupilColor);

    // === Mắt phải ===
    mat4 rightEyeMat = headTransform * TRS(vec3(0.3f, 0.2f, 0.5f), vec3(0, 0, 0), vec3(1, 1, 1));
    sphereTransformMatrix(rightEyeMat);
    drawSphere(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.2f, 0.2f, 0.05f), eyeColor);
    drawSphere(vec3(0, 0, 0.05f), vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.05f), pupilColor);


    // === Má hồng ===
    drawCube(vec3(-0.35f, -0.05f, 0.5f), vec3(0, 0, 0), vec3(0.15f, 0.1f, 0.05f), blushColor);
    drawCube(vec3(0.35f, -0.05f, 0.5f), vec3(0, 0, 0), vec3(0.15f, 0.1f, 0.05f), blushColor);

    // === Antenna ===
    // === Antenna trái ===
    mat4 leftAntennaMat = headTransform * TRS(vec3(-0.5f, 0.5f, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cylinderTransformMatrix(leftAntennaMat);
    drawCylinder(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.05f, 0.4f, 0.05f), bodyColor);

    mat4 leftAntennaTip = leftAntennaMat * TRS(vec3(0, 0.35f, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    sphereTransformMatrix(leftAntennaTip);
    drawSphere(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.1f), bodyColor);

    // === Antenna phải ===
    mat4 rightAntennaMat = headTransform * TRS(vec3(0.5f, 0.5f, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cylinderTransformMatrix(rightAntennaMat);
    drawCylinder(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.05f, 0.4f, 0.05f), bodyColor);

    mat4 rightAntennaTip = rightAntennaMat * TRS(vec3(0, 0.35f, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    sphereTransformMatrix(rightAntennaTip);
    drawSphere(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.1f, 0.1f, 0.1f), bodyColor);


    // === Tay trái ===
    mat4 leftArmTransform = globalTransformMatrix * TRS(vec3(-0.5f, 0.3f, 0), vec3(0, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateX(-armSwing2) * RotateZ(-vai2) : identity());
    cubeTransformMatrix(leftArmTransform);
    drawCube(vec3(0, -0.3f, 0), vec3(0, 0, 0), vec3(0.2f, 0.6f, 0.2f), bodyColor);

    // Bàn tay trái
    mat4 handLeft = leftArmTransform * TRS(vec3(0, -0.6f, 0), vec3(0, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateZ(-cotay2) : identity());
    cubeTransformMatrix(handLeft);
    drawCube(vec3(0, 0.0f, 0), vec3(90, 0, 0), vec3(0.3f, 0.3f, 0.1f), bodyColor);

    // === Tay phải ===
    mat4 rightArmTransform = globalTransformMatrix * TRS(vec3(0.5f, 0.3f, 0), vec3(0, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateX(armSwing2) * RotateZ(vai2) : identity());
    cubeTransformMatrix(rightArmTransform);
    drawCube(vec3(0, -0.3f, 0), vec3(0, 0, 0), vec3(0.2f, 0.6f, 0.2f), bodyColor);

    // Bàn tay phải
    mat4 handRight = rightArmTransform * TRS(vec3(0, -0.6f, 0), vec3(0, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateZ(cotay2) : identity());
    cubeTransformMatrix(handRight);
    drawCube(vec3(0, 0.0f, 0), vec3(90, 0, 0), vec3(0.3f, 0.3f, 0.1f), bodyColor);



    // === Chân trái ===
    mat4 leftLegTransform = globalTransformMatrix * TRS(vec3(-0.2f, -0.8f, 0), vec3(0, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateX(-legSwing2) : identity());
    cubeTransformMatrix(leftLegTransform);
    drawCube(vec3(0, -0.12f, 0), vec3(0, 0, 0), vec3(0.3f, 0.6f, 0.3f), bodyColor);

    mat4 footLeft = leftLegTransform * TRS(vec3(0, -0.5f, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(footLeft);
    drawCube(vec3(0, 0.0f, 0.1f), vec3(-30, 0, 0), vec3(0.4f, 0.2f, 0.5f), bodyColor);

    // === Chân phải ===
    mat4 rightLegTransform = globalTransformMatrix * TRS(vec3(0.2f, -0.8f, 0), vec3(0, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateX(legSwing2) : identity());
    cubeTransformMatrix(rightLegTransform);
    drawCube(vec3(0, -0.12f, 0), vec3(0, 0, 0), vec3(0.3f, 0.6f, 0.3f), bodyColor);

    mat4 footRight = rightLegTransform * TRS(vec3(0, -0.5f, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(footRight);
    drawCube(vec3(0, 0.0f, 0.1f), vec3(-30, 0, 0), vec3(0.4f, 0.2f, 0.5f), bodyColor);
}

void Robot2Keyboard(unsigned char key, int x, int y) {
    switch (key) {
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
    case 'l':
        dau2 += 2;
        if (dau2 > 30) dau2 = 30;
        break;
    case 'L':
        dau2 -= 2;
        if (dau2 < -30) dau2 = -30;
        break;
    case 'k':
        cotay2 += 2;
        if (cotay2 > 30) cotay2 = 30;
        break;
    case 'K':
        cotay2 -= 2;
        if (cotay2 < -30) cotay2 = -30;
        break;
    case 'b':
        vai2 += 2;
        if (vai2 > 60) vai2 = 60;
        break;
    case 'B':
        vai2 -= 2;
        if (vai2 < 0) vai2 = 0;
        break;
    default:
        break;
    }
}