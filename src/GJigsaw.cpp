#include "GJigsaw.h"

G_Jigsaw::G_Jigsaw( int parts ) : working_parts( parts ) { }

void G_Jigsaw::start() { }

void G_Jigsaw::init() {
	for( int i = 0; i < working_parts; i++ ) {
		m_images.push_back( std::to_string( i ) + ".jpg" );
	}
}

G_Jigsaw::~G_Jigsaw() { }

