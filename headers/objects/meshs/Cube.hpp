#ifndef CUBE_HPP
#define CUBE_HPP

#include "Mesh.hpp"

class Cube : public Mesh
{
    private:
        float height, width;

    public:
        Cube(point3 center, float a_height, float a_width, color a_obj_color);
};

#endif