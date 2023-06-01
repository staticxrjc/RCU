#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <iostream>
#include "JSONValue.h"
#include <stack>

namespace RCU
{

class JSONParser 
{
public:
    JSONParser();
    ~JSONParser();
    void parseData(const std::string& str);
private:
    JSON::Token checkToken(const char token);
    JSON::Token peakAhead(const std::string& json, size_t ref);
    void createObject(const std::string& key);
    void createArray(const std::string& key);
    void createNumber(const std::string& key);
    void createString(const std::string& key);
    void assignValue(const std::string& value);
    void printToken(const JSON::Token token);
    RCU::jObject mRootJSON;
    std::string rawData;
    std::stack<JSON::Token> mTokenStack;
    std::stack<std::string> mBreadcrumb;
};

    
} // namespace RCU


#endif // JSONPARSER_H