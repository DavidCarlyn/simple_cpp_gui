#include <Snake.hpp>

Direction getDirection( Vector2D<int> src, Vector2D<int> target ) {
    int dx = src.getFirst() - target.getFirst();
    int dy = src.getSecond() - target.getSecond();
    if ( dx == 0 ) {
        return dy > 0 ? Direction::UP : Direction::DOWN;
    } else {
        return dx < 0 ? Direction::RIGHT : Direction::LEFT;
    }
}


Snake::Snake() : ScreenComponent() {
    _snakeSprites = NULL;
    _direction = Direction::DOWN;
    _gamePosition = Vector2D<int>( 0, 0 );
    _body = new SnakePart( _absoluteSize,  Vector2D<int>( _gamePosition.getFirst(), _gamePosition.getSecond() - 1 ), this );
    _body->setPosition( _absolutePosition );
}

Snake::Snake( Vector2D<int> size, Vector2D<int> gamePosition ) : ScreenComponent( size ) {
    _snakeSprites = NULL;
    _direction = Direction::DOWN;
    _gamePosition = gamePosition;
    _body = new SnakePart( size, Vector2D<int>( gamePosition.getFirst(), gamePosition.getSecond() - 1 ), this );
    _body->setPosition( _absolutePosition );
}

void Snake::setSize( Vector2D<int> size ) {
    ScreenComponent::setSize( size );
    _body->setSize( size );
}

void Snake::setPosition( Vector2D<int> position ) {
    ScreenComponent::setPosition( position );
    _body->setPosition( position );
}

bool Snake::didCollide( Vector2D<int> gamePosition ) {
    if ( _gamePosition.equals( gamePosition ) ) return true;
    return didCollideWithBody( gamePosition );
}

bool Snake::didCollideWithBody( Vector2D<int> gamePosition ) {
    return _body->didCollide( gamePosition );
}

void Snake::updateDirection( SDL_Keycode key ) {
    //e.key.repeat == 0
    switch( key ) {
        case SDLK_UP:
        case SDLK_w:
            if ( _direction == Direction::DOWN ) break;
            _direction = Direction::UP;
            break;
        case SDLK_s:
        case SDLK_DOWN:
            if ( _direction == Direction::UP ) break;
            _direction = Direction::DOWN;
            break;
        case SDLK_a:
        case SDLK_LEFT:
            if ( _direction == Direction::RIGHT ) break;
            _direction = Direction::LEFT;
            break;
        case SDLK_d:
        case SDLK_RIGHT:
            if ( _direction == Direction::LEFT ) break;
            _direction = Direction::RIGHT;
            break;
    }
}

void Snake::onKeyUp( SDL_Keycode key ) {
    updateDirection( key );
}

void Snake::onKeyDown( SDL_Keycode key ) {
    updateDirection( key );
}

void Snake::move() {
    _body->update( _gamePosition );
    int x = _gamePosition.getFirst();
    int y = _gamePosition.getSecond();
    switch ( _direction ) {
        case UP:
            y -= 1;
            break;
        case RIGHT:
            x += 1;
            break;
        case DOWN:
            y += 1;
            break;
        case LEFT:
            x -= 1;
            break;
        default:
            break;
    }

    _gamePosition = Vector2D<int>( x, y );
}

void Snake::grow() {
    _body->grow( _gamePosition );
}

void Snake::render( SDL_Renderer* renderer, SDL_Rect* clip, const double angle ) {
    SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );

    if ( _snakeSprites != NULL ) {
        SDL_Rect snakeHeadClip;
        snakeHeadClip.x = 0;
        snakeHeadClip.y = 0;
        snakeHeadClip.w = 16;
        snakeHeadClip.h = 16;
        _snakeSprites->setRenderSize( getRenderSize() );
        _snakeSprites->setRenderPosition( Vector2D<int>( getRenderPosition().getFirst() + _gamePosition.getFirst() * getRenderSize().getFirst(),
                                                         getRenderPosition().getSecond() + _gamePosition.getSecond() * getRenderSize().getSecond() ) );
        double angle = 0.0;
        switch ( _direction ) {
            case RIGHT:
                angle = 90.0;
                break;
            case DOWN:
                angle = 180.0;
                break;
            case LEFT:
                angle = 270.0;
                break;
            default:
                break;
        }
        _snakeSprites->render( renderer, &snakeHeadClip, angle );

    } else {
        SDL_Rect rect;
        rect.x = getRenderPosition().getFirst() + _gamePosition.getFirst() * getRenderSize().getFirst();
        rect.y = getRenderPosition().getSecond() + _gamePosition.getSecond() * getRenderSize().getSecond();
        rect.w = getRenderSize().getFirst();
        rect.h = getRenderSize().getSecond();
        SDL_RenderFillRect( renderer, &rect );
    }
    _body->updateAbsolutePosition( getRenderPosition() );
    _body->render( renderer );

}

Snake::SnakePart::SnakePart() : ScreenComponent() {
    _snakeSprites = NULL;
    _next = NULL;
    _head = NULL;
    _next = NULL;
    _gamePosition = Vector2D<int>( 0, 0 );
}

Snake::SnakePart::SnakePart( Vector2D<int> size, Vector2D<int> gamePosition, SnakePart* prev ) : ScreenComponent( size ) {
    _snakeSprites = NULL;
    _next = NULL;
    _head = NULL;
    _prev = prev;
    _gamePosition = gamePosition;
}

Snake::SnakePart::SnakePart( Vector2D<int> size, Vector2D<int> gamePosition, Snake* head ) : ScreenComponent( size ) {
    _snakeSprites = NULL;
    _next = NULL;
    _prev = NULL;
    _gamePosition = gamePosition;
    _head = head;
}

void Snake::SnakePart::setSize( Vector2D<int> size ) {
    ScreenComponent::setSize( size );
    if ( _next != NULL ) {
        _next->setSize( size );
    }
}

void Snake::SnakePart::setPosition( Vector2D<int> position ) {
    ScreenComponent::setPosition( position );
    if ( _next != NULL ) {
        _next->setPosition( position );
    }
}

bool Snake::SnakePart::didCollide( Vector2D<int> gamePosition ) {
    if ( _gamePosition.equals( gamePosition ) ) return true;
    if ( _next == NULL ) return false;
    return _next->didCollide( gamePosition );
}

void Snake::SnakePart::update( Vector2D<int> gamePosition ) {
    if ( _next != NULL ) {
        _next->update( _gamePosition );
    }

    _gamePosition = gamePosition;
}

void Snake::SnakePart::grow( Vector2D<int> prevGamePosition ) {
    if ( _next != NULL ) {
        _next->grow( _gamePosition );
        return;
    }

    int dx = 0;
    int dy = 0;

    if ( _gamePosition.getFirst() != prevGamePosition.getFirst() ) {
        dx = _gamePosition.getFirst() - prevGamePosition.getFirst();
    } else {
        dy = _gamePosition.getSecond() - prevGamePosition.getSecond();
    }

    _next = new SnakePart( _absoluteSize, Vector2D<int>( _gamePosition.getFirst() + dx, _gamePosition.getSecond() + dy ), this ); //TODO: set correct position
    _next->setPosition( _absolutePosition );
    _next->setTexture( _snakeSprites );
}

void Snake::SnakePart::updateAbsolutePosition( Vector2D<int> position ) {
    setAbsolutePosition( position );
    if ( _next != NULL ) {
        _next->setAbsolutePosition( position );
    }
}

int Snake::SnakePart::getSpriteType() {
    // End sprite
    if ( _next == NULL ) {
        return 1;
    }

    Vector2D<int> target;
    if ( _head == NULL ) {
        target = _prev->getGamePosition();
    } else {
        target = _head->getGamePosition();
    }

    Direction prevDirection = getDirection( _gamePosition, target );
    Direction nextDirection = getDirection( _gamePosition, _next->getGamePosition() );

    if ( prevDirection == UP && nextDirection == DOWN ||
         prevDirection == DOWN && nextDirection == UP ||
         prevDirection == LEFT && nextDirection == RIGHT ||
         prevDirection == RIGHT && nextDirection == LEFT ) {

             return 0;
    }

    return 2;
}

/**
 * 0 : body
 * 1 : tail
 * 2 : corner
 **/
#include <iostream>
double Snake::SnakePart::getAngle( int spriteType ) {
    Vector2D<int> target;
    if ( _head == NULL ) {
        target = _prev->getGamePosition();
    } else {
        target = _head->getGamePosition();
    }

    Direction prevDirection = getDirection( _gamePosition, target );

    Direction nextDirection;
    if ( spriteType != 1 ) {
        nextDirection = getDirection( _gamePosition, _next->getGamePosition() );
    }

    switch ( spriteType ) {
        case 0:
        case 1:
            switch ( prevDirection ) {
                case UP: return 0.0;
                case RIGHT: return 90.0;
                case DOWN: return 180.0;
                case LEFT: return 270 ;
            }
            break;
        case 2:
            switch ( prevDirection ) {
                case UP:
                    return nextDirection == RIGHT ? 270.0 : 180.0;
                    break;
                case RIGHT:
                    return nextDirection == DOWN ? 0.0 : 270.0;
                    break;
                case DOWN:
                    return nextDirection == LEFT ? 90.0 : 0.0;
                    break;
                case LEFT:
                    return nextDirection == UP ? 180.0 : 90.0;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }

    return 0.0;
}

void Snake::SnakePart::render( SDL_Renderer* renderer, SDL_Rect* clip, const double angle ) {
    if ( _snakeSprites != NULL ) {
        int spriteType = getSpriteType();
        SDL_Rect snakeBodyClip;
        snakeBodyClip.w = 16;
        snakeBodyClip.h = 16;
        snakeBodyClip.x = spriteType == 0 || spriteType == 1 ? 0 : 16;
        snakeBodyClip.y = spriteType == 0 || spriteType == 2 ? 16 : 32;
        _snakeSprites->setRenderSize( getAbsoluteSize() );
        _snakeSprites->setRenderPosition( Vector2D<int>( getAbsolutePosition().getFirst() + _gamePosition.getFirst() * getAbsoluteSize().getFirst(),
                                                         getAbsolutePosition().getSecond() + _gamePosition.getSecond() * getAbsoluteSize().getSecond() ) );
        double angle = getAngle ( spriteType );
        _snakeSprites->render( renderer, &snakeBodyClip, angle );
    } else {
        SDL_Rect rect;
        rect.x = getAbsolutePosition().getFirst() + _gamePosition.getFirst() * getAbsoluteSize().getFirst();
        rect.y = getAbsolutePosition().getSecond() + _gamePosition.getSecond() * getAbsoluteSize().getSecond();
        rect.w = getAbsoluteSize().getFirst();
        rect.h = getAbsoluteSize().getSecond();
        SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
        SDL_RenderFillRect( renderer, &rect );
    }

    if ( _next != NULL ) {
        _next->render( renderer );
    }
}