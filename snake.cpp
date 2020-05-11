#define SDL_MAIN_HANDLED

#include <Window.hpp>
#include <Button.hpp>
#include <Engine.hpp>
#include <Snake.hpp>
#include <Food.hpp>

#include <iostream>
#include <stdlib.h>
#include <ctime>

const std::string FONT_PATH = "LemonMilk.otf";
const std::string SPRITE_PATH = "snake_sprite_sheet.png";

class FlipAction : public ActionListener {
    public:
        FlipAction( bool* flip ) : ActionListener() { _flip = flip; }

        void onAction() {
            *_flip = !(*_flip);
        }

    private:
        bool* _flip;
};

class SnakeButton : public Button {
    public:
        SnakeButton() : Button() {}
        ~SnakeButton() { }
        SnakeButton( Vector2D<int> size, Vector2D<int> position = Vector2D<int>( 0, 0 ) ) : Button( size, position ) {}
        SnakeButton( Vector2D<float> size, Vector2D<float> position = Vector2D<float> ( 0.0f, 0.0f ) ) : Button( size, position ) {}
        SnakeButton( Vector2D<int> size, Vector2D<float> position ) : Button( size, position ) {}
        SnakeButton( Vector2D<float> size, Vector2D<int> position ) : Button( size, position ) {}

        void render( SDL_Renderer* renderer, SDL_Rect* clip = NULL, const double angle = 0 ) override {
            SDL_Rect rect;
            rect.x = getRenderPosition().getFirst();
            rect.y = getRenderPosition().getSecond();
            rect.w = getRenderSize().getFirst();
            rect.h = getRenderSize().getSecond();

            switch ( _state ) {
                case MOUSEDOWN:
                    SDL_SetRenderDrawColor( renderer, 0x99, 0xFF, 0x99, 0xFF );
                    break;
                case MOUSEOVER:
                    SDL_SetRenderDrawColor( renderer, 0x33, 0xFF, 0x33, 0xFF );
                    break;
                case BASE:
                default:
                    SDL_SetRenderDrawColor( renderer, 0x66, 0xFF, 0x66, 0xFF );
                    break;
            }

            SDL_RenderFillRect( renderer, &rect );
            if ( _textTexture != NULL ) {
                renderText( renderer, clip, angle );
            }
        }
};

class MainMenu;

class GameOverMenu : public Scene {
    public:
        GameOverMenu() : GameOverMenu( 0 ) {}

        GameOverMenu( int score ) : Scene() {
            _score = score;
            _nextScene = NULL;
            _closeWindow = new bool( false );
            _playAgain = new bool( false );
        }

        ~GameOverMenu() {
            delete _closeWindow;
            delete _playAgain;
            TTF_CloseFont( _gameOverFont );
            TTF_CloseFont( _scoreFont );
            TTF_CloseFont( _buttonFont );
        }

        bool loadFonts() {
            _gameOverFont = TTF_OpenFont( FONT_PATH.c_str(), 32 );
    		if( _gameOverFont == NULL ) {
        		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
				return false;
    		}

            _scoreFont = TTF_OpenFont( FONT_PATH.c_str(), 28 );
    		if( _scoreFont == NULL ) {
        		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
				return false;
    		}

            _buttonFont = TTF_OpenFont( FONT_PATH.c_str(), 16 );
    		if( _buttonFont == NULL ) {
        		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
				return false;
    		}

            return true;
        }

        bool build( Panel* panel, SDL_Renderer* renderer ) override {
            if ( !loadFonts() ) { return false; }

            SDL_Color color = { 0, 255, 0, 255 };
            panel->setDisplayMode( new Anchor() );
            
            Texture* gameOverText = new Texture( Vector2D<float>( 0.6f, 0.2f ) );
            gameOverText->setAnchorLocation( NORTH );
            gameOverText->loadText( renderer, "Game Over", _gameOverFont, color );

            Texture* scoreText = new Texture( Vector2D<float>( 0.4f, 0.15f ) );
            scoreText->setAnchorLocation( CENTER );
            scoreText->loadText( renderer, "Score: " + std::to_string( _score ), _scoreFont, color );

            SnakeButton* playAgainButton = new SnakeButton( Vector2D<float>( 0.2f, 0.1f ), Vector2D<float>( 0.1f, 0.1f ) );
            playAgainButton->setAnchorLocation( SOUTHWEST );
            playAgainButton->setText( renderer, "Play Again", _buttonFont, { 0, 160, 0, 255 } );
            playAgainButton->addActionListener( new FlipAction( _playAgain ) );
            panel->addMouseListener( playAgainButton );

            SnakeButton* quitButton = new SnakeButton( Vector2D<float>( 0.2f, 0.1f ), Vector2D<float>( 0.1f, 0.1f ) );
            quitButton->setAnchorLocation( SOUTHEAST );
            quitButton->setText( renderer, "Quit", _buttonFont, { 0, 160, 0, 255 } );
            quitButton->addActionListener( new FlipAction( _closeWindow ) );
            panel->addMouseListener( quitButton );            

            panel->addComponent( gameOverText );
            panel->addComponent( scoreText );
            panel->addComponent( playAgainButton );
            panel->addComponent( quitButton );

            return true;
        }

        bool loop() override;

        Scene* getNextScene() { return _nextScene; }

    
    private:
        Scene* _nextScene;
        int _score;

        bool* _closeWindow;
        bool* _playAgain;

        TTF_Font* _gameOverFont;
        TTF_Font* _scoreFont;
        TTF_Font* _buttonFont;
};

class SnakeGame : public Scene {
    public:
        SnakeGame() : Scene() {
            srand(time(NULL));
            _yBlocks = 30;
	        _xBlocks = 50;
            _lastTicks = SDL_GetTicks();
            _ticks = 0;
        }

        ~SnakeGame() {
            TTF_CloseFont( _font );
        }

        int getRandomPosition( int blocks ) {
            return rand() % blocks;
        }

        int getBlockSize( Vector2D<int> size ) {
			int xBlockSize = ( size.getFirst() ) / _xBlocks;
			int yBlockSize = ( size.getSecond() ) / _yBlocks;
			return xBlockSize < yBlockSize ? xBlockSize : yBlockSize;
		}

        void resizeGameBoard() {
            int blockSize = getBlockSize( _gamePanel->getRenderSize() );
            _snake->setSize( Vector2D<int>( blockSize, blockSize ) );
            _food->setSize( Vector2D<int>( blockSize, blockSize ) );
            _gameBoard->setSize( Vector2D<int>( _xBlocks * blockSize, _yBlocks * blockSize ) );
        }

        Scene* getNextScene() {
            return new GameOverMenu( _score );
        }

        bool build( Panel* panel, SDL_Renderer* renderer ) override {
            panel->setDisplayMode( new Relative() );

            Panel* topPanel = new Panel( Vector2D<float>( 1.0f, 0.2f ) );
            topPanel->setDisplayMode( new Anchor() );
            topPanel->setBackgroundColor( { 0, 0, 0, 255 } );

            _font = TTF_OpenFont( FONT_PATH.c_str(), 24 );
    		if( _font == NULL ) {
        		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
				return false;
    		}

            _score = 0;
            _scoreTexture = new Texture( Vector2D<float>( 0.3f, 0.6f ) );
            _scoreTexture->loadText( renderer, "Score: " + std::to_string( _score ), _font, { 0, 255, 0, 255 } );
            _scoreTexture->setAnchorLocation( CENTER );

            topPanel->addComponent( _scoreTexture );


            _gamePanel = new Panel( Vector2D<float>( 1.0f, 0.8f ) );
            _gamePanel->setDisplayMode( new Anchor() );
            _gamePanel->setBackgroundColor( { 50, 50, 50, 255 } );

            _gameBoard = new Panel( Vector2D<int>( 0, 0 ) );
            _gameBoard->setBackgroundColor( { 0, 0, 0, 255 } );
            _gameBoard->setAnchorLocation( CENTER );

            Texture* snakeSprites = new Texture();
	        snakeSprites->load( renderer, SPRITE_PATH );

            _snake = new Snake( Vector2D<int>( 0, 0 ), Vector2D<int>( 1, 1 ) );
	        _snake->setTexture( snakeSprites );
	        _food = new Food( Vector2D<int>( 0, 0 ), Vector2D<int>( getRandomPosition( _xBlocks ), getRandomPosition( _yBlocks ) ) );
	        _food->setTexture( snakeSprites );

            _gameBoard->addComponent( _snake );
            _gameBoard->addComponent( _food );

            _gamePanel->addComponent( _gameBoard );


            panel->addComponent( topPanel );
            panel->addComponent( _gamePanel );
            
            panel->addKeyListener( _snake );
            
            _renderer = renderer; 

            return true;
        }

        bool loop() override {
            resizeGameBoard();

		    Uint32 curTicks = SDL_GetTicks();
		    _ticks += curTicks - _lastTicks;
		    _lastTicks = curTicks;

		    if ( _ticks >= ticksPerFrame ) {
		    	int movements = _ticks / ticksPerFrame;
		    	for ( int i = 0; i < movements; ++i ) {
		    		_snake->move();
		    		_ticks -= ticksPerFrame;

                    int snakeX = _snake->getGamePosition().getFirst();
                    int snakeY = _snake->getGamePosition().getSecond();
		    		if ( snakeX < 0 || snakeX > _xBlocks-1 ) {
		    			return false;
		    		} else if ( snakeY < 0 || snakeY > _yBlocks-1 ) {
                        return false;
		    		} else if ( _snake->didCollideWithBody( Vector2D<int>( snakeX, snakeY ) ) ) {
                        return false;
		    		}

		    		if ( _snake->getGamePosition().equals( _food->getGamePosition() ) ) {
		    			_snake->grow();
		    			++_score;
		    			_scoreTexture->loadText( _renderer, "Score: " + std::to_string( _score ), _font, { 0, 255, 0, 255 } );
		    			int newX = 0;
		    			int newY = 0;
		    			do {
		    				newX = getRandomPosition( _xBlocks );
		    				newY = getRandomPosition( _yBlocks );
		    			} while ( _snake->didCollide( Vector2D<int>( newX, newY ) ) );
    
		    			_food->setGamePosition( Vector2D<int>( newX, newY ) );
		    		}
		    	}
		    }

            return true;
        }
    private:
        Snake* _snake;
        Food* _food;

        Panel* _gamePanel;
        Panel* _gameBoard;

        TTF_Font* _font;
        Texture* _scoreTexture;

        int _xBlocks;
        int _yBlocks;

        int _score;

        int _ticks;
        Uint32 _lastTicks;
        const int ticksPerFrame = 100;

        SDL_Renderer* _renderer;
};

class MainMenu : public Scene {
    public:
        MainMenu() : Scene() {
            _endScene = new bool( false );
        }

        ~MainMenu() {
            TTF_CloseFont( _font );
            TTF_CloseFont( _titleFont );
            delete _endScene;
        }

        bool build( Panel* panel, SDL_Renderer* renderer ) {
            _font = TTF_OpenFont( FONT_PATH.c_str(), 16 );
    		if( _font == NULL ) {
        		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
				return false;
    		}

            _titleFont = TTF_OpenFont( FONT_PATH.c_str(), 32 );
    		if( _titleFont == NULL ) {
        		std::cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << std::endl;
				return false;
    		}

            panel->setDisplayMode( new Anchor() );
            panel->setBackgroundColor( { 0, 0, 0, 255 } );
            
            SnakeButton* playButton = new SnakeButton( Vector2D<float>( 0.2, 0.1f ), Vector2D<float>( 0.0f, 0.1f ) );
            playButton->setText( renderer, "Play", _font, { 0, 160, 0, 255 } );
            playButton->setAnchorLocation( SOUTH );
            playButton->addActionListener( new FlipAction( _endScene ) );

            Texture* title = new Texture( Vector2D<float>( 0.5f, 0.2f ), Vector2D<float>( 0.0f, 0.1f ) );
            title->setAnchorLocation( NORTH );
            title->loadText( renderer, "Snake", _titleFont, { 0, 255, 0, 255 } );

            panel->addMouseListener( playButton );
            panel->addComponent( playButton );
            panel->addComponent( title );

            return true;
        }


        bool loop() {
            return !(*_endScene);
        }

        Scene* getNextScene() {
            return new SnakeGame();
        }

    private:
        bool* _endScene;
        TTF_Font* _font;
        TTF_Font* _titleFont;
};

bool GameOverMenu::loop() {
    if ( *_closeWindow ) { return false; }
    if ( *_playAgain ) {
        _nextScene = new MainMenu();
        return false;
    }
    return true;
}

int main( int argc, char* args[] ) {
	Engine* engine = new Engine();
	Window* window = new Window( "Snake", Vector2D<int>( 1080, 720 ) );
	window->setScene( new MainMenu() );
	window->display();

	return 0;
}