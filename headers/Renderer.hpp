#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Scene.hpp"
#include "SDLEngine.h"

class Renderer {
public:
    Renderer(Scene &a_scene);
    void render();

private:
    SDLEngine sdl_engine;
    Scene scene;
    vec3 new_dir;

    void handle_key_event(SDL_Event &event);

    bool is_move_front(SDL_Event &event);
    bool is_move_back(SDL_Event &event);
    bool is_move_left(SDL_Event &event);
    bool is_move_right(SDL_Event &event);

    bool is_look_left(SDL_Event &event);
    bool is_look_right(SDL_Event &event);
    bool is_look_up(SDL_Event &event);
    bool is_look_down(SDL_Event &event);

    bool is_turn_on_anti_aliasing(SDL_Event &event);
    bool is_turn_OFF_anti_aliasing(SDL_Event &event);
};


#endif //RENDERER_HPP