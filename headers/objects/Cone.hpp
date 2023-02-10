#ifndef CONE_HPP
#define CONE_HPP

#include "Plan.hpp"

class Cone : public Object
{
public:
    Cone(point3 a_center, vec3 a_dr, float a_radius, float a_height, color a_obj_color);

    bool intersect(Ray ray, hit_record &hr);
    vec3 get_normal(point3 pi);

    void apply_matrix(const mat4 &m);

    void set_reflectivity(float a_reflectivity);
    void set_ka(vec3 a_ka);
    void set_ke(vec3 a_ke);
    void set_kd(vec3 a_kd);

private:
    vec3 dr;
    point3 top;
    float radius, height, cos_theta;
    Plan *bot_cover;

    bool get_closest_t(float x, const Ray &ray, hit_record &hr);
};

#endif