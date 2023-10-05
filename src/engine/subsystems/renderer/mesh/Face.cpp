/******************************************************************************
 * @file   Example.h
 * @author Valentin Dumitru
 * @date   2023-09-26
 *
 * Copyright (c) 2023 Valentin Dumitru. Licensed under the MIT License.
 * See LICENSE.txt in the project root for license information.
 ******************************************************************************/
#include "engine/subsystems/renderer/mesh/Face.h"

using namespace GLESC;


void
Face::calculateData(Vertex &vertex1, Vertex &vertex2, Vertex &vertex3) {
    Vector3D v1 = vertex2.getPosition() - vertex1.getPosition();
    Vector3D v2 = vertex3.getPosition() - vertex1.getPosition();
    crossProduct = v1.cross(v2);
    
    this->vertexA = std::make_shared<Vertex>(vertex1);
    this->vertexB = std::make_shared<Vertex>(vertex2);
    this->vertexC = std::make_shared<Vertex>(vertex3);
    
}

bool Face::operator==(const Face &other) const {
    return crossProduct == other.crossProduct;
}

bool Face::operator<(const Face &other) const {
    return crossProduct < other.crossProduct;
}

Vector3D Face::getNormal() const {
    return crossProduct.normalize();
}

double Face::getArea() const {
    return crossProduct.length() / 2;
}

Vector3D Face::getCrossProduct() const {
    return crossProduct;
}

std::string Face::toString() const {
    std::string result = "Face: \n";
    result += "Vertex A: \n";
    result += vertexA->toString() + "\n";
    result += "Vertex B: \n";
    result += vertexB->toString() + "\n";
    result += "Vertex C: \n";
    result += vertexC->toString() + "\n";
    result += "Cross Product: \n";
    result += crossProduct.toString() + "\n";
    result += "Normal: \n";
    result += getNormal().toString() + "\n";
    result += "Area: \n";
    result += std::to_string(getArea()) + "\n";
    return result;
}