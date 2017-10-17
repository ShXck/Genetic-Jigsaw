#include "GUIApplication.h"

GUIApplication::GUIApplication( Image_Handler handler ) : _jigsaw( handler ) {
	init();
}

void GUIApplication::run() {

	while( _window.isOpen() ) {

		sf::Event _event;

		while( _window.pollEvent( _event ) ) {
			handle_events( _event );
		}
		_window.clear();
		draw();
		_window.display();
	}

}

void GUIApplication::init() {
	_window.create( { WINDOW_WIDTH, WINDOW_HEIGHT }, "Genetic Jigsaw", sf::Style::Close );
	_window.setFramerateLimit( 60 );
}

void GUIApplication::handle_events( const sf::Event& e ) {
	switch( e.type ) {
		case sf::Event::Closed: {
			_window.close();
			break;
		}
	}

	switch( e.key.code ) {
		case sf::Mouse::Left: {
			std::cout << "LEFT!" << std::endl;
			break;
		}
	}
}

void GUIApplication::draw() {

}

GUIApplication::~GUIApplication() { }

