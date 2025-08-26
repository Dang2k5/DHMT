#include "objects/cylinder1.h"

#include "core/camera.h"
#include "core/lighting.h"



const int CYLINDER1_SIDES = 256;
const int HEMI_STACKS = 32;
const int HEMI_SLICES = 64;

// Thân trụ + mặt phẳng đáy + bán cầu trên
const int CYLINDER1_VERTEX_COUNT =
CYLINDER1_SIDES * 6 +              // mặt bên
CYLINDER1_SIDES * 3 +              // mặt đáy
HEMI_STACKS * HEMI_SLICES * 6;    // bán cầu trên

point4 cylinder1_points[CYLINDER1_VERTEX_COUNT];
point4 cylinder1_vertices[CYLINDER1_SIDES * 2];
vec3 cylinder1_normals[CYLINDER1_VERTEX_COUNT];


int cylinder1_index = 0;

void createCylinder1() {
    float angelStep = 2.0f * M_PI / CYLINDER1_SIDES;
    for (int i = 0; i < CYLINDER1_SIDES; ++i) {
        float angle = i * angelStep;
        float x = cos(angle) * 0.5f;
        float z = sin(angle) * 0.5f;
        cylinder1_vertices[i] = point4(x, 0.5f, z, 1.0f);
        cylinder1_vertices[i + CYLINDER1_SIDES] = point4(x, -0.5f, z, 1.0f);
    }
}

void cylinder1_quad(int a, int b, int c, int d) {
    vec4 u = cylinder1_vertices[b] - cylinder1_vertices[a];
    vec4 v = cylinder1_vertices[c] - cylinder1_vertices[b];
    vec3 normal = normalize(cross(u, v));
    cylinder1_normals[cylinder1_index] = normal; cylinder1_points[cylinder1_index] = cylinder1_vertices[a]; cylinder1_index++;
    cylinder1_normals[cylinder1_index] = normal; cylinder1_points[cylinder1_index] = cylinder1_vertices[b]; cylinder1_index++;
    cylinder1_normals[cylinder1_index] = normal; cylinder1_points[cylinder1_index] = cylinder1_vertices[c]; cylinder1_index++;
    cylinder1_normals[cylinder1_index] = normal; cylinder1_points[cylinder1_index] = cylinder1_vertices[a]; cylinder1_index++;
    cylinder1_normals[cylinder1_index] = normal; cylinder1_points[cylinder1_index] = cylinder1_vertices[c]; cylinder1_index++;
    cylinder1_normals[cylinder1_index] = normal; cylinder1_points[cylinder1_index] = cylinder1_vertices[d]; cylinder1_index++;
}

// Tạo bán cầu phía trên
void makeHemisphereTop(float radius = 0.5f, int stacks = HEMI_STACKS, int slices = HEMI_SLICES) {
    for (int i = 0; i < stacks; i++) {
        float phi1 = (M_PI / 2.0f) * (float)i / stacks;
        float phi2 = (M_PI / 2.0f) * (float)(i + 1) / stacks;

        for (int j = 0; j < slices; j++) {
            float theta1 = 2.0f * M_PI * (float)j / slices;
            float theta2 = 2.0f * M_PI * (float)(j + 1) / slices;

            vec3 p1 = vec3(radius * cos(theta1) * cos(phi1),
                radius * sin(phi1),
                radius * sin(theta1) * cos(phi1));

            vec3 p2 = vec3(radius * cos(theta2) * cos(phi1),
                radius * sin(phi1),
                radius * sin(theta2) * cos(phi1));

            vec3 p3 = vec3(radius * cos(theta2) * cos(phi2),
                radius * sin(phi2),
                radius * sin(theta2) * cos(phi2));

            vec3 p4 = vec3(radius * cos(theta1) * cos(phi2),
                radius * sin(phi2),
                radius * sin(theta1) * cos(phi2));

            // Dời lên trên mặt trụ
            p1.y += 0.5f;
            p2.y += 0.5f;
            p3.y += 0.5f;
            p4.y += 0.5f;

            vec3 normal1 = normalize(p1);
            vec3 normal2 = normalize(p2);
            vec3 normal3 = normalize(p3);
            vec3 normal4 = normalize(p4);

            // Tam giác 1
            cylinder1_normals[cylinder1_index] = normal1; cylinder1_points[cylinder1_index++] = point4(p1, 1.0f);
            cylinder1_normals[cylinder1_index] = normal2; cylinder1_points[cylinder1_index++] = point4(p2, 1.0f);
            cylinder1_normals[cylinder1_index] = normal3; cylinder1_points[cylinder1_index++] = point4(p3, 1.0f);
            // Tam giác 2
            cylinder1_normals[cylinder1_index] = normal1; cylinder1_points[cylinder1_index++] = point4(p1, 1.0f);
            cylinder1_normals[cylinder1_index] = normal3; cylinder1_points[cylinder1_index++] = point4(p3, 1.0f);
            cylinder1_normals[cylinder1_index] = normal4; cylinder1_points[cylinder1_index++] = point4(p4, 1.0f);
        }
    }
}

void makeCylinder1() {
    // Thân trụ
    for (int i = 0; i < CYLINDER1_SIDES; i++) {
        int next = (i + 1) % CYLINDER1_SIDES;
        cylinder1_quad(i, next, next + CYLINDER1_SIDES, i + CYLINDER1_SIDES);
    }

    // Bán cầu trên
    makeHemisphereTop(0.5f);

    // Mặt dưới phẳng
    vec3 bottomNormal = vec3(0.0f, -1.0f, 0.0f);
    point4 bottomCenter = point4(0.0f, -0.5f, 0.0f, 1.0f);
    for (int i = 0; i < CYLINDER1_SIDES; i++) {
        int next = (i + 1) % CYLINDER1_SIDES;
        cylinder1_normals[cylinder1_index] = bottomNormal; cylinder1_points[cylinder1_index++] = bottomCenter;
        cylinder1_normals[cylinder1_index] = bottomNormal; cylinder1_points[cylinder1_index++] = cylinder1_vertices[next + CYLINDER1_SIDES];
        cylinder1_normals[cylinder1_index] = bottomNormal; cylinder1_points[cylinder1_index++] = cylinder1_vertices[i + CYLINDER1_SIDES];
    }
}


//void makeColorPlane()
//{
//	cylinder1_quad1(1, 0, 3, 2);
//	plane_quad(2, 3, 7, 6);
//	plane_quad(3, 0, 4, 7);
//	plane_quad(6, 5, 1, 2);
//	plane_quad(4, 5, 6, 7);
//	plane_quad(5, 4, 0, 1);
//}

GLuint cylinder1_VAO, cylinder1_VBO;

void initCylinder1Buffers()
{
	cylinder1_VAO = initVAO();
	cylinder1_VBO = initVBO(sizeof(cylinder1_points) + sizeof(cylinder1_normals), cylinder1_points, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(cylinder1_points), sizeof(cylinder1_normals), cylinder1_normals);

	GLuint cylinder1_program = engine::defaultShader.program;

	GLuint loc_vPos = glGetAttribLocation(cylinder1_program, "vPosition");
	GLuint loc_vNormal = glGetAttribLocation(cylinder1_program, "vNormal");
	glEnableVertexAttribArray(loc_vNormal);
	glVertexAttribPointer(loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(cylinder1_points)));

	glEnableVertexAttribArray(loc_vPos);
	glVertexAttribPointer(loc_vPos, sizeof(float), GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
}

void initCylinder1()
{
    createCylinder1();
    makeCylinder1();
    initCylinder1Buffers();
}

mat4 cylinder1ModelMatrix;

void drawCylinder1(const vec3& position, const vec3& rotation, const vec3& scale, const color& mainColor, engine::shader shader)
{
	bind(shader.program, cylinder1_VAO);
	useCameraMatrix(shader.view_loc, shader.projection_loc);

	mat4 instance = TRS(position, rotation, scale);
	glUniformMatrix4fv(shader.model_loc, 1, GL_TRUE, cylinder1ModelMatrix * instance);

	setUniformVec4(shader.program, "mainColor", mainColor);
	useLights(shader.program, "lightPosition", "lightColor", "viewPosition", CAM_POS_3);

	glDrawArrays(GL_TRIANGLES, 0, CYLINDER1_VERTEX_COUNT);
	unbind();
}

mat4 cylinder1TransformMatrix(mat4 matrix)
{
	return cylinder1ModelMatrix = matrix;
}

mat4 cylinder1Transform(const vec3& position, const vec3& rotation, const vec3& scale)
{
	return cylinder1ModelMatrix = TRS(position, rotation, scale);
}

void cylinder1Reset()
{
	cylinder1ModelMatrix = identity();
}