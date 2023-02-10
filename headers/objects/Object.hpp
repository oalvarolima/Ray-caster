#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "../utils/Matrix.hpp"

using Matrix::mat4;

struct hit_record {
    float t;
    point3 pi;
    vec3 obj_normal;
    color out_color;
    uint32_t shininess;
    float reflectivity;
    vec3 ka, kd, ke;

    hit_record() : t(infinity) {}

    void set(float a_t, point3 a_pi, vec3 a_obj_normal, color a_out_color, uint32_t a_shininess, float a_reflectivity, vec3 a_ka, vec3 a_kd, vec3 a_ke) {
        t = a_t;
        pi = a_pi;
        obj_normal = a_obj_normal;
        out_color = a_out_color;
        shininess = a_shininess;
        reflectivity = a_reflectivity;
        ka = a_ka;
        kd = a_kd;
        ke = a_ke;
    }
};

class Object {
public:
    Object();
    Object(vec3 a_center, color a_obj_color);
    virtual void apply_matrix(const mat4 &m) = 0;

    virtual bool intersect(Ray ray, hit_record &hr) = 0;

    virtual vec3 get_normal(point3 pi) = 0;
    void set_color(color a_obj_color);

    void set_center(point3 a_center);
    void set_ka(vec3 a_ka);
    void set_kd(vec3 a_kd);
    void set_ke(vec3 a_ke);
    void set_shininess(int a_shininess);
    void set_reflectivity(float a_reflectivity);

public:
    color out_color;

    vec3 ka, ke, kd;
    uint32_t shininess = 0;
    float reflectivity = -1;

protected:
    vec3 center;
    color obj_color;
};

#endif