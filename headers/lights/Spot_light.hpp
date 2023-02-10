#ifndef SPOT_LIGHT_HPP
#define SPOT_LIGHT_HPP

#include "Light.hpp"

class Spot_light: public Light {
public:
    Spot_light(point3 a_center, vec3 a_direction, float a_opening, color a_intensity);

    vec3 compute_intensity(Ray ray, const hit_record &hr);

    float distance_from(point3 p);
    vec3 direction_coming_from(point3 p);

    void apply_matrix(const mat4 &m);

private:
    vec3 direction;
    float opening;
    bool is_in_the_spot(vec3 direc_to_light_from_pi);
};

#endif