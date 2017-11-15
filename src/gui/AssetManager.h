#ifndef GUI_ASSETMANAGER_H_
#define GUI_ASSETMANAGER_H_
#include <map>
#include <SFML/Graphics.hpp>
#include <iostream>

class Asset_Manager {
public:
	Asset_Manager();
	sf::Texture& get_texture( std::string key );
	sf::Font& get_font( std::string key );
	void load_fittest();
	void update_fittest();
	virtual ~Asset_Manager();
private:
	std::map<std::string, sf::Texture> _textures;
	std::map<std::string, sf::Font> _fonts;
};

#endif /* GUI_ASSETMANAGER_H_ */
