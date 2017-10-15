#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "gui/GUIApplication.h"
#include "ImageHandler.h"
#include "Jigsaw.h"
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

	h.set_img_cords();

	Jigsaw _jig( h );

	_jig.start_population();
	_jig.run();

	/*Mat sol_1 = imread( "sol0.jpg", IMREAD_COLOR );
	Mat sol_2 = imread( "sol1.jpg", IMREAD_COLOR );

	Individual a( sol_1, 0.0f );
	Individual b( sol_2, 0.0f );

	Mat off = _jig.crossover( a, b )._solution;

	imshow( "OFFSPRING", off );
	imshow( "A", sol_1 );
	imshow( "B", sol_2 );*/

	/*Mat r;

	for( int i = 0; i < 10; i++ ) {
		r = h.join_parts();
		h.create_img( "sol" + std::to_string( i ) + ".jpg", r );
		//h.create_img( "sol0.jpg", r );
	}*/

	namedWindow("TEST WINDOW", WINDOW_AUTOSIZE);
	imshow("TEST WINDOW", image );

	waitKey(0);

	return 0;
}


