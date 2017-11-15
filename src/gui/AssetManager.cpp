#include "AssetManager.h"

Asset_Manager::Asset_Manager() {

	sf::Texture play_button;
	play_button.loadFromFile( "assets/play.png");
	_textures.insert( std::pair<std::string, sf::Texture>( "play", play_button ) );

	sf::Texture pause_button;
	pause_button.loadFromFile( "assets/pause.png");
	_textures.insert( std::pair<std::string, sf::Texture>( "pause", pause_button ) );

	sf::Texture stop_button;
	stop_button.loadFromFile( "assets/stop.png");
	_textures.insert( std::pair<std::string, sf::Texture>( "stop", stop_button ) );

	sf::Font default_font;
	default_font.loadFromFile( "assets/DroidSans.ttf");
	_fonts.insert( std::pair<std::string, sf::Font>( "default", default_font ) );
}

sf::Texture& Asset_Manager::get_texture( std::string key ) {
	return _textures.at( key );
}

sf::Font& Asset_Manager::get_font( std::string key ) {
	return _fonts.at( key );
}

void Asset_Manager::load_fittest() {

	sf::Texture _fit0;
	_fit0.loadFromFile( "fit0.jpg");
	_textures.insert( std::pair<std::string, sf::Texture>( "fit0", _fit0 ) );

	sf::Texture _fit1;
	_fit1.loadFromFile( "fit1.jpg");
	_textures.insert( std::pair<std::string, sf::Texture>( "fit1", _fit1 ) );

	sf::Texture _fit2;
	_fit2.loadFromFile( "fit2.jpg");
	_textures.insert( std::pair<std::string, sf::Texture>( "fit2", _fit2 ) );
}

void Asset_Manager::update_fittest() {
	for( int i = 0; i < 3; i++ ) {
		sf::Texture curr_ind;
		std::string _img( "fit" + std::to_string( i ) + ".jpg" );
		std::string _key( "fit" + std::to_string( i ) );
		curr_ind.loadFromFile( _img );
		_textures[ _key ] = curr_ind;
	}
}

Asset_Manager::~Asset_Manager() { }

