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

void JSONParser::createNumber(const std::string& key) {
    std::cout << "Create Number: " << key << std::endl;
    mBreadcrumb.push(key);
}

void JSONParser::createString(const std::string& key) {
    std::cout << "Create String: " << key << std::endl;
    mBreadcrumb.push(key);
}

void JSONParser::createArray(const std::string& key) {
    std::cout << "Create Array: " << key << std::endl;
    mBreadcrumb.push(key);
}

void JSONParser::assignValue(const std::string& value) {
    std::cout << "Assign Value: " << value << std::endl;
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
                else {
                    createObject(keyValue.word);
                }
                keyValue.word = "";
                break;
            case JSON::Token::NONE:
                mTokenStack.pop();
                if(keyValue.appendWord) keyValue.word += rawData[i];
                break;
            case JSON::Token::QUOTE:
                mTokenStack.pop();
                keyValue.appendWord = !keyValue.appendWord;
                break;
            case JSON::Token::COLON:
                printToken(peakAhead(rawData,i));
                switch(peakAhead(rawData,i)) {
                    case(JSON::Token::OPEN_BRACKET):
                        createArray(keyValue.word);
                        keyValue.word = "";
                        break;
                    case(JSON::Token::QUOTE):
                        createString(keyValue.word);
                        keyValue.word = "";
                        break;
                    case(JSON::Token::COMMA):
                    case(JSON::Token::CLOSE_CURLY):
                        createNumber(keyValue.word);
                        keyValue.word = "";
                        keyValue.appendWord = true;
                }
                break;
            case(JSON::Token::FORWARD_SLASH):
                mTokenStack.pop();
                break;
            case(JSON::Token::OPEN_BRACKET):
                mTokenStack.pop();
                break;
            case(JSON::Token::CLOSE_BRACKET):
                mTokenStack.pop();
                break;
            case(JSON::Token::CLOSE_CURLY):
                mTokenStack.pop();
            case(JSON::Token::COMMA):
                mTokenStack.pop();
                if(mTokenStack.top() == JSON::Token::COLON) {
                    assignValue(keyValue.word);
                    keyValue.word = "";
                    keyValue.appendWord = false;
                    mTokenStack.pop();
                }
                break;
            }
    }
}

JSON::Token JSONParser::peakAhead(const std::string& json, size_t ref) {
    JSON::Token token = JSON::Token::NONE;
    if((ref+1) >= json.length()) return JSON::Token::NONE;
    for(size_t i = ref + 1; i < json.length(); i++) {
        token = checkToken(json[i]);
        mTokenStack.pop();
        if(token == JSON::Token::NONE) continue;
        else break;
    }
    return token;
}

void JSONParser::printToken(const JSON::Token token) {
    switch(token) {
        case(JSON::Token::OPEN_CURLY):
            std::cout << "{" << std::endl;
            break;
        case(JSON::Token::CLOSE_CURLY):
            std::cout << "}" << std::endl;
            break;
        case(JSON::Token::QUOTE):
            std::cout << "\"" << std::endl;
            break;
        case(JSON::Token::FORWARD_SLASH):
            std::cout << "\\" << std::endl;
            break;
        case(JSON::Token::COLON):
            std::cout << ":" << std::endl;
            break;
        case(JSON::Token::OPEN_BRACKET):
            std::cout << "[" << std::endl;
            break;
        case(JSON::Token::CLOSE_BRACKET):
            std::cout << "]" << std::endl;
            break;
        case(JSON::Token::COMMA):
            std::cout << "," << std::endl;
            break;
    }

}

JSON::Token JSONParser::checkToken(const char token) {
    switch(token) {
        case('{'):
            mTokenStack.push(JSON::Token::OPEN_CURLY);
            break;
        case('}'):
            mTokenStack.push(JSON::Token::CLOSE_CURLY);
            break;
        case('"'):
            mTokenStack.push(JSON::Token::QUOTE);
            break;
        case('\\'):
            mTokenStack.push(JSON::Token::FORWARD_SLASH);
            break;
        case(':'):
            mTokenStack.push(JSON::Token::COLON);
            break;
        case('['):
            mTokenStack.push(JSON::Token::OPEN_BRACKET);
            break;
        case(']'):
            mTokenStack.push(JSON::Token::CLOSE_BRACKET);
            break;
        case(','):
            mTokenStack.push(JSON::Token::COMMA);
            break;
        default:
            mTokenStack.push(JSON::Token::NONE);
    }
    return mTokenStack.top();
}

JSONParser::~JSONParser() {}
    
} // namespace RCU
