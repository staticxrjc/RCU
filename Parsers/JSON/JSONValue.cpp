#include "JSONValue.h"
#include <string>

namespace RCU {

// template<>
// RCU::JSONValue<double>::JSONValue() : type(JSON::Type::Number), value() {}

template <>
RCU::JSONValue<double>::JSONValue(double val) : type(JSON::Type::Number), value(val) {}

template <>
RCU::JSONValue<jObject>::JSONValue() : type(JSON::Type::Object), value() {}

template <>
RCU::JSONValue<jArray>::JSONValue() : type(JSON::Type::Array), value() {}
template <>
RCU::JSONValue<std::string>::JSONValue(std::string val) : type(JSON::Type::String), value(val) {}

template <typename T>
JSONValue<T>::JSONValue() : type(JSON::Type::Null) {}

template <typename T>
JSONValue<T>::~JSONValue() {}

// Constructors
template JSONValue<double>::JSONValue();
template JSONValue<bool>::JSONValue();
template JSONValue<std::string>::JSONValue(std::string val);
template JSONValue<std::string>::JSONValue();
template JSONValue<jObject>::JSONValue();
template JSONValue<jArray>::JSONValue();

// Destructors
template JSONValue<double>::~JSONValue();
template JSONValue<bool>::~JSONValue();
template JSONValue<jObject>::~JSONValue();
template JSONValue<jArray>::~JSONValue();
template JSONValue<std::string>::~JSONValue();

}  // namespace RCU
