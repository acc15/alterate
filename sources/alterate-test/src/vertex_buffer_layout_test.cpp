#include <gtest/gtest.h>  // C++ Google Test Framework
#include <alterate/gl/vertex_buffer_layout.h>

TEST(vertex_buffer_layout_test, correctly_computes_offsets) {

    alterate::gl::vertex_buffer_layout vbl;
    vbl.attribute(GL_FLOAT, 4).
        attribute(GL_INT, 2).
        attribute(GL_SHORT, 1).
        attribute(GL_BYTE, 1);

    size_t expected_stride = sizeof(GLfloat) * 4 + sizeof(GLint) * 2 + sizeof(GLshort) * 1 + sizeof(GLbyte) * 1;
    ASSERT_EQ(expected_stride, vbl.stride());

    ASSERT_EQ(0, vbl.offset(0));
    ASSERT_EQ(sizeof(GLfloat) * 4, vbl.offset(1));
    ASSERT_EQ(sizeof(GLfloat) * 4 + sizeof(GLint) * 2, vbl.offset(2));

    ASSERT_EQ(4, vbl.element_count(0));
    ASSERT_EQ(2, vbl.element_count(1));
    ASSERT_EQ(1, vbl.element_count(2));
    ASSERT_EQ(1, vbl.element_count(3));

    ASSERT_EQ(GL_FLOAT, vbl.attribute_type(0));
    ASSERT_EQ(GL_INT, vbl.attribute_type(1));
    ASSERT_EQ(GL_SHORT, vbl.attribute_type(2));
    ASSERT_EQ(GL_BYTE, vbl.attribute_type(3));

}

TEST(vertex_buffer_layout_test, attribute_by_offset_returns_correct_index) {

    alterate::gl::vertex_buffer_layout vbl;
    vbl.attribute(GL_FLOAT, 4).
        attribute(GL_INT, 2).
        attribute(GL_SHORT, 1).
        attribute(GL_BYTE, 1);

    ASSERT_EQ(0, vbl.attribute_by_offset(vbl.offset(0)));
    ASSERT_EQ(0, vbl.attribute_by_offset(vbl.offset(1)-1));
    ASSERT_EQ(1, vbl.attribute_by_offset(vbl.offset(1)));
    ASSERT_EQ(2, vbl.attribute_by_offset(vbl.offset(2)));
    ASSERT_EQ(3, vbl.attribute_by_offset(vbl.offset(3)));

}

TEST(vertex_buffer_layout_test, constructible_from_initializer_list) {

    alterate::gl::vertex_buffer_layout vbl;
    vbl.attribute(GL_FLOAT, 4).
        attribute(GL_INT, 2).
        attribute(GL_SHORT, 1).
        attribute(GL_BYTE, 1);

    size_t expected_stride = sizeof(GLfloat) * 4 + sizeof(GLint) * 2 + sizeof(GLshort) * 1 + sizeof(GLbyte) * 1;
    ASSERT_EQ(expected_stride, vbl.stride());

    ASSERT_EQ(0, vbl.offset(0));
    ASSERT_EQ(sizeof(GLfloat) * 4, vbl.offset(1));
    ASSERT_EQ(sizeof(GLfloat) * 4 + sizeof(GLint) * 2, vbl.offset(2));

    ASSERT_EQ(4, vbl.element_count(0));
    ASSERT_EQ(2, vbl.element_count(1));
    ASSERT_EQ(1, vbl.element_count(2));
    ASSERT_EQ(1, vbl.element_count(3));

    ASSERT_EQ(GL_FLOAT, vbl.attribute_type(0));
    ASSERT_EQ(GL_INT, vbl.attribute_type(1));
    ASSERT_EQ(GL_SHORT, vbl.attribute_type(2));
    ASSERT_EQ(GL_BYTE, vbl.attribute_type(3));

}
