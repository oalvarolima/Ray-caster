#include "../../headers/objects/Plan.hpp"

Plan::Plan(point3 a_center, vec3 a_normal, color a_obj_color)
: Object(a_center, a_obj_color), normal(glm::normalize(a_normal)), radius(HAS_NOT_RADIUS) {}

bool Plan::intersect(Ray ray, hit_record &hr) {
    vec3 w = ray.origin - center;
    float ti = -dot(w, normal)/dot(ray.direction, normal);
    if( ti < EPS )
        return false;

    if( has_radius() ) {
        point3 pi = ray.at(ti);
        if (ti > hr.t_closest || !is_in_plan_radius(pi))
            return false;

        hr.set(ti, pi, normal, out_color, shininess, reflectivity, ka, kd, ke);
        return true;
    }

    if (ti < hr.t_closest) {
        point3 pi = ray.at(ti);
        hr.set(ti, pi, normal, out_color, shininess, reflectivity, ka, kd, ke);
        return true;
    }

    return false;
}

bool Plan::has_radius() const {
    return radius > 0.f;
}

bool Plan::is_in_plan_radius(point3 pi) {
    return glm::length(pi - center) < radius;
}

vec3 Plan::get_normal(point3 pi) { return normal; }

void Plan::set_radius(float a_radius) {
    radius = a_radius;
}

void Plan::apply_matrix(const mat4 &m) {
    center = Matrix::mat4_t_point3(m, center);
    normal = Matrix::mat4_t_vec3(m, normal);
}