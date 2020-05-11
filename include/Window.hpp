#pragma once

#include <Scene.hpp>
#include <Listeners.hpp>
#include <string>

class Window {
    public:
        Window();
        Window( std::string name );
        Window( Vector2D<int> size );
        Window( std::string name, Vector2D<int> size );
        ~Window();

        Panel* getPanel() { return _windowPanel; }
        SDL_Renderer* getRenderer() { return _renderer; }

        void addMouseListener( MouseListener* listener ) { _mouseListeners.push_back( listener ); }
        void addKeyListener( KeyListener* listener ) { _keyListeners.push_back( listener ); }

        void setScene( Scene* scene );
        void addComponent( ScreenComponent* component ) { _windowPanel->addComponent( component ); }
        void display();

    protected:
        SDL_Renderer* _renderer;

    private:
        Panel* _windowPanel;
        SDL_Window* _window;
        SDL_Surface* _surface;
        Vector2D<int> _size;

        std::list<MouseListener*> _mouseListeners;
        std::list<KeyListener*> _keyListeners;

        Scene* _scene;

};