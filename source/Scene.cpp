#include "../headers/Scene.hpp"

Scene::Scene(Camera a_cam, int a_img_height, int a_img_width, color a_bg_color, color a_ambient_intensity)
: cam(a_cam),
bg_color(a_bg_color),
ambient_intensity(a_ambient_intensity),
img_height(a_img_height),
img_width(a_img_width)
{
    color_buffer.resize(img_height*img_width*3);
    uint32_t cores_available = std::thread::hardware_concurrency();
    threads_num = threads_num > cores_available ? cores_available : threads_num;
    for( uint32_t i = 0; i < threads_num; i++ ) {
        canvas_indexes.emplace_back();
    }
    for( uint32_t i = 0; i < img_height*img_width; i += threads_num ) {
        for( int j = 0; j < threads_num; j++ ) {
            canvas_indexes[j].push_back(i + j);
        }
    }
}

void Scene::draw_scene() {
    std::for_each(std::execution::par, canvas_indexes.begin(), canvas_indexes.end(),
            [this](const vector<uint32_t>& viewport_indexes) {
            color pixel_color;
            for (uint32_t i: viewport_indexes) {
                pixel_color = viewport_color_at(i/img_height, i%img_width);
                uint32_t i_t_3 = i*3;
                color_buffer[i_t_3] = clamp(pixel_color.r, 0.f, 255.f)/255.f;
                color_buffer[++i_t_3] = clamp(pixel_color.g, 0.f, 255.f)/255.f;
                color_buffer[++i_t_3] = clamp(pixel_color.b, 0.f, 255.f)/255.f;
            }
        }
    );
}

color Scene::viewport_color_at(float h, float w) {
    float u, v;
    vec3 direction = cam.get_direction(h/( float )img_height, w/( float )img_width);
    color accumulated_color = ray_color(Ray({}, direction), max_recursion_depth);
    for( uint32_t s = 0; s < samples_per_pixel - 1; s++ ) {
        u = float(h + randomF0to1())/img_height;
        v = float(w + randomF0to1())/img_width;
        direction = cam.get_direction(u, v);
        accumulated_color += ray_color(Ray({}, direction), max_recursion_depth);
    }

    return accumulated_color/(float)samples_per_pixel;
}

color Scene::ray_color(Ray ray, uint32_t recursion_depth) {
    if( recursion_depth == 0 )
        return {};

    hit_record hr = get_closest_obj(ray);
    if( hr.t == infinity )
        return bg_color;

    color point_color = color_of_intersection_point(ray, hr);

    float color_attenuation;
    interaction_ray_object(ray, hr, color_attenuation, recursion_depth);

    return point_color*(1.f - color_attenuation) +
           ray_color(ray, recursion_depth)*color_attenuation;
}

hit_record Scene::get_closest_obj(const Ray &ray) {
    hit_record hr;
    uint32_t objs_num = objects.size();
    for( uint32_t i = 0; i < objs_num; i++ ) {
        objects[i]->intersect(ray, hr);
    }
    return hr;
}

color Scene::color_of_intersection_point(Ray intersection_ray, hit_record &hr) {
    vec3 total_intensity = compute_total_intensity(intersection_ray, hr);
    color point_color = hr.out_color*total_intensity;
    return point_color;
}

vec3 Scene::compute_total_intensity(Ray intersection_ray, hit_record &hr) {
    vec3 total_intensity = ambient_intensity;
    for( Light *l: lights ) {
        if( has_shadow_to(l, hr.pi) )
            continue;
        total_intensity += l->compute_intensity(intersection_ray, hr)*l->intensity;
    }

    return total_intensity;
}

bool Scene::has_shadow_to(Light *l, point3 p) {
    float distance_to_light = glm::distance(p, l->center);
    vec3 direction_to_light = glm::normalize(l->center - p);
    hit_record obj = get_closest_obj(Ray(p, direction_to_light));
    return obj.t < distance_to_light;
}

void Scene::interaction_ray_object(Ray &intersection_ray, hit_record &hr, float &color_attenuation, uint32_t &recursion_depth) {
    if( hr.reflectivity > 0.001f) {
        intersection_ray.origin = hr.pi;
        intersection_ray.direction = glm::reflect(intersection_ray.direction, hr.obj_normal);
        color_attenuation = hr.reflectivity;
        recursion_depth--;
    } else {
        color_attenuation = NO_ATTENUATION;
        recursion_depth = STOP_RECURSION;
    }
}

void Scene::world_to_cam(point3 eye, point3 at, point3 up) {
    mat4 world_to_cam_M = Matrix::world_to_cam(eye, at, up);

    for( Light *l: lights ) {
        l->apply_matrix(world_to_cam_M);
    }

    for( Object *o: objects ) {
        o->apply_matrix(world_to_cam_M);
    }
}

void Scene::set_image_quality(image_quality img_qlt) {
    if( img_qlt == LOW ) {
        set_low_quality();
    } else if( img_qlt == HIGH ) {
        set_high_quality();
    } else if( img_qlt == ULTRA ) {
        set_ultra_quality();
    }
}

void Scene::set_low_quality() {
    max_recursion_depth = 5;
    samples_per_pixel = 1;
}

void Scene::set_high_quality() {
    max_recursion_depth = 4;
    samples_per_pixel = 30;
}

void Scene::set_ultra_quality() {
    img_height = img_width = 600;
    max_recursion_depth = 10;
    samples_per_pixel = 50;
}

void Scene::set_max_recursion_depth(int mrd) { max_recursion_depth = mrd; }
void Scene::add_light(Light *light) { lights.push_back(light); }
void Scene::add_object(Object *object) { objects.push_back(object); }
