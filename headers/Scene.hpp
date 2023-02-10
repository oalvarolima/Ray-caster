#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <algorithm>
#include <execution>

#include "lights/Light.hpp"
#include "objects/Object.hpp"
#include "Camera.hpp"

using std::vector;

enum image_quality{LOW, HIGH, ULTRA};

class Scene
{
    const float NO_ATTENUATION = 0.f;
    const uint32_t STOP_RECURSION = 0;

public:
    Scene(Camera a_cam, int a_img_height, int a_img_width, color a_bg_color, color a_ambient_intensity);
    Scene() : cam(Camera(0, 0, 0)) , img_height(0), img_width(0), bg_color({}), ambient_intensity({}){};

    void world_to_cam(point3 eye, point3 at, point3 up);
    void add_object(Object *object);
    void add_light(Light *light);
    void set_max_recursion_depth(int mrd);
    void set_image_quality(image_quality img_qlt);

    vector<vector<uint32_t>> canvas_indexes;

    void draw_scene();
    vector<float> color_buffer;
    uint32_t img_height, img_width;

private:
    vector<Object*> objects;
    vector<Light*> lights;
    color ambient_intensity, bg_color;
    Camera cam;
    uint32_t max_recursion_depth = 4;
    uint32_t samples_per_pixel = 20;
    uint32_t threads_num = 4;

private:
    color viewport_color_at(float h, float w);
    hit_record get_closest_obj(const Ray &ray);
    color ray_color(Ray ray, uint32_t recursion_depth);
    color color_of_intersection_point(Ray intersection_ray, hit_record &hr);
    bool has_shadow_to(Light *l, point3 p);
    void interaction_ray_object(Ray &intersection_ray, hit_record &hr, float &color_attenuation, uint32_t &recursion_depth);
    vec3 compute_total_intensity(Ray intersection_ray, hit_record &hr);
    void set_low_quality();
    void set_high_quality();
    void set_ultra_quality();
};

#endif