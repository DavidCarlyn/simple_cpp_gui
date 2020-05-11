#include <Food.hpp>
#include <iostream>

Food::Food() : ScreenComponent() {
    _gamePosition = Vector2D<int>( 0, 0 );
	_spriteClip.x = 16;
	_spriteClip.y = 0;
	_spriteClip.w = 16;
	_spriteClip.h = 16;
}

Food::Food( Vector2D<int> size, Vector2D<int> position ) : ScreenComponent( size ) {
    _gamePosition = position;
    _spriteClip.x = 16;
	_spriteClip.y = 0;
	_spriteClip.w = 16;
	_spriteClip.h = 16;
}

void Food::render( SDL_Renderer* renderer, SDL_Rect* clip, const double angle ) {
    if ( _spriteSheet != NULL ) {
        _spriteSheet->setRenderPosition( Vector2D<int>( getRenderPosition().getFirst() + _gamePosition.getFirst() * getRenderSize().getFirst(),
                                                        getRenderPosition().getSecond() + _gamePosition.getSecond() * getRenderSize().getSecond() ) );
        _spriteSheet->setRenderSize( getRenderSize() );
        _spriteSheet->render( renderer, &_spriteClip );
        return;
    }
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_Rect rect;
    rect.x = getRenderPosition().getFirst() + _gamePosition.getFirst() * getRenderSize().getFirst();
    rect.y = getRenderPosition().getSecond() + _gamePosition.getSecond() * getRenderSize().getSecond();
    rect.w = getRenderSize().getFirst();
    rect.h = getRenderSize().getSecond();
    SDL_RenderFillRect( renderer, &rect );
}
