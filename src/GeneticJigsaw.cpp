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

	Mat a_s = imread( "sol1.jpg", IMREAD_COLOR );
	Mat b_s = imread( "sol2.jpg", IMREAD_COLOR );

	G_Jigsaw jig( h );
	Individual a( a_s, 0.0f );
	Individual b( b_s, 0.0f );

	float af = jig.fitness_of( a._solution, a.s_genes );
	float bf = jig.fitness_of( b._solution, b.s_genes );

	std::cout << "FIT A: " << af << " FIT B: " << bf << std::endl;


	namedWindow("TEST WINDOW", WINDOW_AUTOSIZE);
	imshow("TEST WINDOW", image );
	imshow("A", a_s );
	imshow("B", b_s );

	waitKey(0);

	return 0;
}


