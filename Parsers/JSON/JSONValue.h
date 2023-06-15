#ifndef JSONVALUE_H
#define JSONVALUE_H
#include <unordered_map>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace RCU
{

template<typename T>
struct JSONValue;
struct JSONContainerBase;

using jObject = std::unordered_map<std::string,std::shared_ptr<JSONContainerBase>>;
using jArray = std::vector<std::shared_ptr<JSONContainerBase>>;

struct JSON {
    enum class Type {
        Null,
        Boolean,
        Number,
        String,
        Object,
        Array
    };
    
    enum class Token {
        OPEN_CURLY,
        CLOSE_CURLY,
        QUOTE,
        COLON,
        OPEN_BRACKET,
        CLOSE_BRACKET,
        FORWARD_SLASH,
        COMMA,
        NONE
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
    ~JSONValue();
};

struct JSONContainerBase {
    int tab = 2;
    jObject nilO;
    jArray nilA; 
    virtual void setValue(std::string val) {}
    virtual void setValue(float val) {}
    virtual void setValue(bool) {}
    virtual std::string getString() = 0;
    virtual float getNumber() = 0;
    virtual bool getBool() = 0;
    virtual jObject& getObject() { return nilO; }
    virtual jArray& getArray() { return nilA; }
    virtual void printSelf(int level = 0) {};
    void printSpaces(int spaces) { for(int i = 0; i < (spaces * tab); i++) { std::cout << " ";}}
};

template<typename T>
struct JSONContainer : JSONContainerBase, JSONValue<T> {
    JSONValue<T> Json;
};

struct JSONNumber : JSONContainer<float> {
    JSONNumber(float val = 0) { Json.value = val; }
    void setValue(float val) override { Json.value = val; }
    float getNumber() override { return Json.value; }
    std::string getString() override { return std::to_string(Json.value); }
    bool getBool() override { return (Json.value == 0) ? false : true; }
    void printSelf(int level = 0) override { 
        std::cout << getString() << std::endl;
    }
};

struct JSONString : JSONContainer<std::string> {
    JSONString(std::string val = "") { Json.value = val; }
    void setValue(std::string val) override { Json.value = val; }
    float getNumber() override { return std::stoi(Json.value); }
    std::string getString() override { return Json.value; }
    bool getBool() override { return (Json.value == "true") ? true : false; }
    void printSelf(int level = 0) override { 
        std::cout << "\"" << getString() << "\"\n";
    }
};

struct JSONBool : JSONContainer<bool> {
    JSONBool(bool val = false) { Json.value = val; }
    void setValue(bool val) override { Json.value = val; }
    float getNumber() override { return Json.value ? 1 : 0; }
    std::string getString() override { return Json.value ? "true" : "false"; }
    bool getBool() override { return Json.value; }
    void printSelf(int level = 0) override { 
        std::cout << getString() << std::endl;
    }
};

struct JSONObject : JSONContainer<jObject> {
    float getNumber() override { return 0; }
    std::string getString() override { return ""; }
    bool getBool() override { return true; }
    jObject& getObject() override { return Json.value; }
    void printSelf(int level = 0) override { 
        std::cout << "\n";
        printSpaces(level);
        std::cout << "{\n";
        for(auto& it : Json.value) {
            printSpaces(level);
            std::cout << "  \"" << it.first << "\" : ";
            it.second->printSelf(level + 1);
        }
        printSpaces(level);
        std::cout << "}\n";
    }
};

struct JSONArray : JSONContainer<jArray> {
    float getNumber() override { return 0; }
    std::string getString() override { return ""; }
    bool getBool() override { return true; }
    jArray& getArray() override { return Json.value; }
    void printSelf(int level = 0) override { 
        std::cout << "[";
        for(int i = 0; i < Json.value.size(); i++) {
            Json.value.at(i)->printSelf(level);
            if(i != (Json.value.size()-1)) {
                printSpaces(level);
                std::cout << ",";
            }
        }
        printSpaces(level);
        std::cout << "]\n";
    }
};

} // namespace RCU

#endif // JSONVALUE_H
