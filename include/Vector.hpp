#pragma once

template <class T>
class Vector2D {
    public:
        Vector2D() : _v0( 0 ), _v1( 0 ) {}
        template<class K>
        Vector2D( const Vector2D<K> &vector ) : _v0( vector.getFirst() ), _v1( vector.getSecond() ) {}
        Vector2D( T v0, T v1 ) : _v0( v0 ), _v1( v1 ) {}
        T getFirst() const { return _v0; }
        T getSecond() const { return _v1; }
        void setFirst( T v ) { _v0 = v; }
        void setSecond( T v ) { _v1 = v; }

        Vector2D<T> operator+( const Vector2D<T>& rhs ) {
            return Vector2D<T>( _v0 + rhs._v0, _v1 + rhs._v1 );
        }

        Vector2D<T> operator-( const Vector2D<T>& rhs ) {
            return Vector2D<T>( _v0 - rhs._v0, _v1 - rhs._v1 );
        }

        Vector2D<T> operator*( const Vector2D<T>& rhs ) {
            return Vector2D<T>( _v0 * rhs._v0, _v1 * rhs._v1 );
        }

        Vector2D<T> operator/( const Vector2D<T>& rhs ) {
            return Vector2D<T>( _v0 / rhs._v0, _v1 / rhs._v1 );
        }

        bool equals( Vector2D rhs ) { return rhs.getFirst() == _v0 && rhs.getSecond() == _v1; }


    private:
        T _v0;
        T _v1;
};