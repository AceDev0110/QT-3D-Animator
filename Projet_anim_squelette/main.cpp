
#include <QApplication>
#include <QGLViewer/simple_viewer.h>
#include <matrices.h>
#include <primitives.h>
#include <squelette.h>

void create_squelette(Squelette& s)
{
   
// creation of a basic skeleton already ready
}

int main(int argc, char *argv[])
{
    // init of the viewer
    QApplication a(argc, argv);
    SimpleViewer::init_gl();
    SimpleViewer viewer({0.1,0.1,0.1},10);

    // skelet
    Squelette s;
    // primitives
    Primitives prim;
    
// position of the object to follow by animating the skeleton
    Vec3 obj = Vec3(0);
    // skeleton edit mode on/off
    bool editMode = false;
    // position of a cube indicating that we are in edit mode
    Vec3 editPrimPos = Vec3(10, 10, 0);
    // is a face selected in edit mode?
    bool selected_face = false;
    // articulation just added in edit mode
    Articulation* new_art = nullptr;

    // GL init
    viewer.f_init = [&] ()
    {
        s.prim.gl_init();
        prim.gl_init();
    };

    // drawing
    viewer.f_draw = [&] ()
    {
        s.prim.set_matrices(viewer.getCurrentModelViewMatrix(),viewer.getCurrentProjectionMatrix());
        prim.set_matrices(viewer.getCurrentModelViewMatrix(),viewer.getCurrentProjectionMatrix());

        if (viewer.animationIsStarted() && s.selected_a_)
        {
            prim.draw_sphere(translate(obj), BLEU);
            s.inverse_kinematic(obj);
        }

        s.draw();
        if (editMode) prim.draw_cube(translate(editPrimPos), VERT);
    };

    // to do when key pressed
    viewer.f_keyPress = [&] (int key, Qt::KeyboardModifiers mod)
    {
        switch(key)
        {
            case Qt::Key_S:
               // If we are not in edit mode: we clear the skeleton and we "load" the basic skeleton
                break;

            case Qt::Key_C:
                // If we are not in edit mode: we clear the skeleton
                break;

            // Skeleton editing mode
            case Qt::Key_E:
                
            // Activate / deactivate edit mode
                // if we activate it and the skeleton is empty we add the torso
                break;

            case Qt::Key_Enter:
                // If we are in edit mode and a face is selected:
                // we deselect the face and we change the color of the primitive to WHITE
                break;
            case Qt::Key_1:
                // If we are in edit mode and a face is selected:
                // we set up an enlargement dilation on the X axis for the new articulation
                break;

            case Qt::Key_3:
               // If we are in edit mode and a face is selected:
                // we set up a reduction dilation on the X axis for the new joint
                break;

            case Qt::Key_4:
                // If we are in edit mode and a face is selected:
                // we set up an enlargement dilation on the Y axis for the new articulation
                break;

            case Qt::Key_6:
             // If we are in edit mode and a face is selected:
                // we set up a reduction dilation on the Y axis for the new joint
                break;

            case Qt::Key_7:
                // If we are in edit mode and a face is selected:
                // we set up an enlargement dilation on the Z axis for the new articulation
                break;

            case Qt::Key_9:
               // If we are in edit mode and a face is selected:
                // we set up a reduction dilation on the Z axis for the new joint
                break;

            case Qt::Key_Left:
                // If we are in edit mode and a face is selected:
                // move the joint on the X axis
                break;
            case Qt::Key_Right:
               // If we are in edit mode and a face is selected:
                // move the joint on the X axis
                break;
            case Qt::Key_Up:
                // If we are in edit mode and a face is selected:
                // move the joint on the Y axis
                break;
            case Qt::Key_Down:
                // If we are in edit mode and a face is selected:
                // move the joint on the Y axis
                break;

            case Qt::Key_Z:
               // If an articulation is selected (not in edit mode):
                // apply a rotation on Z
                break;
            case Qt::Key_Y:
                // If an articulation is selected (not in edit mode):
                // apply a rotation on Y
                break;
            case Qt::Key_X:
              // If an articulation is selected (not in edit mode):
                // apply a rotation on X
                break;

            case Qt::Key_A:
                // do not touch ! : we start/stop the animation
                if (viewer.animationIsStarted()) viewer.stopAnimation();
                else viewer.startAnimation();
                break;

            case Qt::Key_J:
             // we move the object to "catch" on the X axis
                // (positive or negative if you also press the shift key (mod == Qt::ShiftModifier))
                break;
            case Qt::Key_K:
                // we move the object to "catch" on the Y axis
                // (positive or negative if you also press the shift key (mod == Qt::ShiftModifier))
                break;
            case Qt::Key_L:
          // we move the object to "catch" on the Z axis
                // (positive or negative if you also press the shift key (mod == Qt::ShiftModifier))
                break;

            default:
                break;
        }
        viewer.update();
    };


    // mouse click
    viewer.f_mousePress3D = [&] (Qt::MouseButton b, const glm::vec3& P, const glm::vec3& Dir)
    {
        // If we are in edit mode and no face is selected:
        // we retrieve the closest intersected face with the radius of origin P and direction Dir
        // if we have intersected a face well then we add a joint along its normal
        // (the new articulation will be displayed in YELLOW until you press "Enter" to "validate" it

        // If we are not in edit mode, we retrieve the closest intersection between the radius and the spheres of the joints
        // if there is an intersection, the joint becomes "selected"
    };

    viewer.f_animate = [&]()
    {};

    viewer.clearShortcuts();
    viewer.setShortcut(QGLViewer::EXIT_VIEWER,Qt::Key_Escape);
    viewer.show();
    return a.exec();
}
