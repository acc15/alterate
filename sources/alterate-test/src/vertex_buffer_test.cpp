#include <gtest/gtest.h>

#include <alterate/gl/vertex_buffer.h>

TEST(vertex_buffer_test, initializes_correctly) {
    alterate::gl::vertex_buffer<> vb({{ GL_FLOAT, 4 }, { GL_INT, 2 }});
    ASSERT_EQ(16, vb.layout().offset(1));
}

TEST(vertex_buffer_test, put_works_correctly) {

    alterate::gl::vertex_buffer<> vb({{ GL_FLOAT, 4 }, { GL_INT, 2 }});

    vb.put(5.0f).put(6.0f).put(7.0f).put(8.0f).put(1).put(2);
    ASSERT_EQ(sizeof(GLfloat) * 4 + sizeof(GLint) * 2, vb.size());

    float* first = vb.attribute<float>(0, 0);
    ASSERT_EQ(first[0], 5.0f);
    ASSERT_EQ(first[1], 6.0f);
    ASSERT_EQ(first[2], 7.0f);
    ASSERT_EQ(first[3], 8.0f);

    int* second = vb.attribute<int>(1, 0);
    ASSERT_EQ(second[0], 1);
    ASSERT_EQ(second[1], 2);

}

TEST(vertex_buffer_test, put_disallows_value_which_doesnt_follow_layout) {

}
