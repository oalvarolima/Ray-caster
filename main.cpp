#include "headers/lights/Point_light.hpp"
#include "headers/objects/Cylinder.hpp"
#include "headers/objects/Cone.hpp"
#include "headers/objects/meshs/Cube.hpp"
#include "headers/objects/meshs/Pentagon_sphere.hpp"
#include "headers/Renderer.hpp"

int main(int argc, char **argv) {
    auto *point_light = new Point_light({-10, 20, 3}, {.7, .7, .7});

    color white = {255, 255, 255};

    auto *floor = new Plan({0, -16, 0}, {0, 1, 0}, white);
    floor->set_ka({.8, .8, .8});

    auto *right_wall = new Plan({-25, -15, 0}, {1, 0, 0}, white);
    right_wall->set_ka({0.686, 0.933, 0.933});

    auto *left_wall = new Plan({25, -15, 0}, {-1, 0, 0}, white);
    left_wall->set_ka({0.686, 0.933, 0.933});

    auto *back_wall = new Plan({-20, -15, -55}, {0, 0, 1}, white);
    back_wall->set_shininess(10);
    back_wall->set_ka({0.686, 0.933, 0.933});

    auto *front_wall = new Plan({0, -15, 20}, {0, 0, -1}, white);
    front_wall->set_shininess(10);
    front_wall->set_ka({0.686, 0.933, 0.933});

    auto *roof = new Plan({0, 21, 0}, {0, -1, 0}, white);
    roof->set_ka({0.933, 0.933, 0.933});

    auto *base = new Cylinder({0, -16, -27}, {0, 1, 0}, 15, 5, {255, 70, 70});
    base->set_reflectivity(.3);

    auto *cube = new Cube({8, -11, -28}, 25, 8, {185, 225, 0});
    cube->set_shininess(50);
    cube->set_reflectivity(.4);
    cube->rotate_y(45);

    auto *cylinder = new Cylinder({-8, -11, -28}, {0, 1, 0}, 4, 25, {0, 220, 150});
    cylinder->set_reflectivity(.2);

    auto *cone = new Cone({0, -11, -20}, {0, 1, 0}, 2, 10, {147, 112, 219});
    cone->set_reflectivity(.2);

    auto *p_sphere = new Pentagon_sphere({0, 18, -23}, 1.5, {30, 120, 30});
    p_sphere->rotate_y(60);
    p_sphere->set_shininess(5);
    p_sphere->set_reflectivity(.3);

    auto *sphere = new Sphere({-8, -9, -18}, 2, {120, 30, 120});
    sphere->set_reflectivity(.4);
    sphere->set_shininess(100);

    Camera cam(6.f, 6.f, 3.f);
    color background_color = {100.f, 100.f, 100.f};
    vec3 ambient_intensity = {.3f, .3f, .3f};
    Scene scene(cam, 400, 400, background_color, ambient_intensity);
    scene.set_image_quality(LOW);

    scene.add_light(point_light);

    scene.add_object(cone);
    scene.add_object(floor);
    scene.add_object(front_wall);
    scene.add_object(back_wall);
    scene.add_object(right_wall);
    scene.add_object(left_wall);
    scene.add_object(roof);
    scene.add_object(cube);
    scene.add_object(base);
    scene.add_object(cylinder);
    scene.add_object(p_sphere);
    scene.add_object(sphere);

    Renderer renderer(scene);
    renderer.render();

    return EXIT_SUCCESS;
}
