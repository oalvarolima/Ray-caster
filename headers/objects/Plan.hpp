#ifndef PLAN_HPP
#define PLAN_HPP

#include "Object.hpp"

class Plan : public Object
{
    const float HAS_NOT_RADIUS = -1.f;

    public:
    Plan(point3 a_center, vec3 a_normal, color a_obj_color);
    vec3 normal;

    void set_radius(float a_radius);
    void apply_matrix(const mat4 &m);
    bool intersect(Ray ray, hit_record &hr);
    vec3 get_normal(point3 pi);

private:
    float radius;
    bool is_in_plan_radius(point3 pi);
    bool has_radius() const;
};

#endif