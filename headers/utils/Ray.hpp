#ifndef RAY_HPP
#define RAY_HPP

#include <iostream>
#include <vector>
#include <glm/glm.hpp>

using glm::vec3;
using point3 = vec3;
using color = vec3;

using std::sqrt;
using std::cout;
using std::endl;

#define EPS (0.001f)
#define infinity std::numeric_limits<float>::infinity()

inline float randomF0to1() { return rand()/(RAND_MAX + 1.0); }
inline float clamp(float x, float min, float max) {
    if( x > max )
        return max;
    if( x < min )
        return min;
    return x;
}

inline float deg(float angle) {
    return glm::radians(angle);
}

class Ray
{
public:
    Ray(point3 a_origin, vec3 a_direction);
    point3 at(float t) const;

public:
    point3 origin;
    vec3 direction;
};

#endif