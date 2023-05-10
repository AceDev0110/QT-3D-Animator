#ifndef SQUELETTE_H
#define SQUELETTE_H

#include "matrices.h"
#include "primitives.h"
#include <vector>

const Vec3 ROUGE   = {1,0,0};
const Vec3 VERT    = {0,1,0};
const Vec3 BLEU    = {0,0,1};
const Vec3 JAUNE   = {1,1,0};
const Vec3 CYAN    = {0,1,1};
const Vec3 MAGENTA = {1,0,1};
const Vec3 BLANC   = {1,1,1};
const Vec3 GRIS    = {0.5,0.5,0.5};
const Vec3 NOIR    = {0,0,0};
// Articulation = tree node (1 sphere and 1 associated cube)
struct Articulation
{
    Articulation *parent;   // articulation parent
    Mat4 rotation;          // rotation matrix
    Mat4 mat_Sphere;        //  translation matrix(relative to the position of the parent cube) of the sphere
    Mat4 mat_Cube;          //  translation matrix (relative to the position of the parent cube) of the cube
    Vec3 dir_;              // joint direction vector relative to its parent
    Vec3 radius_;           // cube radius
    Vec3 color_;            // joint color

  
// Constructor of a joint
    Articulation(Articulation *p = nullptr, const Vec3& l = Vec3(1), const Vec3& d = Vec3(1), const Vec3& col = BLANC)
        : parent(p), rotation(), dir_(d), radius_(l), color_(col)
    {
        // set mat_Sphere and mat_Cube matrices relative to parent radius
        // and knowing that a cube has a base radius of 1 and a sphere of 0.5

        // For the torso we don't have a specific matrix
    }

    Mat4 get_pos_sphere()
    {
        
// we return the position matrix of the sphere with respect to the position of the parent cube (if we have one)
        // also taking rotations into account

        return Mat4();
    }

    Mat4 get_pos_cube()
    {
        
// we return the position matrix of the cube with respect to the position of the parent cube (if we have one)
        // also taking rotations into account

        return Mat4();
    }

  // Give the point at the end of the joint
    Vec3 get_ext() { return Vec3((get_pos_cube() * translate(radius_*dir_))[3]); }

    void rotate_Cardan(double r1, double r2, double r3)
    {
       // We apply a rotation with r1 the angle on X, r2 the angle on Y and r3 the angle on Z
    }

    void move_articulation(const Vec3& tr)
    {
       // we apply a translation to the sphere and to the cube to move the whole joint
        // we check that the sphere does not come out of the cube of the parent
    }

    void scale_articulation(const Vec3& sc)
    {
        // we update the radius of the cube
        // we apply the translation necessary to reposition the cube after dilation
        // Attention: here we do not apply the homothety, it will be applied at the time of display (Skeleton::draw_articulation())
    }

    // Modify the color of the joint
    void changeColor(const Vec3& color) {color_ = color;}
 };

class Squelette
{
    std::vector<Articulation *> articulations_;

public:
    Primitives prim;
    Articulation *selected_a_;

    Squelette();
    ~Squelette();

    Articulation* add_articulation(Articulation *p = nullptr, const Vec3& l = Vec3(1,1,1), const Vec3& d = Vec3(1,1,1), const Vec3& coul = BLANC);

    void clear();
    bool isEmpty();

    void draw_articulation(Articulation &a, Vec3 coul);
    void draw();

    /**
     * @brief calculates the intersection between a ray and a sphere
     * @param has the joint for which we are testing the intersection
     * @param P starting point of the ray
     * @param Dir ray direction
     * @param t intersection distance along radius [out]
     * @return if there is an intersection
     */
    bool intersect_sphere(Articulation *a, const Vec3 &P, const Vec3 &Dir, double &t);

    /**
     * @brief finds the nearest intersection (of P) with a sphere by a radius
     * @param P starting point of the ray
     * @param Dir ray direction
     * @return nearest intersected joint nullptr otherwise
     */
    Articulation* intersect_closest_sphere(const Vec3 &P, const Vec3 &Dir);

    /**
     * @brief calculation the normal vector has a plane given by 3 points
     * @param A
     * @param B
     * @param C
     * @return normalized normal
     */

    Vec3 normal_of(const Vec3& A, const Vec3& B, const Vec3& C);

    /**
     * @brief Determine if P is in quad A,B,C,D (P considered ~ in plane ABCD)
     * @param P
     * @param A, B, C, D quad points
     * @return P in quad A,B,C,D
     */
    bool is_points_in_quad(const Vec3& P, const Vec3& A, const Vec3& B, const Vec3& C, const Vec3& D);

  /**
     * @brief calculates the intersection between a ray and a quad A,B,C,D
     * @param P starting point of the ray
     * @param Dir ray direction
     * @param A, B, C, D (quad points)
     * @param calculated inter intersection [out]
     * @param normal quad A,B,C,D [out]
     * @return the intersection is in the quad
     */
    bool intersect_ray_quad(const Vec3& P, const Vec3& Dir, const Vec3& A, const Vec3& B, const Vec3& C, const Vec3& D, Vec3& inter, Vec3& norm);

    /**
     * @brief finds the closest intersection (of P) with the face of a cube by a radius
     * @param P starting point of the ray
     * @param Dir ray direction
     * @param norm normal of nearest intersected face [out]
     * @return nearest intersected joint nullptr otherwise
     */
    Articulation* intersected_closest_cube_face(const Vec3& P, const Vec3& Dir, Vec3& norm);

    /**
     * @brief calculates the intersection between two bounding boxes
     * @param A, B the two bounding boxes
     * @return A and B intersect
     */
    bool intersectAABB(const std::vector<Vec3>& A, const std::vector<Vec3>& B);

   
/**
     * @brief applies the principle of inverse kinematics from the joint
     * selected to orient the chain of joints towards a goal
     * @param objective point to follow
     */
    void inverse_kinematic(const Vec3& objectif);


};

#endif // SQUELETTE_H
