//
// Created by massi on 01.06.2020.
//

#include "solid.h"

Solid::Solid(std::vector<Vertex> vertices, std::vector<GLuint> indices) :
    _vertices{std::move(vertices)},
    _indices{std::move(indices)}
{
}

Solid::~Solid() {
    // Cancella tutti i buffers allocati
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Solid::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
}

void Solid::init() {
    glGenVertexArrays(1, &VAO); // Vertex Array Object
    glGenBuffers(1, &VBO);      // Vertex Buffer Object
    glGenBuffers(1, &EBO);      // Element Buffer Object

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), &_indices[0], GL_STATIC_DRAW);

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,    // indice dell’attributo
                          3,                  // n. di componenti (1..4)
                          GL_FLOAT,           // tipo di dato
                          GL_TRUE,            // se da normalizzare
                          sizeof(Vertex),     // offset (in byte) fra dati consecutivi
                          (void*)0);

    // color attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    // texture coord attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}


Box::Box(std::vector<Vertex> vertices) :
        Solid{std::move(vertices), std::vector<GLuint>{
                0, 1, 2, 0, 2, 3, // front
                1, 4, 7, 1, 7, 2, // right
                4, 5, 6, 4, 6, 7, // back
                5, 0, 3, 5, 3, 6, // left
                0, 1, 4, 0, 4, 5, // bottom
                3, 2, 7, 3, 7, 6, // top
        }}
{
}


Prism::Prism(std::vector<Vertex> vertices) :
        Solid{std::move(vertices), std::vector<GLuint>{
                0, 1, 2, // front
                3, 4, 5, // back
        }}
{
}
