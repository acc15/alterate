#include <iostream>
#include <string>

#include <alterate/engine.h>
#include <alterate/gl/util.h>


#include <vector>

class shader {
private:
    const char* _source;
    const int   _type;
    GLuint      _id;

public:
    shader(int type, const char* source) : _source(source), _type(type) {}

    GLuint create() {

        const GLuint shaderId = glCreateShader(_type);
        if(shaderId == 0) {
            std::cerr << "Unable to create shader: " << alterate::gl::get_gl_error_as_string() << std::endl;
            return 0;
        }

        // Load the shader source
        glShaderSource(shaderId, 1, &_source, NULL);

        // Compile the shader
        glCompileShader(shaderId);
        // Check the compile status

        GLint compiled;
        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
        if(!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLen);
            if(infoLen > 1) {
                std::string message(0, infoLen);
                glGetShaderInfoLog(shaderId, infoLen, NULL, &message[0]);
                std::cerr << "Unable to compile shader: " << message << ". Shader source: " << _source << std::endl;
            }
            glDeleteShader(shaderId);
            return 0;
        }
        return shaderId;
    }

};

class program {
private:

    std::vector<shader*> _shaders;
    GLuint               _id;

public:

    program& add_shader(shader& shader) {
        _shaders.push_back(&shader);
        return *this;
    }

    GLuint create(alterate::gl::context& context) {

        const GLuint programId = glCreateProgram();
        if (programId == 0) {
            std::cerr << "Unable to create program: " << alterate::gl::get_gl_error_as_string() << std::endl;
            return 0;
        }

        for (shader* shader: _shaders) {
            context.create_if_needed(shader);
            glAttachShader(programId, shader->get_id());
        }

        // bind attributes..

        //glBindAttribLocation(programObject, 0, "vPosition");
        // Link the program
        glLinkProgram(programObject);
        // Check the link status
        glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
        if(!linked)
        {
        GLint infoLen = 0;
        glGetProgramiv(programObject, GL_INFO_LOG_LENGTH, &infoLen);

        if(infoLen > 1)
        {
        char* infoLog = malloc(sizeof(char) * infoLen);
        glGetProgramInfoLog(programObject, infoLen, NULL, infoLog);
        esLogMessage("Error linking program:\n%s\n", infoLog);

        free(infoLog);
        }
        glDeleteProgram(programObject);
        return FALSE;
        }
        // Store the program object
        userData->programObject = programObject;
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        return TRUE;


    }


};

class pong: public alterate::engine_object {

public:

    virtual void on_attach(alterate::engine &engine) {

        GLuint vertexId = shader(GL_VERTEX_SHADER,
                "uniform mat4 u_mvpMatrix;"
                "attribute vec4 a_position;"
                "attribute vec4 a_color;"
                "varying vec4 v_color;"
                "void main() {"
                "v_color = a_color;"
                "gl_Position = u_mvpMatrix * a_position;"
                "}").create();

        GLuint fragmentId = shader(GL_FRAGMENT_SHADER,
               "precision mediump float;"
               "varying vec4 v_color;"
               "void main(void)"
               "{"
                   "gl_FragColor = v_color;"
               "}").create();

        std::cout << "compiled vertex shader: " << vertexId << std::endl <<
                     "compiled fragment shader: " << fragmentId << std::endl;




    }

    virtual void on_draw(alterate::gl::context& context) {


        //glDrawArrays(GL_TRIANGLES, );

    }

};

std::unique_ptr<alterate::engine_object> alterate_init(alterate::engine& e) {

    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << version << std::endl;
    std::cout << "in alterate pong" << std::endl;
    return std::unique_ptr<alterate::engine_object>(new pong());
}
