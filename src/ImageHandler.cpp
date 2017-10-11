#include "ImageHandler.h"

Image_Handler::Image_Handler() { }

Mat Image_Handler::crop( Mat image, int x, int y, int width, int height, std::string name ) {

	Mat _roi(image, Rect( x, y, width, height ) );

	Mat cropped_img;

	_roi.copyTo( cropped_img );

	imwrite( name + ".jpg", cropped_img);

	return cropped_img;
}

void Image_Handler::join( Mat& m_image, Mat& s_image, int x_pos, int y_pos ) {
	s_image.copyTo( m_image( Rect( x_pos, y_pos, s_image.cols, s_image.rows ) ) );
}

void Image_Handler::split_image( Mat& image, int parts ) {

	int n = std::sqrt( parts ); // partes que se dividen en cada lado de la imagen.

	int curr_x = 0; int curr_y = 0; int new_width = std::floor( image.cols / n ); double new_height = std::floor( image.rows / n ); int name_ctr = 0;

	for( int i = 0; i < n; i++ ) {
		for( int j = 0; j < n; j++ ) {
			crop( image, curr_x, curr_y, new_width, new_height, std::to_string( name_ctr ) );
			curr_x += new_width;
			name_ctr++;
		}
		curr_x = 0;
		curr_y += new_height;
	}

	d_container.parts_width = new_width;
	d_container.parts_height = new_height;
	d_container.total_parts = parts;
}

Mat Image_Handler::create_empty_img( int width, int height, std::string name ) {
	Mat empty_img( height, width, CV_8UC3, Scalar( 0,0,0 ) );
	imwrite( name + ".jpg", empty_img );
	return empty_img;
}

Mat Image_Handler::join_parts( ) {

	std::vector< std::pair<int,int> > _coords;
	std::vector<int> used_coords;

	int curr_x = 0; int curr_y = 0;

	int n = std::sqrt( d_container.total_parts );

	for( int i = 0; i < n; i++ ) {
		for( int j = 0; j < n; j++ ) {
			_coords.push_back( std::pair<int,int>( curr_x, curr_y ) );
			curr_x += d_container.parts_width;
		}
		curr_x = 0;
		curr_y += d_container.parts_height;
	}

	int image_ctr = 0;
	Mat _canvas = create_empty_img( d_container.base_image.cols, d_container.base_image.rows );

	while( used_coords.size() != _coords.size() ) {
		int r_index = util::random_int( 0, _coords.size() );
		if( !util::contains_int( used_coords, r_index ) ) {
			Mat curr_img = imread( std::to_string( image_ctr ) + ".jpg", IMREAD_COLOR );
			std::pair<int,int> pos = _coords[r_index];
			join( _canvas, curr_img, pos.first, pos.second );
			used_coords.push_back( r_index );
			image_ctr++;
		}
	}

	return _canvas;
}

void Image_Handler::set_base( Mat image ) {
	d_container.base_image = image;
}

void Image_Handler::create_img( std::string path, Mat img ) {
	imwrite( path, img );
}

bool Image_Handler::compare( Mat base, Mat other ) {
	for( int i = 0; i < base.rows; i++ ) {
		for( int j = 0; j < base.cols; j++ ) {
			auto R_base = base.at<Vec3b>( i,j )[0];
			auto R_other = other.at<Vec3b>( i,j )[0];
			auto G_base = base.at<Vec3b>( i,j )[1];
			auto G_other = other.at<Vec3b>( i,j )[1];
			auto B_base = base.at<Vec3b>( i,j )[2];
			auto B_other = other.at<Vec3b>( i,j )[2];
			if( R_base != R_other && G_base != G_other && B_base != B_other ) {
				return false;
			}
		}
	}
	return true;
}

Mat& Image_Handler::base() {
	return d_container.base_image;
}

Image_Handler::~Image_Handler() { }

