#ifndef JSONVALUE_H
#define JSONVALUE_H
#include <unordered_map>
#include <memory>

namespace RCU
{

template<typename T>
struct JSONValue;
struct JSONContainer;

using JSONObject = std::unordered_map<std::string,std::unique_ptr<JSONContainer>>;

// template<typename T>
// using JSONArray = std::vector<std::unique_ptr<JSONValue<T>>>;

struct JSON {
    enum class Type {
        Null,
        Boolean,
        Number,
        String,
        Object,
        Array
    };
};

template<typename T>
struct JSONValue {
public:

    JSON::Type type;
    T value;

    JSONValue();
    JSONValue(T val);
    // JSONValue(const T& val);
    // JSONValue(const JSONObject<T>& val) : type(Type::Object), value(val) {}
    // JSONValue(const JSONArray<T>& val) : type(Type::Array), value(val) {}
    ~JSONValue();
};

struct JSONContainer {
    virtual void setValue(std::string val) {}
    virtual void setValue(int val) {}
    virtual std::string getString(){ return ""; }
    virtual int getNumber(){ return 0; }
};

struct JSONNumber : JSONContainer {
    JSONValue<int> Json;
    JSONNumber(int val = 0) { Json.value = val; }
    void setValue(int val) override { Json.value = val; }
    int getNumber() override { return Json.value; }
};

struct JSONString : JSONContainer {
    JSONValue<std::string> Json;
    JSONString(std::string val = "") { Json.value = val; }
    void setValue(std::string val) override { Json.value = val; }
    std::string getString() override { return Json.value; }
};
    
} // namespace RCU

#endif // JSONVALUE_H
