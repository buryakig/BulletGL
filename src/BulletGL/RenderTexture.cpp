#include "RenderTexture.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace BulletGL
{

	//RenderTexture::RenderTexture();

	RenderTexture::RenderTexture(int w, int h, int depth, unsigned format,  unsigned graphicsFormat)
		: Texture(w, h)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_RGBA32F, width, height);
		glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		//glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
		
		glCreateRenderbuffers(1, &rboDepth);
		glNamedRenderbufferStorage(rboDepth, GL_DEPTH_COMPONENT32F, width, height);
		
		glCreateFramebuffers(1, &FBO);
		glNamedFramebufferTexture(FBO, GL_COLOR_ATTACHMENT0, id, 0);
		glNamedFramebufferRenderbuffer(FBO, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	
		if (glCheckNamedFramebufferStatus(FBO, GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "FrameBuffer failed" << std::endl;
	}

	RenderTexture::~RenderTexture()
	{
		glDeleteTextures(1, &id);
		glDeleteRenderbuffers(1, &rboDepth);
		glDeleteFramebuffers(1, &FBO);
	}
}