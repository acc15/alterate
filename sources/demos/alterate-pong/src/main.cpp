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

    alterate::gl::mat4 world_tx;
    alterate::gl::mat4 local_tx;
    alterate::gl::vertex_buffer<> vb;

    float rot = 0;

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
             vb({{GL_FLOAT, 2}, {GL_FLOAT, 3}})
    {
        program.shader(vertex_shader).
                shader(fragment_shader).
                attribute("a_Position").
                attribute("a_Color").
                uniform("u_MVPMatrix");
    }

    // 0,   0
    //
    //          sx, sy

    // 0,   0
    //
    //          2,  2

    // -1,  1
    //
    //          1,  -1

    virtual void on_update(float seconds) {
        vb.clear(3).
           put(0.f).put(-50.f).put(1.f).put(0.f).put(0.f).
           put(-50.f).put(50.f).put(0.f).put(1.f).put(0.f).
           put(50.f).put(50.f).put(0.f).put(0.f).put(1.f);

        rot += 2*3.1415f*seconds;

        local_tx.build().identity().rotate_z(rot).local_to_world();
    }

    virtual void on_size(const alterate::dimension& size) {
        world_tx.build().identity().scale({size.x/2.f, -(size.y/2.f)}).world_to_local();
    }

    virtual void on_draw(alterate::gl::context& context) {
        alterate::gl::mat4 m = world_tx * local_tx;
        context.clear().
                use(program).
                uniform(m).
                attributes(vb).
                draw(GL_TRIANGLES);
    }

};

void alterate_init(alterate::engine& e) {
    e.init<pong>();
}
