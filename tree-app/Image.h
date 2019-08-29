#pragma once

#include <QImage>
#include <memory>

class Image
{
public:
    Image() = default;
    Image(const std::string& filename);

    const std::shared_ptr<QImage>& getQImage() const;

    void serialize(std::ostream& os) const;
    void deserialize(std::istream& is);

private:
    std::shared_ptr<QImage> qImage_;
};
