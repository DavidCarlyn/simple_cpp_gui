#pragma once

#include <ScreenComponent.hpp>
#include <Listeners.hpp>
#include <DisplayMode.hpp>
#include <list>

class Panel : public ScreenComponent, public MouseListener, public KeyListener {
    public:
        Panel();
        ~Panel();

        Panel( Vector2D<int> size, Vector2D<int> position = Vector2D<int>( 0, 0 ), DisplayMode* displayMode = new Relative() );
        Panel( Vector2D<float> size, Vector2D<float> position = Vector2D<float>( 0.0f, 0.0f ), DisplayMode* displayMode = new Relative() );
        Panel( Vector2D<int> size, Vector2D<float> position, DisplayMode* displayMode = new Relative() );
        Panel( Vector2D<float> size, Vector2D<int> position, DisplayMode* displayMode = new Relative() );

        void setDisplayMode( DisplayMode* mode ) { delete _displayMode; _displayMode = mode; }
        void setBackgroundColor( SDL_Color color ) { _backgroundColor = color; }
        void clearComponents() { _components.clear(); }
        void clearMouseListeners() { _mouseListeners.clear(); }
        void clearKeyListeners() { _keyListeners.clear(); }
        void clearAll() { clearComponents(); clearKeyListeners(); clearMouseListeners(); }

        virtual void addComponent( ScreenComponent* component );
        virtual void addMouseListener( MouseListener* listener ) { _mouseListeners.push_back( listener ); }
        virtual void addKeyListener( KeyListener* listener ) { _keyListeners.push_back( listener ); }
        virtual void render( SDL_Renderer* renderer, SDL_Rect* clip = NULL, const double angle = 0 ) override;

        virtual void onMouseDown( Vector2D<int> mousePosition ) override;
        virtual void onMouseUp( Vector2D<int> mousePosition ) override;
        virtual void onMouseMove( Vector2D<int> mousePosition ) override;
        virtual void onKeyDown( SDL_Keycode key ) override;
        virtual void onKeyUp( SDL_Keycode key ) override;

    protected:
        std::list<ScreenComponent*> _components;
        SDL_Color _backgroundColor;
        DisplayMode* _displayMode;

        std::list<MouseListener*> _mouseListeners;
        std::list<KeyListener*> _keyListeners;
};