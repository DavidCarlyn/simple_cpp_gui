#include <Texture.hpp>
#include <SDL_image.h>
#include <iostream>

Texture::Texture() : ScreenComponent() {
	_texture = NULL;
	_textureSize = Vector2D<int>( 0, 0 );
}

Texture::Texture( Vector2D<int> size ) : ScreenComponent( size ) {
	_texture = NULL;
	_textureSize = Vector2D<int>( 0, 0 );
}

Texture::Texture( Vector2D<int> size, Vector2D<int> position ) : ScreenComponent( size, position ) {
	_texture = NULL;
	_textureSize = Vector2D<int>( 0, 0 );
}

Texture::Texture( Vector2D<float> size ) : ScreenComponent( size ) {
	_texture = NULL;
	_textureSize = Vector2D<int>( 0, 0 );
}

Texture::~Texture() {
	free();
}

bool Texture::load( SDL_Renderer* renderer, std::string path, SDL_Color colorKey ) {
	free();

	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if ( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
        //TODO: Log here
        return false;
	}

	//Color key image
	SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, colorKey.r, colorKey.g, colorKey.b ) );

	//Create texture from surface pixels
    newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
	if( newTexture == NULL ) {
		printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
        //TODO: Log here
        return false;
	}

	//Get image dimensions
	_textureSize.setFirst( loadedSurface->w );
	_textureSize.setSecond( loadedSurface->h );

	//Get rid of old loaded surface
	SDL_FreeSurface( loadedSurface );

	//Return success
	_texture = newTexture;
	return _texture != NULL;
}

bool Texture::loadText( SDL_Renderer* renderer, std::string textureText, TTF_Font* font, SDL_Color textColor ) {
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
    if ( textSurface == NULL ) {
        std::cerr << "Unable to render text surface! SDL_ttf Error: \n" << TTF_GetError() << std::endl;
		return false;
    }

    _texture = SDL_CreateTextureFromSurface( renderer, textSurface );
    if ( _texture == NULL ) {
        std::cerr << "Unable to create texture from rendered text! SDL Error: \n" << SDL_GetError() << std::endl;
		return false;
    }

    //Get image dimensions
    _textureSize.setFirst( textSurface->w );
	_textureSize.setSecond( textSurface->h );

    //Get rid of old surface
    SDL_FreeSurface( textSurface );
    
    //Return success
    return _texture != NULL;
}

void Texture::free() {
	//Free texture if it exists
	if( _texture != NULL )
	{
		SDL_DestroyTexture( _texture );
		_texture = NULL;
		_textureSize = Vector2D<int>( 0, 0 );
	}
}

void Texture::setColor( Uint8 red, Uint8 green, Uint8 blue ) {
	SDL_SetTextureColorMod( _texture, red, green, blue );
}

void Texture::setBlendMode( SDL_BlendMode blending ) {
	SDL_SetTextureBlendMode( _texture, blending );
}
		
void Texture::setAlpha( Uint8 alpha ) {
	SDL_SetTextureAlphaMod( _texture, alpha );
}

void Texture::render( SDL_Renderer* renderer, SDL_Rect* clip, const double angle ) {
	SDL_Rect renderQuad = { getRenderPosition().getFirst(), getRenderPosition().getSecond(),
							getRenderSize().getFirst(), getRenderSize().getSecond() };

	SDL_RenderCopyEx( renderer, _texture, clip, &renderQuad, angle, NULL, SDL_FLIP_NONE );
}