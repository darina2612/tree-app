#pragma once

#include <vector>
#include <memory>
#include <string>
#include <iostream>

namespace Serialization
{
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    serialize(std::ostream& stream, const T& value)
    {
        stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
    }

    template <typename T>
    typename std::enable_if<!std::is_arithmetic<T>::value>::type
    serialize(std::ostream& stream, const T& value)
    {
        value.serialize(stream);
    }

    inline void serialize(std::ostream& stream, const std::string& value)
    {
        auto size = sizeof(char) * (value.length() + 1);
        serialize(stream, size);
        stream.write(reinterpret_cast<const char*>(value.data()), sizeof(char) * (value.length() + 1));
    }

    template<typename T>
    void serialize(std::ostream& stream, const std::vector<T>& values)
    {
        serialize(stream, values.size());

        if(values.size() == 0)
            return;

        for(const auto& value : values)
            serialize(stream, value);
    }

    template<typename T>
    void serialize(std::ostream& stream, const std::shared_ptr<T>& value)
    {
        bool exists = (value != nullptr);

        serialize(stream, exists);

        if(!exists)
            return;

        serialize(stream, *value);
    }

    template<typename T>
    void serialize(std::ostream& stream, const std::vector<std::shared_ptr<T>>& values)
    {
        serialize(stream, values.size());

        if(values.size() == 0)
            return;

        for(const auto& value : values)
            serialize(stream, value);
    }
}

namespace Deserialization
{
    template <typename T>
    typename std::enable_if<std::is_arithmetic<T>::value>::type
    deserialize(std::istream& stream, T& value)
    {
        stream.read(reinterpret_cast<char*>(&value), sizeof(T));
    }

    template <typename T>
    typename std::enable_if<!std::is_arithmetic<T>::value>::type
    deserialize(std::istream& stream, T& value)
    {
        value.deserialize(stream);
    }

    inline void deserialize(std::istream& stream, std::string& value)
    {
        size_t size;
        deserialize(stream, size);

        if(size == 0)
            return;

        auto data = new char[size];

        stream.read(reinterpret_cast<char*>(data), size);
        value.append(data);
    }

    template<typename T>
    void deserialize(std::istream& stream, std::vector<T>& values)
    {
        size_t size;
        deserialize(stream, size);

        if(size == 0)
            return;

        values.resize(size);
        for(auto& value : values)
            deserialize(stream, value);
    }

    template<typename T>
    void deserialize(std::istream& stream, std::shared_ptr<T>& value)
    {
        bool exists;

        deserialize(stream, exists);

        if(!exists)
            return;

        value =  std::make_shared<T>();
        deserialize(stream, *value);
    }

    template<typename T>
    void deserialize(std::istream& stream, std::vector<std::shared_ptr<T>>& values)
    {
        size_t size;
        deserialize(stream, size);

        if(size == 0)
            return;

        values.resize(size);
        for(auto& value : values)
            deserialize(stream, value);
    }
}
