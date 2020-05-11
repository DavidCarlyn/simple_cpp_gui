#pragma once

#include <Texture.hpp>
#include <Listeners.hpp>
#include <list>

class Button : public ScreenComponent, public MouseListener {
    public:
        Button() { _state = BASE; _textTexture = NULL; }
        Button( Vector2D<int> size, Vector2D<int> position = Vector2D<int>( 0, 0 ) ) : ScreenComponent( size, position ) { _state = BASE; _textTexture = NULL; }
        Button( Vector2D<float> size, Vector2D<float> position = Vector2D<float> ( 0.0f, 0.0f ) ) : ScreenComponent( size, position ) { _state = BASE; _textTexture = NULL; }
        Button( Vector2D<int> size, Vector2D<float> position ) : ScreenComponent( size, position ) { _state = BASE; _textTexture = NULL; }
        Button( Vector2D<float> size, Vector2D<int> position ) : ScreenComponent( size, position ) { _state = BASE; _textTexture = NULL; }

        void addActionListener( ActionListener* listener ) { _actionListeners.push_back( listener ); }
        virtual void setText( SDL_Renderer* renderer, std::string textureText, TTF_Font* font, SDL_Color textColor );

        virtual void onMouseUp( Vector2D<int> pos ) override;
        virtual void onMouseDown( Vector2D<int> pos ) override;
        virtual void onMouseMove( Vector2D<int> pos ) override;
        virtual void render( SDL_Renderer* renderer, SDL_Rect* clip = NULL, const double angle = 0 );

    protected:
        virtual void renderText( SDL_Renderer* renderer, SDL_Rect* clip = NULL, const double angle = 0 );
        
        enum State {
            BASE,
            MOUSEOVER,
            MOUSEDOWN
        };

        std::list<ActionListener*> _actionListeners;
        State _state;

        std::string _text;
        Texture* _textTexture;
};