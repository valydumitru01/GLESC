#pragma once
#include "Entity.h"
#include "core/renderer/ShaderManager.h"

#include <GL/glew.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;
class Cube : public Entity
{
public:
    Cube(ShaderManager* shaderManager);
    void render();
    void update();
private:
    vector<float> vertices;
    vector<int> indices;
};