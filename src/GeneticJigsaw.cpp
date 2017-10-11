#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "gui/GUIApplication.h"
#include "ImageHandler.h"

using namespace cv;

int main() {

	/*GUIApplication app;
	app.run();*/

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

	Mat r = h.join_parts();

	h.create_img( "sols.jpg", r );

	namedWindow("TEST WINDOW", WINDOW_AUTOSIZE);
	imshow("TEST WINDOW", r );

	waitKey(0);

	return 0;
}


