#include <Button.hpp>

#include <iostream>
bool collided ( Vector2D<int> src, Vector2D<int> target, Vector2D<int> targetSize ) {
    if ( src.getFirst() < target.getFirst() ) { return false; }
    if ( src.getFirst() > target.getFirst() + targetSize.getFirst() ) { return false; }
    if ( src.getSecond() < target.getSecond() ) { return false; }
    if ( src.getSecond() > target.getSecond() + targetSize.getSecond() ) { return false; }

    return true;
}

void Button::onMouseUp( Vector2D<int> pos ) {
    _state = BASE;
    if ( !collided( pos, getRenderPosition(), getRenderSize() ) ) { _state = BASE; return; }
    _state = MOUSEOVER;
    for ( auto l : _actionListeners ) {
        l->onAction();
    }
}

void Button::onMouseDown( Vector2D<int> pos ) {
    if ( !collided( pos, getRenderPosition(), getRenderSize() ) ) { _state = BASE; return; }
    _state = MOUSEDOWN;
}

void Button::onMouseMove( Vector2D<int> pos ) {

    if ( !collided( pos, getRenderPosition(), getRenderSize() ) ) { _state = BASE; return; }
    _state = _state == MOUSEDOWN ? MOUSEDOWN : MOUSEOVER;
}

void Button::setText( SDL_Renderer* renderer, std::string textureText, TTF_Font* font, SDL_Color textColor ) {
    if ( _textTexture != NULL ) {
        delete _textTexture;
    }

    _text = textureText;
    _textTexture = new Texture();
    _textTexture->loadText( renderer, textureText, font, textColor );
}

void Button::render( SDL_Renderer* renderer, SDL_Rect* clip, const double angle ) {
    SDL_Rect rect;
    rect.x = getRenderPosition().getFirst();
    rect.y = getRenderPosition().getSecond();
    rect.w = getRenderSize().getFirst();
    rect.h = getRenderSize().getSecond();

    switch ( _state ) {
        case MOUSEDOWN:
            SDL_SetRenderDrawColor( renderer, 0x11, 0x11, 0x11, 0xFF );
            break;
        case MOUSEOVER:
            SDL_SetRenderDrawColor( renderer, 0x33, 0x33, 0x33, 0xFF );
            break;
        case BASE:
        default:
            SDL_SetRenderDrawColor( renderer, 0x22, 0x22, 0x22, 0xFF );
            break;
    }

    SDL_RenderFillRect( renderer, &rect );
    if ( _textTexture != NULL ) {
        renderText( renderer, clip, angle );
    }
}

void Button::renderText( SDL_Renderer* renderer, SDL_Rect* clip, const double angle ) {
    Vector2D<int> extraSpace = getRenderSize() - _textTexture->getTextureSize();
    _textTexture->setRenderPosition( getRenderPosition() + extraSpace / Vector2D<int>( 2, 2 ) );
    _textTexture->setRenderSize( _textTexture->getTextureSize() );
    _textTexture->render( renderer, clip, angle );
}