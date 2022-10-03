#pragma once

#include "components/simple_scene.h"
#include "lab_m1/Tema2/lab_camera.h"
#include "lab_m1/Tema2/transform3D.h"
#define Z_FAR		(200.f)
#define Z_NEAR		(.01f)

using namespace std;


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
     public:
         Tema2();
        ~Tema2();
        //initial setup for player's coordinates
        GLfloat startX = 1;
        GLfloat startY = 3;
        GLfloat startZ = 1;

        GLfloat length1 = 0.5;
        GLfloat length2 = 0.7;
        GLfloat length3 = 1.3;

        //dimensions for projectile
        GLfloat lengthP = 0.3;

        //dimensions for Body
        GLfloat widthBody = 0.5;
        GLfloat lengthBody = 0.7;
        GLfloat heightBody = 1.3;
        GLfloat distance = 0.03;

        float time;

        //dimensions for Head
        GLfloat lengthHead = 0.45;

        //dimensions for Hand and Arm
        GLfloat heightArm = 0.8; 
        GLfloat lengthHand = 0.5;
        GLfloat heightHand = length3 - heightArm - distance;

        //dimensions for Leg
        GLfloat widthLeg = 0.5;
        GLfloat lengthLeg = lengthBody / 2 - distance / 2;
        GLfloat heightLeg = 1.2;

        GLfloat cameraX = 1.35;
        GLfloat cameraY = 6.555;
        GLfloat cameraZ = 4;

        //dimension for wall
        GLfloat lengthWall = 8.3;
        GLfloat heightWall = 5.3;

        GLfloat angular = 0;
        int width = 6;
        int height = 6;
        int numberExcavation = width * height;
            

        int Width = width * 2 + 1;
        int Height = height * 2 + 1;

        int matrix[100][100];

        float spawnX;
        float spawnZ;

        bool perspective;




        //colors
        glm::vec3 blueGreen = glm::vec3(0, 0.6470, 0.6470); // blue-green
        glm::vec3 blueDark = glm::vec3(0, 0, 0.6470); // blue-dark
        glm::vec3 cream = glm::vec3(1, 0.9098, 0.8352); // cream
        glm::vec3 red = glm::vec3(1, 0, 0); // red
        glm::vec3 green = glm::vec3(0.5, 0.5, 0); // olive

        struct proiectilePos {
            float x1;
            float y1;
            float z1;

            float x2;
            float y2;
            float z2;

            float time;
            glm::vec3 poz;
            glm::vec3 dir;
        };


        vector<proiectilePos> projectiles;

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void UpdatePlayer(float deltaTimeSeconds);
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

     protected:
        implemented::Camera *camera;


        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        bool projectionType;

        GLfloat right;
        GLfloat left;
        GLfloat bottom;
        GLfloat top;
        GLfloat fov;


    };
}   // namespace m1
