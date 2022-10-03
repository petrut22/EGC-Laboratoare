#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"


using namespace std;
using namespace m1;
 
int gasit = 0;

double valMax = 1e-9;
/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}
//this function verify the colision of two rectangles
// (x1P1, y1P1) -> is left-down point of the rectangle 1
// (x2P1, y2P1) -> is right-up point of the rectangle 1
// (x1P2, y1P2) -> is left-down point of the rectangle 2
// (x2P2, y2P2) -> is right-up point of the rectangle 2

int VerifyColisionRectangles(float x1P1, float y1P1, float x2P1, float y2P1, float x1P2, float y1P2, float x2P2, float y2P2) {
    
    if (x1P1 >= x2P2 || x1P2 >= x2P1 || y1P1 >= y2P2 || y1P2 >= y2P1) {
        return 0;
    }

    return 1;

} 

//this function verify the colision of circle and rectangle
// (x1P, y1P) -> is left-down point of the rectangle 
// (x2P, y2P) -> is right-up point of the rectangle 
// R -> radius
// (xC, yC) -> is the center of the circle

int VerifyColisionRectangleCircle(float xP1, float yP1, float xP2, float yP2, float R, float xC, float yC) {
    float x = max(xP1, min(xP2, xC));
    float y = max(yP1, min(yP2, yC));

    double distance = sqrt((x - xC) * (x - xC) + (y - yC) * (y - yC));

        if (R >= distance) {
            return 1;
        }

    return 0;

}


void Tema1::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    score = 0;

    logicSpace.x = 2;       // logic x
    logicSpace.y = 4;       // logic y
    logicSpace.width = 4;   // logic width
    logicSpace.height = 4;  // logic height



    glm::vec3 corner = glm::vec3(0, 0, 0);
    length = 8.f;
    length1 = 0.28;
    length2 = 0.12;
    length3 = 0.12;
    width = 0.1;
    damage = 0;
    lengthBorder = length * 1.5;
    translateX = logicSpace.x + logicSpace.width / 2;
    translateY = logicSpace.y + logicSpace.height / 2;
    translateX1 = translateX + 0.15;
    translateY1 = translateY + 0.1;
    translateX2 = translateX + 0.15;
    translateY2 = translateY - 0.1;

    xHealthBar = 5;
    yHealthBar = 7.5;

    time = 0;
    angular = 0;
    cx = corner.x + length1 / 2;
    cy = corner.y + length1 / 2;

    Mesh* rectangle = object2D::CreateRectangle("rectangle", corner, length, width, glm::vec3(0, 0, 0), true);
    AddMeshToList(rectangle);

    Mesh* rectangle1 = object2D::CreateRectangle("rectangle1", corner, lengthBorder, width, glm::vec3(0, 0, 0), true);
    AddMeshToList(rectangle1);

    Mesh* rectangle2 = object2D::CreateRectangle("rectangle2", corner, (length * 0.1), (width * 40), glm::vec3(0.3, 0.7, 0), true);
    AddMeshToList(rectangle2);

    Mesh* rectangle3 = object2D::CreateRectangle("rectangle3", corner, (length * 0.25), (width * 7.25), glm::vec3(0.6, 0.3, 0), true);
    AddMeshToList(rectangle3);

    Mesh* rectangle4 = object2D::CreateRectangle("rectangle4", corner, (length * 0.5), (width * 7.25), glm::vec3(0.2, 0.45, 0), true);
    AddMeshToList(rectangle4);

    Mesh* rectangle5 = object2D::CreateRectangle("rectangle5", corner, lengthBorder, length, glm::vec3(0, 0, 0), false);
    AddMeshToList(rectangle5);

    Mesh* rectangle6 = object2D::CreateRectangle("rectangle6", corner, (width * 2.25), (length * 0.3), glm::vec3(0, 1, 0), true);
    AddMeshToList(rectangle6);

    Mesh* rectangle7 = object2D::CreateRectangle("rectangle7", corner, 0.24, (width * 2.25), glm::vec3(1, 0, 0), true);
    AddMeshToList(rectangle7);


    corner = glm::vec3(0, 0, 0);
    Mesh* circle = object2D::CreateCircle("circle", corner, glm::vec3(1, 1, 0), true);
    AddMeshToList(circle);

    corner = glm::vec3(0, 0, 0);
    Mesh* circle1 = object2D::CreateCircle("circle1", corner, glm::vec3(0, 0, 0), true);
    AddMeshToList(circle1);


    corner = glm::vec3(0, 0, 0);
    Mesh* square = object2D::CreateSquare("square", corner, length, glm::vec3(0.7, 0, 0), true);
    AddMeshToList(square);

    corner = glm::vec3(0, 0, 0);
    Mesh* square1 = object2D::CreateSquare("square1", corner, length1, glm::vec3(0.2, 0, 0), true);
    AddMeshToList(square1);

    corner = glm::vec3(0, 0, 0);
    Mesh* square2 = object2D::CreateSquare("square2", corner, length2, glm::vec3(0.7, 0, 0), true);
    AddMeshToList(square2);

    corner = glm::vec3(0, 0, 0);
    Mesh* square3 = object2D::CreateSquare("square3", corner, length3, glm::vec3(0, 0, 0), true);
    AddMeshToList(square3);

}



// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}


// Uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}


void Tema1::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Tema1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();

    // Sets the screen area where to draw 
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.5f), true);

 

    // Compute the 2D visualization matrix
    int i;
    visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);
    time += deltaTimeSeconds;

    for (int i = 0; i < projectiles.size(); i++) {

        if ( (int)projectiles[i].time != 5) {
            projectiles[i].x1 += deltaTimeSeconds * cos(projectiles[i].angular) * 5;
            projectiles[i].y1 += deltaTimeSeconds * sin(projectiles[i].angular) * 5;

            projectiles[i].x2 += deltaTimeSeconds * cos(projectiles[i].angular) * 5;
            projectiles[i].y2 += deltaTimeSeconds * sin(projectiles[i].angular) * 5;

            projectiles[i].time += deltaTimeSeconds;
        }
        else {
            projectiles.erase(projectiles.begin() + i);
        }
    }

    //spawn the enemy
    if ((int)time == 10 && time != 0) {
        time = 0;
        for (i = 0; i < 5; i++) {
            float xP1 = length1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (length - 3 * length1)));
            float yP1 = length1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (lengthBorder - 3 * length1)));

            float xP2 = xP1 + length1;
            float yP2 = yP1 + length1;

            float xL1 = xP1 - length2;
            float yL1 = yP1 + length1;

            float xR1 = xP1 + length1;
            float yR1 = yP1 + length1;

            float xL2 = xL1 + length2;
            float yL2 = yL1 + length2;

            float xR2 = xR1 + length2;
            float yR2 = yR1 + length2;

            positionEnemy.push_back({ xP1, yP1, xP2, yP2, xL1, yL1, xR1, yR1, xL2, yL2, xR2, yR2,  0 });

        }

    }

    //verify the collision between projectile and enemy
    for (int i = 0; i < projectiles.size(); i++) {
        int hit = 0;
        for (int j = 0; j < positionEnemy.size() && hit == 0; j++) {


            if (VerifyColisionRectangles(projectiles[i].x1, projectiles[i].y1, projectiles[i].x2, projectiles[i].y2,
                positionEnemy[j].xP1, positionEnemy[j].yP1, positionEnemy[j].xP2, positionEnemy[j].yP2) == 1) {
                projectiles.erase(projectiles.begin() + i);
                positionEnemy.erase(positionEnemy.begin() + j);
                hit = 1;
            }

            if (hit == 0 && VerifyColisionRectangles(projectiles[i].x1, projectiles[i].y1, projectiles[i].x2, projectiles[i].y2,
                positionEnemy[j].xL1, positionEnemy[j].yL1, positionEnemy[j].xL2, positionEnemy[j].yL2) == 1) {
                projectiles.erase(projectiles.begin() + i);
                positionEnemy.erase(positionEnemy.begin() + j);
                hit = 1;
            }

            if (hit == 0 && VerifyColisionRectangles(projectiles[i].x1, projectiles[i].y1, projectiles[i].x2, projectiles[i].y2,
                positionEnemy[j].xR1, positionEnemy[j].yR1, positionEnemy[j].xR2, positionEnemy[j].yR2) == 1) {
                projectiles.erase(projectiles.begin() + i);
                positionEnemy.erase(positionEnemy.begin() + j);
                hit = 1;
            }

            if (hit == 1) {
                score++;     
            }
        }
   }

    //verify the collision between projectile and borders
    for (int i = 0; i < projectiles.size(); i++) {
            if (VerifyColisionRectangles(width, width, length - width,
                lengthBorder - width, projectiles[i].x1, projectiles[i].y1, projectiles[i].x2,
                projectiles[i].y2) == 0) {

                projectiles.erase(projectiles.begin() + i);

            }

    }

    //verify the collision between projectile and obstacles
    for (int i = 0; i < projectiles.size(); i++) {
        int hit = 0;
        for (int j = 0; j < obstacles.size() && hit == 0; j++) {
           if (VerifyColisionRectangles(obstacles[j].x1, obstacles[j].y1, obstacles[j].x2,
                obstacles[j].y2, projectiles[i].x1, projectiles[i].y1, projectiles[i].x2,
                projectiles[i].y2) == 1) {

                projectiles.erase(projectiles.begin() + i);
                hit = 1;

           }
        }
    }

    //verify the collision between player and enemy
    for (int i = 0; i < positionEnemy.size(); i++) {
            if (VerifyColisionRectangleCircle(positionEnemy[i].xP1, positionEnemy[i].yP1, positionEnemy[i].xP2, 
                positionEnemy[i].yP2, 0.4, translateX, translateY) == 1) {
                damage++;
                positionEnemy.erase(positionEnemy.begin() + i);
            }
    }
    

    //moving the enemy
    for (i = 0; i < positionEnemy.size(); i++) {
        bool flag = false;
        float diffX = (positionEnemy[i].xP1 - translateX);
        float diffY = (positionEnemy[i].yP1 - translateY);
        positionEnemy[i].angularBoot= atan2(diffY, diffX) + M_PI_2;


        if (translateX <= positionEnemy[i].xP1 + length2 / 2 || translateX > positionEnemy[i].xP1 + length2 / 2) {


            float distanceCos = deltaTimeSeconds * cos(positionEnemy[i].angularBoot - M_PI_2);
            //verify collision between enemies and borders
            if ( (positionEnemy[i].xP1 + distanceCos > 0 && positionEnemy[i].xP2 + distanceCos < length) && (positionEnemy[i].xL1 + distanceCos > 0 && positionEnemy[i].xR1 + distanceCos < length)
                && (positionEnemy[i].xL2 + distanceCos > 0 && positionEnemy[i].xR2 + distanceCos < length)) {

                positionEnemy[i].xP1 -= distanceCos;
                positionEnemy[i].xP2 -= distanceCos;
                positionEnemy[i].xL1 -= distanceCos;
                positionEnemy[i].xR1 -= distanceCos;
                positionEnemy[i].xL2 -= distanceCos;
                positionEnemy[i].xR2 -= distanceCos;
            }

        }

        float distanceSin = deltaTimeSeconds * sin(positionEnemy[i].angularBoot - M_PI_2);

        if (translateY <= positionEnemy[i].yP1 + length2 / 2 || translateY > positionEnemy[i].yP1 + length2 / 2) {

            if ((positionEnemy[i].yP1 - distanceSin > 0 && positionEnemy[i].yP2 - distanceSin < lengthBorder) && (positionEnemy[i].yL1 - distanceSin > 0 && positionEnemy[i].yR1 - distanceSin < lengthBorder)
                && (positionEnemy[i].yL2 - distanceSin > 0 && positionEnemy[i].yR2 - distanceSin < lengthBorder)) {

                positionEnemy[i].yP1 -= distanceSin;
                positionEnemy[i].yP2 -= distanceSin;
                positionEnemy[i].yL1 -= distanceSin;
                positionEnemy[i].yR1 -= distanceSin;
                positionEnemy[i].yL2 -= distanceSin;
                positionEnemy[i].yR2 -= distanceSin;
            }
        }

    }


    DrawScene(visMatrix);

}


void Tema1::FrameEnd()
{
}


void Tema1::DrawScene(glm::mat3 visMatrix)
{

    if (damage == 10) {
        cout << endl << endl;
        cout << "Enemies killed " << score << endl;
        cout << "GAME OVER" << endl;
        exit(1);
    }
    modelMatrix = visMatrix * transform2D::Translate((xHealthBar + length * 0.3), yHealthBar);
    modelMatrix *= transform2D::Rotate(M_PI/2);
    modelMatrix *= transform2D::Scale(1, damage);
    RenderMesh2D(meshes["rectangle7"], shaders["VertexColor"], modelMatrix);

    modelMatrix = visMatrix * transform2D::Translate(xHealthBar, yHealthBar);
    RenderMesh2D(meshes["rectangle6"], shaders["VertexColor"], modelMatrix);


    //creating the projectiles
    for (int i = 0; i < projectiles.size(); i++) {
        modelMatrix = visMatrix * transform2D::Translate(projectiles[i].x1, projectiles[i].y1);
        modelMatrix *= transform2D::Rotate(projectiles[i].angular);
        RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);
    }


    //creating the player + hands
    float diffX = (translateX1 - translateX);
    float diffY = (translateY1 - translateY);
    modelMatrix = visMatrix * transform2D::Translate(translateX1, translateY1);
    modelMatrix *= transform2D::Translate(-diffX, -diffY);
    modelMatrix *= transform2D::Rotate(angular);
    modelMatrix *= transform2D::Translate(diffX, diffY);
    modelMatrix *= transform2D::Scale(0.05, 0.05);
    RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);


    diffX = (translateX2 - translateX);
    diffY = (translateY2 - translateY);
    modelMatrix = visMatrix * transform2D::Translate(translateX2, translateY2);
    modelMatrix *= transform2D::Translate(-diffX, -diffY);
    modelMatrix *= transform2D::Rotate(angular);
    modelMatrix *= transform2D::Translate(diffX, diffY);
    modelMatrix *= transform2D::Scale(0.05, 0.05);
    RenderMesh2D(meshes["circle1"], shaders["VertexColor"], modelMatrix);


    modelMatrix = visMatrix * transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(angular);
    modelMatrix *= transform2D::Scale(0.2, 0.2);
    RenderMesh2D(meshes["circle"], shaders["VertexColor"], modelMatrix);

    //creating the enemy
    for (int i = 0; i < positionEnemy.size(); i++) {

        diffX = length2 + cx;
        diffY = cy;

        modelMatrix = visMatrix * transform2D::Translate(positionEnemy[i].xL1, positionEnemy[i].yL1);
        modelMatrix *= transform2D::Translate(diffX, -diffY);
        modelMatrix *= transform2D::Rotate(positionEnemy[i].angularBoot);
        modelMatrix *= transform2D::Translate(-diffX, diffY);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        diffX = length1 / 2;
        diffY = length1 / 2;

        modelMatrix = visMatrix * transform2D::Translate(positionEnemy[i].xR1, positionEnemy[i].yR1);
        modelMatrix *= transform2D::Translate(-diffX, -diffY);
        modelMatrix *= transform2D::Rotate(positionEnemy[i].angularBoot);
        modelMatrix *= transform2D::Translate(diffX, diffY);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);


        modelMatrix = visMatrix * transform2D::Translate(positionEnemy[i].xP1, positionEnemy[i].yP1);
        modelMatrix *= transform2D::Translate(cx, cy);
        modelMatrix *= transform2D::Rotate(positionEnemy[i].angularBoot);
        modelMatrix *= transform2D::Translate(-cx, -cy);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
    }




    //creating the obstacles on the map 

    float xr = 1 + (width * 40);
    float yr = 3 + (length * 0.1);

    obstacles.push_back({ 1, 3, xr, yr });
    modelMatrix = visMatrix * transform2D::Translate(1, 3);
    RenderMesh2D(meshes["rectangle2"], shaders["VertexColor"], modelMatrix);

    xr = 6 + width * 7.25;
    yr = 7 + length * 0.25;

    obstacles.push_back({ 6, 7, xr, yr });
    modelMatrix = visMatrix * transform2D::Translate(6, 7);
    RenderMesh2D(meshes["rectangle3"], shaders["VertexColor"], modelMatrix);
    
    xr = (2 + width * 7.5);
    yr = (7 + length * 0.5);

    obstacles.push_back({ 2, 7, xr, yr });
    modelMatrix = visMatrix * transform2D::Translate(2, 7);
    RenderMesh2D(meshes["rectangle4"], shaders["VertexColor"], modelMatrix);

    //the borders of the map

    borders.push_back({ 0, 0, length, lengthBorder });
    modelMatrix = visMatrix * transform2D::Translate(0, 0);
    RenderMesh2D(meshes["rectangle5"], shaders["VertexColor"], modelMatrix);

}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    //  Move the player with W, A, S, D (up, left, down, right)
    if (window->KeyHold(GLFW_KEY_W)) {
        bool flag = true;
        for (int i = 0; i < obstacles.size(); i++) {
            if (VerifyColisionRectangleCircle(obstacles[i].x1, obstacles[i].y1, obstacles[i].x2, obstacles[i].y2, 0.2, translateX, translateY + deltaTime) == 1) {
                flag = false;
            }
        }

        if (flag == true && translateX - 0.2 > 0 && translateX + 0.2 < length && translateY - 0.2 + deltaTime > 0 && translateY + 0.2 + deltaTime < lengthBorder) {
            logicSpace.y += deltaTime;
            translateY += deltaTime;
            translateY1 += deltaTime;
            translateY2 += deltaTime;
            yHealthBar += deltaTime;

        }

    }

    if (window->KeyHold(GLFW_KEY_A)) {
        bool flag = true;
        for (int i = 0; i < obstacles.size(); i++) {
            if (VerifyColisionRectangleCircle(obstacles[i].x1, obstacles[i].y1, obstacles[i].x2, obstacles[i].y2, 0.2, translateX - deltaTime, translateY) == 1) {
                flag = false;
            }
        }
        if (flag == true && translateX - 0.2 - deltaTime > 0 && translateX + 0.2 - deltaTime < length && translateY - 0.2 > 0 && translateY + 0.2 < lengthBorder) {
            logicSpace.x -= deltaTime;
            translateX -= deltaTime;
            translateX1 -= deltaTime;
            translateX2 -= deltaTime;
            xHealthBar -= deltaTime;

        }
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        bool flag = true;
        for (int i = 0; i < obstacles.size(); i++) {
            if (VerifyColisionRectangleCircle(obstacles[i].x1, obstacles[i].y1, obstacles[i].x2, obstacles[i].y2, 0.2, translateX, translateY - deltaTime) == 1) {
                flag = false;
            }
        }
        if (flag == true && translateX - 0.2 > 0 && translateX + 0.2 < length && translateY - 0.2 - deltaTime > 0 && translateY + 0.2 - deltaTime < lengthBorder) {
            logicSpace.y -= deltaTime;
            translateY -= deltaTime;
            translateY1 -= deltaTime;
            translateY2 -= deltaTime;
            yHealthBar -= deltaTime;
        }

    }

    if (window->KeyHold(GLFW_KEY_D)) {
        bool flag = true;
        for (int i = 0; i < obstacles.size(); i++) {
            if (VerifyColisionRectangleCircle(obstacles[i].x1, obstacles[i].y1, obstacles[i].x2, obstacles[i].y2, 0.2, translateX + deltaTime, translateY) == 1) {
                flag = false;
            }
        }
        if (flag == true && translateX - 0.2 + deltaTime > 0 && translateX + 0.2 + deltaTime < length && translateY - 0.2 > 0 && translateY + 0.2 < lengthBorder) {
            logicSpace.x += deltaTime;
            translateX += deltaTime;
            translateX1 += deltaTime;
            translateX2 += deltaTime;
            xHealthBar += deltaTime;
        }

    }
    //  Zoom in and zoom out logic window with Z and X
  /*  if (window->KeyHold(GLFW_KEY_Z)) {
        logicSpace.x += deltaTime;
        logicSpace.y += deltaTime;
        logicSpace.width -= 2 * deltaTime;
        logicSpace.height -= 2 * deltaTime;

    }

    if (window->KeyHold(GLFW_KEY_X)) {
        logicSpace.x -= deltaTime;
        logicSpace.y -= deltaTime;
        logicSpace.width += 2 * deltaTime;d
        logicSpace.height += 2 * deltaTime;

    }*/


}


void Tema1::OnKeyPress(int key, int mods)
{


}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

    glm::ivec2 resolution = window->GetResolution();
    int dX = mouseX - resolution.x/2;
    int dY = mouseY - resolution.y/2;

    angular = atan2(-dY, dX);

    // Add mouse move event

}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    glm::ivec2 resolution = window->GetResolution();


    if (projectiles.size() == 0 || (projectiles[projectiles.size() - 1].time > 0.5)) {
        int dX = mouseX - resolution.x / 2;
        int dY = mouseY - resolution.y / 2;
        float angularP = atan2(-dY, dX);

        float x2 = translateX + length3 / 2;
        float y2 = translateY + length3 / 2;
        projectiles.push_back({ translateX , translateY, x2, y2, 0, angularP });
    }

}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}
