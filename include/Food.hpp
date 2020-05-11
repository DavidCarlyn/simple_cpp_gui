#pragma once

#include <Texture.hpp>

class Food : public ScreenComponent {
    public:
        Food();
        Food( Vector2D<int> size, Vector2D<int> position );

        Vector2D<int> getGamePosition() { return _gamePosition; }
        void setGamePosition( Vector2D<int> position ) { _gamePosition = position; }

        void setTexture( Texture* texture ) { _spriteSheet = texture; }

        virtual void render( SDL_Renderer* renderer, SDL_Rect* clip = NULL, const double angle = 0 ) override;
    private:
        Vector2D<int> _gamePosition;
        Texture* _spriteSheet;
        SDL_Rect _spriteClip;
};