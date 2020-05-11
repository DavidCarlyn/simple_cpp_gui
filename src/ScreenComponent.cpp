#include <ScreenComponent.hpp>

ScreenComponent::ScreenComponent() : ScreenComponent( Vector2D<float>( 1.0f, 1.0f ) ) {}

ScreenComponent::ScreenComponent( Vector2D<int> size, Vector2D<int> position ) {
    _anchor = AnchorLocation::NONE;
    _absoluteSize = size;
    _absolutePosition = position;
    _positionConstraint = ABSOLUTE;
    _sizeConstraint = ABSOLUTE;
    _renderPosition = Vector2D<int>( 0, 0 );
    _renderSize = Vector2D<int>( 0, 0 );
}

ScreenComponent::ScreenComponent( Vector2D<float> size, Vector2D<float> position ) {
    _anchor = AnchorLocation::NONE;
    _relativeSize = size;
    _relativePosition = position;
    _positionConstraint = RELATIVE;
    _sizeConstraint = RELATIVE;
    _renderPosition = Vector2D<int>( 0, 0 );
    _renderSize = Vector2D<int>( 0, 0 );
}

ScreenComponent::ScreenComponent( Vector2D<int> size, Vector2D<float> position ) {
    _anchor = AnchorLocation::NONE;
    _absoluteSize = size;
    _relativePosition = position;
    _positionConstraint = RELATIVE;
    _sizeConstraint = ABSOLUTE;
    _renderPosition = Vector2D<int>( 0, 0 );
    _renderSize = Vector2D<int>( 0, 0 );
}

ScreenComponent::ScreenComponent( Vector2D<float> size, Vector2D<int> position ) {
    _anchor = AnchorLocation::NONE;
    _relativeSize = size;
    _absolutePosition = position;
    _positionConstraint = ABSOLUTE;
    _sizeConstraint = RELATIVE;
    _renderPosition = Vector2D<int>( 0, 0 );
    _renderSize = Vector2D<int>( 0, 0 );
}