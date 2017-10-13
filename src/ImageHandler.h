#ifndef IMAGEHANDLER_H_
#define IMAGEHANDLER_H_
#include <opencv2/core/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include "util.h"
#include <thread>

using namespace cv;

struct Data_Container {
	int parts_width;
	int parts_height;
	int total_parts;
	Mat base_image;
};

typedef std::vector<std::pair<int,int>> Coords;

class Image_Handler {
public:
	Image_Handler();
	/**
	 * Corta una pieza de una imagen.
	 * @param image la imagen a cortar.
	 * @param x la posición en x donde se corta.
	 * @param y la posición en y donde se corta.
	 * @param width el ancho del corte.
	 * @param height la altura del corte.
	 * @return la pieza de imagen cortada.
	 */
	Mat crop( Mat image, int x, int y, int width, int height, std::string name = "cropped_img" );
	/**
	 * Une una imagen con otra.
	 * @param m_image la imagen principal.
	 * @param s_image la imagen secundaria.
	 * @param x_pos la posición en x donde se inserta la imagen.
	 * @param y_pos la posición en y donde se inserta la imagen.
	 */
	void join( Mat& m_image, Mat& s_image, int x_pos, int y_pos );
	/**
	 * Descompone una imagen en la cantidad de partes dada.
	 * @param image la imagen a descomponer.
	 * @param parts el número de partes que se quiere.
	 */
	void split_image( Mat& image, int parts );

	/**
	 * Crea una imagen vacía con fondo negro.
	 * @param width el ancho de la imagen.
	 * @param height la altura de la imagen.
	 * @return la imagen vacía construida.
	 */
	Mat create_empty_img( int width, int height, std::string name = "empty" );

	/**
	 * Junta aleatoriamente las partes generadas en una imagen vacía.
	 * @param empty_pic la imagen vacía.
	 * @param part_width el ancho de cada parte.
	 * @param part_height el largo de cada partes.
	 * @param n el número de partes por lado de la imagen.
	 * @return la imagen terminada.
	 */
	Mat join_parts( );

	/**
	 * Asigna la imagen base con la que se trabaja.
	 * @param image la imagen base.
	 */
	void set_base( Mat image );

	/**
	 * Crea una imagen.
	 * @param path el nombre y el espacio donde se guarda la imagen.
	 * @param img la imagen que se quiere crear.
	 */
	void create_img( std::string path, Mat img );

	/**
	 * Compara dos imágenes y determina si son iguales.
	 * @param base la imagen base.
	 * @param sec la imagen que se quiere comparar.
	 * @return si las imágenes son iguales o no.
	 */
	bool compare( const Mat& base, const Mat& other );

	/**
	 * @return La imagen base u original.
	 */
	Mat& base();

	/**
	 * @return Las posiciones que se pueden manejar en la imagen.
	 */
	Coords& coords();

	/**
	 * @return Los detalles de la imagen base.
	 */
	Data_Container& img_details();

	virtual ~Image_Handler();

private:
	Data_Container d_container;
	Coords _coords;
};

#endif /* IMAGEHANDLER_H_ */
