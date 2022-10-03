#include "object3D.h"

#include <vector>
#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object3D::CreateCube(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
            VertexFormat(corner + glm::vec3(0, 0, length), color),
            VertexFormat(corner + glm::vec3(length, 0, length), color),
            VertexFormat(corner + glm::vec3(0, length, length), color),
            VertexFormat(corner + glm::vec3(length, length, length), color),
            VertexFormat(corner + glm::vec3(0, 0, 0), color),
            VertexFormat(corner + glm::vec3(length, 0, 0), color),
            VertexFormat(corner + glm::vec3(0, length, 0), color),
            VertexFormat(corner + glm::vec3(length, length, 0), color),
    };

    Mesh* cube = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,    // indices for first triangle
        1, 3, 2,    // indices for second triangle
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4,

    };



    cube->InitFromData(vertices, indices);
    return cube;
}


Mesh* object3D::CreateParalelipiped(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length1,
    float length2,
    float length3,
    glm::vec3 color)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {       
            VertexFormat(corner + glm::vec3(0, 0, length1), color),
            VertexFormat(corner + glm::vec3(length2, 0, length1), color),
            VertexFormat(corner + glm::vec3(0, length3, length1), color),
            VertexFormat(corner + glm::vec3(length2, length3, length1), color),
            VertexFormat(corner + glm::vec3(0, 0, 0), color),
            VertexFormat(corner + glm::vec3(length2, 0, 0), color),
            VertexFormat(corner + glm::vec3(0, length3, 0), color),
            VertexFormat(corner + glm::vec3(length2, length3, 0), color),
    };

    Mesh* paralelipiped = new Mesh(name);
    std::vector<unsigned int> indices =
    {
        0, 1, 2,    // indices for first triangle
        1, 3, 2,    // indices for second triangle
        2, 3, 7,
        2, 7, 6,
        1, 7, 3,
        1, 5, 7,
        6, 7, 4,
        7, 5, 4,
        0, 4, 1,
        1, 4, 5,
        2, 6, 4,
        0, 2, 4,

    };



    paralelipiped->InitFromData(vertices, indices);
    return paralelipiped;
}


