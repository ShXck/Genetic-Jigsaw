#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "gui/GUIApplication.h"
#include "ImageHandler.h"
#include "GJigsaw.h"
#include "util.h"

using namespace cv;


int main() {


	Image_Handler h;

	std::string img_name("assets/test.jpg");

	Mat image;

	image = imread( img_name.c_str(), IMREAD_COLOR );

	if ( image.empty() ) {
		std::cout << "COULD NOT OPEN" << std::endl;
		return -1;
	}

	h.set_base( image );

	h.split_image( image, 16 );

	Mat r;

	for( int i = 0; i < 10; i++ ) {
		r = h.join_parts();
		h.create_img( "sol" + std::to_string( i ) + ".jpg", r );
		//h.create_img( "sol0.jpg", r );
	}

	Coords& _coords = h.coords();
	float _result = 0.0f;

	Mat curr_block;
	Mat individual;
	Mat sol_block;

	for( int j = 0; j < 10; j++ ) {
		individual = imread( "sol" + std::to_string( j ) + ".jpg", IMREAD_COLOR );;
		for( unsigned int i = 0; i < _coords.size(); i++ ) {
			auto curr_cords = _coords[i];

			Mat curr_block = h.crop( image, curr_cords.first,
					curr_cords.second, h.img_details().parts_width
					,h.img_details().parts_height, "tmp1" );

			Mat sol_block = h.crop( individual, curr_cords.first,
					curr_cords.second, h.img_details().parts_width
					,h.img_details().parts_height, "tmp2" );

			if( h.compare( curr_block, sol_block ) ) {
				_result += 10.0f;
			}

			if( _result == 160.f ) {
				std::cout << "RESULT!" << std::endl;
			}
		}

		std::cout << "RESULT: " << j << " " << _result << std::endl;
		_result = 0.0f;
	}

	namedWindow("TEST WINDOW", WINDOW_AUTOSIZE);
	imshow("TEST WINDOW", image );

	waitKey(0);

	return 0;
}


