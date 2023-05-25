#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <iostream>
#include "JSONValue.h"

namespace RCU
{

class JSONParser 
{
public:
    JSONParser();
    ~JSONParser();
private:
    JSONValue<int> mNode;
};

    
} // namespace RCU


#endif // JSONPARSER_H