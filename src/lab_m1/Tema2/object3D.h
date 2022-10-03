#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace object3D
{

    // Create square with given bottom left corner, length and color
    Mesh* CreateCube(const std::string &name, glm::vec3 leftBottomCorner, float length, glm::vec3 color);
    Mesh* CreateParalelipiped(const std::string& name, glm::vec3 leftBottomCorner, float length1, float length2, float length3, glm::vec3 color);
}
