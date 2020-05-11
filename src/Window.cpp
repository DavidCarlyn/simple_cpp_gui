#include <Window.hpp>
#include <iostream>

Window::Window() : Window( "NO NAME" ) {}

Window::Window( std::string name ) : Window( name, Vector2D<int> ( 1080, 720 ) ) {}

Window::Window( Vector2D<int> size ) : Window( "NO NAME", size ) {}

Window::Window( std::string name, Vector2D<int> size ) {
    _size = size;
	_window = SDL_CreateWindow( name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, size.getFirst(), size.getSecond(), SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
	if ( _window == NULL ) {
		std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
	}

    _surface = SDL_GetWindowSurface( _window );

    _renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
	if ( _renderer == NULL ) {
		std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
	}

    _windowPanel = new Panel( size, Vector2D<int>(0, 0) );
	_windowPanel->setRenderSize( size );

	addMouseListener( _windowPanel );
}

Window::~Window() {
    SDL_FreeSurface( _surface );
    SDL_DestroyRenderer( _renderer );
    SDL_DestroyWindow( _window );
	delete _scene;

	_scene = NULL;
    _surface = NULL;
    _window = NULL;
    _renderer = NULL;
}

void Window::setScene( Scene* scene ) {
	if ( _scene != NULL ) {
		_windowPanel->clearComponents();
		delete _scene;
	}

	_scene = scene;
	_scene->build( _windowPanel, _renderer );
}

void Window::display() {
    SDL_Event e;
    bool quit = false;
    while ( !quit ) {


		//Handle events on queue
		while ( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if ( e.type == SDL_QUIT ) {
				quit = true;
			} else if ( e.type == SDL_WINDOWEVENT ) {
				switch ( e.window.event ) {
					case SDL_WINDOWEVENT_SIZE_CHANGED:
					case SDL_WINDOWEVENT_RESIZED:
						int screenWidth = e.window.data1;
						int screenHeight = e.window.data2;
                        _windowPanel->setSize( Vector2D<int>( screenWidth, screenHeight ) );
                        _windowPanel->setRenderSize( Vector2D<int>( screenWidth, screenHeight ) );
                }
            } else if ( e.type == SDL_MOUSEBUTTONDOWN ) {
				for ( auto listener : _mouseListeners ) {
					listener->onMouseDown( Vector2D<int>( e.button.x, e.button.y ) );
				}
			} else if ( e.type == SDL_MOUSEBUTTONUP ) {
				for ( auto listener : _mouseListeners ) {
					listener->onMouseUp( Vector2D<int>( e.button.x, e.button.y ) );
				}
			} else if ( e.type == SDL_MOUSEMOTION ) {
				for ( auto listener : _mouseListeners ) {
					listener->onMouseMove( Vector2D<int>( e.button.x, e.button.y ) );
				}
			} else if ( e.type == SDL_KEYDOWN ) {
				for ( auto listener : _keyListeners ) {
					listener->onKeyDown( e.key.keysym.sym );
				}
			} else if ( e.type == SDL_KEYUP ) {
				for ( auto listener : _keyListeners ) {
					listener->onKeyUp( e.key.keysym.sym );
				}
			}
		}

		if ( _scene == NULL ) {
			return;
		} else if ( !_scene->loop() ) {
			setScene( _scene->getNextScene() );
		}

        //Clear screen
		SDL_SetRenderDrawColor( _renderer, 0x00, 0x00, 0x00, 0xFF );
		SDL_RenderClear( _renderer );

        _windowPanel->render( _renderer );

		//Update screen
		SDL_RenderPresent( _renderer );
        
    }
}
