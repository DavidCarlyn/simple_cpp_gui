/*This source code copyrighted by Lazy Foo' Productions (2004-2020)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#define SDL_MAIN_HANDLED

#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <Engine.hpp>
#include <Window.hpp>

int main( int argc, char* args[] ) {
	Window* window = new Window( "Testing", Vector2D<int>( 1080, 720 ) );

	Panel* testPanel = new Panel( Vector2D<float>( 1.0f, 1.0f ), Vector2D<int>( 0, 0 ), new Anchor() );
	testPanel->setBackgroundColor( { 100, 200, 50, 255} );

	window->addComponent( testPanel );

	Panel* grid1 = new Panel( Vector2D<float>( 0.2f, 0.2f ), Vector2D<float>( 0.2f, 0.2f ) );
	grid1->setBackgroundColor( { 255, 0, 0, 255} );
	grid1->setAnchorLocation( NORTHWEST );
	Panel* grid2 = new Panel( Vector2D<float>( 0.2f, 0.2f ), Vector2D<float>( 0.2f, 0.2f ) );
	grid2->setBackgroundColor( { 0, 255, 0, 255} );
	grid2->setAnchorLocation( NORTHEAST );
	Panel* grid3 = new Panel( Vector2D<float>( 0.2f, 0.2f ), Vector2D<float>( 0.2f, 0.2f ) );
	grid3->setBackgroundColor( { 0, 0, 255, 255} );
	grid3->setAnchorLocation( SOUTHWEST );
	Panel* grid4 = new Panel( Vector2D<float>( 0.2f, 0.2f ), Vector2D<float>( 0.2f, 0.2f ) );
	grid4->setBackgroundColor( { 255, 0, 255, 255} );
	grid4->setAnchorLocation( SOUTHEAST );

	Panel* grid5 = new Panel( Vector2D<float>( 0.2f, 0.2f ), Vector2D<float>( 0.0f, 0.1f ) );
	grid5->setBackgroundColor( { 100, 100, 100, 255} );
	grid5->setAnchorLocation( NORTH );
	Panel* grid6 = new Panel( Vector2D<float>( 0.2f, 0.2f ), Vector2D<float>( 0.1f, 0.0f ) );
	grid6->setBackgroundColor( { 200, 10, 90, 255} );
	grid6->setAnchorLocation( EAST );
	Panel* grid7 = new Panel( Vector2D<float>( 0.2f, 0.2f ), Vector2D<float>( 0.1f, 0.0f ) );
	grid7->setBackgroundColor( { 50, 170, 230, 255} );
	grid7->setAnchorLocation( WEST );
	Panel* grid8 = new Panel( Vector2D<float>( 0.2f, 0.2f ), Vector2D<float>( 0.0f, 0.1f ) );
	grid8->setBackgroundColor( { 150, 170, 230, 255} );
	grid8->setAnchorLocation( SOUTH );

	Panel* grid9 = new Panel( Vector2D<float>( 0.2f, 0.2f ) );
	grid9->setBackgroundColor( { 255, 255, 255, 255} );
	grid9->setAnchorLocation( CENTER );

	testPanel->addComponent( grid1 );
	testPanel->addComponent( grid2 );
	testPanel->addComponent( grid3 );
	testPanel->addComponent( grid4 );

	testPanel->addComponent( grid5 );
	testPanel->addComponent( grid6 );
	testPanel->addComponent( grid7 );
	testPanel->addComponent( grid8 );
	testPanel->addComponent( grid9 );

	window->display();

	return 0;
}