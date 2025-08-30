#include "objects/RobotStore.h"

void drawRobotStore(vec3 position, vec3 rotation, vec3 scale)
{
    mat4 globalTransformMatrix = cubeTransform(position, rotation, scale);
    cylinderTransform(position, rotation, scale);

    color frameColor = color(0.6, 0.7, 0.9, 1);        // Xanh lam nhạt
    color frameColor1 = color(0.7, 0.9, 1.0, 1);       // Xanh ngọc sáng
    color frameColor2 = color(0.8, 0.9, 0.95, 1);      // Gần màu trắng lạnh
    color shelfColor = color(0.75, 0.85, 0.95, 1);     // Xanh dương nhạt
    color color1 = color(0.3, 0.4, 0.5, 1);            // Xanh xám
    color color2 = color(0.2, 0.3, 0.4, 1);            // Xanh đậm dịu
    color wallColor = color(180, 220, 255, 255) / 255.0f; // Màu tường xanh bầu trời nhạt
    color color4 = color(0.6, 0.75, 0.85, 1);          // Nền xanh lam ấm
    color red = color(0.4, 0.2, 0.5, 1);               // Đỏ tím trầm (chuyển sang màu lạnh)

    // nền
    drawCylinder(vec3(0, 2, 10), vec3(0, 0, 0), vec3(20, .1, 15), color2);


    drawCube(vec3(0, 1.78, 0), vec3(0, 0, 0), vec3(65, .5, 45), color4);
    drawCube(vec3(0, 0, 0), vec3(0, 0, 0), vec3(70, 4, 50), frameColor);
    drawCube(vec3(0, 40.5, 0), vec3(0, 0, 0), vec3(72, 1.5, 52), frameColor);
    drawCube(vec3(0, 48, 0), vec3(0, 0, 0), vec3(70, 15, 50), frameColor1);
    drawCube(vec3(0, 55, 0), vec3(0, 0, 0), vec3(72, 1.5, 52), frameColor);
    drawCube(vec3(-33, 20, 0), vec3(0, 0, 0), vec3(2, 40, 48), wallColor);
    drawCube(vec3(0, 20, -23), vec3(0, 0, 0), vec3(68, 40, 2), wallColor);

    drawCube(vec3(-33, 5, -23), vec3(0, 0, 0), vec3(3, 8, 3), color1);
    drawCube(vec3(-33, 5, 23), vec3(0, 0, 0), vec3(3, 8, 3), color1);
    drawCube(vec3(33, 5, -23), vec3(0, 0, 0), vec3(3, 8, 3), color1);

    drawCube(vec3(-33, 8, 0), vec3(0, 0, 0), vec3(2.8, 2, 48), color1);
    drawCube(vec3(-33, 5, 0), vec3(0, 0, 0), vec3(2.8, 6, 48), color2);

    drawCube(vec3(0, 8, -23), vec3(0, 0, 0), vec3(68, 2, 2.8), color1);
    drawCube(vec3(0, 5, -23), vec3(0, 0, 0), vec3(68, 6, 2.4), color2);

    //khung cua kinh
    drawCube(vec3(-21, 3, 23), vec3(0, 0, 0), vec3(23, 2, 2), color1);
    drawCube(vec3(21, 3, 23), vec3(0, 0, 0), vec3(23, 2, 2), color1);
    drawCube(vec3(33, 5, 23), vec3(0, 0, 0), vec3(3, 8, 3), color1);
    drawCube(vec3(33, 20, 23), vec3(0, 0, 0), vec3(2, 40, 2), color1);
    drawCube(vec3(10, 20, 23), vec3(0, 0, 0), vec3(2, 40, 2), color1);
    drawCube(vec3(-10, 20, 23), vec3(0, 0, 0), vec3(2, 40, 2), color1);
    drawCube(vec3(33, 3, 0), vec3(0, 0, 0), vec3(2, 2, 48), color1);

    //bac thang
    drawCube(vec3(0, 1, 26), vec3(0, 0, 0), vec3(20, 2, 2), frameColor1);
    drawCube(vec3(0, -.5, 27), vec3(0, 0, 0), vec3(20, 2, 5), frameColor1);

    //duong
    drawCube(vec3(0, -2, 0), vec3(0, 0, 0), vec3(100, 1, 100), frameColor);


	//be trung bay
	drawCube(vec3(7, 5, -17), vec3(0, 0, 0), vec3(48, 5, 10), frameColor1); 

    //hop do trong tu
	drawCube(vec3(-28, 5, 15), vec3(0, 90, 0), vec3(10, 5, 5), color(1,1,0,1));



}