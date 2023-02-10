#include "../../headers/objects/Sphere.hpp"

Sphere::Sphere(point3 a_center, float a_radius, color a_obj_color)
: Object(a_center, a_obj_color), radius(a_radius) {}

bool Sphere::intersect(Ray ray, hit_record &hr) {
    vec3 w = ray.origin - center;
    float b = dot(w, ray.direction);
    float c = dot(w, w) - (radius*radius);

    float discriminant = (b*b) - c;
    if( discriminant < 0.f )
        return false;

    float sqrtd_disc = fsqrt(discriminant);
    float x = (-b - sqrtd_disc);
    if( x > EPS && x < hr.t ) {
        point3 pi = ray.at(x);
        hr.set(x, pi, get_normal(pi), out_color, shininess, reflectivity, ka, kd, ke);
        return true;
    }

    x = (-b + sqrtd_disc);
    if( x > EPS && x < hr.t ) {
        point3 pi = ray.at(x);
        hr.set(x, pi, get_normal(pi), out_color, shininess, reflectivity, ka, kd, ke);
        return true;
    }

    return false;
}

vec3 Sphere::get_normal(point3 pi) {
    return (pi - center)/radius;
}

void Sphere::scale(float scala) {
    radius *= scala;
}

void Sphere::set_center(point3 a_center) {
    center = a_center;
}

void Sphere::apply_matrix(const mat4 &m) {
    center = Matrix::mat4_t_point3(m, center);
}