#pragma once

#include <SDL.h>
#include <Vector.hpp>

class MouseListener {
    public:
        MouseListener() {}

        virtual void onMouseDown( Vector2D<int> mousePosition ) {}
        virtual void onMouseUp( Vector2D<int> mousePosition ) {}
        virtual void onMouseMove( Vector2D<int> mousePosition ) {}
};

class KeyListener {
    public:
        KeyListener() {}

        virtual void onKeyDown( SDL_Keycode key ) {}
        virtual void onKeyUp( SDL_Keycode key ) {}
};

class ActionListener {
    public:
        ActionListener() {}

        virtual void onAction() {}
};