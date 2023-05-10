#include <cmath>
#include "primitives.h"


void Primitives::set_matrices(const Mat4& view, const Mat4& projection)
{
	viewMatrix = view;
	projectionMatrix = projection;
}

void Primitives::add_cube(float radius, std::vector<int>& indices)
{
    int beg = m_points.size();

    
// add 8 vertices (-radius +radius)
    m_points.push_back(Vec3(-radius,-radius,-radius));
    m_points.push_back(Vec3( radius,-radius,-radius));
    m_points.push_back(Vec3( radius, radius,-radius));
    m_points.push_back(Vec3(-radius, radius,-radius));

    m_points.push_back(Vec3(-radius,-radius,radius));
    m_points.push_back(Vec3( radius,-radius,radius));
    m_points.push_back(Vec3( radius, radius,radius));
    m_points.push_back(Vec3(-radius, radius,radius));

    // add 6 quad faces: 12 tri (trigo sense)
    Quad q;
    q.indices.resize(4);
    indices.push_back(beg + 0); indices.push_back(beg + 3); indices.push_back(beg + 2);
    indices.push_back(beg + 0); indices.push_back(beg + 2); indices.push_back(beg + 1);
    q.indices[0] = beg + 0; q.indices[1] = beg + 3; q.indices[2] = beg + 2; q.indices[3] = beg + 1;
    m_cubeFaces.push_back(q);

    indices.push_back(beg + 0); indices.push_back(beg + 1); indices.push_back(beg + 5);
    indices.push_back(beg + 0); indices.push_back(beg + 5); indices.push_back(beg + 4);
    q.indices[0] = beg + 0; q.indices[1] = beg + 1; q.indices[2] = beg + 5; q.indices[3] = beg + 4;
    m_cubeFaces.push_back(q);

    indices.push_back(beg + 1); indices.push_back(beg + 2); indices.push_back(beg + 6);
    indices.push_back(beg + 1); indices.push_back(beg + 6); indices.push_back(beg + 5);
    q.indices[0] = beg + 1; q.indices[1] = beg + 2; q.indices[2] = beg + 6; q.indices[3] = beg + 5;
    m_cubeFaces.push_back(q);

    indices.push_back(beg + 2); indices.push_back(beg + 3); indices.push_back(beg + 7);
    indices.push_back(beg + 2); indices.push_back(beg + 7); indices.push_back(beg + 6);
    q.indices[0] = beg + 2; q.indices[1] = beg + 3; q.indices[2] = beg + 7; q.indices[3] = beg + 6;
    m_cubeFaces.push_back(q);

    indices.push_back(beg + 3); indices.push_back(beg + 0); indices.push_back(beg + 4);
    indices.push_back(beg + 3); indices.push_back(beg + 4); indices.push_back(beg + 7);
    q.indices[0] = beg + 3; q.indices[1] = beg + 0; q.indices[2] = beg + 4; q.indices[3] = beg + 7;
    m_cubeFaces.push_back(q);

    indices.push_back(beg + 4); indices.push_back(beg + 5); indices.push_back(beg + 6);
    indices.push_back(beg + 4); indices.push_back(beg + 6); indices.push_back(beg + 7);
    q.indices[0] = beg + 4; q.indices[1] = beg + 5; q.indices[2] = beg + 6; q.indices[3] = beg + 7;
    m_cubeFaces.push_back(q);

    // AABB
    m_cubeAABB.push_back(Vec3(-radius,-radius,-radius));
    m_cubeAABB.push_back(Vec3( radius, radius,radius));
}

void Primitives::add_sphere(int sides, float radius, std::vector<int>& indices)
{
    int beg = m_points.size();

    int nbPara = sides;
	int nbMeri = sides;

    float a1 = (180.0/(nbPara+1))*M_PI/180.0;
	float a2 = (360.0/nbMeri)*M_PI/180.0;

	// the parallels
	for (int i= 0; i< nbPara; ++i)
	{
		float angle = -M_PI/2.0 + a1*(i+1);
		float z = radius*sin(angle);
		float rad = radius*cos(angle);

		for  (int j=0; j< nbMeri; ++j)
		{
            m_points.push_back(Vec3(rad*cos(a2*j), rad*sin(a2*j),z));
		}
	}
	// the poles
    m_points.push_back(Vec3(0.0,0.0,-radius));
    m_points.push_back(Vec3(0.0,0.0, radius));

	// triangles
	for (int i= 0; i< (nbPara-1); ++i)
	{
		for  (int j=0; j< nbMeri; ++j)
		{
            indices.push_back(beg+nbMeri*i+j);
            indices.push_back(beg+nbMeri*i+(j+1)%nbMeri);
            indices.push_back(beg+nbMeri*(i+1)+(j+1)%nbMeri);
            indices.push_back(beg+nbMeri*((i+1))+(j+1)%nbMeri);
            indices.push_back(beg+nbMeri*((i+1))+j);
            indices.push_back(beg+nbMeri*i+j);
		}
	}
	// poles
	for  (int j=0; j< nbMeri; ++j)
	{
        indices.push_back(beg+nbMeri*nbPara);
        indices.push_back(beg+(j+1)%nbMeri);
        indices.push_back(beg+j);
	}
	for  (int j=0; j< nbMeri; ++j)
	{
        indices.push_back(beg+nbMeri*nbPara+1);
        indices.push_back(beg+nbMeri*(nbPara-1)+j);
        indices.push_back(beg+nbMeri*(nbPara-1)+(j+1)%nbMeri);
	}
}


void Primitives::gl_init()
{
	m_shader_flat = new ShaderProgramFlat();

	//VBO
	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	const std::vector<Vec3>& points = getPoints();
	glBufferData(GL_ARRAY_BUFFER, 3 * points.size() * sizeof(GLfloat), &(points.front()[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//VAO
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glEnableVertexAttribArray(m_shader_flat->idOfVertexAttribute);
	glVertexAttribPointer(m_shader_flat->idOfVertexAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBindVertexArray(0);

	//EBO index
	glGenBuffers(1, &m_ebo_cube);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_cube);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_indices_cube.size() * sizeof(int), &(m_indices_cube.front()), GL_STATIC_DRAW);

	glGenBuffers(1, &m_ebo_sphere);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo_sphere);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,m_indices_sphere.size() * sizeof(int), &(m_indices_sphere.front()), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Primitives::draw_cube(const Mat4& transfo, const Vec3& color) const
{
	m_shader_flat->startUseProgram();

	m_shader_flat->sendViewMatrix(viewMatrix*transfo);
	m_shader_flat->sendProjectionMatrix(projectionMatrix);

	glUniform3fv(m_shader_flat->idOfColorUniform, 1, glm::value_ptr(color));
	glUniform3fv(m_shader_flat->idOfBColorUniform, 1, glm::value_ptr(color));

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ebo_cube);
	glDrawElements(GL_TRIANGLES, m_indices_cube.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	m_shader_flat->stopUseProgram();
}

void Primitives::draw_sphere(const Mat4& transfo, const Vec3& color) const
{
	m_shader_flat->startUseProgram();

	m_shader_flat->sendViewMatrix(viewMatrix*transfo);
	m_shader_flat->sendProjectionMatrix(projectionMatrix);

	glUniform3fv(m_shader_flat->idOfColorUniform, 1, glm::value_ptr(color));
	glUniform3fv(m_shader_flat->idOfBColorUniform, 1, glm::value_ptr(color));

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_ebo_sphere);
	glDrawElements(GL_TRIANGLES, m_indices_sphere.size(),GL_UNSIGNED_INT,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
	glBindVertexArray(0);

	m_shader_flat->stopUseProgram();
}


Primitives::Primitives()
{
    add_cube(1.f,m_indices_cube);
	add_sphere(32,0.5f,m_indices_sphere);
}
