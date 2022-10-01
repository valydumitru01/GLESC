#pragma once
#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Cube : public Entity
{
public:
    Cube(ShaderManager* shaderManager):Entity(shaderManager)
    void render();
private:
    vector<float> vertices;
    vector<int> indices;
};