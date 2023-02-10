#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Ray.hpp"

namespace Matrix {

using glm::mat4;

vec3 mat4_t_vec3(mat4 m, vec3 v);
vec3 mat4_t_point3(mat4 m, point3 v);

mat4 rotation_x(float angle);
mat4 rotation_y(float angle);
mat4 rotation_z(float angle);

mat4 translation(vec3 v);

mat4 scaling(float x, float y, float z);

mat4 shearing_xy(float angle);
mat4 shearing_xz(float angle);
mat4 shearing_yx(float angle);
mat4 shearing_yz(float angle);
mat4 shearing_zx(float angle);
mat4 shearing_zy(float angle);

mat4 reflection_xy_matrix();
mat4 reflection_zx_matrix();
mat4 reflection_zy_matrix();

mat4 world_to_cam(point3 eye, point3 at, point3 up);
}

#endif //MATRIX_HPP