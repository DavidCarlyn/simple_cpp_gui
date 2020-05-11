#include <Panel.hpp>

Panel::Panel() : Panel( Vector2D<float>( 1.0f, 1.0f ) ) {}

Panel::Panel( Vector2D<int> size, Vector2D<int> position, DisplayMode* displayMode ) : ScreenComponent( size, position ) {
    _displayMode = displayMode;
    _backgroundColor = { 255, 255, 255, 255 };
}

Panel::Panel( Vector2D<float> size, Vector2D<float> position, DisplayMode* displayMode ) : ScreenComponent( size, position ) {
    _displayMode = displayMode;
    _backgroundColor = { 255, 255, 255, 255 };
}

Panel::Panel( Vector2D<int> size, Vector2D<float> position, DisplayMode* displayMode ) : ScreenComponent( size, position ) {
    _displayMode = displayMode;
    _backgroundColor = { 255, 255, 255, 255 };
}

Panel::Panel( Vector2D<float> size, Vector2D<int> position, DisplayMode* displayMode ) : ScreenComponent( size, position ) {
    _displayMode = displayMode;
    _backgroundColor = { 255, 255, 255, 255 };
}


Panel::~Panel() {
    delete _displayMode;
    while ( _components.size() > 0 ) {
        delete _components.front();
        _components.pop_front();
    }
}

void Panel::addComponent( ScreenComponent* component ) {
    _components.push_back( component );
}

void Panel::render( SDL_Renderer* renderer, SDL_Rect* clip, const double angle ) {
    SDL_SetRenderDrawColor( renderer, _backgroundColor.r, _backgroundColor.g, _backgroundColor.b, _backgroundColor.a );
    SDL_Rect rect;
    rect.x = getRenderPosition().getFirst();
    rect.y = getRenderPosition().getSecond();
    rect.w = getRenderSize().getFirst();
    rect.h = getRenderSize().getSecond();
    SDL_RenderFillRect( renderer, &rect );

    _displayMode->positionComponents( &rect, _components );

    for ( auto comp : _components ) {
        comp->render( renderer );
    }
}

void Panel::onMouseDown( Vector2D<int> mousePosition ) {
    for ( auto listener : _mouseListeners ) {
        listener->onMouseDown( mousePosition );
    }
}

void Panel::onMouseUp( Vector2D<int> mousePosition ) {
    for ( auto listener : _mouseListeners ) {
        listener->onMouseUp( mousePosition );
    }
}

void Panel::onMouseMove( Vector2D<int> mousePosition ) {
    for ( auto listener : _mouseListeners ) {
        listener->onMouseMove( mousePosition );
    }
}

void Panel::onKeyDown( SDL_Keycode key ) {
    for ( auto listener : _keyListeners ) {
        listener->onKeyDown( key );
    }
}

void Panel::onKeyUp( SDL_Keycode key ) {
    for ( auto listener : _keyListeners ) {
        listener->onKeyUp( key );
    }
}
