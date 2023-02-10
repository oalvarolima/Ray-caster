#include "../../headers/utils/Matrix.hpp"

vec3 Matrix::mat4_t_vec3(mat4 m, vec3 v) {
    return {m*glm::vec4(v, 0.f)};
}

vec3 Matrix::mat4_t_point3(mat4 m, point3 v) {
    return {m*glm::vec4(v, 1.f)};
}

Matrix::mat4 Matrix::rotation_x(float angle) {
    return { 1.f, .0f, .0f, .0f,
             0.f, cosf(angle), sinf(angle), 0.f,
             0.f, -sinf(angle), cosf(angle), 0.f,
             0.f, 0.f, 0.f, 0.f};
}

Matrix::mat4 Matrix::rotation_y(float angle) {
    return {cosf(angle), 0.f, -sinf(angle), 0.f,
            0.f, 1.f, 0.f, 0.f,
            sinf(angle), 0.f, cosf(angle), 0.f,
            0.f, 0.f, 0.f, 1.f
    };
}

Matrix::mat4 Matrix::rotation_z(float angle) {
    return  {cosf(angle), sinf(angle), 0.f, 0.f,
            -sinf(angle), cosf(angle), 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f,  0.f, 0.f, 1.f
    };
}

Matrix::mat4 Matrix::translation(vec3 v) {
    return {1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            v.x, v.y, v.z, 1.f
    };
}

Matrix::mat4 Matrix::scaling(float x, float y, float z) {
    return {x, 0.f, 0.f, 0.f,
            0.f, y, 0.f, 0.f,
            0.f, 0.f, z, 0.f,
            0.f, 0.f, 0.f, 1.f
    };
}

Matrix::mat4 Matrix::shearing_xy(float angle) {
    return {1.f, 0.f, 0.f, 0.f,
            tanf(angle), 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
    };
}

Matrix::mat4 Matrix::shearing_xz(float angle) {
    return {1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            tanf(angle), 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
    };
}

Matrix::mat4 Matrix::shearing_yx(float angle) {
    return {1.f, tanf(angle), 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
    };
}

Matrix::mat4 Matrix::shearing_yz(float angle) {
    return {1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, tanf(angle), 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
    };
}

Matrix::mat4 Matrix::shearing_zx(float angle) {
    return {1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            tanf(angle), 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
    };
}

Matrix::mat4 Matrix::shearing_zy(float angle) {
    return {1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, tanf(angle), 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
    };
}

Matrix::mat4 Matrix::reflection_xy_matrix() {
    return {1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, -1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
    };
}

Matrix::mat4 Matrix::reflection_zx_matrix() {
    return {1.f, 0.f, 0.f, 0.f,
            0.f, -1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
    };
}

Matrix::mat4 Matrix::reflection_zy_matrix() {
    return{-1.f, 0.f, 0.f, 0.f,
            0.f, 1.f, 0.f, 0.f,
            0.f, 0.f, 1.f, 0.f,
            0.f, 0.f, 0.f, 1.f
    };
}

Matrix::mat4 Matrix::world_to_cam(point3 eye, point3 at, point3 up) {
    vec3 kc = glm::normalize(eye - at);
    vec3 ic = glm::normalize(cross(up - eye, kc));
    vec3 jc = cross(kc, ic);

    return { ic.x, jc.x, kc.x, 0.f,
             ic.y, jc.y, kc.y, 0.f,
             ic.z, jc.z, kc.z, 0.f,
             -dot(ic, eye), -dot(jc, eye), -dot(kc, eye), 1.f
    };
}