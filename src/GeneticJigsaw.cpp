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

	GUIApplication gui_app( h );
	gui_app.run();


	/*Jigsaw _jig( h );

	_jig.start_population();
	_jig.run();*/

	namedWindow("TEST WINDOW", WINDOW_AUTOSIZE);
	imshow("TEST WINDOW", image );

	waitKey(0);

	return 0;
}


