#include "../headers/Camera.hpp"

Camera::Camera(float vp_height, float vp_width, float focal_lgth)
: viewport_height(vp_height),
  viewport_width(vp_width),
  focal_length(focal_lgth),
  half_vp_height(vp_height/2.f),
  half_vp_width(vp_width/2.f)
{}

vec3 Camera::get_direction(float h, float w) const {
    point3 p = point3(w*viewport_width - half_vp_width , half_vp_height - h*viewport_height, -focal_length); 
    vec3 r = p - point3(0, 0, 0);
    return glm::normalize(r);
}