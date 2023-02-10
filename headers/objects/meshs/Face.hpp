#ifndef FACE_HPP
#define FACE_HPP

#include "../Plan.hpp"

class Face: public Object {
public:
    Face(point3 a_p1, point3 a_p2, point3 a_p3, color a_obj_color);

    point3 p1, p2, p3;
    vec3 normal;
    void apply_matrix(const mat4 &m);

    inline vec3 get_normal(point3 pi);
    bool intersect(Ray ray, hit_record &hr);

private:
    vec3 r1, r2;
    float dot_cross_r1_r2__normal;
    Plan *face_plan;

};

#endif