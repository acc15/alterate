#include <gtest/gtest.h>  // C++ Google Test Framework
#include <alterate/gl/vertex_buffer_layout.h>

TEST(vertex_buffer_layout_test, correctly_computes_offsets) {

    alterate::gl::vertex_buffer_layout vbl;
    vbl.register_attribute(GL_FLOAT, 4).
        register_attribute(GL_INT, 2).
        register_attribute(GL_SHORT, 1).
        register_attribute(GL_BYTE, 1);

    size_t expected_stride = sizeof(GLfloat) * 4 + sizeof(GLint) * 2 + sizeof(GLshort) * 1 + sizeof(GLbyte) * 1;
    ASSERT_EQ(expected_stride, vbl.stride());

    ASSERT_EQ(0u, vbl.attribute_offset(0));
    ASSERT_EQ(sizeof(GLfloat) * 4, vbl.attribute_offset(1));
    ASSERT_EQ(sizeof(GLfloat) * 4 + sizeof(GLint) * 2, vbl.attribute_offset(2));

    ASSERT_EQ(4u, vbl.element_count(0));
    ASSERT_EQ(2u, vbl.element_count(1));
    ASSERT_EQ(1u, vbl.element_count(2));
    ASSERT_EQ(1u, vbl.element_count(3));

    ASSERT_EQ(static_cast<GLenum>(GL_FLOAT), vbl.attribute_type(0));
    ASSERT_EQ(static_cast<GLenum>(GL_INT), vbl.attribute_type(1));
    ASSERT_EQ(static_cast<GLenum>(GL_SHORT), vbl.attribute_type(2));
    ASSERT_EQ(static_cast<GLenum>(GL_BYTE), vbl.attribute_type(3));

}

TEST(vertex_buffer_layout_test, attribute_by_offset_returns_correct_index) {

    alterate::gl::vertex_buffer_layout vbl;
    vbl.register_attribute(GL_FLOAT, 4).
        register_attribute(GL_INT, 2).
        register_attribute(GL_SHORT, 1).
        register_attribute(GL_BYTE, 1);

    ASSERT_EQ(0u, vbl.attribute_by_offset(vbl.attribute_offset(0)));
    ASSERT_EQ(0u, vbl.attribute_by_offset(vbl.attribute_offset(1)-1));
    ASSERT_EQ(1u, vbl.attribute_by_offset(vbl.attribute_offset(1)));
    ASSERT_EQ(2u, vbl.attribute_by_offset(vbl.attribute_offset(2)));
    ASSERT_EQ(3u, vbl.attribute_by_offset(vbl.attribute_offset(3)));

}

TEST(vertex_buffer_layout_test, constructible_from_initializer_list) {

    alterate::gl::vertex_buffer_layout vbl;
    vbl.register_attribute(GL_FLOAT, 4).
        register_attribute(GL_INT, 2).
        register_attribute(GL_SHORT, 1).
        register_attribute(GL_BYTE, 1);

    size_t expected_stride = sizeof(GLfloat) * 4 + sizeof(GLint) * 2 + sizeof(GLshort) * 1 + sizeof(GLbyte) * 1;
    ASSERT_EQ(expected_stride, vbl.stride());

    ASSERT_EQ(0u, vbl.attribute_offset(0));
    ASSERT_EQ(sizeof(GLfloat) * 4, vbl.attribute_offset(1));
    ASSERT_EQ(sizeof(GLfloat) * 4 + sizeof(GLint) * 2, vbl.attribute_offset(2));

    ASSERT_EQ(4u, vbl.element_count(0));
    ASSERT_EQ(2u, vbl.element_count(1));
    ASSERT_EQ(1u, vbl.element_count(2));
    ASSERT_EQ(1u, vbl.element_count(3));

    ASSERT_EQ(static_cast<GLenum>(GL_FLOAT), vbl.attribute_type(0));
    ASSERT_EQ(static_cast<GLenum>(GL_INT), vbl.attribute_type(1));
    ASSERT_EQ(static_cast<GLenum>(GL_SHORT), vbl.attribute_type(2));
    ASSERT_EQ(static_cast<GLenum>(GL_BYTE), vbl.attribute_type(3));

}
