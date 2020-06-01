//
// Created by massi on 01.06.2020.
//

#include "box.h"

void Box::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

Box::Box(std::vector<Vertex> vertices) :
    vertices{std::move(vertices)},
    indices{
        0, 1, 2, 0, 2, 3, // front
        1, 4, 7, 1, 7, 2, // right
        4, 5, 6, 4, 6, 7, // back
        5, 0, 3, 5, 3, 6, // left
        0, 1, 4, 0, 4, 5, // bottom
        3, 2, 7, 3, 7, 6, // top
    }
{
}

Box::~Box() {
    // Cancella tutti i buffers allocati
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Box::init() {
    glGenVertexArrays(1, &VAO); // Vertex Array Object
    glGenBuffers(1, &VBO);      // Vertex Buffer Object
    glGenBuffers(1, &EBO);      // Element Buffer Object

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

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
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));

    // texture coord attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}
