#pragma once

#include <SDL.h>
#include <string>

class Engine {
    public:
        Engine();

        SDL_Window* createWindow(const int width, const int height, std::string name = "WINDOW NAME");
        SDL_Surface* createSurface(SDL_Window* window);
        SDL_Surface* createImageSurface(SDL_Surface* surface, std::string path);
        SDL_Renderer* createRenderer(SDL_Window* window);

        void freeSurface(SDL_Surface* surface);
        void destroyWindow(SDL_Window* window);
        void destroyRenderer(SDL_Renderer* renderer);
        void close();
    private:
        
};