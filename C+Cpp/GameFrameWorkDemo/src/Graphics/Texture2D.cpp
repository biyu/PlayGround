#include "Texture2D.h"

Texture2D::Texture2D(std::string fileName)
	: _gTextureTarget(GL_TEXTURE_2D), 
	_fileName(fileName), _pImage(0)
{
}

Texture2D::~Texture2D()
{
	delete this->_pImage;
}

bool Texture2D::load()
{
	if(this->_fileName.empty())
	{
		Debug(L"empty texture file name");
		return false;
	}

    try {
        this->_pImage = new Magick::Image(this->_fileName);
        this->_pImage->write(&_blob, "RGBA");
    }
    catch (Magick::Error& Error) {
        std::cout << "error loading texture '" << this->_fileName << "': " << Error.what() << std::endl;
        return false;
    }

    glGenTextures(1, &(this->_gTextureObject));
	glBindTexture(this->_gTextureTarget, this->_gTextureObject);
    glTexImage2D(this->_gTextureTarget, 0, GL_RGBA, this->_pImage->columns(), this->_pImage->rows(), 0, GL_RGBA, GL_UNSIGNED_BYTE, this->_blob.data());
    glTexParameterf(this->_gTextureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(this->_gTextureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return true;
}

void Texture2D::bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(this->_gTextureTarget, this->_gTextureObject);
}