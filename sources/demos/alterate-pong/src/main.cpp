#include <iostream>
#include <string>

#include <alterate/engine.h>
#include <alterate/gl/util.h>

#include <alterate/gl/shader.h>
#include <alterate/gl/program.h>

#include <vector>

class pong: public alterate::engine_handler {
public:

    alterate::gl::shader VERTEX_SHADER;
    alterate::gl::shader FRAGMENT_SHADER;
    alterate::gl::program PROGRAM;

    pong() : VERTEX_SHADER(GL_VERTEX_SHADER,
                           "uniform mat4 u_MVPMatrix;"
                           "attribute vec4 a_Position;"
                           "attribute vec4 a_Color;"
                           "varying vec4 v_Color;"
                           "void main()"
                           "{"
                               "gl_Position = u_MVPMatrix * a_Position;"
                               "v_Color = a_Color;"
                           "}"),
             FRAGMENT_SHADER(GL_FRAGMENT_SHADER,
                             "varying vec4 v_Color;"
                             "void main()"
                             "{"
                                 "gl_FragColor = v_Color;"
                             "}")
    {

        PROGRAM.shader(VERTEX_SHADER).
                shader(FRAGMENT_SHADER).
                attribute("a_Position").
                attribute("a_Color").
                uniform("u_MVPMatrix");
    }

    //matfloat

    virtual void on_attach() {
        PROGRAM.create();
        //        PROGRAM.create();
    }

    virtual void on_update(float seconds) {


    }

    virtual void on_draw(alterate::gl::context& context) {

//        context.use(PROGRAM);

        //context.use(PROGRAM).


        //glDrawArrays(GL_TRIANGLES, );

    }

};

void alterate_init(alterate::engine& e) {
    e.init<pong>();
}
