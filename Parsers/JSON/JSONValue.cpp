#include "JSONValue.h"
#include <string>

namespace RCU
{

    // template <>
    // JSONValue<bool>::JSONValue(bool val) : type(Type::Boolean), value(val) {}

    // template <typename T>
    // JSONValue<T>::JSONValue(T val) : type(Type::Number), value(val) {}

    template<> 
    RCU::JSONValue<jObject>::JSONValue() : type(JSON::Type::Object), value() {}

    template<>
    RCU::JSONValue<jArray>::JSONValue() : type(JSON::Type::Array), value() {}

    template<> 
    RCU::JSONValue<std::string>::JSONValue() : type(JSON::Type::String), value("") {}

    template<> 
    RCU::JSONValue<std::string>::JSONValue(std::string val) : type(JSON::Type::String), value(val) {}

    template<typename T>
    JSONValue<T>::JSONValue() : type(JSON::Type::Null) {}

    template<typename T>
    JSONValue<T>::~JSONValue() {}


    
// Nested operator[] overload 
// template<typename U>
// JSONValue<U>& operator[](const std::string& key) {
//     std::cout << key << std::endl;
//     return value[key];
// }

// const nested operator[] overload
// template<typename U>
// const JSONValue<U>& operator[](const std::string& key) const {
//     return value.at(key);
// }

// Constructors
template JSONValue<int>::JSONValue();
template JSONValue<bool>::JSONValue();
template JSONValue<std::string>::JSONValue(std::string val);
template JSONValue<std::string>::JSONValue();
template JSONValue<jObject>::JSONValue();
template JSONValue<jArray>::JSONValue();

// Destructors
template JSONValue<int>::~JSONValue();
template JSONValue<bool>::~JSONValue();
template JSONValue<jObject>::~JSONValue();
template JSONValue<jArray>::~JSONValue();
template JSONValue<std::string>::~JSONValue();

} // namespace RCU
