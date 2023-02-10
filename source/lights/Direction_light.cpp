#include "../../headers/lights/Direction_light.hpp"

Direction_light::Direction_light(vec3 a_dr, vec3 a_intensity): Light(vec3(), a_intensity), dr(glm::normalize(a_dr)) {}

vec3 Direction_light::compute_intensity(Ray ray, const hit_record &hr) {
    vec3 l = -dr;
    float diffuse = dot(l, hr.obj_normal);
    if (diffuse < 0)
        return {};
    vec3 rl = (hr.obj_normal*(2*diffuse)) - l;
    float specular = dot(rl, -ray.direction);
    specular = hr.shininess ? powf(specular, hr.shininess) : 0;

    return (hr.ke*vec3(specular, specular, specular)) +
           hr.kd*vec3(diffuse, diffuse, diffuse);
}

float Direction_light::distance_from(point3 p) { return infinity; }
vec3 Direction_light::direction_coming_from(point3 p) { return -dr; }

void Direction_light::apply_matrix(const mat4 &m) {
    dr = Matrix::mat4_t_vec3(m, dr);
}