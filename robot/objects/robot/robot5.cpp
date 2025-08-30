#include "objects/robot5.h"

vec3 robot5_rotate(0, 0, 0), robot5_position(0, 0, 0);
GLfloat vai5 = 0.0f, dau5 = 0.0f;
GLfloat khuyu5 = 0.0f, cotay5 = 0.0f;

void drawRobot5(vec3 position, vec3 rotation, vec3 scale, bool enableInput) {
    if (enableInput) {
        rotation += robot5_rotate;
        position += robot5_position;
    }

    // ================= MÀU S?C =================
    color headColor = color(0.0f, 0.0f, 1.0f);
    color eyeColor = color(1.0f, 1.0f, 0.0f);
    color mouthColor = color(0.0f, 0.6f, 1.0f);
    color earColor = color(0.6f, 0.0f, 0.6f);
    color antenColor = color(0.0f, 1.0f, 0.0f);

    color bodyColor = color(0.0f, 0.6f, 0.0f);
    color shoulderColor = color(0.0f, 0.0f, 0.0f);

    color armColor = color(1.0f, 0.5f, 0.0f);
    color wristColor = color(0.8f, 0.0f, 0.0f);
    color handColor = color(0.0f, 0.0f, 1.0f);
    color stickColor = color(0.5f, 0.25f, 0.0f);

    color legColor = color(0.0f, 0.2f, 0.2f);
    color bootColor = color(0.5f, 0.0f, 0.3f);

    color neckColor = color(0.8f, 0.8f, 0.0f);
    color backpackColor = color(0.6f, 0.3f, 0.1f);
    color pocketColor = color(0.4f, 0.2f, 0.0f);

    // ================= MA TR?N TOÀN C?C =================
    mat4 globalTransformMatrix = TRS(position, rotation, scale);

    // ================= THÂN =================
    cubeTransformMatrix(globalTransformMatrix);
    drawCube(vec3(0, 1.1f, 0), vec3(0, 0, 0), vec3(2.6f, 2.0f, 1.2f), bodyColor);
    drawCube(vec3(0, -0.2f, 0), vec3(0, 0, 0), vec3(2.3f, 1.2f, 1.1f), bodyColor);
    // khôis n?i
    drawCube(vec3(0, 1.1f, 0), vec3(0, 0, 0), vec3(1.0f, 1.8f, 1.5f), bodyColor);
    drawCube(vec3(0, 1.3f, 0), vec3(0, 0, 0), vec3(1.8f, 1.0f, 1.5f), bodyColor);

    // Vai (?en)
    drawCube(vec3(-1.7, 1.7f, 0), vec3(0, 0, 0), vec3(0.9f, 0.8f, 1.0f), shoulderColor);
    drawCube(vec3(1.7f, 1.7f, 0), vec3(0, 0, 0), vec3(0.9f, 0.8f, 1.0f), shoulderColor);

    // ================= C? =================
    mat4 neck = globalTransformMatrix * TRS(vec3(0, 2.0f, 0), vec3(0, dau5, 0), vec3(0.8f, 0.6f, 0.8f));
    cubeTransformMatrix(neck);
    drawCube(vec3(0, 0.4, 0), vec3(0, 0, 0), vec3(1.5f, 0.6f, 0.8f), neckColor);

    // ================= ??U =================
    mat4 head = globalTransformMatrix * TRS(vec3(0, 3.3f, 0), vec3(0, 0, 0), vec3(1, 1, 1)) 
        * (enableInput ? Angel::RotateY(dau5) : identity());
    cubeTransformMatrix(head);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(2.0f, 2.0f, 1.2f), headColor);

    // M?t
    drawCube(vec3(-0.5f, 0.3f, 0.7f), vec3(0, 0, 0), vec3(0.4f, 0.4f, 0.1f), eyeColor);
    drawCube(vec3(0.5f, 0.3f, 0.7f), vec3(0, 0, 0), vec3(0.4f, 0.4f, 0.1f), eyeColor);

    // Mi?ng
    drawCube(vec3(0, -0.5f, 0.8f), vec3(0, 0, 0), vec3(1.0f, 0.3f, 0.1f), mouthColor);

    // Tai
    drawCube(vec3(-1.2f, 0.2f, 0), vec3(0, 0, 0), vec3(0.4f, 0.8f, 0.5f), earColor);
    drawCube(vec3(1.2f, 0.2f, 0), vec3(0, 0, 0), vec3(0.4f, 0.8f, 0.5f), earColor);

    // ================= BALÔ =================
    mat4 backpack = globalTransformMatrix * TRS(vec3(0, 0.6f, -0.8f), vec3(0, 0, 0), vec3(1.2f, 1.8f, 0.5f));
    cubeTransformMatrix(backpack);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(1.2f, 1.8f, 0.5f), backpackColor);

    // Túi bên trái
    drawCube(vec3(-0.7f, 0.0f, 0.0f), vec3(0, 0, 0), vec3(0.4f, 1.0f, 0.2f), pocketColor);
    // Túi bên ph?i
    drawCube(vec3(0.7f, 0.0f, 0.0f), vec3(0, 0, 0), vec3(0.4f, 1.0f, 0.2f), pocketColor);
    // kh?i n?i
    drawCube(vec3(0.f, 0.0f, -0.4f), vec3(0, 0, 0), vec3(0.7f, 1.2f, 0.5f), pocketColor);
    drawCube(vec3(0.f, 0.0f, 0.2f), vec3(0, 0, 0), vec3(0.7f, 1.2f, 0.5f), pocketColor);
    // ================= TAY TRÁI =================
    mat4 leftarm = globalTransformMatrix * TRS(vec3(-1.8f, 1.2f, 0), vec3(0, 0, 0), vec3(1, 1, 1)) 
        * (enableInput ? Angel::RotateX(-vai5) : identity());
    cubeTransformMatrix(leftarm);
    drawCube(vec3(0, -0.4f, 0), vec3(0, 0, 0), vec3(0.6f, 1.2f, 0.6f), armColor);
    drawCube(vec3(0, -1.3f, 0), vec3(0, 0, 0), vec3(0.8f, 0.6f, 0.6f), wristColor);
    drawCube(vec3(0, -1.8f, 0), vec3(0, 0, 0), vec3(0.4f, 0.6f, 0.4f), handColor);

    // ================= TAY PH?I  =================
    mat4 rightarm = globalTransformMatrix * TRS(vec3(1.8f, 1.2f, 0), vec3(0, 0, 0), vec3(1, 1, 1))
        * (enableInput ? Angel::RotateX(-vai5) : identity());
    cubeTransformMatrix(rightarm);
    drawCube(vec3(0, -0.4f, 0), vec3(0, 0, 0), vec3(0.6f, 1.2f, 0.6f), armColor);
    drawCube(vec3(0, -1.3f, 0), vec3(0, 0, 0), vec3(0.8f, 0.6f, 0.6f), wristColor);
    drawCube(vec3(0, -1.8f, 0), vec3(0, 0, 0), vec3(0.4f, 0.6f, 0.4f), handColor);
    drawCube(vec3(0, -2.6f, 0), vec3(-vai5, 0, 0), vec3(0.2f, 1.5f, 0.2f), stickColor);

    // ================= CHÂN TRÁI =================
    mat4 leftleg = globalTransformMatrix * TRS(vec3(-0.6f, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(leftleg);
    drawCube(vec3(0, -1.0f, 0), vec3(0, 0, 0), vec3(1.0f, 1.5f, 1.0f), legColor); // ?ùi
    drawCube(vec3(0, -2.0f, 0), vec3(0, 0, 0), vec3(0.8f, 0.8f, 0.8f), legColor);   // ??u g?i
    drawCube(vec3(0, -2.8f, 0), vec3(0, 0, 0), vec3(1.0f, 1.5f, 1.0f), legColor); // B?p chân
    drawCube(vec3(0, -3.9f, 0), vec3(0, 0, 0), vec3(1.0f, 0.8f, 1.2f), bootColor); // Giày

    // ================= CHÂN PH?I =================
    mat4 rightleg = globalTransformMatrix * TRS(vec3(0.6f, 0, 0), vec3(0, 0, 0), vec3(1, 1, 1));
    cubeTransformMatrix(rightleg);
    drawCube(vec3(0, -1.0f, 0), vec3(0, 0, 0), vec3(1.0f, 1.5f, 1.0f), legColor);
    drawCube(vec3(0, -2.0f, 0), vec3(0, 0, 0), vec3(0.8f, 0.8f, 0.8f), legColor);
    drawCube(vec3(0, -2.8f, 0), vec3(0, 0, 0), vec3(1.0f, 1.5f, 1.0f), legColor);
    drawCube(vec3(0, -3.9f, 0), vec3(0, 0, 0), vec3(1.0f, 0.8f, 1.2f), bootColor);
}

// ================= BÀN PHÍM =================
void Robot5Keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'a': robot5_position.z -= 0.5f; break;
    case 'd': robot5_position.z += 0.5f; break;
    case 's': robot5_position.x -= 0.5f; break;
    case 'w': robot5_position.x += 0.5f; break;
    case 'q': robot5_rotate.y += 2; break;
    case 'e': robot5_rotate.y -= 2; break;
    case 'l': dau5 += 2; if (dau5 > 30) dau5 = 30; break;
    case 'L': dau5 -= 2; if (dau5 < -30) dau5 = -30; break;
    case 'b': vai5 += 2; if (vai5 > 60) vai5 = 60; break;
    case 'B': vai5 -= 2; if (vai5 < -60) vai5 = -60; break;
    default: break;
    }
}