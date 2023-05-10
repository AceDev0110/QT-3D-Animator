TEMPLATE = subdirs

SUBDIRS = QGLViewer OGLRender Transfos Revolution Triangulation Projet_modeling Projet_anim_squelette

 # what subproject depends on others
Transfos.depends = QGLViewer OGLRender
Revolution.depends = QGLViewer OGLRender
Triangulation.depends = QGLViewer OGLRender
Projet_modeling.depends = QGLViewer OGLRender
Projet_anim_squelette.depends = QGLViewer OGLRender