#include <iostream>
#include <string>

#include <GL/glew.h>

#include <alterate/engine.h>

class shader {
private:
    const char* _source;
    const int _type;

public:
    shader(int type, const char* source) : _source(source), _type(type) {}

    GLuint create() {

//        GLuint shaderId;

//        // Create the shader object
//        shaderId = glCreateShader(type);
//        if(shaderId == 0) {
//            return 0;
//        }

//        // Load the shader source
//        glShaderSource(shaderId, 1, &shaderSrc, NULL);

//        // Compile the shader
//        glCompileShader(shaderId);
//        // Check the compile status

//        GLint compiled;
//        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compiled);
//        if(!compiled) {
//            GLint infoLen = 0;
//            glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLen);
//            if(infoLen > 1) {
//                char* infoLog = malloc(sizeof(char) * infoLen);
//                glGetShaderInfoLog(shaderId, infoLen, NULL, infoLog);
//                //esLogMessage("Error compiling shader:\n%s\n", infoLog);
//                free(infoLog);
//            }
//            glDeleteShader(shaderId);
//            return 0;
//        }
//        return shaderId;
        return 0;
    }

};

class pong: public alterate::engine_object {

public:
    virtual void on_draw(alterate::gl::context& context) {


        //gl
        //glDrawArrays(GL_TRIANGLES, );

    }

};

std::unique_ptr<alterate::engine_object> alterate_init(alterate::engine& e) {

    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << version << std::endl;
    std::cout << "in alterate pong" << std::endl;
    return std::unique_ptr<alterate::engine_object>(new alterate::engine_object());
}
