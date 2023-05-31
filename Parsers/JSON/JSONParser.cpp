#include "JSONParser.h"
#include <iostream>

namespace RCU
{

JSONParser::JSONParser() {

}

void JSONParser::createObject(const std::string& key) {
    std::cout << "Create Object: " << key << std::endl;
    mRootJSON[key] = std::make_unique<RCU::JSONObject>();
    mBreadcrumb.push(key);
}

void JSONParser::parseData(const std::string& data) {
    rawData = data;
    typedef struct wordTrack {
        std::string word = "";
        bool appendWord = false;
    } wordTrack;
    wordTrack keyValue;

    std::cout << "----- Before Parse -----" << std::endl;
    std::cout << rawData << std::endl;
    std::cout << "----- After Parse -----" << std::endl;

    for(int i = 0; i < rawData.length(); i++) {
        switch(checkToken(rawData[i])) {
            case JSON::Token::OPEN_CURLY:
                if(mBreadcrumb.empty()) 
                    createObject("root");
                else 
                    createObject(keyValue.word);
                keyValue.word = "";
                break;
            case JSON::Token::NONE:
                if(keyValue.appendWord) keyValue.word += rawData[i];
                break;
            case JSON::Token::QUOTE:
                keyValue.appendWord = !keyValue.appendWord;
                break;
        }
    }
}

JSON::Token JSONParser::checkToken(const char token) {
    switch(token) {
        case('{'):
            std::cout << "OPEN CURLY" << std::endl;
            return JSON::Token::OPEN_CURLY;
            break;
        case('}'):
            std::cout << "CLOSE CURLY" << std::endl;
            return JSON::Token::CLOSE_CURLY;
            break;
        case('"'):
            std::cout << "QUOTE" << std::endl;
            return JSON::Token::QUOTE;
            break;
        case('\\'):
            std::cout << "FORWARD SLASH" << std::endl;
            return JSON::Token::FORWARD_SLASH;
            break;
        case(':'):
            std::cout << "COLON" << std::endl;
            return JSON::Token::COLON;
            break;
        case('['):
            std::cout << "OPEN BRACKET" << std::endl;
            return JSON::Token::OPEN_BRACKET;
            break;
        case(']'):
            std::cout << "CLOSE BRACKET" << std::endl;
            return JSON::Token::CLOSE_BRACKET;
            break;
        default:
            std::cout << token;
            return JSON::Token::NONE;
    }
}

JSONParser::~JSONParser() {}
    
} // namespace RCU
