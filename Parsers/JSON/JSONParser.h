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
    void createObject(const std::string& key);
    RCU::jObject mRootJSON;
    std::string rawData;
    std::stack<JSON::Token> mTokenStack;
    std::stack<std::string> mBreadcrumb;
};

    
} // namespace RCU


#endif // JSONPARSER_H