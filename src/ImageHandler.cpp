#include "ImageHandler.h"

Image_Handler::Image_Handler() { }

Mat Image_Handler::crop( Mat image, int x, int y, int width, int height, std::string name ) {

	Mat _roi(image, Rect( x, y, width, height ) );

	Mat cropped_img;

	_roi.copyTo( cropped_img );

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
	return empty_img;
}

Mat Image_Handler::create_empty_img( std::string name ) {
	Mat empty_img( d_container.base_image.rows,  d_container.base_image.cols, CV_8UC3, Scalar( 0,0,0 ) );
	return empty_img;
}

Mat Image_Handler::join_parts( ) {

	std::vector<int> used_coords;

	int image_ctr = 0;
	Mat _canvas = create_empty_img( d_container.base_image.cols, d_container.base_image.rows );

	while( used_coords.size() != _coords.size() ) {
		int r_index = util::random_int( 0, _coords.size() - 1 );
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

bool Image_Handler::compare( const Mat& base, const Mat& other ) {

	if( base.rows != other.rows || base.cols != other.cols ) return false;

	double _error = norm( base, other, CV_L2 );

	double _similarity = _error / (double)( base.rows * base.cols );
	if( _similarity < 0.09 ) return true;

	return false;
}

coord* Image_Handler::position_of( Mat base, Mat& cropped ) {
	for( auto& coord : _coords ) {
		Mat base_roi = crop( base, coord.first, coord.second, d_container.parts_width, d_container.parts_height, "tmp5" );
		if( compare( base_roi, cropped ) ) {
			return &coord;
		}
	}
	return nullptr;
}

bool Image_Handler::contains( Mat base, Mat& cropped ) {
	for( auto& coord : _coords ) {
		Mat base_roi = crop( base, coord.first, coord.second, d_container.parts_width, d_container.parts_height, "tmp5" );
		if( compare( base_roi, cropped ) ) {
			return true;
		}
	}
	return false;
}

void Image_Handler::switch_parts( coord from, coord to, Mat& img ) {
	Mat p_from = crop( img, from.first, from.second, d_container.parts_width, d_container.parts_height, "tmp5" );
	Mat p_to = crop( img, to.first, to.second, d_container.parts_width, d_container.parts_height, "tmp6" );

	join( img, p_from, to.first, to.second );
	join( img, p_to, from.first, from.second );
}

void Image_Handler::set_img_cords() {
	if( _coords.empty() ) {
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
	}
}

Mat& Image_Handler::base() {
	return d_container.base_image;
}

Coords& Image_Handler::coords() {
	return _coords;
}

Data_Container& Image_Handler::img_details() {
	return d_container;
}

Image_Handler::~Image_Handler() { }

