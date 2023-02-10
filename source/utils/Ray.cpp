#include "../../headers/utils/Ray.hpp"

Ray::Ray(point3 a_origin, vec3 a_direction) : origin(a_origin), direction(a_direction) {}

point3 Ray::at(float t) const {return origin + (direction*t);}