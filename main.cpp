/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#define SDL_MAIN_HANDLED

#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Engine.hpp>
#include <Window.hpp>
#include <Button.hpp>

class MyActionListener : public ActionListener {
    public:
        MyActionListener() {}

        void onAction() override {
            std::cout << "Action" << std::endl;
        }
};

class MyScene : public Scene {
	public:
		MyScene() : Scene() {}

		bool build( Panel* panel, SDL_Renderer* renderer ) override {
			_font = TTF_OpenFont( "bin/LemonMilk.otf", 12 );
    		if( _font == NULL ) {
        		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
				return false;
    		}

			panel->setDisplayMode( new Anchor );
			Button* button = new Button( Vector2D<float>( 0.2f, 0.2f ) );
			button->setAnchorLocation( CENTER );
			button->addActionListener( new MyActionListener() );
			button->setText( renderer, "Press Me", _font, { 255, 255, 255, 255} );

			panel->addComponent( button );
			panel->addMouseListener( button );
			return true;
		}

		bool loop() override { return true; }

	private:
		TTF_Font* _font;


};

int main( int argc, char* args[] ) {
	Engine* engine = new Engine();
	Window* window = new Window( "Testing", Vector2D<int>( 1080, 720 ) );
	window->setScene( new MyScene() );
    

	window->display();

	return 0;
}