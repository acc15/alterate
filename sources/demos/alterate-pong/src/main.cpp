#include <iostream>
#include <string>

#include <alterate/engine.h>
#include <alterate/gl/util.h>

#include <alterate/gl/shader.h>
#include <alterate/gl/program.h>
#include <alterate/gl/vertex_buffer.h>

#include <vector>

class pong: public alterate::engine_handler {
public:

    alterate::gl::shader vertex_shader;
    alterate::gl::shader fragment_shader;
    alterate::gl::program program;

    alterate::gl::mat4 tx;
    alterate::gl::vertex_buffer<> vb;

    pong() : vertex_shader(GL_VERTEX_SHADER,
                           "uniform mat4 u_MVPMatrix;"
                           "attribute vec4 a_Position;"
                           "attribute vec4 a_Color;"
                           "varying vec4 v_Color;"
                           "void main()"
                           "{"
                               "gl_Position = u_MVPMatrix * a_Position;"
                               "v_Color = a_Color;"
                           "}"),
             fragment_shader(GL_FRAGMENT_SHADER,
                             "varying vec4 v_Color;"
                             "void main()"
                             "{"
                                 "gl_FragColor = v_Color;"
                             "}"),
             tx(alterate::gl::mat4::identity()),
             vb({{GL_FLOAT, 2}, {GL_FLOAT, 3}})
    {
        program.shader(vertex_shader).
                shader(fragment_shader).
                attribute("a_Position").
                attribute("a_Color").
                uniform("u_MVPMatrix");
    }

    virtual void on_update(float seconds) {
        vb.clear(3).
           put(0.f).put(1.f).put(1.f).put(0.f).put(0.f).
           put(-1.f).put(-1.f).put(0.f).put(1.f).put(0.f).
           put(1.f).put(-1.f).put(0.f).put(0.f).put(1.f);
    }

    virtual void on_draw(alterate::gl::context& context) {
        context.use(program).
                uniform(tx).
                attributes(vb).
                draw(GL_TRIANGLES);
    }

};

void alterate_init(alterate::engine& e) {
    e.init<pong>();
}
