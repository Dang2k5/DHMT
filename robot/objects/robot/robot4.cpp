#include "objects/robot4.h"


// Biến trạng thái/điều khiển 
vec3 robot4_rotate(0, 0, 0), robot4_position(0, 0, 0);
GLfloat vai4 = 0.0f, dau4 = 0.0f;     // vai (xoay cánh tay trên), đầu (yaw)
GLfloat khuyu4 = 0.0f;               // khuỷu tay (gập)
GLfloat cotay4 = 0.0f;               // cổ tay
GLfloat armSwing4 = 0.0f, legSwing4 = 0.0f;



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
    mat4 head = globalTransformMatrix * TRS(vec3(0, 2.2, 0), vec3(0, 0, 0), vec3(1, 1, 1)) 
        * (enableInput ? Angel::RotateY(dau4) : identity());
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
    mat4 leftArm = globalTransformMatrix * TRS(vec3(-1.3, 1.2, 0), vec3(0, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateX(vai4) : identity());
    cubeTransformMatrix(leftArm);

    // Bả vai 
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.6, 0.6, 0.6), silverColor);

    // Cánh tay trên
    drawCube(vec3(0, -0.8, 0), vec3(0, 0, 0), vec3(0.6, 1.6, 0.6), bodyColor);

    // Khuỷu tay - khớp nối
    mat4 leftElbow = leftArm * TRS(vec3(0, -1.6, 0), vec3(0, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateX(-khuyu4) : identity());
    cubeTransformMatrix(leftElbow);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.5, 0.4, 0.5), jointColor);

    // Cẳng tay
    drawCube(vec3(0, -0.7, 0), vec3(0, 0, 0), vec3(0.5, 1.4, 0.5), bodyColor);

    // Bàn tay - hình hộp
    mat4 leftHand = leftElbow * TRS(vec3(0, -1.4, 0), vec3(0, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateX(-cotay4) : identity());
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
    mat4 rightArm = globalTransformMatrix * TRS(vec3(1.3, 1.2, 0), vec3(0, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateX(vai4) : identity()) ;
    cubeTransformMatrix(rightArm);

    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.6, 0.6, 0.6), silverColor);
    drawCube(vec3(0, -0.8, 0), vec3(0, 0, 0), vec3(0.6, 1.6, 0.6), bodyColor);

    mat4 rightElbow = rightArm * TRS(vec3(0, -1.6, 0), vec3(0, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateX(-khuyu4) : identity());;
    cubeTransformMatrix(rightElbow);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.5, 0.4, 0.5), jointColor);

    drawCube(vec3(0, -0.7, 0), vec3(0, 0, 0), vec3(0.5, 1.4, 0.5), bodyColor);

    mat4 rightHand = rightElbow * TRS(vec3(0, -1.4, 0), vec3(cotay4, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateX(-cotay4) : identity());;
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
    drawCube(vec3(0.3, 0.0, 0.0), vec3(0, 0, 0), vec3(0.75, 2.45, 0.75), silverColor);

    // Các gờ tăng cứng ngang
    for (float y = -1.0; y <= 1.0; y += 0.8) {
        drawCube(vec3(0.3, y, 0.0), vec3(0, 0, 0), vec3(0.7, 0.1, 0.7), silverColor);
    }

    // Hệ thống ống thủy lực/dẫn năng lượng
    for (float y = -0.8; y <= 0.8; y += 1.6) {
        // Ống dọc chính
        drawCylinder(vec3(0.1, y, 0.3), vec3(0, 0, 90), vec3(0.08, 0.08, 0.5), silverColor);
        drawCylinder(vec3(0.1, y, -0.3), vec3(0, 0, 90), vec3(0.08, 0.08, 0.5), silverColor);

        // Đầu nối
        drawCylinder(vec3(0.1, y, 0.0), vec3(0, 0, 0), vec3(0.12, 0.12, 0.15), highlightColor);
    }

    // Bộ phận phản xạ năng lượng ở khuỷu tay
    mat4 elbowShield = armShieldFrame * TRS(vec3(0.0, -1.6, 0.0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(elbowShield);
    drawCylinder(vec3(0.4, 0.0, 0.0), vec3(0, 0, 0), vec3(0.4, 0.4, 0.1), highlightColor);
    drawCube(vec3(0.4, 0.0, 0.0), vec3(0, 0, 0), vec3(0.3, 0.3, 0.05), silverColor);

    // Tấm bảo vệ cổ tay
    mat4 wristGuard = armShieldFrame * TRS(vec3(0.0, -2.3, 0.0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(wristGuard);
    drawCube(vec3(0.3, 0.0, 0.0), vec3(0, 0, 0), vec3(0.8, 0.3, 0.8), silverColor);

    // Gờ chữ V đặc trưng Gundam
    drawCube(vec3(0.5, 0.0, 0.0), vec3(0, 45, 0), vec3(0.2, 0.1, 0.6), highlightColor);
    drawCube(vec3(0.5, 0.0, 0.0), vec3(0, -45, 0), vec3(0.2, 0.1, 0.6), highlightColor);

    // Hệ thống đèn báo và cảm biến
    for (float y = -0.6; y <= 0.6; y += 1.2) {
        drawCylinder(vec3(0.4, y, 0.25), vec3(0, 0, 0), vec3(0.06, 0.06, 0.04), highlightColor);
        drawCylinder(vec3(0.4, y, -0.25), vec3(0, 0, 0), vec3(0.06, 0.06, 0.04), highlightColor);
    }

    // Kết nối linh hoạt với bàn tay
    drawCube(vec3(0.0, -1.2, 0.0), vec3(0, 0, 0), vec3(0.2, 0.4, 0.4), jointColor);
    drawCylinder(vec3(-0.1, -1.2, 0.0), vec3(0, 0, 90), vec3(0.1, 0.1, 0.3), silverColor);

    // CHÂN PHẢI - Thiết kế đơn giản
    mat4 rightLeg = globalTransformMatrix * TRS(vec3(0.5, -1.7, 0), vec3(legSwing4, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightLeg);

    // Hông - đơn giản hóa
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.8, 0.6, 0.8), bodyColor);

    // Đùi - hình hộp đơn giản
    drawCube(vec3(0, -1.0, 0), vec3(0, 0, 0), vec3(0.7, 2.0, 0.7), bodyColor);

    // Đầu gối - khớp nối đơn giản
    mat4 rightKnee = rightLeg * TRS(vec3(0, -2.0, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightKnee);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.6, 0.5, 0.6), silverColor);

    // Ống chân - đơn giản
    drawCube(vec3(0, -1.0, 0), vec3(0, 0, 0), vec3(0.6, 2.0, 0.6), bodyColor);

    // Mắt cá chân - đơn giản
    mat4 rightAnkle = rightKnee * TRS(vec3(0, -2.0, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightAnkle);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.5, 0.4, 0.5), silverColor);

    // Bàn chân - hình hộp lớn đơn giản
    mat4 rightFoot = rightAnkle * TRS(vec3(0, -0.2, 0.3), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightFoot);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.7, 0.4, 1.2), bodyColor);

    // Thêm một chi tiết nhỏ cho mũi chân
    drawCube(vec3(0, 0.1, 0.55), vec3(0, 0, 0), vec3(0.65, 0.1, 0.35), silverColor);

    // CHÂN TRÁI - tương tự chân phải
    mat4 leftLeg = globalTransformMatrix * TRS(vec3(-0.5, -1.7, 0), vec3(-legSwing4, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftLeg);

    // Hông - đơn giản hóa
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.8, 0.6, 0.8), bodyColor);

    // Đùi - hình hộp đơn giản
    drawCube(vec3(0, -1.0, 0), vec3(0, 0, 0), vec3(0.7, 2.0, 0.7), bodyColor);

    // Đầu gối - khớp nối đơn giản
    mat4 leftKnee = leftLeg * TRS(vec3(0, -2.0, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftKnee);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.6, 0.5, 0.6), silverColor);
    // Ống chân - đơn giản
    drawCube(vec3(0, -1.0, 0), vec3(0, 0, 0), vec3(0.6, 2.0, 0.6), bodyColor);

    // Mắt cá chân - đơn giản
    mat4 leftAnkle = leftKnee * TRS(vec3(0, -2.0, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftAnkle);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.5, 0.4, 0.5), silverColor);

    // Bàn chân - hình hộp lớn đơn giản
    mat4 leftFoot = leftAnkle * TRS(vec3(0, -0.2, 0.3), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftFoot);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.7, 0.4, 1.2), bodyColor);

    // Thêm một chi tiết nhỏ cho mũi chân
    drawCube(vec3(0, 0.1, 0.55), vec3(0, 0, 0), vec3(0.65, 0.1, 0.35), silverColor);

    // HỆ THỐNG ĐẨY PHẢN LỰC GUNDAM

    // Khung chính của bộ đẩy
    mat4 boosterBase = globalTransformMatrix * TRS(vec3(0.0, 0.5, -0.8), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(boosterBase);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1.2, 1.5, 0.6), silverColor);

    // Ống đẩy chính
    for (int i = -1; i <= 1; i += 2) {
        mat4 mainThruster = boosterBase * TRS(vec3(i * 0.3, 0.2, -0.2), vec3(0, 0, 0), vec3(1, 1, 1));
        cylinderTransformMatrix(mainThruster);
        drawCylinder(vec3(0, 0, 0), vec3(90, 0, 0), vec3(0.25, 0.25, 0.8), color(0.3, 0.3, 0.4));

        // Vòng kim loại bảo vệ
        drawCylinder(vec3(0, 0, 0.4), vec3(90, 0, 0), vec3(0.3, 0.3, 0.1), silverColor);
        drawCylinder(vec3(0, 0, -0.4), vec3(90, 0, 0), vec3(0.3, 0.3, 0.1), silverColor);

        // Lõi phản lực
        drawCylinder(vec3(0, 0, 0), vec3(90, 0, 0), vec3(0.2, 0.2, 0.7), highlightColor);
    }

    // Bộ tản nhiệt trung tâm
    mat4 heatVent = boosterBase * TRS(vec3(0, -0.4, 0.1), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(heatVent);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.6, 0.3, 0.4), bodyColor);

    // Cánh tản nhiệt
    for (int i = 0; i < 5; i++) {
        mat4 ventFin = heatVent * TRS(vec3(0, 0, 0), vec3(0, i * 72, 0), vec3(1, 1, 1));
        cubeTransformMatrix(ventFin);
        drawCube(vec3(0.3, 0, 0), vec3(0, 0, 0), vec3(0.6, 0.05, 0.1), silverColor);
    }

    // Ống dẫn năng lượng
    for (int i = -1; i <= 1; i += 2) {
        mat4 energyConduit = boosterBase * TRS(vec3(i * 0.4, 0.6, 0.1), vec3(0, 0, 0), vec3(1, 1, 1));
        cylinderTransformMatrix(energyConduit);
        drawCylinder(vec3(0, 0, 0), vec3(0, 0, 90), vec3(0.1, 0.1, 0.4), accentColor);

        // Đầu nối
        drawCylinder(vec3(0.2, 0, 0), vec3(0, 0, 0), vec3(0.15, 0.15, 0.15), silverColor);
        drawCylinder(vec3(-0.2, 0, 0), vec3(0, 0, 0), vec3(0.15, 0.15, 0.15), silverColor);
    }

    // Cánh ổn định bên hông
    for (int i = -1; i <= 1; i += 2) {
        mat4 stabilizer = globalTransformMatrix * TRS(vec3(i * 1.1, 0.2, -0.7), vec3(0, 0, i * 15), vec3(1, 1, 1));
        cubeTransformMatrix(stabilizer);
        drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.2, 0.8, 0.1), silverColor);
        drawCube(vec3(0, 0.4, 0), vec3(0, 0, 0), vec3(0.4, 0.1, 0.1), silverColor);
    }

    // Đèn báo hiệu
    for (int i = -1; i <= 1; i += 2) {
        for (int j = -1; j <= 1; j += 2) {
            mat4 indicator = boosterBase * TRS(vec3(i * 0.2, j * 0.3 + 0.1, 0.3), vec3(0, 0, 0), vec3(1, 1, 1));
            cubeTransformMatrix(indicator);
            drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0.1, 0.1, 0.1), highlightColor);
        }
    }
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
        khuyu4 -= 2; if (khuyu4 < 0) khuyu4 = 0;
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
        vai4 -= 2; if (vai4 < -60) vai4 = -60;
        break;
    case 'B':
        vai4 += 2; if (vai4 > 0) vai4 = 0;
        break;
    }
}