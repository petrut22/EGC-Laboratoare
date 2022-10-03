#include "lab_m1/Tema2/Tema2.h"
#include "lab_m1/Tema2/object3D.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}

bool verifyBorder(int x, int y, int Height, int Width) {

    if (x > 0 && x < Height - 1  && y > 0 && y < Width - 1) {
        return true;
    }
    return false;
}


void validPosition(int x, int y, int matrix[100][100], int Height, int Width, int type, int *xNew, int *yNew) {
        
        int dirX[100] = { -2, 2, 0, 0 };
        int dirY[100] = { 0, 0, -2, 2 };
        *xNew = x;
        *yNew = y;


        vector< pair <int, int> > validNeighbors;

        for (int i = 0; i < 4; i++) {
            int xAdd = x + dirX[i];
            int yAdd = y + dirY[i];

            if (verifyBorder(xAdd, yAdd, Height, Width) == true && matrix[xAdd][yAdd] == type) {
                validNeighbors.push_back(make_pair(xAdd, yAdd));
            }

        }

        if (validNeighbors.size() != 0) {
            int index = rand() % validNeighbors.size();
            *xNew = validNeighbors.at(index).first;
            *yNew = validNeighbors.at(index).second;
        }
}



void escapePosition(int x, int y, int matrix[100][100], int Height, int Width, int *escX, int *escY) {

    int dirX[100] = { -1, 1, 0, 0 };
    int dirY[100] = { 0, 0, -1, 1 };

    for (int i = 0; i < 4; i++) {
        if (x + dirX[i] == 0 || x + dirX[i] == Height - 1) {
            matrix[x][y] = 0;
            matrix[(x + dirX[i])][y] = 0;

            *escX = x + dirX[i];
            *escY = y;

            break;
        }

        if (y + dirY[i] == 0 || y + dirY[i] == Width - 1) {
            matrix[x][y] = 0;
            matrix[x][y + dirY[i]] = 0;

            *escX = x;
            *escY = y + dirY[i];

            break;
        }
    }
}


void Tema2::Init()
{
    renderCameraTarget = false;
    projectionType = true;
    glm::vec3 corner = glm::vec3(0, 0, 0);
    right = 10.f;
    left = .01f;
    bottom = .01f;
    top = 10.f;
    fov = 40.f;
    perspective = true;

    time = 0;

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 8, 9), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    camera->SetDistance(9);



    //camera->SetDistance(5);

    //Aldous-Broder

    int x, y, startPosX, startPosY;

    do {
        x = 1 + rand() % (Height -1);
    } while (x % 2 == 0);

    do {
        y = 1 + rand() % (Width - 1);
    } while (y % 2 == 0);

    for (int i = 0; i < Height; i++)
        for (int j = 0; j < Width; j++)
            matrix[i][j] = 1;
        
    startPosX = x;
    startPosY = y;

   // cout << Height << " " << Width << endl;
    cout << x << " " << y << endl;
    matrix[x][y] = 0;
    int visited = 1;

    while (visited <= numberExcavation) {
        int xNew = 0, yNew = 0;
        validPosition(x, y, matrix, Height, Width, 1, &xNew, &yNew);

        if (matrix[xNew][yNew] == 1) {
            matrix[x][y] = 0;
            matrix[(x + xNew) / 2][(y + yNew) / 2] = 0;
            visited++;
        }

        if (x == xNew && y == yNew) {
            validPosition(x, y, matrix, Height, Width, 0, &xNew, &yNew);
        }

        x = xNew;
        y = yNew;

    }


   cout << "positions " << startPosX << " " << startPosY << endl;
   cout << "positions finale " << x << " " << y << endl;

   int escapeAdd = 0;
   int escX = 0, escY = 0;

   for (int i = 0; i < Height; i++) {
       for (int j = 0; j < Width; j++) {
           if (i == 1 || i == Height - 2 || j == 1 || j == Width - 2) {
               if (matrix[i][j] == 0 && escapeAdd == 0) {
                   escapePosition(x, y, matrix, Height, Width, &escX, &escY);
                   matrix[escX][escY] = 0;
                   escapeAdd = 1;
               }
           }

           cout << matrix[i][j] << " ";
       }
       cout << endl;
   }

   cout << endl;





    float xWall = 0;
    float zWall = 0;

    spawnX = startPosX * lengthWall + lengthWall / 2;
    spawnZ = startPosY * lengthWall;

    //cout << spawnX << " " << spawnZ << endl;

    camera->SetDistance(1);
    camera->MoveForward(-spawnZ);
    camera->TranslateRight(spawnX);



   
    Mesh* paralelipipedHead = object3D::CreateParalelipiped("paralelipipedHead", corner, lengthHead, lengthHead, lengthHead, cream);
    AddMeshToList(paralelipipedHead);

    Mesh* paralelipipedBody = object3D::CreateParalelipiped("paralelipipedBody", corner, widthBody, lengthBody, heightBody, blueGreen);
    AddMeshToList(paralelipipedBody);

    Mesh* paralelipipedArm = object3D::CreateParalelipiped("paralelipipedArm", corner, lengthHand, lengthHand, heightArm, blueGreen);
    AddMeshToList(paralelipipedArm);

    Mesh* paralelipipedHand = object3D::CreateParalelipiped("paralelipipedHand", corner, lengthHand, lengthHand, heightHand, cream);
    AddMeshToList(paralelipipedHand);

    Mesh* paralelipipedLeg = object3D::CreateParalelipiped("paralelipipedLeg", corner, widthLeg, lengthLeg, heightLeg, blueDark);
    AddMeshToList(paralelipipedLeg);

    Mesh* cubeWall = object3D::CreateParalelipiped("cubeWall", corner, lengthWall, lengthWall, heightWall, green);
    AddMeshToList(cubeWall);


    Mesh* projectile = object3D::CreateParalelipiped("projectile", corner, lengthP, lengthP, lengthP, red);
    AddMeshToList(projectile);

    {
        Mesh* mesh = new Mesh("plane");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "plane50.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }


    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, Z_NEAR, Z_FAR);

}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{

    time += deltaTimeSeconds;
    glm::vec3 cameraPos = camera->GetTargetPosition();

    startX = cameraPos.x;
    startY = cameraPos.y + 1;
    startZ = cameraPos.z;


    //Projectiles
    for (int i = 0; i < projectiles.size(); i++) {

        if ((int)projectiles[i].time != 5) {
            projectiles[i].time += deltaTimeSeconds;
            float speed = 10 * deltaTimeSeconds;
            projectiles[i].poz += projectiles[i].dir * speed;
        }
        else {
            projectiles.erase(projectiles.begin() + i);
        }
    }


    //HEAD
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(startX, startY, startZ);

        modelMatrix *= transform3D::Translate(lengthHead / 2, 0, lengthHead / 2);
        modelMatrix *= transform3D::RotateOY(angular);
        modelMatrix *= transform3D::Translate(-lengthHead / 2, 0, -lengthHead / 2);

       // modelMatrix *= transform3D::Translate(lengthBody / 2 - lengthHead / 2, heightBody + distance, 0);
        RenderMesh(meshes["paralelipipedHead"], shaders["VertexColor"], modelMatrix);
    }

    // BODY
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(startX, startY, startZ);
        modelMatrix *= transform3D::Translate(-lengthBody / 2 + lengthHead / 2, -heightBody - distance, -widthBody / 2 + lengthHead / 2);

        modelMatrix *= transform3D::Translate(lengthBody / 2, 0, widthBody / 2);
        modelMatrix *= transform3D::RotateOY(angular);
        modelMatrix *= transform3D::Translate(-lengthBody / 2, 0, -widthBody / 2);

     
        RenderMesh(meshes["paralelipipedBody"], shaders["VertexColor"], modelMatrix);
    }
    


    //RIGHT ARM
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(startX, startY, startZ);
        modelMatrix *= transform3D::Translate(-lengthHand / 2 + lengthHead / 2, -distance - heightArm, -lengthHand / 2 + lengthHead / 2);

        modelMatrix *= transform3D::Translate(lengthHand / 2, 0, lengthHand / 2);
        modelMatrix *= transform3D::RotateOY(angular);
        modelMatrix *= transform3D::Translate(-lengthHand / 2, 0, -lengthHand / 2);
        
        modelMatrix *= transform3D::Translate(lengthHand / 2 + lengthBody / 2 + distance, 0, 0);
        RenderMesh(meshes["paralelipipedArm"], shaders["VertexColor"], modelMatrix);
    }


    ////LEFT ARM
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(startX, startY, startZ);
        modelMatrix *= transform3D::Translate(-lengthHand / 2 + lengthHead / 2, -distance - heightArm, -lengthHand / 2 + lengthHead / 2);

        modelMatrix *= transform3D::Translate(lengthHand / 2, 0, lengthHand / 2);
        modelMatrix *= transform3D::RotateOY(angular);
        modelMatrix *= transform3D::Translate(-lengthHand / 2, 0, -lengthHand / 2);

        modelMatrix *= transform3D::Translate(-lengthHand / 2 - lengthBody / 2 - distance, 0, 0);
        RenderMesh(meshes["paralelipipedArm"], shaders["VertexColor"], modelMatrix);
    }


    ////RIGHT HAND
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(startX, startY, startZ);
        modelMatrix *= transform3D::Translate(-lengthHand / 2 + lengthHead / 2, - 2 * distance - heightArm - heightHand, -lengthHand / 2 + lengthHead / 2);

        modelMatrix *= transform3D::Translate(lengthHand / 2, 0, lengthHand / 2);
        modelMatrix *= transform3D::RotateOY(angular);
        modelMatrix *= transform3D::Translate(-lengthHand / 2, 0, -lengthHand / 2);

        modelMatrix *= transform3D::Translate(lengthHand / 2 + lengthBody / 2 + distance, 0, 0);
        RenderMesh(meshes["paralelipipedHand"], shaders["VertexColor"], modelMatrix);
    }


    ////LEFT HAND
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(startX, startY, startZ);
        modelMatrix *= transform3D::Translate(-lengthHand / 2 + lengthHead / 2, -2 * distance - heightArm - heightHand, -lengthHand / 2 + lengthHead / 2);

        modelMatrix *= transform3D::Translate(lengthHand / 2, 0, lengthHand / 2);
        modelMatrix *= transform3D::RotateOY(angular);
        modelMatrix *= transform3D::Translate(-lengthHand / 2, 0, -lengthHand / 2);

        modelMatrix *= transform3D::Translate(-lengthHand / 2 - lengthBody / 2 - distance, 0, 0);
        RenderMesh(meshes["paralelipipedHand"], shaders["VertexColor"], modelMatrix);
    }


    ////RIGHT LEG
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(startX, startY, startZ);
        modelMatrix *= transform3D::Translate(-lengthLeg / 2 + lengthHead / 2, -heightBody - 2 * distance - heightLeg, -widthLeg / 2 + lengthHead / 2);

        modelMatrix *= transform3D::Translate(lengthLeg / 2, 0, widthLeg / 2);
        modelMatrix *= transform3D::RotateOY(angular);
        modelMatrix *= transform3D::Translate(-lengthLeg / 2, 0, -widthLeg / 2);


        modelMatrix *= transform3D::Translate(lengthBody / 2 - lengthLeg / 2 + distance / 2, 0, 0);
        RenderMesh(meshes["paralelipipedLeg"], shaders["VertexColor"], modelMatrix);
    }


    ////LEFT LEG
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(startX, startY, startZ);
        modelMatrix *= transform3D::Translate(-lengthLeg / 2 + lengthHead / 2, -heightBody - 2 * distance - heightLeg, -widthLeg / 2 + lengthHead / 2);

        modelMatrix *= transform3D::Translate(lengthLeg / 2, 0, widthLeg / 2);
        modelMatrix *= transform3D::RotateOY(angular);
        modelMatrix *= transform3D::Translate(-lengthLeg / 2, 0, -widthLeg / 2);


        modelMatrix *= transform3D::Translate(-lengthBody / 2 + lengthLeg / 2 - distance / 2, 0, 0);
        RenderMesh(meshes["paralelipipedLeg"], shaders["VertexColor"], modelMatrix);
    }
    
    //Draw projectiles
    for (int i = 0; i < projectiles.size(); i++) {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix *= transform3D::Translate(projectiles[i].poz.x, projectiles[i].poz.y, projectiles[i].poz.z);
        RenderMesh(meshes["projectile"], shaders["VertexColor"], modelMatrix);
    }


    //    // Render ground
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.01f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(4.4f));
        RenderMesh(meshes["plane"], shaders["VertexColor"], modelMatrix);
    }

    ////WALLS
    float xWall = 0;
    float zWall = 0;
    int ok = 1;
    for (int i = 0; i < Height; i++) {
        for (int j = 0; j < Width; j++) {
            if(matrix[i][j] == 1) {
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix *= transform3D::Translate(xWall, 0, zWall);
                RenderMesh(meshes["cubeWall"], shaders["VertexColor"], modelMatrix);
            }
            xWall += lengthWall;

        }
        zWall += lengthWall;
        xWall = 0;
        //cout << endl;
    }





 


}


void Tema2::FrameEnd()
{
    //DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed
        float cameraSpeed = 2;


     /*   if (window->KeyHold(GLFW_KEY_E)) {
             Translate the camera up
            camera->TranslateUpward(deltaTime * cameraSpeed * 5);
        }
        if (window->KeyHold(GLFW_KEY_Q)) {
             Translate the camera down
            camera->TranslateUpward(-deltaTime * cameraSpeed * 5);
        }*/
        if (window->KeyHold(GLFW_KEY_W)) {
            // Translate the camera forward
            camera->MoveForward(deltaTime * cameraSpeed * 5);

        }
        if (window->KeyHold(GLFW_KEY_S)) {
            // Translate the camera backwards
            camera->MoveForward(-deltaTime * cameraSpeed * 5);

        }
        if (window->KeyHold(GLFW_KEY_A)) {
            // Translate the camera to the left
            camera->TranslateRight(-deltaTime * cameraSpeed * 5);

        }
        if (window->KeyHold(GLFW_KEY_D)) {
            // Translate the camera to the right
            camera->TranslateRight(deltaTime * cameraSpeed * 5);

        }


}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    // TODO(student): Switch projections
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    if (key == GLFW_KEY_O)
    {
        projectionType = false;
        projectionMatrix = glm::ortho(left, right, bottom, top, Z_NEAR, Z_FAR);
    }
    if (key == GLFW_KEY_P)
    {
        projectionType = true;
        projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, Z_NEAR, Z_FAR);
    }


}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    float sensivityOY = 0.008f;
    angular += sensivityOY * -deltaX;


        if (perspective == true) {
            camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
        }
        else {
            camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
        }






}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event


    if (button == GLFW_MOUSE_BUTTON_2 && perspective == false) {
        float x1 = startX - lengthBody / 2 + lengthHead / 2 + lengthP;
        float y1 = startY - heightBody / 2 - distance;
        float z1 = startZ - widthBody / 2 + lengthHead / 2;


        if (projectiles.size() == 0 || (projectiles[projectiles.size() - 1].time > 0.5)) {

            float x2 = x1 + lengthP;
            float y2 = y1 + lengthP;
            float z2 = z1 + lengthP;
           // glm::vec3 vector = glm::vec3(camera->forward.x, 0, camera->forward.z);
            projectiles.push_back({ x1, y1, z1, x2, y2, z2, 0, camera->position, camera->forward});
        }
    }



    if (button == GLFW_MOUSE_BUTTON_3) {
        if (perspective == true) {
            perspective = false;
            camera->TranslateForward(9);
            camera->distanceToTarget = -1;
        }
        else {
            perspective = true;
            camera->TranslateForward(-9);
            camera->distanceToTarget = 9;

        }

        

    } 
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
