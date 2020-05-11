#pragma once

#include <Texture.hpp>
#include <Listeners.hpp>


enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class Snake : public ScreenComponent, public KeyListener {
    public:
        Snake();
        Snake( Vector2D<int> size, Vector2D<int> gamePosition );

        void setTexture( Texture* snakeSprites ) { _snakeSprites = snakeSprites; _body->setTexture( snakeSprites ); }
        void setSize( Vector2D<int> size );
        void setPosition( Vector2D<int> position ) override;
        Vector2D<int> getGamePosition() { return _gamePosition; }

        bool didCollide( Vector2D<int> gamePosition );
        bool didCollideWithBody( Vector2D<int> gamePosition );

        void onKeyUp( SDL_Keycode key ) override;
        void onKeyDown( SDL_Keycode key ) override;

        void move();
        void grow();

        virtual void render( SDL_Renderer* renderer, SDL_Rect* clip = NULL, const double angle = 0 ) override;
    private:
        void updateDirection( SDL_Keycode key );
        class SnakePart : public ScreenComponent {
            public:
                SnakePart();
                SnakePart( Vector2D<int> size, Vector2D<int> gamePosition, Snake* head );
                SnakePart( Vector2D<int> size, Vector2D<int> gamePosition, SnakePart* prev );

                void setTexture( Texture* snakeSprites ) { _snakeSprites = snakeSprites; }
                void setAbsolutePosition( Vector2D<int> position ) { ScreenComponent::setPosition( position ); }
                void setSize( Vector2D<int> size );
                void setPosition( Vector2D<int> position ) override;
                Vector2D<int> getGamePosition() { return _gamePosition; }

                bool didCollide( Vector2D<int> gamePosition );

                void update( Vector2D<int> gamePosition );
                void grow( Vector2D<int> prevGamePosition );

                void updateAbsolutePosition( Vector2D<int> position );

                virtual void render( SDL_Renderer* renderer, SDL_Rect* clip = NULL, const double angle = 0 ) override;
            private:
                int getSpriteType();
                double getAngle( int spriteType );
                SnakePart* _next;
                Snake* _head;
                SnakePart* _prev;
                Vector2D<int> _gamePosition;
                Texture* _snakeSprites;
        };

        Direction _direction;
        SnakePart* _body;
        Vector2D<int> _gamePosition;
        Texture* _snakeSprites;

};