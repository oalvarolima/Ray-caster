#ifndef PENTAGON_SPHERE_HPP
#define PENTAGON_SPHERE_HPP

#include "Mesh.hpp"

class Pentagon_sphere : public Mesh
{
public:
    Pentagon_sphere(point3 a_center, float a_size, color a_obj_color);
private:
    float size;
};

#endif