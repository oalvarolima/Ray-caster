#include "../../../headers/objects/meshs/Face.hpp"

Face::Face(point3 a_p1, point3 a_p2, point3 a_p3, color a_obj_color)
: Object(a_p1, a_obj_color),
  p1(a_p1), p2(a_p2), p3(a_p3), r1(a_p2 - a_p1), r2(a_p3 - a_p1)
{
    vec3 cross_r1_r2 = cross(r1, r2);
    normal = glm::normalize(cross_r1_r2);
    face_plan = new Plan(center, normal, a_obj_color);
    dot_cross_r1_r2__normal = dot(cross_r1_r2, normal);
}

bool Face::intersect(Ray ray, hit_record &hr) {
    if( dot(ray.direction, normal) > 0.f )
        return false;

    hit_record temp;
    face_plan->intersect(ray, temp);
    if( temp.t > hr.t )
        return false;

    point3 sub_p1_pi = p1 - temp.pi;
    float c1 = dot(cross(p3 - temp.pi, sub_p1_pi), normal)/dot_cross_r1_r2__normal;
    if( c1 < 0.f )
        return false;
    float c2 = dot(cross(sub_p1_pi, p2 - temp.pi), normal)/dot_cross_r1_r2__normal;
    if( c2 < 0.f )
        return false;
    float c3 = 1.0f - c1 - c2;
    if( c3 < 0.f )
        return false;

    hr.set(temp.t, temp.pi, normal, out_color, shininess, reflectivity, ka, kd, ke);
    return true;
}

vec3 Face::get_normal(point3 pi) {
    return normal;
}

void Face::apply_matrix(const mat4 &m) {
    p1 = Matrix::mat4_t_point3(m, p1);
    p2 = Matrix::mat4_t_point3(m, p2);
    p3 = Matrix::mat4_t_point3(m, p3);
    center = p1;

    r1 = p2 - p1;
    r2 = p3 - p1;

    vec3 cross_r1_r2 = cross(r1, r2);
    normal = glm::normalize(cross_r1_r2);
    dot_cross_r1_r2__normal = dot(cross_r1_r2, normal);
    face_plan->normal = normal;
    face_plan->set_center(center);
}