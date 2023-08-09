/*******************************************************************************
 *
 * Copyright (c) 2023.
 * Licensed under the MIT License. See LICENSE.txt in the project root for license information.
 ******************************************************************************/

#pragma once

#include "engine/core/low-level-renderer/graphic-device-interface/GraphicInterface.h"
#include "SDL2/SDL.h"
#include <functional>

class OpenGLGDI final : public GraphicInterface {


public:
    explicit OpenGLGDI();
    
    [[nodiscard]] GraphicsAPI getGraphicsAPI() const override { return GraphicsAPI::OPENGL; }
    
    
    void deleteTexture(GDIuint textureID) override;
    
    void deleteContext() override;
    
    void setViewport(int x, int y, int width, int height) override;
    
    void setViewport(int width, int height) override;
    
    void setViewport() override;
    
    GDIuint createTexture(SDL_Surface &surface,
                          GDIValues minFilter,
                          GDIValues magFilter,
                          GDIValues wrapS,
                          GDIValues wrapT) override;
    
    GDIuint createTexture(SDL_Surface &surface) override;
    
    void bindTexture(GDIuint textureID) override;
    
    std::function<void(SDL_Window &)> getSwapBuffersFunc() override;
    
    [[nodiscard]] SDL_GLContext getContext() const { return context; };
    
    void postWindowCreationInit() override;
    
    
    // -------------------------------- Shaders -------------------------------------
    // ------------------------------------------------------------------------------
    
    
    GDIuint loadAndCompileShader(GDIValues shaderType, const std::string &shaderSource) override;
    
    [[nodiscard]] bool compilationOK(GDIuint shaderID, GDIchar *message) override;
    
    GDIuint createShaderProgram(GDIuint vertexShaderID, GDIuint fragmentShaderID) override;
    
    [[nodiscard]] bool linkOK(GDIuint programID, GDIchar *message) override;
    
    
    // -------------------------------- Uniforms ------------------------------------
    
    [[nodiscard]] GDIint getUniformLocation(GDIuint program, const std::string &name) override;
    
    void setUniform1Float(GDIint location, GDIfloat v0) override;
    
    void setUniform1FloatVector(GDIint location, GDIsize count, const GDIfloat *value) override;
    
    void setUniform1Int(GDIint location, GDIint v0) override;
    
    void setUniform1IntVector(GDIint location, GDIsize count, const GDIint *value) override;
    
    void setUniform2Float(GDIint location, GDIfloat v0, GDIfloat v1) override;
    
    void setUniform2FloatVector(GDIint location, GDIsize count, const GDIfloat *value) override;
    
    void setUniform2Int(GDIint location, GDIint v0, GDIint v1) override;
    
    void setUniform2IntVector(GDIint location, GDIsize count, const GDIint *value) override;
    
    void setUniform3Float(GDIint location, GDIfloat v0, GDIfloat v1, GDIfloat v2) override;
    
    void setUniform3FloatVector(GDIint location, GDIsize count, const GDIfloat *value) override;
    
    void setUniform3Int(GDIint location, GDIint v0, GDIint v1, GDIint v2) override;
    
    void setUniform3IntVector(GDIint location, GDIsize count, const GDIint *value) override;
    
    void setUniform4Float(GDIint location, GDIfloat v0, GDIfloat v1, GDIfloat v2, GDIfloat v3) override;
    
    void setUniform4FloatVector(GDIint location, GDIsize count, const GDIfloat *value) override;
    
    void setUniform4Int(GDIint location, GDIint v0, GDIint v1, GDIint v2, GDIint v3) override;
    
    void setUniform4IntVector(GDIint location, GDIsize count, const GDIint *value) override;
    
    void
    setUniformMatrix2FloatVector(GDIint location, GDIsize count, GDIbool transpose, const GDIfloat *value) override;
    
    void
    setUniformMatrix3FloatVector(GDIint location, GDIsize count, GDIbool transpose, const GDIfloat *value) override;
    
    void
    setUniformMatrix4FloatVector(GDIint location, GDIsize count, GDIbool transpose, const GDIfloat *value) override;
    
    void useShaderProgram(GDIuint shaderProgram) override;
    
    void clear(GDIValues clearBits, ...) override;
    
    void clearColor(GDIfloat r, GDIfloat g, GDIfloat b, GDIfloat a) override;
    
    void genBuffers(GDIuint amount, GDIint &bufferID) override;
    
    void bindBuffer(GDIValues bufferType, GDIuint buffer) override;
    
    void unbindBuffer(GDIValues bufferType) override;
    
    void deleteBuffer(GDIuint buffer) override;
    
    void
    setBufferData(const void *data, GDIsize size, GDIuint buffer, GDIValues bufferType, GDIValues bufferUsage) override;
    
    void deleteShader(GDIuint shaderID) override;


private:
    
    void createContext(SDL_Window &window, GDIint w, GDIint h, GDIint x, GDIint y) override;
    
    static void setSDLGLAttribute(SDL_GLattr attrib, int val);
    
    /**
     * @brief Must be called after creating the window and before enabling gl functions like glEnable() or glCullFace()
     */
    static void initGLEW();
    
    static GDIint translateEnumToOpenGL(GDIValues value);
    
    SDL_GLContext context;
    
};

