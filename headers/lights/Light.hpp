#ifndef LIGHT_H
#define LIGHT_H

#include "../objects/Object.hpp"

class Light
{
    public:
    Light(vec3 a_center, vec3 a_intensity);

    vec3 intensity;
    vec3 center;

    virtual vec3 compute_intensity(Ray ray, const hit_record &hr) = 0;

    virtual float distance_from(point3 p) = 0;
    virtual vec3 direction_coming_from(point3 p) = 0;

    virtual void apply_matrix(const mat4 &m) = 0;
};

#endif