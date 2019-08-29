#include "Image.h"
#include <QBuffer>
#include <QDataStream>

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
    if(qImage_ ==  nullptr)
    {
        os << false;
        return;
    }

    os << true;

    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QDataStream ds{&buffer};
    ds << *qImage_;
    buffer.close();
    os << buffer.buffer().data();

}

void Image::deserialize(std::istream& is)
{
    bool exists;
    is >> exists;
    if(!exists)
    {
        qImage_.reset();
        return;
    }

    qImage_ = std::make_shared<QImage>();

}
