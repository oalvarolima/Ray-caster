#ifndef CYLINDER_HPP
#define CYLINDER_HPP

#include "Plan.hpp"

class Cylinder: public Object {
public:
    Cylinder(point3 a_center, vec3 a_dr, float a_radius, float a_height, color a_obj_clr);

    bool intersect(Ray r, hit_record &hr);
    vec3 get_normal(point3 pi);

    void apply_matrix(const mat4 &m);

    void set_reflectivity(float a_reflectivity);
    void set_ka(vec3 a_ka);
    void set_ke(vec3 a_ke);
    void set_kd(vec3 a_kd);

private:
    vec3 dr;
    float radius, height;
    Plan *top_cover, *bot_cover;

    glm::mat3 aux_matrix;

private:
    bool get_closest_t(float x, const Ray &ray, hit_record &hr);
    void set_aux_matrix();
};


#endif
