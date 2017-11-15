#include "GUIApplication.h"

GUIApplication::GUIApplication( Image_Handler handler ) : _jigsaw( handler ) {
	init();
	_updater = std::async( std::launch::async, &GUIApplication::update_fittest, this );
}

void GUIApplication::run() {

	while( _window.isOpen() ) {

		sf::Event _event;

		while( _window.pollEvent( _event ) ) {
			handle_events( _event );
		}

		_text[0].setString( "Generacion: " + std::to_string( _jigsaw.generation() ) );

		_window.clear();
		draw();
		_window.display();
	}
}

void GUIApplication::run_algorithm() {

	_jigsaw.start_population();

	std::thread t( [this]() {
		_jigsaw.run();
	});
	t.detach();
}

void GUIApplication::init() {

	_window.create( { WINDOW_WIDTH, WINDOW_HEIGHT }, "Genetic Jigsaw", sf::Style::Close );
	_window.setFramerateLimit( 60 );

	play_button.setTexture( &asset_manager.get_texture( "play" ) );
	pause_button.setTexture( &asset_manager.get_texture( "pause" ) );
	stop_button.setTexture( &asset_manager.get_texture( "stop" ) );

	play_button.setSize( sf::Vector2f( 75.f, 75.f ) );
	pause_button.setSize( sf::Vector2f( 85.f, 85.f ) );
	stop_button.setSize( sf::Vector2f( 75.f, 75.f ) );

	play_button.setPosition( sf::Vector2f( 465.f, 450.f ) );
	pause_button.setPosition( sf::Vector2f( 315.f, 450.f ) );
	stop_button.setPosition( sf::Vector2f( 615.f, 450.f ) );

	_text[0].setFont( asset_manager.get_font( "default" ) );
	_text[0].setFillColor( sf::Color::White );
	_text[0].setPosition( 150.f, 420.f );
	_text[0].setString( "Generacio: " + std::to_string( _jigsaw.generation() ) );
	_text[0].setCharacterSize( 20 );

	_text[1].setFont( asset_manager.get_font( "default" ) );
	_text[1].setFillColor( sf::Color::Blue );
	_text[1].setPosition( 300.f, 25.f );
	_text[1].setString( "Genetic Jigsaw" );
	_text[1].setCharacterSize( 50 );
}

void GUIApplication::load_images() {

	asset_manager.load_fittest();

	float curr_x = 0.f; float y_pos = 125.f;

	for( int i = 0; i < 3; i++ ) {
		_fittest.push_back( sf::Sprite( asset_manager.get_texture( "fit" + std::to_string( i ) ) ) );
		_fittest[i].setPosition( curr_x, y_pos );
		curr_x += 350.f;
	}
}

void GUIApplication::update_fittest() {
	while( true ) {
		std::this_thread::sleep_for( std::chrono::seconds(2) );
		asset_manager.update_fittest();
		for( unsigned int i = 0; i < _fittest.size(); i++ ) {
			_fittest[i].setTexture( asset_manager.get_texture( "fit" + std::to_string( i ) ) );
		}
	}
}

void GUIApplication::check_button( sf::Vector2i mouse_pos ) {

	sf::Vector2f fl_pos( static_cast<float>( mouse_pos.x ), static_cast<float>( mouse_pos.y ) );

	if( play_button.getGlobalBounds().contains( fl_pos ) ) {
		std::cout << "PLAY!" << std::endl;
		if( _jigsaw.is_stopped() ) {
			_jigsaw.restart();
			run_algorithm();
		} else if( _jigsaw.is_paused() ) {
			_jigsaw.continue_run();
		}
	}

	if( pause_button.getGlobalBounds().contains( fl_pos ) ) {
		std::cout << "PAUSE!" << std::endl;
		if( !_jigsaw.is_paused() ) {
			_jigsaw.pause();
		}
	}

	if( stop_button.getGlobalBounds().contains( fl_pos ) ) {
		std::cout << "STOP!" << std::endl;
		if( !_jigsaw.is_stopped() ) {
			_jigsaw.stop();
		}
	}
}

void GUIApplication::handle_events( const sf::Event& e ) {

	switch( e.type ) {
		case sf::Event::Closed: {
			_window.close();
			break;
		}

		case sf::Event::MouseButtonReleased: {
			sf::Vector2i mouse_pos = sf::Mouse::getPosition( _window );
			check_button( mouse_pos );
			break;
		}
	}
}

void GUIApplication::draw() {
	_window.draw( play_button );
	_window.draw( pause_button );
	_window.draw( stop_button );

	for( auto& spr : _fittest ) {
		_window.draw( spr );
	}

	for( int i = 0; i < 2; i++ ) {
		_window.draw( _text[i] );
	}
}

GUIApplication::~GUIApplication() { }

