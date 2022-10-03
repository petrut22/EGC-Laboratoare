#pragma once

#include "components/simple_scene.h"

using namespace std;

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

     public:
         Tema1();
        ~Tema1();

        void Init() override;

     private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        // Sets the logic space and view space
        // logicSpace: { x, y, width, height }
        // viewSpace: { x, y, width, height }
        glm::mat3 VisualizationTransf2D(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);

        void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

     protected:
        float length;
        float length1;
        float length2;
        float length3;
        float lengthBorder;

        float translateX;
        float translateY;
        float translateX1;
        float translateY1;
        float translateX2;
        float translateY2;

        float translateX3;
        float translateY3;
        double angular;
        //double angularBoot[100];
        
        //vector with all enemy's positions
        struct position {
            //the enemy's body
            float xP1;
            float yP1;
            float xP2;
            float yP2;
            //his hands

            float xL1;
            float yL1;

            float xR1;
            float yR1;

            float xL2;
            float yL2;

            float xR2;
            float yR2;
            double angularBoot;
        };
        
        struct proiectilePos {
            float x1;
            float y1;
            float x2;
            float y2;
            float time;
            float angular;
        };

        struct borderPoint {
            float x1;
            float y1;
            float x2;
            float y2;
        };

        struct obstaclesPoint {
            float x1;
            float y1;
            float x2;
            float y2;
        };

        vector<obstaclesPoint> obstacles;

        vector<proiectilePos> projectiles;

        vector<borderPoint> borders;

       float time;
       float width;
       int score;
       int damage;

       float xHealthBar;
       float yHealthBar;
        
        vector<position> positionEnemy;
        //number of enemies

        float cx;
        float cy;
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;
    };
}   // namespace m1
