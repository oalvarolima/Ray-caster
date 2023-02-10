#include "../../headers/lights/Point_light.hpp"

Point_light::Point_light(vec3 center, vec3 intensity): Light(center, intensity) {}

vec3 Point_light::compute_intensity(Ray ray, const hit_record &hr) {
    vec3 lightDir = glm::normalize(center - hr.pi);
    float diffuse = dot(lightDir, hr.obj_normal);
    if( diffuse < 0 )
        return  {};
    vec3 rl = (hr.obj_normal*(2*diffuse)) - lightDir;
    float specular = dot(rl, -ray.direction);
    specular = hr.shininess && specular > 0 ? powf(specular, hr.shininess) : 0;

    return hr.ke*vec3(specular, specular, specular) +
           hr.kd*vec3(diffuse, diffuse, diffuse);
}

float Point_light::distance_from(point3 p) { return glm::distance(center, p); }
vec3 Point_light::direction_coming_from(point3 p) { return glm::normalize(center - p); }

void Point_light::apply_matrix(const mat4 &m) {
    center = Matrix::mat4_t_point3(m, center);
}