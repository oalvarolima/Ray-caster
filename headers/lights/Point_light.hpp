#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "Light.hpp"

class Point_light : public Light
{
    public:
    Point_light(vec3 center, vec3 intensity);

    vec3 compute_intensity(Ray ray, const hit_record &hr);

    float distance_from(point3 p);
    vec3 direction_coming_from(point3 p);

    void apply_matrix(const mat4 &m);
};

#endif