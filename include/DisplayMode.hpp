#pragma once

#include <list>
#include <ScreenComponent.hpp>

class DisplayMode {
    public:
        DisplayMode() {}
        virtual void positionComponents( SDL_Rect* clippingRectangle, std::list<ScreenComponent*> components ) = 0;
};

class Relative : public DisplayMode {
    public:
        Relative() : DisplayMode() {}
        virtual void positionComponents( SDL_Rect* clippingRectangle, std::list<ScreenComponent*> components );
};

class Anchor : public DisplayMode {
    public:
        Anchor() : DisplayMode() {}
        virtual void positionComponents( SDL_Rect* clippingRectangle, std::list<ScreenComponent*> components );
};

class Grid : public DisplayMode {
    public:
        Grid( int rows, int cols ) : DisplayMode() { _rows = rows; _cols = cols; }
        virtual void positionComponents( SDL_Rect* clippingRectangle, std::list<ScreenComponent*> components );

    private:
        int _rows;
        int _cols;
};