#pragma once

#include "FBO.h"
#include "Image.h"

namespace PAG
{
	class FBOScreenshot : public FBO
	{
	protected:
		GLuint _multisampledFBO, _colorBufferID;
		GLuint _mColorBufferID, _mDepthBufferID;

	public:
		FBOScreenshot(const uint16_t width, const uint16_t height);
		virtual ~FBOScreenshot();

		virtual GLuint getId() const { return _multisampledFBO; }
		PAG::Image* getImage() const;

		virtual void bindFBO();
		virtual void modifySize(const uint16_t width, const uint16_t height);
		void saveImage(const std::string& filename);
	};
}



