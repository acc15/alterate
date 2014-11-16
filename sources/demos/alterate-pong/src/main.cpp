#include <iostream>
#include <string>

#include <alterate/engine.h>
#include <alterate/gl/util.h>


#include <vector>

class shader {
private:
    const char* _source;
    const int   _type;
    GLuint      _id = 0;

public:
    shader(int type, const char* source) : _source(source), _type(type) {}

    GLuint create(alterate::gl::context& context) {

        if (context.is_live(this)) {
            return _id;
        }

        _id = glCreateShader(_type);
        if(_id == 0) {
            std::cerr << "Unable to create shader: " << alterate::gl::get_gl_error_as_string() << std::endl;
            return 0;
        }

        glShaderSource(_id, 1, &_source, NULL);
        glCompileShader(_id);

        GLint compiled;
        glGetShaderiv(_id, GL_COMPILE_STATUS, &compiled);
        if(!compiled) {
            std::cerr << "Unable to compile shader: " << alterate::gl::get_shader_info_log(_id) << ". Shader source: " << _source << std::endl;
            glDeleteShader(_id);
            _id = 0;
            return false;
        }

        context.mark_live(this);
        return true;
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

    // 1. Mark as deleted notification -> Needed some virtual interface
    // 2. Keep set of live objects (use object address = void*) -> No requirement for interface
    //    Check map before creating object
    //    Clean this map if EGL context was re-created

    GLuint create(alterate::gl::context& context) {

        if (context.is_live(this)) {
            return _id;
        }

        _id = glCreateProgram();
        if (_id == 0) {
            std::cerr << "Unable to create program: " << alterate::gl::get_gl_error_as_string() << std::endl;
            return 0;
        }

        for (shader* shader: _shaders) {
            const GLuint shader_id = shader->create(context);
            glAttachShader(_id, shader_id);
        }

        // bind attributes..
        //glBindAttribLocation(program_id, 0, "vPosition");

        // Link the program
        glLinkProgram(_id);

        GLint linked;
        glGetProgramiv(_id, GL_LINK_STATUS, &linked);
        if (!linked) {
            std::cerr << "Unable to link program: " << alterate::gl::get_program_info_log(_id) << std::endl;
            glDeleteProgram(_id);
            _id = 0;
            return false;
        }

        context.mark_live(this);
        return true;
    }


};

class pong: public alterate::engine_object {
public:

    static shader VERTEX_SHADER;
    static shader FRAGMENT_SHADER; /*(GL_FRAGMENT_SHADER,
                                  "precision mediump float;"
                                  "varying vec4 v_color;"
                                  "void main(void) {"
                                      "gl_FragColor = v_color;"
                                  "}");*/

    static program PROGRAM;

    virtual void on_attach(alterate::engine &engine) {

        GLuint program_id = PROGRAM.create(engine.get_context());

        std::cout << "linked program id: " << program_id << std::endl;




    }

    virtual void on_draw(alterate::gl::context& context) {


        //glDrawArrays(GL_TRIANGLES, );

    }

};

class object_factory {

public:
    shader* create_shader() {
        return nullptr;
    }

};

shader* new_shader = object_factory().create_shader();

shader pong::VERTEX_SHADER(GL_VERTEX_SHADER, "uniform mat4 u_mvpMatrix;"
                                                  "attribute vec4 a_position;"
                                                  "attribute vec4 a_color;"
                                                  "varying vec4 v_color;"
                                                  "void main() {"
                                                      "v_color = a_color;"
                                                      "gl_Position = u_mvpMatrix * a_position;"
                                                  "}");


shader pong::FRAGMENT_SHADER(GL_FRAGMENT_SHADER,
                              "varying vec4 v_color;"
                              "void main(void) {"
                                  "gl_FragColor = v_color;"
                              "}");
program pong::PROGRAM = program().add_shader(pong::VERTEX_SHADER).add_shader(pong::FRAGMENT_SHADER);


std::unique_ptr<alterate::engine_object> alterate_init(alterate::engine& e) {

    pong* p = new pong();

    //e.set_root(std::unique_ptr<pong>(new pong()));

    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << version << std::endl;
    std::cout << "in alterate pong" << std::endl;
    return std::unique_ptr<alterate::engine_object>(p);
}
