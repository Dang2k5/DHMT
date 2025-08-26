#include "objects/hemisphere.h"
#include "core/camera.h"
#include "core/lighting.h"

const int HEMI_SLICES = 32;
const int HEMI_STACKS = 64; // Chỉ bằng một nửa Sphere
const int HEMI_VERTEX_COUNT = HEMI_STACKS * HEMI_SLICES * 6;

point4 hemi_points[HEMI_VERTEX_COUNT];
vec3 hemi_normals[HEMI_VERTEX_COUNT];

GLuint hemi_VAO, hemi_VBO;

mat4 hemiModelMatrix;

void createHemiSphere()
{
    int index = 0;
    float dPhi = (M_PI / 2.0f) / HEMI_STACKS;  // Chỉ từ 0 -> PI/2
    float dTheta = 2.0f * M_PI / HEMI_SLICES;
    float radius = 0.5f;

    for (int i = 0; i < HEMI_STACKS; i++) {
        float phi1 = i * dPhi;
        float phi2 = (i + 1) * dPhi;

        for (int j = 0; j < HEMI_SLICES; j++) {
            float theta1 = j * dTheta;
            float theta2 = (j + 1) * dTheta;

            point4 A = point4(radius * sin(phi1) * cos(theta1),
                radius * cos(phi1),
                radius * sin(phi1) * sin(theta1),
                1.0f);
            point4 B = point4(radius * sin(phi1) * cos(theta2),
                radius * cos(phi1),
                radius * sin(phi1) * sin(theta2),
                1.0f);
            point4 C = point4(radius * sin(phi2) * cos(theta2),
                radius * cos(phi2),
                radius * sin(phi2) * sin(theta2),
                1.0f);
            point4 D = point4(radius * sin(phi2) * cos(theta1),
                radius * cos(phi2),
                radius * sin(phi2) * sin(theta1),
                1.0f);

            vec3 nA = normalize(vec3(A.x, A.y, A.z));
            vec3 nB = normalize(vec3(B.x, B.y, B.z));
            vec3 nC = normalize(vec3(C.x, C.y, C.z));
            vec3 nD = normalize(vec3(D.x, D.y, D.z));

            hemi_points[index] = A; hemi_normals[index] = nA; index++;
            hemi_points[index] = B; hemi_normals[index] = nB; index++;
            hemi_points[index] = C; hemi_normals[index] = nC; index++;

            hemi_points[index] = A; hemi_normals[index] = nA; index++;
            hemi_points[index] = C; hemi_normals[index] = nC; index++;
            hemi_points[index] = D; hemi_normals[index] = nD; index++;
        }
    }
}

void initHemiSphereBuffers()
{
    hemi_VAO = initVAO();
    hemi_VBO = initVBO(sizeof(hemi_points) + sizeof(hemi_normals), hemi_points, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(hemi_points), sizeof(hemi_normals), hemi_normals);

    GLuint hemi_program = engine::defaultShader.program;

    GLuint loc_vPos = glGetAttribLocation(hemi_program, "vPosition");
    glEnableVertexAttribArray(loc_vPos);
    glVertexAttribPointer(loc_vPos, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));

    GLuint loc_vNormal = glGetAttribLocation(hemi_program, "vNormal");
    glEnableVertexAttribArray(loc_vNormal);
    glVertexAttribPointer(loc_vNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(hemi_points)));
}

void initHemiSphere()
{
    createHemiSphere();
    initHemiSphereBuffers();
}

void drawHemiSphere(const vec3& position, const vec3& rotation, const vec3& scale, const color& mainColor, engine::shader shader)
{
    bind(shader.program, hemi_VAO);

    useCameraMatrix(shader.view_loc, shader.projection_loc);
    mat4 instance = TRS(position, rotation, scale);
    glUniformMatrix4fv(shader.model_loc, 1, GL_TRUE, hemiModelMatrix * instance);
    setUniformVec4(shader.program, "mainColor", mainColor);
    useLights(shader.program, "lightPosition", "lightColor", "viewPosition", CAM_POS_3);

    glDrawArrays(GL_TRIANGLES, 0, HEMI_VERTEX_COUNT);
    unbind();
}

mat4 hemiSphereTransformMatrix(mat4 matrix)
{
    return hemiModelMatrix = matrix;
}

mat4 hemiSphereTransform(const vec3& position, const vec3& rotation, const vec3& scale)
{
    return hemiModelMatrix = TRS(position, rotation, scale);
}

void hemiSphereReset()
{
    hemiModelMatrix = identity();
}
