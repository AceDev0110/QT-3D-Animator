#include "squelette.h"

Squelette::Squelette() : selected_a_(nullptr) {}

Squelette::~Squelette()
{
    for (auto a : articulations_)
        delete a;
}

Articulation* Squelette::add_articulation(Articulation *p, const Vec3& l, const Vec3& d, const Vec3& coul)
{
    // add an articulation to the articulations_ vector
    // return the new joint

    return nullptr;
}

void Squelette::clear()
{
    // delete all joints
    // clear the joints_ vector

}

bool Squelette::isEmpty()
{
    return articulations_.empty();
}

void Squelette::draw_articulation(Articulation &a, Vec3 coul)
{
    // display the two cube and sphere primitives of the joint
    // remember here to apply homothety on the cube for its radius
    // the torso should only display a cube
}

void Squelette::draw()
{
    // display all joints
    // in Yellow for the selected joint (selected_a_) and with the right color otherwise
 }

bool Squelette::intersect_sphere(Articulation *a, const Vec3 &P, const Vec3 &Dir, double &t)
{
   // we replace the radius (origin and direction) in the reference of the sphere of the joint

    // we calculate the discriminant t
    // if t is positive then there is an intersection

    return false;
}

Articulation* Squelette::intersect_closest_sphere(const Vec3 &P, const Vec3 &Dir)
{
    // we seek the closest intersection by testing with all the joints
    return nullptr;
}

Vec3 Squelette::normal_of(const Vec3& A, const Vec3& B, const Vec3& C)
{
   // Pay attention to the order of the points!
    // the vector product is not commutative U ^ V = - V ^ U
    // don't forget to normalize the result.
    return Vec3(0);
}

bool Squelette::is_points_in_quad(const Vec3& P, const Vec3& A, const Vec3& B, const Vec3& C, const Vec3& D)
{
    // P is in the plane of the quad.

    // Is P above the 4 planes each containing the normal to the quad and an edge AB/BC/CD/DA?
    // if yes he is in the quad

    return true;
}

bool Squelette::intersect_ray_quad(const Vec3& P, const Vec3& Dir, const Vec3& A, const Vec3& B, const Vec3& C, const Vec3& D, Vec3& inter, Vec3& norm)
{
    // calculate the plane equation (N+d)

    // calculation of the plane radius intersection
    // I = P + alpha*Dir is in the plane => calculation of alpha

    // alpha => calculation of I

    // I in the quad

    return false;
}

Articulation* Squelette::intersected_closest_cube_face(const Vec3& P, const Vec3& Dir, Vec3& norm)
{
    Articulation* inter = nullptr;
    float lmin = std::numeric_limits<float>::max();

    // we go through all the joints
        // we traverse all the faces of the cube of the articulation
            // retrieve points from the quad at the origin (prim.getPoints();)
            // we move the quad to its position in the scene
            // we test if there is an intersection with the radius
            // we keep the closest (to P)

    return inter;
}

bool Squelette::intersectAABB(const std::vector<Vec3>& A, const std::vector<Vec3>& B)
{
    // we look on the 3 axes if the AABBs overlap
    return false;

}

void Squelette::inverse_kinematic(const Vec3& objectif)
{
  // For a given number of iterations (ex: 100 iterations)
        // For each joint from the selected one, up to the torso
            // For each axis
                // we determine the gradient by applying a very slight rotation (eg 0.1) and by calculating the new distance to the objective
                // we update the distance
                // we apply a greater rotation according to the gradient

}
