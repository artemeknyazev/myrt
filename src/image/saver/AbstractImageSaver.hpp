#ifndef MYRT_ABSTRACT_IMAGE_SAVER_HPP
#define MYRT_ABSTRACT_IMAGE_SAVER_HPP

#include "options/Options.hpp"
#include "image/buffer/ImageBuffer.hpp"
#include "image/saver/ImageType.hpp"

namespace Myrt::Image::Saver {

using Myrt::Options::ImageSaverOptionsPtr;
using Myrt::Image::Buffer::ImageBufferPtr;

class AbstractImageSaver;
using ImageSaverPtr = std::shared_ptr<AbstractImageSaver>;

class AbstractImageSaver {
public:
    void save() const {
        doSave();
    }

    virtual void init(ImageSaverOptionsPtr pOptions, ImageBufferPtr pImageBuffer) {
        mpImageBuffer = pImageBuffer;
        mGamma = pOptions->getGamma();
        mPath = pOptions->getOutputPath();
    }

    virtual ~AbstractImageSaver() = default;

protected:
    virtual void doSave() const = 0;

    rgb_color getPixelColor(unsigned int x, unsigned int y) const {
        return RGBColor(Gamma(mpImageBuffer->getPixelColor(x, y), mGamma));
    }

    const std::string& getPath() const
    { return mPath; }

    unsigned int getImageWidth() const
    { return mpImageBuffer->getWidth(); }

    unsigned int getImageHeight() const
    { return mpImageBuffer->getHeight(); }

private:
    ImageBufferPtr mpImageBuffer;
    float mGamma;
    std::string mPath;
};

} // namespace Myrt::Image::Saver

#endif

