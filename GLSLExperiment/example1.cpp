//Chương trình vẽ 1 hình lập phương đơn vị theo mô hình lập trình OpenGL hiện đại

#include "Angel.h"  /* Angel.h là file tự phát triển (tác giả Prof. Angel), có chứa cả khai báo includes glew và freeglut*/


// remember to prototype
void generateGeometry( void );
void initGPUBuffers( void );
void shaderSetup( void );
void display( void );
void keyboard( unsigned char key, int x, int y );


typedef vec4 point4;
typedef vec4 color4;
using namespace std;

// Số các đỉnh của các tam giác
const int NumPoints = 36;

point4 points[NumPoints]; /* Danh sách các đỉnh của các tam giác cần vẽ*/
color4 colors[NumPoints]; /* Danh sách các màu tương ứng cho các đỉnh trên*/


point4 vertices[8]; /* Danh sách 8 đỉnh của hình lập phương*/
color4 vertex_colors[8]; /*Danh sách các màu tương ứng cho 8 đỉnh hình lập phương*/

GLuint program, model_loc, view_loc, projection_loc;

GLfloat Theta[] = { 0.0f, 0.0f, 0.0f };
// Các biến điều khiển dịch chuyển
GLfloat tx = 0.0f, ty = 0.0f, tz = 0.0f, kz = 0.0f;

void initCube()
{
	// Gán giá trị tọa độ vị trí cho các đỉnh của hình lập phương
	vertices[0] = point4(-0.5, -0.5, 0.5, 1.0);
	vertices[1] = point4(-0.5, 0.5, 0.5, 1.0);
	vertices[2] = point4(0.5, 0.5, 0.5, 1.0);
	vertices[3] = point4(0.5, -0.5, 0.5, 1.0);
	vertices[4] = point4(-0.5, -0.5, -0.5, 1.0);
	vertices[5] = point4(-0.5, 0.5, -0.5, 1.0);
	vertices[6] = point4(0.5, 0.5, -0.5, 1.0);
	vertices[7] = point4(0.5, -0.5, -0.5, 1.0);

	// Gán giá trị màu sắc cho các đỉnh của hình lập phương	
	vertex_colors[0] = color4(0.0, 0.0, 0.0, 1.0); // black
	vertex_colors[1] = color4(1.0, 0.0, 0.0, 1.0); // red
	vertex_colors[2] = color4(1.0, 1.0, 0.0, 1.0); // yellow
	vertex_colors[3] = color4(0.0, 1.0, 0.0, 1.0); // green
	vertex_colors[4] = color4(0.0, 0.0, 1.0, 1.0); // blue
	vertex_colors[5] = color4(1.0, 0.0, 1.0, 1.0); // magenta
	vertex_colors[6] = color4(1.0, 1.0, 1.0, 1.0); // white
	vertex_colors[7] = color4(0.0, 1.0, 1.0, 1.0); // cyan
}
int Index = 0;
void quad(int a, int b, int c, int d)  /*Tạo một mặt hình lập phương = 2 tam giác, gán màu cho mỗi đỉnh tương ứng trong mảng colors*/
{
	colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
	colors[Index] = vertex_colors[b]; points[Index] = vertices[b]; Index++;
	colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
	colors[Index] = vertex_colors[a]; points[Index] = vertices[a]; Index++;
	colors[Index] = vertex_colors[c]; points[Index] = vertices[c]; Index++;
	colors[Index] = vertex_colors[d]; points[Index] = vertices[d]; Index++;
}
void makeColorCube(void)  /* Sinh ra 12 tam giác: 36 đỉnh, 36 màu*/

{
	quad(1, 0, 3, 2);
	quad(2, 3, 7, 6);
	quad(3, 0, 4, 7);
	quad(6, 5, 1, 2);
	quad(4, 5, 6, 7);
	quad(5, 4, 0, 1);
}
void generateGeometry( void )
{
	initCube();
	makeColorCube();
}


void initGPUBuffers( void )
{
	// Tạo một VAO - vertex array object
	GLuint vao;
    glGenVertexArrays( 1, &vao );     
    glBindVertexArray( vao );

    // Tạo và khởi tạo một buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(points)+sizeof(colors), NULL, GL_STATIC_DRAW );

	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(points), sizeof(colors), colors); 
	
}


void shaderSetup( void )
{
	// Nạp các shader và sử dụng chương trình shader
    program = InitShader( "vshader1.glsl", "fshader1.glsl" );   // hàm InitShader khai báo trong Angel.h
    glUseProgram( program );

    // Khởi tạo thuộc tính vị trí đỉnh từ vertex shader
    GLuint loc_vPosition = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray( loc_vPosition );
    glVertexAttribPointer(loc_vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );

	GLuint loc_vColor = glGetAttribLocation(program, "vColor");
	glEnableVertexAttribArray(loc_vColor);
	glVertexAttribPointer(loc_vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(points)));

	model_loc = glGetUniformLocation(program, "model"); // Lấy địa chỉ của biến uniform model trong shader
	view_loc = glGetUniformLocation(program, "view");
	projection_loc = glGetUniformLocation(program, "projection");
	glEnable(GL_DEPTH_TEST); // Bật kiểm tra độ sâu để vẽ hình lập phương đúng thứ tự

    glClearColor( 1.0, 1.0, 1.0, 1.0 );        /* Thiết lập màu trắng là màu xóa màn hình*/
}
mat4 ctm;
GLfloat alpha = 0, beta = 0, delta = 0, gama = 0, xichma = 0; // Góc quay của cánh cửa
;
void chanban(GLfloat x, GLfloat y, GLfloat z) {
	mat4 instance = Translate(x, y, z) * Scale(0.06f, 0.8f, 0.06f);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, ctm * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void nganban() {
	mat4 instance = Translate(0, 0, kz) * Translate(0, 0, 0) * Scale(0.74f, 0.02f, 0.6f);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, ctm * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void canhtu() {
	mat4 instance = Translate(0.2, 0, 0) * RotateY(delta) * Translate(-0.2, 0, 0) * 
		Translate(0, 0, 0) * Scale(0.4f, 0.7f, 0.02f);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, ctm * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	mat4 handle = Translate(0, 0, 0) * Scale(0.04, 0.2, 0.02); // Tạo tay nắm cửa
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, ctm * Translate(0.2, 0, 0) *
		RotateY(delta) * Translate(-0.2, 0, 0) * Translate(-0.1, 0, 0.02f) * handle);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void hoctu() {
	mat4 instance = Translate(0, 0, 0) * Scale(0.4f, 0.7f, 0.62f);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, ctm * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	ctm = ctm * Translate(0, 0, 0.0)  * Translate(0,0,0.33f);
	canhtu();
}
void caiban() {
	mat4 instance = Translate(0.0, 0.0, 0.0) * Scale(1.2, 0.02f, 0.6f);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, ctm * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	chanban(-0.57f, -0.41f, 0.27f);
	chanban(-0.57f, -0.41f, -0.27f);
	chanban(0.57f, -0.41f, -0.27f);
	chanban(0.57f, -0.41f, 0.27f);
	ctm = ctm * Translate(-0.2f, -0.14f, 0);
	nganban();
	ctm = ctm  * Translate(0.37, -0.4f, 0) * Translate(0.2f, 0.14f, 0);
	hoctu();
	
}
void dovat(GLfloat x, GLfloat y, GLfloat z, GLfloat sx, GLfloat sy, GLfloat sz) {
	mat4 instance = Translate(x, y, z) * Scale(sx, sy, sz);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, ctm * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints); /* Vẽ đồ vật */
}

void canhcuaso() {
	mat4 instance = Translate(0,0,0)  * Scale(1.0f, 1.0f, 0.02f); // Cánh cửa đóng mở
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, ctm * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void taynamcuaso(GLfloat x, GLfloat y, GLfloat z) {
	mat4 instance = Translate(0,0,0) * Scale(0.2f, 0.04f, 0.04f); // Tạo tay nắm cửa sổ
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, ctm * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
void cuaso() {
	dovat(-0.5, 0, 0, 0.05, 1, 0.05); // Cửa sổ trái
	dovat(0.5, 0, 0, 0.05, 1, 0.05); // Cửa sổ phải
	dovat(0, 0.5, 0, 1, 0.05, 0.05); // Cửa sổ trên
	dovat(0, -0.5, 0, 1, 0.05, 0.05); // Cửa sổ dưới
	ctm = ctm * Translate(0, 0.5, 0) * RotateX(gama) * Translate(0, -0.5, 0);
	canhcuaso(); // Cánh cửa sổ
	ctm = ctm * Translate(-0.1, 0, 0) * RotateZ(xichma) * Translate(0.1, 0, 0);

	taynamcuaso(0.1,0,0);
}


void khungcua() {
	dovat(-0.515f, 0, 0, 0.03f, 2.26f, 0.05f); // khung trái
	dovat(0.515f, 0, 0, 0.03f, 2.26f, 0.05f); // khung phải
	dovat(0, 1.115, 0, 1, 0.03f, 0.05f); // khung trên
}
mat4 trai = mat4(1.0);
mat4 phai = mat4(1.0);
void taynamtrai(GLfloat x, GLfloat y, GLfloat z) {
	mat4 instance = Translate(x, y, z) * Scale(0.02f, 0.2f, 0.04f);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, trai * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints); /* Vẽ tay nắm cửa */
}
void taynamphai(GLfloat x, GLfloat y, GLfloat z) {
	mat4 instance = Translate(x, y, z) * Scale(0.02f, 0.2f, 0.04f);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, phai * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints); /* Vẽ tay nắm cửa */
}
void canhtrai() {
	mat4 instance = Translate(-0.5, 0, 0) * RotateY(beta) * Translate(-0.25, 0, 0) * 
		Translate(0.5, 0, 0) *  Scale(-0.5f, 2.2f, -0.02f); // Quay cửa 120 độ
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, trai * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	trai = trai * Translate(-0.5, 0, 0) * RotateY(beta) * Translate(0.5, 0, 0);
	taynamtrai(-0.25, 0, 0); // Tạo tay nắm cửa bên trái
}
void canhphai() {
	mat4 instance = Translate(0.5, 0, 0) * RotateY(alpha) * Translate(0.25, 0, 0) * 
		Translate(-0.5, 0, 0) *  Scale(-0.5f, 2.2f, -0.02f); // Quay cửa 120 độ
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, phai * instance);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
	phai = phai * Translate(0.5, 0, 0) * RotateY(alpha) * Translate(-0.5, 0, 0);
	taynamphai(0.25, 0, 0); // Tạo tay nắm cửa bên phải
}
void caicua() {
	/*ctm = ctm * Translate(tx, ty, tz) * RotateY(Theta[1]);*/
	khungcua(); // Vẽ khung cửa
	trai = ctm;
	phai = ctm;
	canhtrai(); // Vẽ cánh cửa bên trái
	canhphai(); // Vẽ cánh cửa bên phải
}

mat4 quat; // Ma trận mô hình cho cánh quạt
void canhQuat(GLfloat x, GLfloat y, GLfloat z, GLfloat Ry) {
	mat4 a = RotateY(Ry) * Translate(x, y, z) *  Scale(4, 0.1f, 0.5f);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, quat * a);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);

}
void truQuat() {
	mat4 a = Translate(0, 0, 0) * Scale(0.2f, 2, 0.2f);
	glUniformMatrix4fv(model_loc, 1, GL_TRUE, quat * a);
	glDrawArrays(GL_TRIANGLES, 0, NumPoints);
}
float speed = 0;
void quayQuatTuDong() {
	Theta[1] += 0.1;
	if (Theta[1] > 360.0) {
		Theta[1] -= 360.0;
	}
	glutPostRedisplay();
}
void Quat()
{	
	truQuat();  //trụ quạt
	quat = quat * Translate(0, -1, 0) * RotateY(speed);
	canhQuat(-2, 0, 0, 0); //cánh quạt 1
	canhQuat(-2, 0, 0, 120);  // cánh quạt 2
	canhQuat(-2, 0, 0, 240);  //cánh quạt 3
}


void display( void )
{
    glClear( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );       

	vec4 eye(-1.0, 1.0, 3.0, 1.0); // Vị trí của mắt z càng lớn càng xa hình thì hình càng nhỏ
	vec4 at(0.0, 0.0, 0.0, 1.0); // Điểm nhìn
	vec4 up(0.0, 1.0, 0.0, 1.0); // Hướng lên
	mat4 view = LookAt(eye, at, up);

	mat4 frustum = Frustum(-1, 1, -1, 1, 1, 10.0); // chỉnh r, l, b, t giảm đi thì hình sẽ lớn hơn
	mat4 ortho = Ortho(-1, 1, -1, 1, 2.0, 100.0);
	// Nên dùng perspective hơn
	mat4 projection = Perspective(45.0, 1.0, 0.1, 10.0); //FOV = 45 càng nhỏ thi hình càng lớn
	glUniformMatrix4fv(view_loc, 1, GL_TRUE, view);
	glUniformMatrix4fv(projection_loc, 1, GL_TRUE, projection);

	ctm = mat4(1.0);
	quat = mat4(1.0); // Khởi tạo ma trận mô hình và ma trận quạt
	// ctm cho cửa sổ, bàn, tủ
	ctm = ctm * Translate(tx, ty, tz) * RotateX(Theta[0]) * RotateY(Theta[1]) * RotateZ(Theta[2]);

	quat = quat * Translate(tx, ty, tz) * Translate(0, 0, -1.0f) * RotateY(Theta[1]) * RotateX(Theta[0]) * RotateZ(Theta[2]);
	/*caiban();*/
	caicua();
	/*Quat();*/
	/*cuaso();*/
	glutSwapBuffers();									   
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	// xoay theo các trục
	case 'a':
		Theta[0] += 5;
		if (Theta[0] > 360) Theta[0] = 0;
		glutPostRedisplay();
		break;
	case 'A':
		Theta[0] -= 5;
		if (Theta[0] < 0) Theta[0] = 360;
		glutPostRedisplay();
		break;
	case 'b':
		Theta[1] += 5;
		if (Theta[1] > 360) Theta[1] = 0;
		glutPostRedisplay();
		break;
	case 'B':
		Theta[1] -= 5;
		if (Theta[1] < 0) Theta[1] = 360;
		glutPostRedisplay();
		break;
	case 'c':
		Theta[2] += 5;
		if (Theta[2] > 360) Theta[2] = 0;
		glutPostRedisplay();
		break;
	case 'C':
		Theta[2] -= 5;
		if (Theta[2] < 0) Theta[2] = 360;
		glutPostRedisplay();
		break;
	// dịch chuyển theo các trục
	case 'd':
		tx += -0.1f;
		if (tx < -1.0f) tx = -1.0f;
		glutPostRedisplay();
		break;
	case 'D':
		tx += 0.1f;
		if (tx > 1.0f) tx = 1.0f;
		glutPostRedisplay();
		break;
	case 'e':
		ty += 0.1f;
		if (ty > 1) ty = 1;
		glutPostRedisplay();
		break;
	case 'E':
		ty -= 0.1f;
		if (ty < -1) ty = -1;
		glutPostRedisplay();
		break;
	case 'f':
		tz += 0.1f;
		if (tz > 1) tz = 1;
		glutPostRedisplay();
		break;
	case 'F':
		tz -= 0.1f;
		if (tz < -1) tz = -1;
		glutPostRedisplay();
		break;
	// kéo ngăn kéo
	case 'w':
		kz += 0.1f;
		if (kz > 0.3f) kz = 0.3f;
		glutPostRedisplay();
		break;
	case 'W':
		kz -= 0.1f;
		if (kz < 0) kz = 0;
		glutPostRedisplay();
		break;
	// Quay cánh tủ
	case 'r':
		delta += 10;
		if (delta > 90) delta = 90;
		glutPostRedisplay();
		break;
	case 'R':
		delta -= 10;
		if (delta < 0) delta = 0;
		glutPostRedisplay();
		break;
	// Quay cánh cửa
	case 'j':
		alpha -= 10;
		if (alpha < -120) alpha = -120;
		glutPostRedisplay();
		break;
	case 'J':
		alpha += 10;
		if (alpha > 0) alpha = 0;
		glutPostRedisplay();
		break;
	case 'k':
		beta += 10;
		if (beta > 120) beta = 120;
		glutPostRedisplay();
		break;
	case 'K':
		beta -= 10;
		if (beta < 0) beta = 0;
		glutPostRedisplay();
		break;
	// Quay cánh quạt
	case 'q':
		glutIdleFunc(quayQuatTuDong);
		break;
	case 'Q':
		glutIdleFunc(NULL);
		break;
	// Quay cánh cửa sổ
	case 'g':
		gama += 10;
		if (gama > 30) gama = 30;
		glutPostRedisplay();
		break;
	case 'G':
		gama -= 10;
		if (gama < 0) gama = 0;
		glutPostRedisplay();
		break;
	// Quay tay nắm cửa sổ
	case 'h':
		xichma -= 10;
		if (xichma < -90) xichma = -90;
		glutPostRedisplay();
		break;
	case 'H':
		xichma += 10;
		if (xichma > 0) xichma = 0;
		glutPostRedisplay();
		break;
	}
}


int main( int argc, char **argv )
{
	// main function: program starts here

    glutInit( &argc, argv );                       
    glutInitDisplayMode( GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize( 640, 640 );                 
	glutInitWindowPosition(100,150);               
    glutCreateWindow( "Drawing a Robot Arm without stack" );            

   
	glewInit();										

    generateGeometry( );                          
    initGPUBuffers( );							   
    shaderSetup( );                               

    glutDisplayFunc( display );                   
    glutKeyboardFunc( keyboard );   

	glutMainLoop();
    return 0;
}
