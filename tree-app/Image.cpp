#include "Image.h"
#include <QBuffer>
#include <QDataStream>
#include "SerializationUtils.h"

Image::Image(const std::string& filename)
{
    qImage_ = std::make_shared<QImage>(filename.c_str());
}

const std::shared_ptr<QImage>& Image::getQImage() const
{
    return  qImage_;
}

void Image::serialize(std::ostream& os) const
{
    Serialization::serialize(os, qImage_);
}

void Image::deserialize(std::istream& is)
{
    Deserialization::deserialize(is, qImage_);
}
