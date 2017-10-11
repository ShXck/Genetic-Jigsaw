#ifndef GJIGSAW_H_
#define GJIGSAW_H_
#include "ImageHandler.h"

class G_Jigsaw {
public:
	G_Jigsaw( int parts );
	void start();
	virtual ~G_Jigsaw();
private:
	void init();
private:
	Image_Handler m_handler;
	std::vector<std::string> m_images;
	int working_parts;
};

#endif /* GJIGSAW_H_ */
