#include "../../headers/objects/Cone.hpp"

Cone::Cone(point3 a_center, vec3 a_dr, float a_radius, float a_height, color a_obj_color)
: Object(a_center, a_obj_color),
  dr(glm::normalize(a_dr)),
  radius(a_radius),
  height(a_height),
  top(a_center + (dr*a_height)),
  cos_theta((a_height*a_height)/ ((a_height*a_height) + (a_radius*a_radius)))
{
    bot_cover = new Plan(a_center, -dr, a_obj_color);
    bot_cover->set_radius(a_radius);
}

bool Cone::intersect(Ray ray, hit_record &hr)
{
    vec3 v = top - ray.origin;
    float dot_raydir_dr = dot(ray.direction, dr);
    float dot_v_dr = dot(v, dr);

    float a = (dot_raydir_dr*dot_raydir_dr) - cos_theta;
    float b = (cos_theta*dot(v, ray.direction)) - (dot_v_dr*dot(ray.direction, dr));
    float c = (dot_v_dr*dot_v_dr) - (cos_theta*dot(v, v));
    float discriminant = (b*b) - (a*c);

    if( discriminant < 0 )
        return false;

    return get_closest_t((-b + sqrtf(discriminant))/a, ray, hr);
}

bool Cone::get_closest_t(float x, const Ray &ray, hit_record &hr) {
    point3 pi = ray.at(x);
    float length = dot(pi - center, dr);
    bool pi_is_in_the_cone = length > 0.f && length < height;
    if ( bot_cover->intersect(ray, hr) && !pi_is_in_the_cone)
        return true;

    if (x > hr.t || x < EPS || !pi_is_in_the_cone)
        return false;

    hr.set(x, pi, get_normal(pi), out_color, shininess, reflectivity, ka, kd, ke);
    return true;
}

inline vec3 Cone::get_normal(point3 pi)
{
    vec3 vpi  = top - pi;
    vec3 nBar = cross(vpi, dr);
    vec3 normal = cross(nBar, vpi);

    return glm::normalize(normal);
}

void Cone::set_ka(vec3 a_ka) {
    bot_cover->set_ka(a_ka);
    ka = a_ka;
    out_color = obj_color*a_ka;
}
void Cone::set_ke(vec3 a_ke) {
    ke = a_ke;
    bot_cover->set_ke(a_ke);
}

void Cone::set_kd(vec3 a_kd) {
    kd = a_kd;
    bot_cover->set_kd(a_kd);
}

void Cone::apply_matrix(const mat4 &m) {
  center = Matrix::mat4_t_point3(m, center);
  dr = Matrix::mat4_t_vec3(m, dr);
  top = Matrix::mat4_t_point3(m, top);
  bot_cover->apply_matrix(m);
}

void Cone::set_reflectivity(float a_reflectivity) {
    reflectivity = a_reflectivity;
    bot_cover->set_reflectivity(a_reflectivity);
}