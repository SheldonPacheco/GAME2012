#include "Mesh.h"
#include <glad/glad.h>
#include <iostream>
#include <fstream>
#include <sstream>
void Mesh::loadFromOBJ(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open OBJ file!" << std::endl;
        return;
    }

    std::vector<glm::vec3> positions;
    std::vector<glm::vec2> tcoords;
    std::vector<glm::vec3> normals;

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string label;
        ss >> label;

        if (label == "v") {
            glm::vec3 position;
            ss >> position.x >> position.y >> position.z;
            positions.push_back(position);
        }
        else if (label == "vt") {
            glm::vec2 tcoord;
            ss >> tcoord.x >> tcoord.y;
            tcoords.push_back(tcoord);
        }
        else if (label == "vn") {
            glm::vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            normals.push_back(normal);
        }
        else if (label == "f") {
            for (int i = 0; i < 3; i++) {
                std::string vertexData;
                ss >> vertexData;
                std::replace(vertexData.begin(), vertexData.end(), '/', ' ');

                std::stringstream vertexStream(vertexData);
                int vIdx, vtIdx, vnIdx;
                vertexStream >> vIdx >> vtIdx >> vnIdx;

                Vertex vertex;
                vertex.position = positions[vIdx - 1];
                vertex.tcoord = tcoords[vtIdx - 1];
                vertex.normal = normals[vnIdx - 1];
                vertices.push_back(vertex);
                indices.push_back(vertices.size() - 1);
            }
        }
    }

    setupMesh(vertices, indices);
    file.close();
}

void Mesh::setupMesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices) {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tcoord));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
