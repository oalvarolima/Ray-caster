#ifndef DIRECTION_LIGHT_HPP
#define DIRECTION_LIGHT_HPP

#include "Light.hpp"

class Direction_light: public Light {
public:
    Direction_light(vec3 a_dr, vec3 a_intensity);

    vec3 compute_intensity(Ray ray, const hit_record &hr);

    float distance_from(point3 p);
    vec3 direction_coming_from(point3 p);

    void apply_matrix(const mat4 &m);

private:
    vec3 dr;
};


#endif