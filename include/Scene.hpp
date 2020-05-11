#pragma once

#include <Panel.hpp>

class Scene {
    public:
        Scene() {}

        virtual bool build( Panel* p, SDL_Renderer* r ) = 0;
        virtual bool loop() = 0;
        virtual Scene* getNextScene() { return NULL; }
    protected:
        Panel* _windowPanel;
};