#include "../../headers/objects/Cylinder.hpp"

Cylinder::Cylinder(point3 a_center, vec3 a_dr, float a_radius, float a_height, color a_obj_clr)
: Object(a_center, a_obj_clr), dr(glm::normalize(a_dr)), radius(a_radius), height(a_height) {
    set_aux_matrix();
    top_cover = new Plan(a_center + (dr*a_height), dr, a_obj_clr);
    top_cover->set_radius(a_radius);
    bot_cover = new Plan(a_center, -dr, a_obj_clr);
    bot_cover->set_radius(a_radius);
}

void Cylinder::set_aux_matrix() {
    float neg__x_t_y = -dr.y*dr.x;
    float neg__z_t_x = -dr.z*dr.x;
    float neg__z_t_y = -dr.z*dr.y;

    aux_matrix = {-(dr.x*dr.x - 1), neg__x_t_y, neg__z_t_x,
                  neg__x_t_y, -(dr.y*dr.y - 1), neg__z_t_y,
                  neg__z_t_x, neg__z_t_y, -(dr.z*dr.z - 1)};
}

bool Cylinder::intersect(Ray ray, hit_record &hr) {
    vec3 w = ray.origin - center;
    vec3 aux_t_raydir = aux_matrix*ray.direction;
    vec3 aux_t_rayir = aux_matrix*w;

    float a = dot(aux_t_raydir, ray.direction);
    float b = dot(ray.direction, aux_t_rayir);
    float c = dot(aux_t_rayir, w) - (radius*radius);
    float discriminant = (b*b) - (a*c);
    if( discriminant < 0 )
        return false;

    return get_closest_t( (-b - sqrtf(discriminant))/a, ray, hr);
}

bool Cylinder::get_closest_t(float x, const Ray &ray, hit_record &hr) {
    point3 pi = ray.at(x);
    float length = dot(pi - center, dr);
    bool pi_is_in_the_cylinder = length > 0.f && length < height;
    if( (top_cover->intersect(ray, hr) || bot_cover->intersect(ray, hr)) && !pi_is_in_the_cylinder ) {
        return true;
    }

    if( x > hr.t || x < EPS || !pi_is_in_the_cylinder )
        return false;

    hr.set(x, pi, get_normal(pi), out_color, shininess, reflectivity, ka, kd, ke);
    return true;
}

vec3 Cylinder::get_normal(point3 pi) {
    vec3 w = pi - center;
    return glm::normalize(w*aux_matrix);
}

void Cylinder::apply_matrix(const mat4 &m) {
    center = Matrix::mat4_t_point3(m, center);
    dr = Matrix::mat4_t_vec3(m, dr);
    set_aux_matrix();
    top_cover->apply_matrix(m);
    bot_cover->apply_matrix(m);
}

void Cylinder::set_reflectivity(float a_reflectivity) {
    reflectivity = a_reflectivity;
    bot_cover->set_reflectivity(a_reflectivity);
    top_cover->set_reflectivity(a_reflectivity);
}

void Cylinder::set_ka(vec3 a_ka) {
    bot_cover->set_ka(a_ka);
    top_cover->set_ka(a_ka);
    ka = a_ka;
    out_color = obj_color*a_ka;
}

void Cylinder::set_ke(vec3 a_ke) {
    ke = a_ke;
    bot_cover->set_ke(a_ke);
    top_cover->set_ke(a_ke);
}

void Cylinder::set_kd(vec3 a_kd) {
    kd = a_kd;
    bot_cover->set_kd(a_kd);
    top_cover->set_kd(a_kd);
}