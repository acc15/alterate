#include <iostream>
#include <string>

#include <alterate/engine.h>
#include <alterate/gl/util.h>

#include <alterate/gl/shader.h>
#include <alterate/gl/program.h>

#include <vector>

class pong: public alterate::engine_object {
public:

    static alterate::gl::shader VERTEX_SHADER;
    static alterate::gl::shader FRAGMENT_SHADER;
    static alterate::gl::program PROGRAM;

    virtual void on_attach(alterate::engine& engine) {

        PROGRAM.create();



    }

    virtual void on_draw(alterate::gl::context& context) {


        //glDrawArrays(GL_TRIANGLES, );

    }

};

alterate::gl::shader pong::VERTEX_SHADER(GL_VERTEX_SHADER,
    "uniform mat4 u_MVPMatrix;"
    "attribute vec4 a_Position;"
    "attribute vec4 a_Color;"
    "varying vec4 v_Color;"
    "void main()"
    "{"
        "gl_Position = u_MVPMatrix * a_Position;"
        "v_Color = a_Color;"
    "}");


alterate::gl::shader pong::FRAGMENT_SHADER(GL_FRAGMENT_SHADER,
   "varying vec4 v_Color;"
   "void main()"
   "{"
       "gl_FragColor = v_Color;"
   "}");

alterate::gl::program pong::PROGRAM = alterate::gl::program().
        add_shader(pong::VERTEX_SHADER).
        add_shader(pong::FRAGMENT_SHADER).
        add_attribute("a_Position").
        add_attribute("a_Color").
        add_uniform("u_MVPMatrix");


std::unique_ptr<alterate::engine_object> alterate_init(alterate::engine& e) {

    pong* p = new pong();

    //e.set_root(std::unique_ptr<pong>(new pong()));

    const GLubyte* version = glGetString(GL_VERSION);
    std::cout << version << std::endl;
    std::cout << "in alterate pong" << std::endl;
    return std::unique_ptr<alterate::engine_object>(p);
}
