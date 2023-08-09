/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include <utility>

#include "engine/core/low-level-renderer/graphic-device-interface/GraphicInterface.h"
#include "engine/core/asserts/Asserts.h"

enum class ShaderDataType {
    None = 0, Float, Int, Bool
};
enum class ShaderDataDim {
    Value = 0, Vec2, Vec3, Vec4, Mat2, Mat3, Mat4
};

struct BufferElement {
    std::string name;
    ShaderDataType type;
    uint32_t size;
    size_t offset;
    bool normalized;
    
    BufferElement(ShaderDataType type, ShaderDataDim dimension, std::string name, bool normalized = false) :
            name(std::move(name)), type(type), size(shaderDataTypeSize(type) * shaderDataDimSize(dimension)), offset(
            0), normalized(normalized) {
        
    }

private:
    static int shaderDataTypeSize(ShaderDataType type) {
        switch (type) {
            case ShaderDataType::Float:
                return sizeof(float);
            case ShaderDataType::Int:
                return sizeof(int);
            case ShaderDataType::Bool:
                return sizeof(bool);
            case ShaderDataType::None:
                return 0;
        }
        ASSERT(false, "Unknown ShaderDataType");
    }
    
    static int shaderDataDimSize(ShaderDataDim type) {
        switch (type) {
            case ShaderDataDim::Value:
                return 1;
            case ShaderDataDim::Vec2:
                return 2;
            case ShaderDataDim::Vec3:
                return 3;
            case ShaderDataDim::Vec4:
            case ShaderDataDim::Mat2:
                return 4;
            case ShaderDataDim::Mat3:
                return 9;
            case ShaderDataDim::Mat4:
                return 16;
        }
        ASSERT(false, "Unknown ShaderDataDim");
    }
};

class BufferLayout {

public:
    BufferLayout(const std::initializer_list<BufferElement> &elements);
    
    [[nodiscard]] const std::vector<BufferElement> &getElements() const { return elements; }
    
    [[nodiscard]] uint32_t getStride() const { return stride; }

private:
    void calculateOffsetsAndStride() {
        size_t offset = 0;
        stride = 0;
        for (auto &element : elements) {
            element.offset = offset;
            offset += element.size;
            stride += element.size;
        }
    }

private:
    std::vector<BufferElement> elements;
    uint32_t stride = 0;
    
};


class VertexBuffer {
public:
    VertexBuffer(GraphicInterface &graphicInterface,
                 const std::initializer_list<BufferElement> &elements,
                 const void *data,
                 GDIsize size);
    
    ~VertexBuffer();
    
    void bind() const;
    
    void unbind() const;

private:
    GraphicInterface &graphicInterface;
    GDIint vertexBufferID;
    
};
