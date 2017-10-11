#ifndef GUIAPPLICATION_H_
#define GUIAPPLICATION_H_
#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 600
#include <SFML/Graphics.hpp>

class GUIApplication {
public:
	GUIApplication();
	void run();
	virtual ~GUIApplication();
private:
	void init();
private:
	sf::RenderWindow m_window;
};

#endif /* GUIAPPLICATION_H_ */
