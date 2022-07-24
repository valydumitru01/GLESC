#pragma once
#include "common.h"
#include "Window.h"
#include "ShaderLoader.h"
class Triangle {

public:
    Triangle(std::array< float, 3 > p1, std::array< float, 3 > p2, std::array< float, 3 > p3);
    
    void draw();

private:

    std::array< float, 9 > vertices;

};
