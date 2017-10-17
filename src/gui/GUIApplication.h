#ifndef GUIAPPLICATION_H_
#define GUIAPPLICATION_H_
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 600
#include <SFML/Graphics.hpp>
#include "../Jigsaw.h"
#include "../ImageHandler.h"

class GUIApplication {
public:
	GUIApplication( Image_Handler handler );
	void run();
	virtual ~GUIApplication();
private:
	void init();
	void handle_events( const sf::Event& e );
	void draw();
private:
	sf::RenderWindow _window;
	Jigsaw _jigsaw;
};

#endif /* GUIAPPLICATION_H_ */
