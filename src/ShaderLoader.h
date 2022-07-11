class ShaderLoader{
    public:
        unsigned int LoadAndLinkAll();
        void LoadVertexShader();
        void LoadFragmentShader();
        unsigned int getShaderProgramID(){ return shaderProgram; }
    private:
        unsigned int vertexShader;
        const char* vertexShaderSource=
        R"glsl(

            #version 430 core
            layout (location = 0) in vec3 aPos;\n
            void main()
            {
                gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
            }

        )glsl";

        unsigned int fragmentShader;
        const char* fragmentShaderSource=
        R"glsl(

            #version 430 core
            out vec4 FragColor;
            void main()
            {
                FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
            }

        )glsl";

        void HandleErrors_VertexShader();
        void HandleErrors_FragmentShader();
        void HandleErrors_Linking();
        void Clean();
        int  success;
        char infoLog[512];
        unsigned int shaderProgram;

};