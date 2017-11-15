#ifndef GUIAPPLICATION_H_
#define GUIAPPLICATION_H_
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 600
#include <SFML/Graphics.hpp>
#include "../Jigsaw.h"
#include "../ImageHandler.h"
#include "AssetManager.h"
#include <future>

typedef std::vector<sf::Sprite> Sprites;

class GUIApplication {
public:
	GUIApplication( Image_Handler handler );
	void run();
	void run_algorithm();
	void load_images();
	virtual ~GUIApplication();
private:
	void init();
	void handle_events( const sf::Event& e );
	void draw();
	void update_fittest();
	void check_button( sf::Vector2i mouse_pos );
private:
	sf::RenderWindow _window;
	Jigsaw _jigsaw;
	Asset_Manager asset_manager;
	sf::RectangleShape play_button;
	sf::RectangleShape pause_button;
	sf::RectangleShape stop_button;
	sf::Text _text[2];
	Sprites _fittest;
	std::future<void> _updater;
};

#endif /* GUIAPPLICATION_H_ */
