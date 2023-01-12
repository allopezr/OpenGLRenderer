#include "stdafx.h"
#include "FBO.h"

PAG::FBO::FBO(const uint16_t width, const uint16_t height) :
	_id(0), _size(width, height)
{
}

PAG::FBO::~FBO()
{
	glDeleteFramebuffers(1, &_id);
}

void PAG::FBO::modifySize(const uint16_t width, const uint16_t height)
{
	_size = vec2(width, height);
}

void PAG::FBO::checkFBOstate()
{
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {
		throw std::runtime_error("FBO could not be created!");
	}
}

void PAG::FBO::threadedWriteImage(std::vector<GLubyte>* pixels, const std::string& filename, const uint16_t width, const uint16_t height)
{
	Image* image = new Image(pixels->data(), width, height, 4);
	image->saveImage(filename);
	delete pixels;
	delete image;
}
