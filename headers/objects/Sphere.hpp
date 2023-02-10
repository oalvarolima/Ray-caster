#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Object.hpp"

class Sphere: public Object {
public:
    Sphere(point3 a_center, float a_radius, color a_obj_color);

    void scale(float scala);
    void set_center(point3 a_center);
    void apply_matrix(const mat4 &m);

    bool intersect(Ray ray, hit_record &hr);
    vec3 get_normal(point3 pi);

private:
    float radius;
};

#endif
