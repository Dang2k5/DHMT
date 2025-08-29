#include "objects/robot4.h"


// Biến trạng thái/điều khiển cho robot4
vec3 robot4_rotate(0, 0, 0), robot4_position(0, 0, 0);
GLfloat vai4 = 0.0f, dau4 = 0.0f;     // vai (xoay cánh tay trên), đầu (yaw)
GLfloat khuyu4 = 0.0f;               // khuỷu tay (gập)
GLfloat cotay4 = 0.0f;               // cổ tay
GLfloat armSwing4 = 0.0f, legSwing4 = 0.0f;
bool swingForward4 = true;

void drawRobot4(vec3 position, vec3 rotation, vec3 scale, bool enableInput) {
    if (enableInput) {
        rotation += robot4_rotate;
        position += robot4_position;
    }


    color bodyColor = color(0.6f, 0.0f, 0.4f);      // Tím đậm 
    color accentColor = color(0.1f, 0.9f, 0.1f);    // Xanh lá, 
    color jointColor = color(0.3f, 0.3f, 0.3f);     // Xám đậm, cho khớp nối
    color highlightColor = color(0.8f, 0.6f, 0.0f); // Vàng cam, cho điểm nhấn
    color silverColor = color(0.8f, 0.8f, 0.9f);    // Bạc, cho trang trí

    mat4 globalTransformMatrix = cylinderTransform(position, rotation, scale);
    cylinder1TransformMatrix(globalTransformMatrix);
    sphereTransformMatrix(globalTransformMatrix);
    cubeTransformMatrix(globalTransformMatrix);

    // THÂN ROBOT - khối vuông lớn
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(2.0, 3.0, 1.2), bodyColor);

    // BỘ NGỰC GUNDAM 

    // Tấm bảo vệ ngực chính - thiết kế hình thang
    drawCube(vec3(0, 0.5, 0.65), vec3(0, 0, 0), vec3(1.2, 1.0, 0.15), silverColor);

    // Khe tản nhiệt trung tâm
    drawCube(vec3(0, 0.5, 0.7), vec3(0, 0, 0), vec3(0.8, 0.8, 0.05), color(0.2, 0.2, 0.3));

    // Các gờ dọc trên tấm bảo vệ ngực
    for (int i = -1; i <= 1; i += 2) {
        drawCube(vec3(i * 0.3, 0.5, 0.68), vec3(0, 0, 0), vec3(0.1, 0.8, 0.1), accentColor);
    }

    // Hộp động cơ trung tâm
    drawCube(vec3(0, 0.5, 0.75), vec3(0, 0, 0), vec3(0.4, 0.4, 0.1), bodyColor);
    drawCube(vec3(0, 0.5, 0.77), vec3(0, 0, 0), vec3(0.3, 0.3, 0.05), highlightColor);

    // Ống xả năng lượng hai bên
    for (int i = -1; i <= 1; i += 2) {
        drawCylinder(vec3(i * 0.6, 0.7, 0.65), vec3(0, 0, 90), vec3(0.15, 0.15, 0.25), silverColor);
        drawCylinder(vec3(i * 0.6, 0.7, 0.75), vec3(0, 0, 0), vec3(0.1, 0.1, 0.05), highlightColor);
    }

    // Tấm bảo vệ vai nối với ngực
    for (int i = -1; i <= 1; i += 2) {
        drawCube(vec3(i * 1.0, 0.8, 0.6), vec3(0, 0, 0), vec3(0.3, 0.4, 0.3), silverColor);
        drawCube(vec3(i * 1.0, 0.8, 0.7), vec3(0, 0, 0), vec3(0.2, 0.3, 0.2), accentColor);
    }

    // CỔ - khối vuông nhỏ
    drawCube(vec3(0, 1.7, 0), vec3(0, 0, 0), vec3(0.8, 0.4, 0.8), jointColor);

    // ĐẦU - khối vuông Lego với phong cách Gundam
    mat4 head = globalTransformMatrix * TRS(vec3(0, 2.2, 0), vec3(0, dau4, 0), vec3(1, 1, 1));
    cubeTransformMatrix(head);

    // Base head shape - hình dạng cơ bản của đầu Gundam
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1.6, 1.8, 1.6), bodyColor);

    // Mặt nạ Gundam - thiết kế góc cạnh đặc trưng
    drawCube(vec3(0, -0.1, 0.85), vec3(0, 0, 0), vec3(1.2, 0.8, 0.2), silverColor);

    // Mắt camera Gundam - thiết kế hình thoi
    drawCube(vec3(0, 0.2, 0.95), vec3(0, 0, 0), vec3(0.4, 0.15, 0.05), highlightColor);

    // V fin (ăng-ten đặc trưng Gundam) trên trán
    drawCube(vec3(0, 1.0, 0.85), vec3(0, 0, 0), vec3(0.1, 0.4, 0.1), silverColor);
    drawCube(vec3(0.15, 0.9, 0.85), vec3(0, 0, 30), vec3(0.1, 0.3, 0.1), silverColor);
    drawCube(vec3(-0.15, 0.9, 0.85), vec3(0, 0, -30), vec3(0.1, 0.3, 0.1), silverColor);

    // Cheek guards (bảo vệ má) - đặc trưng Gundam
    drawCube(vec3(0.7, -0.2, 0.6), vec3(0, 0, 0), vec3(0.2, 0.4, 0.4), silverColor);
    drawCube(vec3(-0.7, -0.2, 0.6), vec3(0, 0, 0), vec3(0.2, 0.4, 0.4), silverColor);

    // Ống thông gió/chi tiết cổ
    drawCube(vec3(0, -0.8, 0.7), vec3(0, 0, 0), vec3(0.4, 0.2, 0.2), jointColor);
    drawCylinder(vec3(0.2, -0.8, 0.7), vec3(90, 0, 0), vec3(0.08, 0.08, 0.1), accentColor);
    drawCylinder(vec3(-0.2, -0.8, 0.7), vec3(90, 0, 0), vec3(0.08, 0.08, 0.1), accentColor);

    // Tay trái
    mat4 leftArm = globalTransformMatrix * TRS(vec3(-1.3, 1.2, 0), vec3(-vai4, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftArm);

    // Bả vai 
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.6, 0.6, 0.6), silverColor);

    // Cánh tay trên
    drawCube(vec3(0, -0.8, 0), vec3(0, 0, 0), vec3(0.6, 1.6, 0.6), bodyColor);

    // Khuỷu tay - khớp nối
    mat4 leftElbow = leftArm * TRS(vec3(0, -1.6, 0), vec3(-khuyu4, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftElbow);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.5, 0.4, 0.5), jointColor);

    // Cẳng tay
    drawCube(vec3(0, -0.7, 0), vec3(0, 0, 0), vec3(0.5, 1.4, 0.5), bodyColor);

    // Bàn tay - hình hộp
    mat4 leftHand = leftElbow * TRS(vec3(0, -1.4, 0), vec3(-cotay4, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftHand);
    drawCube(vec3(0, -0.2, 0), vec3(0, 0, 0), vec3(0.6, 0.4, 0.6), jointColor);

    // Vũ khí - Súng Gundam 
    mat4 gundamRifle = leftHand * TRS(vec3(0.0f, -0.8f, 0.0f), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(gundamRifle);

    // Thân súng chính
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.2, 1.5, 0.4), silverColor);

    // Báng súng
    drawCube(vec3(0, -0.8, -0.15), vec3(0, 0, 0), vec3(0.25, 0.6, 0.2), jointColor);

    // Nòng súng
    drawCube(vec3(0, 0.9, 0), vec3(0, 0, 0), vec3(0.15, 0.8, 0.15), silverColor);

    // Kính ngắm
    drawCube(vec3(0, 0.4, 0.25), vec3(0, 0, 0), vec3(0.1, 0.2, 0.1), highlightColor);
    drawCube(vec3(0, 0.4, 0.25), vec3(0, 0, 0), vec3(0.05, 0.15, 0.05), accentColor);

    // Bộ phận tích năng lượng
    drawCube(vec3(0, 0.1, 0), vec3(0, 0, 0), vec3(0.3, 0.3, 0.3), bodyColor);
    drawCube(vec3(0, 0.1, 0), vec3(0, 0, 0), vec3(0.2, 0.2, 0.2), highlightColor);

    // Tay cầm súng
    drawCube(vec3(0, -0.3, -0.25), vec3(0, 0, 0), vec3(0.15, 0.2, 0.15), jointColor);

    // Đèn phụ / ống phóng
    drawCube(vec3(0.15, 0.7, 0), vec3(0, 0, 0), vec3(0.05, 0.3, 0.05), silverColor);

    // Tay phải - tương tự tay trái
    mat4 rightArm = globalTransformMatrix * TRS(vec3(1.3, 1.2, 0), vec3(vai4, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightArm);

    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.6, 0.6, 0.6), silverColor);
    drawCube(vec3(0, -0.8, 0), vec3(0, 0, 0), vec3(0.6, 1.6, 0.6), bodyColor);

    mat4 rightElbow = rightArm * TRS(vec3(0, -1.6, 0), vec3(-khuyu4, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightElbow);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.5, 0.4, 0.5), jointColor);

    drawCube(vec3(0, -0.7, 0), vec3(0, 0, 0), vec3(0.5, 1.4, 0.5), bodyColor);

    mat4 rightHand = rightElbow * TRS(vec3(0, -1.4, 0), vec3(cotay4, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightHand);
    drawCube(vec3(0, -0.2, 0), vec3(0, 0, 0), vec3(0.6, 0.4, 0.6), jointColor);

    // GIÁP KHIÊN DÀI BẰNG TAY PHẢI GUNDAM

 // Hệ thống gắn khiên vào bả vai
    mat4 shoulderMount = rightArm * TRS(vec3(0.0, 0.0, 0.0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(shoulderMount);
    drawCube(vec3(0.4, 0.0, 0.0), vec3(0, 0, 0), vec3(0.8, 0.8, 0.8), silverColor);

    // Khung chính chạy dọc toàn bộ cánh tay
    mat4 armShieldFrame = shoulderMount * TRS(vec3(0.0, -1.2, 0.0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(armShieldFrame);
    drawCube(vec3(0.0, 0.0, 0.0), vec3(0, 0, 0), vec3(0.15, 2.4, 0.9), silverColor);

    // Tấm khiên chính dọc theo cánh tay
    drawCube(vec3(0.3, 0.0, 0.0), vec3(0, 0, 0), vec3(0.7, 2.4, 0.7), accentColor);

    // Viền kim loại xung quanh khiên
}

void Robot4Keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': robot4_position.z -= 0.5f; break;
    case 'd': robot4_position.z += 0.5f; break;
    case 's': robot4_position.x -= 0.5f; break;
    case 'w': robot4_position.x += 0.5f; break;
    case 'q': robot4_rotate.y += 2; break;
    case 'e': robot4_rotate.y -= 2; break;

        // Đầu quay trái/phải (giới hạn ±30°)
    case 'l':
        dau4 += 2; if (dau4 > 30) dau4 = 30;
        break;
    case 'L':
        dau4 -= 2; if (dau4 < -30) dau4 = -30;
        break;

        // Khuỷu tay (±60°)
    case 'j':
        khuyu4 += 2; if (khuyu4 > 60) khuyu4 = 60;
        break;
    case 'J':
        khuyu4 -= 2; if (khuyu4 < -60) khuyu4 = -60;
        break;

        // Cổ tay (±30°)
    case 'k':
        cotay4 += 2; if (cotay4 > 30) cotay4 = 30;
        break;
    case 'K':
        cotay4 -= 2; if (cotay4 < -30) cotay4 = -30;
        break;

        // Vai (±60°)
    case 'b':
        vai4 += 2; if (vai4 > 60) vai4 = 60;
        break;
    case 'B':
        vai4 -= 2; if (vai4 < -60) vai4 = -60;
        break;
    }
}