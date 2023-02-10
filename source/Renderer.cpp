#include <SDL2/SDL_events.h>
#include "../headers/Renderer.hpp"

#define SHOW_RENDERING_SPEED 0

Renderer::Renderer(Scene &a_scene)
: scene(a_scene), sdl_engine("Raycaster", a_scene.img_width, a_scene.img_height, a_scene.img_width, a_scene.img_height) {}

void Renderer::render() {
    SDL_Event e;
    bool rendering = true;
    while( rendering ) {

#if SHOW_RENDERING_SPEED
        auto begin = std::chrono::high_resolution_clock::now();
#endif

        scene.draw_scene();
        sdl_engine.atualizarCanvas(&scene.color_buffer[0]);
        sdl_engine.atualizarJanela();

        while( SDL_PollEvent(&e) ) {
            switch( e.type ) {
                case SDL_QUIT:
                    rendering = false;
                    break;
                case SDL_KEYDOWN:
                    handle_key_event(e);
                    break;
            }
        }

#if SHOW_RENDERING_SPEED
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        cout << elapsed.count() << " ms\n";
#endif

    }
}

void Renderer::handle_key_event(SDL_Event &event) {
    if( is_move_front(event) )
        scene.world_to_cam({0, 0, -1}, {0, 0, -2}, {0, 1, -2});
    else if( is_move_back(event) )
        scene.world_to_cam({0, 0, 1}, {0, 0, 0}, {0, 1, 0});
    else if( is_move_right(event) )
        scene.world_to_cam({1, 0, 0}, {1, 0, -1}, {1, 1, -1});
    else if( is_move_left(event) )
        scene.world_to_cam({-1, 0, 0}, {-1, 0, -1}, {-1, 1, -1});


    else if( is_look_up(event) )
    {
        new_dir = Matrix::mat4_t_vec3(Matrix::rotation_x(deg(15.f)), {0, 0, -1});
        scene.world_to_cam({}, new_dir, new_dir + vec3(0, 1, 0));
    }
    else if( is_look_down(event) )
    {
        new_dir = Matrix::mat4_t_vec3(Matrix::rotation_x(deg(-15.f)), {0, 0, -1});
        scene.world_to_cam({}, new_dir, new_dir + vec3(0, 1, 0));
    }
    else if( is_look_right(event) )
    {
        new_dir = Matrix::mat4_t_vec3(Matrix::rotation_y(deg(-15.f)), {0, 0, -1});
        scene.world_to_cam({}, new_dir, new_dir + vec3(0, 1, 0));
    }
    else if( is_look_left(event) )
    {
        new_dir = Matrix::mat4_t_vec3(Matrix::rotation_y(deg(15.f)), {0, 0, -1});
        scene.world_to_cam({}, new_dir, new_dir + vec3(0, 1, 0));
    }


    else if( is_turn_on_anti_aliasing(event) )
        scene.set_image_quality(HIGH);
    else if( is_turn_OFF_anti_aliasing(event) )
        scene.set_image_quality(LOW);
}

bool Renderer::is_move_front(SDL_Event &event) {
    return event.key.keysym.sym == SDLK_w;
}

bool Renderer::is_move_back(SDL_Event &event) {
    return event.key.keysym.sym == SDLK_s;
}

bool Renderer::is_move_right(SDL_Event &event) {
    return event.key.keysym.sym == SDLK_d;
}

bool Renderer::is_move_left(SDL_Event &event) {
    return event.key.keysym.sym == SDLK_a;
}



bool Renderer::is_look_up(SDL_Event &event) {
    return event.key.keysym.sym == SDLK_UP;
}

bool Renderer::is_look_down(SDL_Event &event) {
    return event.key.keysym.sym == SDLK_DOWN;
}

bool Renderer::is_look_right(SDL_Event &event) {
    return event.key.keysym.sym == SDLK_RIGHT;
}

bool Renderer::is_look_left(SDL_Event &event) {
    return event.key.keysym.sym == SDLK_LEFT;
}



bool Renderer::is_turn_on_anti_aliasing(SDL_Event &event) {
    return event.key.keysym.sym == SDLK_h;
}

bool Renderer::is_turn_OFF_anti_aliasing(SDL_Event &event) {
    return event.key.keysym.sym == SDLK_l;
}