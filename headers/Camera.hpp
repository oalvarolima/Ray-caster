#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "utils/Ray.hpp"

class Camera {
private:
    float focal_length;
    float viewport_width, viewport_height;
    float half_vp_height, half_vp_width;

public:
    Camera(float vp_height, float vp_width, float focal_length);

    vec3 get_direction(float w, float h) const;
};

#endif