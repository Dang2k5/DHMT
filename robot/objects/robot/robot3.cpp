#include "objects/robot3.h"

// Biến trạng thái/điều khiển
vec3 robot3_rotate(0, 0, 0), robot3_position(0, 0, 0);
GLfloat vai3 = 0.0f, dau3 = 0.0f;     // vai (xoay cánh tay trên), đầu (yaw)
GLfloat khuyu3 = 0.0f;               // khuỷu tay (gập)
GLfloat cotay3 = 0.0f;               // cổ tay
GLfloat armSwing3 = 0.0f, legSwing3 = 0.0f;
bool swingForward3 = true;

void drawRobot3(vec3 position, vec3 rotation, vec3 scale, bool enableInput) {
    if (enableInput) {
        rotation += robot3_rotate;
        position += robot3_position;
    }

    // Màu sắc theo phong cách Lego Ninja
    color bodyColor = color(0.0f, 0.4f, 0.6f);      // Xanh dương đậm
    color accentColor = color(0.9f, 0.1f, 0.1f);    // Đỏ, cho chi tiết
    color jointColor = color(0.2f, 0.2f, 0.2f);     // Đen, cho khớp nối
    color highlightColor = color(0.0f, 0.6f, 0.8f); // Xanh nhạt, cho điểm nhấn
    color goldColor = color(0.9f, 0.8f, 0.1f);      // Vàng, cho trang trí

    mat4 globalTransformMatrix = cylinderTransform(position, rotation, scale);
    cylinder1TransformMatrix(globalTransformMatrix);
    sphereTransformMatrix(globalTransformMatrix);
    cubeTransformMatrix(globalTransformMatrix);

    // THÂN ROBOT - khối vuông lớn
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(2.0, 3.0, 1.2), bodyColor);

    // Các chấm Lego trên ngực
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            drawCylinder(vec3(i * 0.5, j * 0.5 + 0.5, 0.65), vec3(0, 0, 0), vec3(0.15, 0.15, 0.1), highlightColor);
        }
    }

    // CỔ - khối vuông nhỏ
    drawCube(vec3(0, 1.7, 0), vec3(0, 0, 0), vec3(0.8, 0.4, 0.8), jointColor);

    // ĐẦU - khối vuông Lego
    mat4 head = globalTransformMatrix * TRS(vec3(0, 2.2, 0), vec3(0, dau3, 0), vec3(1, 1, 1));
    cubeTransformMatrix(head);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1.6, 1.6, 1.6), bodyColor);

    // Mặt nạ Ninja - phần trước đầu
    drawCube(vec3(0, 0, 0.85), vec3(0, 0, 0), vec3(1.4, 1.4, 0.1), jointColor);

    // Mắt - khe hẹp
    drawCube(vec3(0, 0.2, 0.95), vec3(0, 0, 0), vec3(1.0, 0.15, 0.05), accentColor);

    // Vương miện
    drawCube(vec3(0, 1.0, 0), vec3(0, 0, 0), vec3(0.8, 0.2, 0.8), goldColor);

    // Chấm Lego trên đầu
    drawCylinder(vec3(0, 0.8, 0.85), vec3(0, 0, 0), vec3(0.2, 0.2, 0.1), highlightColor);

    // Tay trái
    mat4 leftArm = globalTransformMatrix * TRS(vec3(-1.3, 1.2, 0), vec3(-vai3, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftArm);

    // Bả vai
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.6, 0.6, 0.6), accentColor);

    // Cánh tay trên
    drawCube(vec3(0, -0.8, 0), vec3(0, 0, 0), vec3(0.6, 1.6, 0.6), bodyColor);

    // Khuỷu tay - khớp nối
    mat4 leftElbow = leftArm * TRS(vec3(0, -1.6, 0), vec3(-khuyu3, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftElbow);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.5, 0.4, 0.5), jointColor);

    // Cẳng tay
    drawCube(vec3(0, -0.7, 0), vec3(0, 0, 0), vec3(0.5, 1.4, 0.5), bodyColor);

    // Bàn tay - hình hộp
    mat4 leftHand = leftElbow * TRS(vec3(0, -1.4, 0), vec3(-cotay3, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftHand);
    drawCube(vec3(0, -0.2, 0), vec3(0, 0, 0), vec3(0.6, 0.4, 0.6), jointColor);

    // Vũ khí - Kiếm Ninja
    mat4 swordRight = leftHand * TRS(vec3(0.0f, 0.0f, 0.15f), vec3(-45, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(swordRight);
    drawCube(vec3(0, -1.2f, 0), vec3(0, 0, 0), vec3(0.12f, 2.2f, 0.12f), color(1.0f, 1.0f, 1.0f));
    drawCube(vec3(0, 0.1f, 0), vec3(0, 0, 0), vec3(0.3f, 0.15f, 0.3f), goldColor);

    // Tay phải - tương tự tay trái
    mat4 rightArm = globalTransformMatrix * TRS(vec3(1.3, 1.2, 0), vec3(vai3, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightArm);

    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.6, 0.6, 0.6), accentColor);
    drawCube(vec3(0, -0.8, 0), vec3(0, 0, 0), vec3(0.6, 1.6, 0.6), bodyColor);

    mat4 rightElbow = rightArm * TRS(vec3(0, -1.6, 0), vec3(-khuyu3, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightElbow);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.5, 0.4, 0.5), jointColor);

    drawCube(vec3(0, -0.7, 0), vec3(0, 0, 0), vec3(0.5, 1.4, 0.5), bodyColor);

    mat4 rightHand = rightElbow * TRS(vec3(0, -1.4, 0), vec3(cotay3, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightHand);
    drawCube(vec3(0, -0.2, 0), vec3(0, 0, 0), vec3(0.6, 0.4, 0.6), jointColor);

    // Khiên
    drawCube(vec3(0, -0.5, 0), vec3(0, 0, 0), vec3(0.8, 0.8, 0.1), accentColor);
    drawCylinder(vec3(0, -0.5, 0.1), vec3(0, 0, 0), vec3(0.1, 0.1, 0.1), goldColor);
    // Chân phải
    mat4 rightLeg = globalTransformMatrix * TRS(vec3(0.5, -1.7, 0), vec3(legSwing3, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightLeg);

    // Hông
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.7, 0.6, 0.7), accentColor);

    // Đùi
    drawCube(vec3(0, -1.0, 0), vec3(0, 0, 0), vec3(0.7, 2.0, 0.7), bodyColor);

    // Đầu gối - khớp nối
    mat4 rightKnee = rightLeg * TRS(vec3(0, -2.0, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightKnee);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.6, 0.5, 0.6), jointColor);

    // Ống chân
    drawCube(vec3(0, -1.0, 0), vec3(0, 0, 0), vec3(0.6, 2.0, 0.6), bodyColor);

    // Bàn chân - hình hộp lớn
    mat4 rightFoot = rightKnee * TRS(vec3(0, -2.0, 0.3), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightFoot);
    drawCube(vec3(0, -0.2, 0), vec3(0, 0, 0), vec3(0.7, 0.4, 1.2), bodyColor);

    // Chân trái
    mat4 leftLeg = globalTransformMatrix * TRS(vec3(-0.5, -1.7, 0), vec3(-legSwing3, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftLeg);

    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.7, 0.6, 0.7), accentColor);
    drawCube(vec3(0, -1.0, 0), vec3(0, 0, 0), vec3(0.7, 2.0, 0.7), bodyColor);

    mat4 leftKnee = leftLeg * TRS(vec3(0, -2.0, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftKnee);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.6, 0.5, 0.6), jointColor);

    drawCube(vec3(0, -1.0, 0), vec3(0, 0, 0), vec3(0.6, 2.0, 0.6), bodyColor);

    mat4 leftFoot = leftKnee * TRS(vec3(0, -2.0, 0.3), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftFoot);
    drawCube(vec3(0, -0.2, 0), vec3(0, 0, 0), vec3(0.7, 0.4, 1.2), bodyColor);

    // Bao kiếm sau lưng
    mat4 sheathBack = globalTransformMatrix * TRS(vec3(-0.8, 1.0, -0.6), vec3(0, 0, 45), vec3(1, 1, 1));
    cubeTransformMatrix(sheathBack);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.4, 1.8, 0.3), jointColor);
    mat4 sheathDetail = sheathBack * TRS(vec3(0, 0.9, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(sheathDetail);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.5, 0.2, 0.4), accentColor);
}


void Robot3Keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': robot3_position.z -= 0.5f; break;
    case 'd': robot3_position.z += 0.5f; break;
    case 's': robot3_position.x -= 0.5f; break;
    case 'w': robot3_position.x += 0.5f; break;
    case 'q': robot3_rotate.y += 2; break;
    case 'e': robot3_rotate.y -= 2; break;

        // Đầu quay trái/phải (giới hạn ±30°)
    case 'l':
        dau3 += 2; if (dau3 > 30) dau3 = 30;
        break;
    case 'L':
        dau3 -= 2; if (dau3 < -30) dau3 = -30;
        break;

        // Khuỷu tay (±60°)
    case 'j':
        khuyu3 += 2; if (khuyu3 > 60) khuyu3 = 60;
        break;
    case 'J':
        khuyu3 -= 2; if (khuyu3 < -60) khuyu3 = -60;
        break;

        // Cổ tay (±30°)
    case 'k':
        cotay3 += 2; if (cotay3 > 30) cotay3 = 30;
        break;
    case 'K':
        cotay3 -= 2; if (cotay3 < -30) cotay3 = -30;
        break;

        // Vai (±60°)
    case 'b':
        vai3 += 2; if (vai3 > 60) vai3 = 60;
        break;
    case 'B':
        vai3 -= 2; if (vai3 < -60) vai3 = -60;
        break;
    }
}