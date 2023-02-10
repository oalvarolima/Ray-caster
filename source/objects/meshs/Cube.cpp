#include <cmath>

#include "../../../headers/objects/meshs/Cube.hpp"

Cube::Cube(point3 a_center, float a_height, float a_width, color a_obj_color)
: Mesh(a_center, a_obj_color), height(a_height), width(a_width) {
    vec3 v1 = center - vec3(width/2.f, 0.f, -width/2.f);
    vec3 v2 = center - vec3(-width/2.f, 0.f, -width/2.f);
    vec3 v3 = center - vec3(-width/2.f, -height, -width/2.f);
    vec3 v4 = center - vec3(width/2.f, -height, -width/2.f);
    vec3 v5 = center - vec3(width/2.f, 0.f, - -width/2.f);
    vec3 v6 = center - vec3(-width/2.f, 0.f, - -width/2.f);
    vec3 v7 = center - vec3(-width/2.f, -height, - -width/2.f);
    vec3 v8 = center - vec3(width/2.f, -height, - -width/2.f);

    Mesh::add_face(new Face(v1, v3, v4, obj_color));
    Mesh::add_face(new Face(v1, v2, v3, obj_color));
    Mesh::add_face(new Face(v5, v1, v4, obj_color));
    Mesh::add_face(new Face(v5, v4, v8, obj_color));
    Mesh::add_face(new Face(v4, v3, v8, obj_color));
    Mesh::add_face(new Face(v8, v3, v7, obj_color));
    Mesh::add_face(new Face(v6, v2, v1, obj_color));
    Mesh::add_face(new Face(v6, v1, v5, obj_color));
    Mesh::add_face(new Face(v7, v6, v5, obj_color));
    Mesh::add_face(new Face(v7, v5, v8, obj_color));
    Mesh::add_face(new Face(v3, v2, v6, obj_color));
    Mesh::add_face(new Face(v3, v6, v7, obj_color));

    Mesh::set_cluster_radius(std::fmax(height, width)*fsqrt(10)/2.);
    Mesh::cluster->set_center(center + vec3(0.f, height/2.f, 0.f));
}