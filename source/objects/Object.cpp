#include "../../headers/objects/Object.hpp"

Object::Object() {}
Object::Object(vec3 a_center, color a_obj_color)
: center(a_center), obj_color(a_obj_color), ka(vec3(1.f, 1.f, 1.f)), kd(vec3(1.f, 1.f, 1.f)), ke(vec3(1.f, 1.f, 1.f)), shininess(-1), out_color(a_obj_color)
{}

void Object::set_color(color a_obj_color) {
    obj_color = a_obj_color;
    out_color = obj_color*ka;
}

void Object::set_center(point3 a_center) { center = a_center; }
void Object::set_ka(vec3 a_ka) {
    ka = a_ka;
    out_color = obj_color*a_ka;
}
void Object::set_kd(vec3 a_kd) { kd = a_kd; }
void Object::set_ke(vec3 a_ke) { ke = a_ke; }
void Object::set_shininess(int a_shininess) { shininess = a_shininess; }
void Object::set_reflectivity(float a_reflectivity) {
    reflectivity = a_reflectivity > 1.f ? 1.f : a_reflectivity;
}