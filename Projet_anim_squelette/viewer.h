#ifndef VIEWER_H
#define VIEWER_H

#include <GL/glew.h>
#include <QGLViewer/qglviewer.h>
#include <OGLRender/shaderprogramcolor.h>

#include <matrices.h>
#include <primitives.h>
#include <meshquad.h>


/**
 * @brief The Viewer class
 *
 *
 */
class Viewer : public QGLViewer
{
	Q_OBJECT

public:
    Viewer();

protected:
	/// OpenGL initialization called by the QGLViewer
    void init();

	
/// draw QGLViewer callback
    void draw();

	/// callback key pressed
	void keyPressEvent(QKeyEvent *event);

	/// callback click mouse
	void mousePressEvent(QMouseEvent* event);


	
/// get the modelview matrix from the QGLViewer
	Mat4 getCurrentModelViewMatrix() const;

	
/// get the modelview matrix from the QGLViewer
	Mat4 getCurrentProjectionMatrix() const;

    /// 0:flat 1:phong
	int m_render_mode;

    /// color shortcuts
	Vec3 ROUGE;
	Vec3 VERT;
	Vec3 BLEU;
	Vec3 JAUNE;
	Vec3 CYAN;
	Vec3 MAGENTA;
	Vec3 BLANC;
	Vec3 GRIS;
	Vec3 NOIR;

	Primitives m_prim;

   /// animation counter
	int m_compteur;

    MeshQuad m_mesh;

	void draw_repere(const Mat4& global);

	int m_selected_quad;
	glm::mat4 m_selected_frame;

};

#endif
