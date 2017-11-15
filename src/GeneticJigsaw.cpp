#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "gui/GUIApplication.h"
#include "ImageHandler.h"
#include "Jigsaw.h"
#include "util.h"
#include <thread>

using namespace cv;

int main() {

	Image_Handler image_handler;

	std::string img_name("assets/test.jpg");

	Mat image;

	image = imread( img_name.c_str(), IMREAD_COLOR );

	if ( image.empty() ) {
		std::cout << "COULD NOT OPEN" << std::endl;
		return -1;
	}

	image_handler.set_base( image );

	std::string _parts;
	int int_parts;

	while( true ) {

		std::cout << "Número de partes: ";
		std::getline( std::cin, _parts );
		int_parts = std::stoi( _parts );
		if( int_parts == 4 || int_parts == 9 || int_parts == 16 ) {
			std::cout << std::endl;
			break;
		} else {
			int_parts = 0;
		}
	}

	image_handler.split_image( image, int_parts );

	image_handler.set_img_cords();

	GUIApplication gui_app( image_handler );
	gui_app.load_images();
	gui_app.run();

	return 0;
}


