#ifndef TEXTURE_H
#define TEXTURE_H

#include <Util\Common.h>
#include <Magick++.h>

class Texture2D
{
public:
	Texture2D(std::string fileName);
	~Texture2D();

	bool load();
    void bind(GLenum TextureUnit);

	size_t width() const { return this->_pImage->columns(); }
	size_t height() const { return this->_pImage->rows(); }

private:
	std::string _fileName;
	// texture object for opengl
	GLenum _gTextureTarget;
	GLuint _gTextureObject;
	// image loader by using Magick++
	Magick::Image* _pImage;
	Magick::Blob _blob;
};

#endif // !TEXTURE_H
