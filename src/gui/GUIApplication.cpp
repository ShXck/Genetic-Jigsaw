#include "GUIApplication.h"

GUIApplication::GUIApplication() {
	init();
}

void GUIApplication::run() {

	while( m_window.isOpen() ) {

		sf::Event _event;

		while( m_window.pollEvent( _event ) ) {
			switch( _event.type ) {
				case sf::Event::Closed: {
					m_window.close();
					break;
				}
			}
		}

		m_window.clear();
		// window draw something.
		m_window.display();
	}

}

void GUIApplication::init() {
	m_window.create( { WINDOW_WIDTH, WINDOW_HEIGHT }, "Genetic Jigsaw", sf::Style::Close );
	m_window.setFramerateLimit( 60 );
}

GUIApplication::~GUIApplication() { }

