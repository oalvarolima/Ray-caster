#ifndef MESH_HPP
#define MESH_HPP

#include "Face.hpp"
#include "../Sphere.hpp"

using std::vector;
using std::max;

class Mesh: public Object {
public:
    Mesh(point3 a_center, color a_obj_color);

    bool intersect(Ray ray, hit_record &hr);
    vec3 get_normal(point3 pi) {return {};}

    void apply_matrix(const mat4 &m);

    void translate_to(point3 p);

    void rotate_x(float angle);
    void rotate_y(float angle);
    void rotate_z(float angle);

    void scale(float x, float y, float z);

    void shear_xy(float angle);
    void shear_xz(float angle);
    void shear_yx(float angle);
    void shear_yz(float angle);
    void shear_zx(float angle);
    void shear_zy(float angle);

    void reflect_xy();
    void reflect_zy();
    void reflect_zx();

    void set_reflectivity(float a_reflectivity);
    void set_shininess(int a_shininess);

protected:
    void add_face(Face *new_face);
    Sphere *cluster;

    void set_cluster_radius(float a_cluster_radius);
    void move_to_origin_apply_M_and_back(const mat4 &M);

private:
    vector<Face *> faces;
};

#endif