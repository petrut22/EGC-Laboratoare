#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    cx = corner.x + squareSide / 2;
    cy = corner.y + squareSide / 2;

    // Initialize tx and ty (the translation steps)
    tx1 = 0;
    ty1 = 0;
    tx3 = 0;
    ty3 = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 0.1;
    scaleY = 0.1;

    // Initialize angularStep
    angularStep2 = 0;
    angularStep3 = 0;
    angularStep4 = 0;
    angularStep5 = 0;
    angularStep6 = 0;

    //boolean variabiles
    directionX = 1;
    directionY = 1;
    scaleBoolean = 1;
    direction = 1;

    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(square1);

    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
    AddMeshToList(square2);

    Mesh* square3 = object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
    AddMeshToList(square3);

    Mesh* square4 = object2D::CreateSquare("square4", corner, squareSide, glm::vec3(1, 1, 0));
    AddMeshToList(square4);

    Mesh* square5 = object2D::CreateSquare("square5", corner, squareSide, glm::vec3(0, 1, 1));
    AddMeshToList(square5);

    Mesh* square6 = object2D::CreateSquare("square6", corner, squareSide, glm::vec3(1, 0, 1));
    AddMeshToList(square6);
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Lab3::Update(float deltaTimeSeconds)
{
    // TODO(student): Update steps for translation, rotation and scale,
    // in order to create animations. Use the class variables in the
    // class header, and if you need more of them to complete the task,
    // add them over there!

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(150, 250);
    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented.
    // Remember, the last matrix in the chain will take effect first!


      if (directionX == 1) {
          tx1 += deltaTimeSeconds * 150;
          if (tx1 >= 600) {
              directionX = 0;
          }
      }

      if (directionX == 0) {
          tx1 -= deltaTimeSeconds * 150;
          if (tx1 < 100) {
              directionX = 1;
          }
      }


      if (directionY == 1) {
          ty1 += deltaTimeSeconds * 150;
          if (ty1 >= 400) {
              directionY = 0;
          }
      }

      if (directionY == 0) {
          ty1 -= deltaTimeSeconds * 150;
          if (ty1 < 100) {
              directionY = 1;
          }
      }


    modelMatrix *= transform2D::Translate(tx1, ty1);
    RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 250);
  

    if (scaleBoolean == 1) {
        scaleX += deltaTimeSeconds * 0.3;
        scaleY += deltaTimeSeconds * 0.3;
        if (scaleX >= 1 && scaleY >= 1) {
            scaleBoolean = 0;
        }
    }

    if (scaleBoolean == 0) {
        scaleX -= deltaTimeSeconds * 0.3;
        scaleY -= deltaTimeSeconds * 0.3;
        if (scaleX < 0.1 && scaleY < 0.1) {
            scaleBoolean = 1;
        }
    }

    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented
    // Remember, the last matrix in the chain will take effect first!

    angularStep2 += deltaTimeSeconds * 0.5;
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Rotate(8 * angularStep2);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    modelMatrix *= transform2D::Scale(scaleX, scaleY);
    RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);


    // TODO(student): Create animations by multiplying the current
    // transform matrix with the matrices you just implemented
    // Remember, the last matrix in the chain will take effect first!
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(650, 250);

    if (direction == 1) {
        tx3 += deltaTimeSeconds * 150;
        ty3 += deltaTimeSeconds * 150;
        if (tx3 >= 500 || ty3 >= 500) {
            direction = 0;
        }
    }

    if (direction == 0) {
        tx3 -= deltaTimeSeconds * 150;
        ty3 -= deltaTimeSeconds * 150;
        if (tx3 < 50 || ty3 < 0) {
            direction = 1;
        }
    }

    angularStep3 += deltaTimeSeconds * 0.5;
    modelMatrix *= transform2D::Translate(tx3, ty3);
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Rotate(5 * angularStep3);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

    //BONUS
    //4 sun
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(800, 300);

    modelMatrix *= transform2D::Scale(0.5, 0.5);
    RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);
   
   
    //5 earth
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(800, 300);

    angularStep5 += deltaTimeSeconds * 0.5;
    modelMatrix *= transform2D::Scale(0.4, 0.4);

    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Rotate(4.f * angularStep5);
    modelMatrix *= transform2D::Translate(squareDistance * 3.5f, squareDistance * 3.5f);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    

    RenderMesh2D(meshes["square5"], shaders["VertexColor"], modelMatrix);
   
    
    
    //moon
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(800, 300);

    angularStep6 += deltaTimeSeconds * 0.5;
    angularStep3 += deltaTimeSeconds * 0.3;

    modelMatrix *= transform2D::Scale(0.2, 0.2);
    modelMatrix *= transform2D::Translate(cx , cy);
    modelMatrix *= transform2D::Rotate(4.f * angularStep6);
    modelMatrix *= transform2D::Translate(squareDistance * 6.0f, squareDistance * 6.0f);
    modelMatrix *= transform2D::Translate(-cx, -cy);


    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Rotate(4.f * angularStep3);
    modelMatrix *= transform2D::Translate(squareDistance * 3.5f, squareDistance * 3.5f);
    modelMatrix *= transform2D::Translate(-cx, -cy);


    RenderMesh2D(meshes["square6"], shaders["VertexColor"], modelMatrix);
}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
}


void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
