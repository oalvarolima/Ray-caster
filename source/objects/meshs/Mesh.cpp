#include "../../../headers/objects/meshs/Mesh.hpp"

Mesh::Mesh(point3 a_center, color a_obj_color)
: Object(a_center, a_obj_color) {}

bool Mesh::intersect(Ray ray, hit_record &hr) {
    hit_record temp;
    if( !cluster->intersect(ray, temp) )
        return false;

    uint32_t faces_num = faces.size();
    for( uint32_t i = 0; i < faces_num; i++ ) {
        faces[i]->intersect(ray, hr);
    }

    return true;
}

void Mesh::set_cluster_radius(float a_cluster_radius) {
    cluster = new Sphere(center, a_cluster_radius, {});
}

void Mesh::move_to_origin_apply_M_and_back(const mat4 &M) {
    point3 curr_center = center;
    point3 origin = {};
    translate_to(origin);
    apply_matrix(M);
    translate_to(curr_center);
}

void Mesh::translate_to(point3 p) {
    vec3 direction = p - center;
    apply_matrix(Matrix::translation(direction));
    cluster->set_center(center);
}

void Mesh::apply_matrix(const mat4 &m) {
    center = Matrix::mat4_t_point3(m, center);
    for(Face* f: faces) {
        f->apply_matrix(m);
    }
    cluster->apply_matrix(m);
}

void Mesh::rotate_x(float angle) {
    move_to_origin_apply_M_and_back(Matrix::rotation_x(deg(angle)));
}

void Mesh::rotate_y(float angle) {
    move_to_origin_apply_M_and_back(Matrix::rotation_y(deg(angle)));
}

void Mesh::rotate_z(float angle) {
    move_to_origin_apply_M_and_back(Matrix::rotation_z(deg(angle)));
}

void Mesh::scale(float x, float y, float z) {
    cluster->scale( max(x, max(y, z)) );
    move_to_origin_apply_M_and_back(Matrix::scaling(x, y, z));
}

void Mesh::shear_xy(float angle) {
    move_to_origin_apply_M_and_back(Matrix::shearing_xy(angle));
    cluster->scale(1 + angle/1.55);
    cluster->set_center(center);
}

void Mesh::shear_xz(float angle) {
    move_to_origin_apply_M_and_back(Matrix::shearing_xz(angle));
    cluster->scale(1 + angle/1.55);
    cluster->set_center(center);
}

void Mesh::shear_yx(float angle) {
    move_to_origin_apply_M_and_back(Matrix::shearing_yx(angle));
    cluster->scale(1 + angle/1.55);
    cluster->set_center(center);
}

void Mesh::shear_yz(float angle) {
    move_to_origin_apply_M_and_back(Matrix::shearing_yz(angle));
    cluster->scale(1 + angle/1.55);
    cluster->set_center(center);
}

void Mesh::shear_zx(float angle) {
    move_to_origin_apply_M_and_back(Matrix::shearing_zx(angle));
    cluster->scale(1 + angle/1.55);
    cluster->set_center(center);
}

void Mesh::shear_zy(float angle) {
    move_to_origin_apply_M_and_back(Matrix::shearing_zy(angle));
    cluster->scale(1 + angle/1.55);
    cluster->set_center(center);
}

void Mesh::reflect_xy() {
    move_to_origin_apply_M_and_back(Matrix::reflection_xy_matrix());
    cluster->set_center(center);
}

void Mesh::reflect_zy() {
    move_to_origin_apply_M_and_back(Matrix::reflection_zy_matrix());
    cluster->set_center(center);
}

void Mesh::reflect_zx() {
    move_to_origin_apply_M_and_back(Matrix::reflection_zx_matrix());
    cluster->set_center(center);
}

void Mesh::add_face(Face *a_face) {
    faces.push_back(a_face);
}

void Mesh::set_shininess(int a_shininess) {
    shininess = a_shininess;
    for (Face *f: faces) {
        f->set_shininess(a_shininess);
    }
}

void Mesh::set_reflectivity(float a_reflectivity) {
    Object::set_reflectivity(a_reflectivity);
    for (Face *f: faces) {
        f->set_reflectivity(a_reflectivity);
    }
}