//include core engine

#include <core/openGL.h>		// open gl and utilities
#include <core/camera.h>		// camera
#include <core/shaders.h>		// shaders
#include <core/lighting.h>		// lighting
#include <core/ui.h>			// user interface

//include objects
#include <objects/cube.h>		
#include <objects/cylinder1.h>
#include <objects/cylinder.h>		
#include <objects/sphere.h>

//robot
#include "objects/robot1.h"	// robot 1
#include "objects/robot2.h"	// robot 2
#include "objects/robot3.h"	// robot 3
#include "objects/robot4.h"	// robot 4
#include "objects/robot5.h"	// robot 5

//scene objects
#include "objects/shelf.h"	
#include "objects/computer.h"	
#include "objects/cabinet.h"
#include "objects/cabinet1.h"
#include "objects/table.h"	
#include "objects/lamp.h"
#include "objects/chair.h"
#include "objects/sign.h"
#include "objects/RobotStore.h"
#include "objects/keyboard.h"
#include "objects/mouse.h"
#include "objects/Salesman.h"


using namespace engine;
using namespace std;

ui::button btnDay;
ui::button btnNight;
ui::button btnSunset;



//DAY TIME PROTOTYPE FUNCS
void day();

void night();


//LIGHTING

directionalLight* sun_light;
pointLight* lamp_light_1;
pointLight* lamp_light_2;
pointLight* lamp_light_3;

bool leftMouseButtonDown = false;
int lastMouseX, lastMouseY;

const char* defaultSelectedInfo = ">> None (Press to select) ";
const char* selectedInfo = defaultSelectedInfo;
const char* selectedInputInfo = "";
int selectedIndex = -1;

bool disableCamRot = false;

void onGUI()
{
	glColor3f(1.0, 1.0, 1.0);

	ui::text2D("Robot Store", 10, 10, ui::window_height - 20, color(1, 1, 0, 1));
	ui::text2D("middle mouse - zoom in/out", 14, 10, ui::window_height - 50);
	ui::text2D("left mouse - rotate camera", 14, 10, ui::window_height - 70);

	btnDay = ui::button2D("Day", 14, 80, 40, ui::window_width - 90, ui::window_height - 100, color(.9f, .9f, .9f, 1), color(0, 0, 0, 1));
	btnNight = ui::button2D("Night", 14, 80, 40, ui::window_width - 90, ui::window_height - 150, color(.1f, .1f, .1f, 1), color(1, 1, 1, 1));
	btnDay.onClick = day;
	btnNight.onClick = night;

	ui::text2D(selectedInfo, 14, 10, ui::window_height - 100);
	ui::text2D("1 - robot1", 14, 15, ui::window_height - 120);
	ui::text2D("2 - robot2", 14, 15, ui::window_height - 140);
	ui::text2D("3 - robot3", 14, 15, ui::window_height - 160);
	ui::text2D("4 - robot4", 14, 15, ui::window_height - 180);
	ui::text2D("5 - robot4", 14, 15, ui::window_height - 200);
	ui::text2D("6 - cabinet", 14, 15, ui::window_height - 220);
	ui::text2D("7 - Salesman", 14, 15, ui::window_height - 240);
	ui::text2D("8 - None", 14, 15, ui::window_height - 260);

	ui::text2D("0 - Camera View", 14, 15, ui::window_height - 280);

	ui::text2D(selectedInputInfo, 14, 15, 50);
}


void setupLights()
{
	sun_light = oneDirectionalLight(vec3(1, 10, 2), vec3(-.5, -1, -.5));
		sun_light->ambient =
		sun_light->diffuse = 
		sun_light->specular = color3(0.15f, 0.15f, 0.15f);

	lamp_light_1 = addPointLight(vec3());
	lamp_light_1->radius = 100;
	lamp_light_1->ambient = color3(1, 1, 1);
	lamp_light_1->diffuse =
		lamp_light_1->specular = color3(1, 1, 0);

	lamp_light_2 = addPointLight(vec3());
	lamp_light_2->radius = 100;
	lamp_light_2->ambient = color3(1, 1, 1);
	lamp_light_2->diffuse =
		lamp_light_2->specular = color3(0, 1, 1);

	lamp_light_3 = addPointLight(vec3());
	lamp_light_3->radius = 100;
	lamp_light_3->ambient = color3(1, 1, 1);
	lamp_light_3->diffuse = 
		lamp_light_3->specular = color3(1, 0, 1);
}


void day()
{
	sun_light->ambient = 
		sun_light->diffuse = 
		sun_light->specular = color3(.9f, .9f, .9f);
}

void night()
{
	sun_light->ambient =
		sun_light->diffuse =
		sun_light->specular = color3(.1f, .1f, .1f);
}



void setUpCam()
{
	int mX = 0;
	int mY = 0;
	for (int i = 0; i < 60; i++)
	{
		lastMouseX = 0;
		lastMouseY = 0;
		cameraMotion(-1, 1, lastMouseX, lastMouseY);
	}

	for (int i = 0; i < 45; i++)
		zoomCamera(-1);
}

void initialize_before_display()
{
	engine::initDefaultShaders();
	setupLights();
	setUpCam();
	initCube();
	initCylinder1();
	initCylinder();
	initSphere();
	initSign();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	//drawLamp(vec3(-32, 45, 20), vec3(), vec3(5, 5, 5), lamp_light_1);

	//drawLamp(vec3(32, 45, 20), vec3(), vec3(5, 5, 5), lamp_light_2);

	drawLamp(vec3(0, 45, 0), vec3(), vec3(5, 5, 5), lamp_light_3);

	drawLamp(vec3(-32, 45, -20), vec3(), vec3(5, 5, 5), lamp_light_1);

	drawLamp(vec3(32, 45, -20), vec3(), vec3(5, 5, 5), lamp_light_2);


	drawRobotStore(vec3(0, 0, 0), vec3(), vec3(1.5, 1.5, 1.5));

	drawCabinet1(vec3(-42, 5, 18.5), vec3(0, 90, 0), vec3(25, 20, 30), false);

	drawTable(vec3(-22, 13, 17), vec3(0, -90, 0), vec3(25, 20, 20));

	drawSalesman(vec3(-32, 17, 17), vec3(0, 0, 0), vec3(8, 8, 8), true);

	drawComputer(vec3(-21, 17, 17), vec3(0, 180, 0), vec3(10, 10, 10));

	drawKeyboard(vec3(-24.5, 13.8, 17), vec3(0, -90, 0), vec3(5, 5, 5));

	drawMouse(vec3(-24.5, 13.8, 24), vec3(0, -90, 0), vec3(5, 5, 5));

	drawTable(vec3(32, 13, 13), vec3(0, 180, 0), vec3(25, 20, 20));

	drawChair(vec3(32, 3, 25), vec3(0, 180, 0), vec3(8, 12, 8));

	drawCabinet(vec3(-42, 13, -15), vec3(0, 90, 0), vec3(30, 20, 30), true);



	

	drawRobot2(vec3(-20, 17, -27), vec3(0, 0, 0), vec3(6, 6, 6), false);

	drawRobot5(vec3(-6, 22, -27), vec3(0, 0, 0), vec3(3, 3, 3), false);

	drawRobot4(vec3(6, 30, -27), vec3(0, 0, 0), vec3(3, 3.5, 3), false);

	drawRobot1(vec3(23, 38, -27), vec3(0, 0, 0), vec3(4, 4, 4), false);

	drawRobot3(vec3(40, 28, -27), vec3(0, 0, 0), vec3(3, 4, 3), false);

	

	
	
	
	drawRobot1(vec3(-40, 21, 9), vec3(0, -90, 0), vec3(2, 0.8, 1.5), false);
	drawRobot2(vec3(-40, 19, 15), vec3(0, 90, 0), vec3(2, 2, 2), false);
	drawRobot3(vec3(-40, 21, 19), vec3(0, 90, 0), vec3(1, 1, 1), false);
	drawRobot4(vec3(-40, 21, 23), vec3(0, 90, 0), vec3(1, 1, 1), false);
	drawRobot5(vec3(-40, 20, 28), vec3(0, 90, 0), vec3(1, 1, 1), false);


	

	
	drawRobot1(vec3(-40, 31, 9), vec3(0, -90, 0), vec3(2, 0.8, 1.5), false);
	drawRobot2(vec3(-40, 29, 15), vec3(0, 90, 0), vec3(2, 2, 2), false);
	drawRobot3(vec3(-40, 31, 19), vec3(0, 90, 0), vec3(1, 1, 1), false);
	drawRobot4(vec3(-40, 31, 23), vec3(0, 90, 0), vec3(1, 1, 1), false);
	drawRobot5(vec3(-40, 30, 28), vec3(0, 90, 0), vec3(1, 1, 1), false);


	drawRobot2(vec3(-40, 17, -10), vec3(0, 90, 0), vec3(3.5, 3, 3), false);
	drawRobot2(vec3(-40, 17, -3), vec3(0, 90, 0), vec3(3.5, 3, 3), false);

	drawRobot3(vec3(-40, 39, -3), vec3(0, 90, 0), vec3(2, 1, 1), false);
	drawRobot3(vec3(-40, 39, -10), vec3(0, 90, 0), vec3(2, 1, 1), false);

	drawRobot5(vec3(-40, 37, -20), vec3(0, 90, 0), vec3(1.5, 1, 1.5), false);
	drawRobot5(vec3(-40, 37, -28), vec3(0, 90, 0), vec3(1.5, 1, 1.5), false);

	drawRobot4(vec3(-40, 29, -3), vec3(0, 90, 0), vec3(2, 1, 2), false);
	drawRobot4(vec3(-40, 29, -10), vec3(0, 90, 0), vec3(2, 1, 2), false);

	drawRobot1(vec3(-40, 29, -20), vec3(0, 90, 0), vec3(1.2, 0.8, 2), false);
	drawRobot1(vec3(-40, 29, -27), vec3(0, 90, 0), vec3(1.2, 0.8, 2), false);

	drawRobot2(vec3(-40, 17, -20), vec3(0, 90, 0), vec3(3.5, 3, 3), false);
	drawRobot4(vec3(-40, 20, -27), vec3(0, 90, 0), vec3(2, 1, 2), false);

	


	

	if (selectedIndex == 1) 
		drawRobot1(vec3(32, 28, 13), vec3(0, 0, 0), vec3(2, 2, 2), true);	//selected robot1
	
	if (selectedIndex == 2)
		drawRobot2(vec3(32, 20, 13), vec3(0, 0, 0), vec3(5, 5, 5), true);;	//selected robot2
	
	if (selectedIndex == 3)
		drawRobot3(vec3(32, 28, 17), vec3(0, 0, 0), vec3(2, 2, 2), true);	//selected robot3

	if (selectedIndex == 4)
		drawRobot4(vec3(32, 28, 17), vec3(0, 0, 0), vec3(2, 2, 2), true);	//selected robot4

	if(selectedIndex == 5)
		drawRobot5(vec3(32, 22, 13), vec3(0, 0, 0), vec3(2, 2, 2), true);	//selected robot5

	drawSign(vec3(0, 73, 40), vec3(0, 0, 0), vec3(105, 20, 30), color(1, 1, 1, 1));

	onGUI();

	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(20, timer, value++);
}
void glutRobot1Motion(int value) {
	updateRobot1Motion();
	glutPostRedisplay();
	glutTimerFunc(16, glutRobot1Motion, 0); // khoảng 60 FPS
}
void input(unsigned char key, int mouseX, int mouseY)
{
	switch (key)
	{
	case '1':
		selectedInfo = ">> Robot1";
		selectedIndex = 1;
		selectedInputInfo = "q,e: rotate -  a,w,s,d: move - l,j,k,h,m,i: control - n: go";
		break;
	case '2':
		selectedInfo = ">> Robot2";
		selectedIndex = 2;
		selectedInputInfo = "q,e: xoay - a,w,s,d: di chuyen - l,k,b: control";
		break;
	case '3':
		selectedInfo = ">> Robot3";
		selectedIndex = 3;
		selectedInputInfo = "q,e: xoay - a,w,s,d: di chuyen - l,j,k,b: control";
		break;
	case '4':
		selectedInfo = ">> Robot4";
		selectedIndex = 4;
		selectedInputInfo = "q,e: xoay - a,w,s,d: di chuyen - l,j,k,b: control";
		break;
	case '5':
		selectedInfo = ">> Robot5";
		selectedIndex = 5;
		selectedInputInfo = "q,e: xoay - a,w,s,d: di chuyen - l,j,k,b: control";
		break;
	case '6':
		selectedInfo = ">> Cabinet";
		selectedIndex = 6;
		selectedInputInfo = "t, p: close - T (shift + t), p (shift + p): open";
		break;
	case '7':
		selectedInfo = ">> Salesman";
		selectedIndex = 7;
		selectedInputInfo = "q,e: xoay - a,w,s,d: move";
		break;
	case '8':
		selectedInfo = defaultSelectedInfo;
		selectedIndex = -1;
		selectedInputInfo = "";
		break;
	case '0':
	{
		engine::setTargetPos(vec4(32, 28, 27, 1));
		engine::setCameraPos(vec4(35, 30, 40, 1));

		disableCamRot = !disableCamRot;

		if (!disableCamRot)
			engine::setTargetPos(vec4(0, 0, 0, 1));
	}
	break;
	case 27:
		exit(0);
		break;
	}

	switch (selectedIndex)
	{
	case 1:
		Robot1Keyboard(key, mouseX, mouseY); //Robot1 keyboard
		break;
	case 2:
		Robot2Keyboard(key, mouseX, mouseY); //Robot2 keyboard
		break;
	case 3:
		Robot3Keyboard(key, mouseX, mouseY);//Robot3 keyboard
		break;
	case 4:
		Robot4Keyboard(key, mouseX, mouseY); //Robot4 keyboard
		break;
	case 5:
		Robot5Keyboard(key, mouseX, mouseY); //Robot5 keyboard
		break;
	case 6:
		cabinetKeyboard(key, mouseX, mouseY);
		break;
	case 7:
		SalesmanKeyboard(key, mouseX, mouseY);
		break;
	default:
		selectedInputInfo = "";
		break;
	}

	glutPostRedisplay();
}


void resharp(int w, int h)
{
	setupCamera(w, h, 0.1f, 1000);
	ui::screenChange(w, h);

	glutReshapeWindow(w, h);
	glViewport(0, 0, w, h);
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	btnDay.onEvent(button, state, x, y);
	btnNight.onEvent(button, state, x, y);

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		leftMouseButtonDown = true;
		lastMouseX = x;
		lastMouseY = y;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		leftMouseButtonDown = false;
	}
	else if (button == 3) // Scroll up
	{
		zoomCamera(1);
	}
	else if (button == 4) // Scroll down
	{
		zoomCamera(-1);
	}
}

void motion(int x, int y)
{
	if (leftMouseButtonDown && !disableCamRot)
		cameraMotion(x, y, lastMouseX, lastMouseY);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glEnable(GL_MULTISAMPLE);
	glutInitWindowSize(840, 600);
	glutInitWindowPosition(100, 80);
	glutCreateWindow("Robot Store");

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "GLEW Init Error: " << glewGetErrorString(err) << std::endl;
		return -1;
	}

	glutDisplayFunc(display);
	glutReshapeFunc(resharp);
	glutIdleFunc(idle);
	glutTimerFunc(20, timer, 0);
	glutTimerFunc(10, glutRobot1Motion, 0);
	glutKeyboardFunc(input);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);


	initialize_before_display();

	glutMainLoop();

	engine::disposeLights();

	return 0;
}
