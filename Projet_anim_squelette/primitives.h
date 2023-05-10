#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <vector>
#include <OGLRender/shaderprogramflat.h>
#include <matrices.h>

struct Quad
{
    std::vector<int> indices;
};

class Primitives
{
    Mat4 viewMatrix;
    Mat4 projectionMatrix;

    std::vector<Vec3> m_points;
    std::vector<int> m_indices_cube;
    std::vector<int> m_indices_sphere;
    std::vector<Quad> m_cubeFaces;
    std::vector<Vec3> m_cubeAABB;

    void add_cube(float radius, std::vector<int>& indices);
    void add_sphere(int sides, float radius, std::vector<int>& indices);

    ShaderProgramFlat* m_shader_flat;
    GLuint m_vao;
    GLuint m_vbo;

    GLuint m_ebo_cube;
    GLuint m_ebo_sphere;

public:
    Primitives();

    void gl_init();

    void set_matrices(const Mat4& view, const Mat4& projection);

    void draw_cube(const Mat4& transfo, const Vec3& color) const;

    void draw_sphere(const Mat4& transfo, const Vec3& color) const;

    inline const std::vector<Vec3>& getPoints() const {return m_points;}

    inline const std::vector<Quad>& getCubeFaces() const {return m_cubeFaces;}

    inline const std::vector<Vec3>& getCubeAABB() const {return m_cubeAABB;}

    inline const std::vector<int>& getCubeIndices() const {return m_indices_cube;}
};

#endif // PRIMITIVES_H
