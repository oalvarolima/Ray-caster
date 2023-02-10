#include "../../headers/lights/Spot_light.hpp"

Spot_light::Spot_light(point3 a_center, vec3 a_direction, float a_opening, color a_intensity)
: Light(a_center, a_intensity), direction(a_direction), opening(a_opening) {}

vec3 Spot_light::compute_intensity(Ray ray, const hit_record &hr) {
    vec3 l = glm::normalize(center - hr.pi);
    if( !is_in_the_spot(l) )
        return {};

    float diffuse = dot(l, hr.obj_normal);
    if (diffuse < 0 )
        return {};
    vec3 r = (hr.obj_normal*(2*diffuse)) - l;

    float specular = dot(r, -ray.direction);
    specular = hr.shininess && specular > 0 ? powf(specular, hr.shininess) : 0;

    return (hr.ke*vec3(specular, specular, specular)) +
           hr.kd*vec3(diffuse, diffuse, diffuse);
}

bool Spot_light::is_in_the_spot(vec3 direc_to_light_from_pi) {
    float pi_opening = dot(direc_to_light_from_pi, -direction);
    return pi_opening < cosf(opening);
}

float Spot_light::distance_from(point3 p) { return glm::length(center - p); }
vec3 Spot_light::direction_coming_from(point3 p) { return glm::normalize(center - p); }

void Spot_light::apply_matrix(const mat4 &m) {
    center = Matrix::mat4_t_point3(m, center);
    direction = Matrix::mat4_t_vec3(m, direction);
}