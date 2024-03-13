#include "JSONParser.h"
#include <iostream>
#include <math.h>

#define DECIMAL_ACCURACY 1000

namespace RCU {

JSONParser::JSONParser() {
    mDebug = false;
}

void JSONParser::printJson() {
    mRootJSON["root"]->printSelf();
}

std::shared_ptr<JSONContainerBase> JSONParser::getRootJSON() {
    return mRootJSON["root"];
}

void JSONParser::createObject(const std::string& key) {
    if (key != "") mBreadcrumb.push_back(std::make_pair(JSON::Type::Object, key));
    if (mDebug) std::cout << "mRootJSON[root]";
    if (key == "root" & mBreadcrumb.size() == 1) {
        if (mDebug) std::cout << " = std::make_shared<JSONObject>()" << std::endl;
        mRootJSON["root"] = std::make_shared<JSONObject>();
        return;
    }
    std::shared_ptr<JSONContainerBase> baseRef = mRootJSON["root"];
    bool arrayUsed;
    for (auto& value : mBreadcrumb) {
        arrayUsed = false;
        if (&value == &mBreadcrumb.front()) continue;
        if (&value == &mBreadcrumb.back())  // Last item
            if (value.first == JSON::Type::Array) {
                if (mDebug) std::cout << "->getObject()[" << value.second << "]->getArray().emplace_back(std::make_shared<RCU::JSONObject>())" << std::endl;
                baseRef->getObject()[value.second]->getArray().emplace_back(std::make_shared<RCU::JSONObject>());
                return;
            }
            else {
                if (mDebug) std::cout << "[" << value.second << "] = std::make_shared<RCU::JSONObject>()" << std::endl;
                baseRef->getObject()[value.second] = std::make_shared<RCU::JSONObject>();
                return;
            }
        if (value.first == JSON::Type::Array) {
            baseRef = baseRef->getObject()[value.second]->getArray().back();
            if (mDebug) std::cout << "->getObject()[" << value.second << "]->getArray().back()";
            arrayUsed = true;
        }
        else if (value.first == JSON::Type::Object) {
            if (arrayUsed) {
                if (mDebug) std::cout << "->getArray().back()";
                baseRef = baseRef->getArray().back();
            }
            else {
                if (mDebug) std::cout << "getObject().at(" << value.second << ")";
                if (mBreadcrumb.size() > 1) baseRef = baseRef->getObject().at(value.second);
            }
        }
    }
}

void JSONParser::createNumber(const std::string& key) {
    mBreadcrumb.push_back(std::make_pair(JSON::Type::Number, key));
}

void JSONParser::createString(const std::string& key) {
    mBreadcrumb.push_back(std::make_pair(JSON::Type::String, key));
}

void JSONParser::createArray(const std::string& key) {
    mRootJSON[key] = std::make_shared<RCU::JSONObject>();
    if (mDebug) std::cout << "mRootJSON[root]";
    std::shared_ptr<JSONContainerBase> baseRef = mRootJSON["root"];
    for (auto& value : mBreadcrumb) {
        if (&value == &mBreadcrumb.front()) continue;
        if (value.first == JSON::Type::Array) {
            if (mDebug) std::cout << "->getObject()[" << value.second << "]->getArray().back()";
            baseRef = baseRef->getObject()[value.second]->getArray().back();
        }
        else {
            if (mDebug) std::cout << "->getObject()[" << value.second << "]";
            baseRef = baseRef->getObject()[value.second];
        }
    }
    mBreadcrumb.push_back(std::make_pair(JSON::Type::Array, key));
    baseRef->getObject()[key] = std::make_shared<RCU::JSONArray>();
    if (mDebug) std::cout << "->getObject()[" << key << "] = std::make_shared<RCU::JSONArray>()" << std::endl;
}

void JSONParser::assignValue(const std::string& value) {
    if (mDebug) std::cout << "mRootJSON[root]";
    mTokenStack.pop();
    std::string finalKey = mBreadcrumb.size() == 1 ? "root" : mBreadcrumb.back().second;
    std::shared_ptr<JSONContainerBase> baseRef = mRootJSON["root"];
    switch (mBreadcrumb.back().first) {
        case (JSON::Type::String):
            for (auto& crumb : mBreadcrumb) {
                if (&crumb == &mBreadcrumb.front()) continue;
                if (&crumb == &mBreadcrumb.back()) continue;
                if (crumb.first == JSON::Type::Array) {
                    baseRef = baseRef->getObject()[crumb.second]->getArray().back();
                    if (mDebug) std::cout << "[" << crumb.second << "]->getArray().back()";
                }
                else {
                    baseRef = baseRef->getObject()[crumb.second];
                    if (mDebug) std::cout << "[" << crumb.second << "]->getObject()";
                }
            }
            baseRef->getObject()[finalKey] = std::make_shared<RCU::JSONString>(value);
            if (mDebug) std::cout << "[" << finalKey << "] = std::make_shared<RCU::JSONString>(" << value << ")" << std::endl;
            mBreadcrumb.pop_back();
            break;
        case (JSON::Type::Number):
            for (auto& crumb : mBreadcrumb) {
                if (&crumb == &mBreadcrumb.front()) continue;
                if (&crumb == &mBreadcrumb.back()) continue;
                if (crumb.first == JSON::Type::Array) {
                    baseRef = baseRef->getObject()[crumb.second]->getArray().back();
                    if (mDebug) std::cout << "[" << crumb.second << "]->getArray().back()";
                }
                else {
                    baseRef = baseRef->getObject()[crumb.second];
                    if (mDebug) std::cout << "[" << crumb.second << "]->getObject()";
                }
            }
            std::string processed = "";
            bool bVal = false;
            bool number = false;
            for (int index = 0; index < value.size(); index++) {
                if (value[index] == ' ') continue;
                if (value[index] == 't' | value[index] == 'T') {
                    bVal = true;
                    break;
                }
                else if (value[index] == 'f' | value[index] == 'F') {
                    break;
                }
                else
                    processed += value[index];
                number = true;
            }

            if (number) {
                baseRef->getObject()[finalKey] = std::make_shared<RCU::JSONNumber>(std::ceil(stod(value) * DECIMAL_ACCURACY) / DECIMAL_ACCURACY);
                if (mDebug) std::cout << "[" << finalKey << "] = std::make_shared<RCU::JSONNumber>(" << value << ")" << std::endl;
            }
            else {
                baseRef->getObject()[finalKey] = std::make_shared<RCU::JSONBool>(bVal);
                if (mDebug) std::cout << "[" << finalKey << "] = std::make_shared<RCU::JSONNumber>(" << value << ")" << std::endl;
            }
            mBreadcrumb.pop_back();
            break;
    }
}

int JSONParser::parseData(const std::string& data) {
    rawData = data;

    std::string input = data;
    // input.erase(std::remove(input.begin(), input.end(), ' '), input.end());
    // input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
    // input.erase(std::remove(input.begin(), input.end(), '\r'), input.end());

    if (input.empty()) return -1;
    mBreadcrumb.clear();
    mTokenStack = std::stack<JSON::Token>();
    mRootJSON = jObject();
    typedef struct wordTrack {
        std::string word = "";
        bool appendWord = false;
    } wordTrack;
    wordTrack keyValue;

    if (mDebug) std::cout << "----- Before Parse -----" << std::endl;
    if (mDebug) std::cout << rawData << std::endl;
    if (mDebug) std::cout << "----- After Parse -----" << std::endl;

    for (int i = 0; i < rawData.length(); i++) {
        switch (checkToken(rawData[i])) {
            case JSON::Token::OPEN_CURLY:
                if (mBreadcrumb.empty())
                    createObject("root");
                else {
                    createObject(keyValue.word);
                }
                keyValue.word = "";
                break;
            case JSON::Token::NONE:
                mTokenStack.pop();
                if (keyValue.appendWord) keyValue.word += rawData[i];
                break;
            case JSON::Token::QUOTE:
                mTokenStack.pop();
                keyValue.appendWord = !keyValue.appendWord;
                break;
            case JSON::Token::COLON:
                switch (peakAhead(rawData, i)) {
                    case (JSON::Token::OPEN_BRACKET):
                        mTokenStack.pop();
                        createArray(keyValue.word);
                        keyValue.word = "";
                        break;
                    case (JSON::Token::QUOTE):
                        createString(keyValue.word);
                        keyValue.word = "";
                        break;
                    case (JSON::Token::COMMA):
                    case (JSON::Token::CLOSE_CURLY):
                        createNumber(keyValue.word);
                        keyValue.word = "";
                        keyValue.appendWord = true;
                        break;
                    case (JSON::Token::OPEN_CURLY):
                        break;
                    default:
                        if (mDebug) std::cout << "Condition on colon not defined: ";
                        printToken(peakAhead(rawData, i));
                }
                break;
            case (JSON::Token::FORWARD_SLASH):
                mTokenStack.pop();
                break;
            case (JSON::Token::OPEN_BRACKET):
                break;
            case (JSON::Token::CLOSE_BRACKET):
                mTokenStack.pop();
                mTokenStack.pop();
                mBreadcrumb.pop_back();
                break;
            case (JSON::Token::CLOSE_CURLY):
                mTokenStack.pop();
                if (mTokenStack.top() == JSON::Token::COLON) {
                    assignValue(keyValue.word);
                    keyValue.word = "";
                    keyValue.appendWord = false;
                }
                mTokenStack.pop();
                if (mBreadcrumb.back().first == JSON::Type::Object) mBreadcrumb.pop_back();
                break;
            case (JSON::Token::COMMA):
                mTokenStack.pop();
                if (mTokenStack.top() == JSON::Token::COLON) {
                    assignValue(keyValue.word);
                    keyValue.word = "";
                    keyValue.appendWord = false;
                }
                break;
        }
    }
    return 1;
}

void JSONParser::setDebug(bool debug) {
    mDebug = debug;
}

JSON::Token JSONParser::peakAhead(const std::string& json, size_t ref) {
    JSON::Token token = JSON::Token::NONE;
    if ((ref + 1) >= json.length()) return JSON::Token::NONE;
    for (size_t i = ref + 1; i < json.length(); i++) {
        token = checkToken(json[i]);
        mTokenStack.pop();
        if (token == JSON::Token::NONE)
            continue;
        else
            break;
    }
    return token;
}

void JSONParser::printToken(const JSON::Token token) {
    switch (token) {
        case (JSON::Token::OPEN_CURLY):
            if (mDebug) std::cout << "{" << std::endl;
            break;
        case (JSON::Token::CLOSE_CURLY):
            if (mDebug) std::cout << "}" << std::endl;
            break;
        case (JSON::Token::QUOTE):
            if (mDebug) std::cout << "\"" << std::endl;
            break;
        case (JSON::Token::FORWARD_SLASH):
            if (mDebug) std::cout << "\\" << std::endl;
            break;
        case (JSON::Token::COLON):
            if (mDebug) std::cout << ":" << std::endl;
            break;
        case (JSON::Token::OPEN_BRACKET):
            if (mDebug) std::cout << "[" << std::endl;
            break;
        case (JSON::Token::CLOSE_BRACKET):
            if (mDebug) std::cout << "]" << std::endl;
            break;
        case (JSON::Token::COMMA):
            if (mDebug) std::cout << "," << std::endl;
            break;
    }
}

JSON::Token JSONParser::checkToken(const char token) {
    switch (token) {
        case ('{'):
            mTokenStack.push(JSON::Token::OPEN_CURLY);
            break;
        case ('}'):
            mTokenStack.push(JSON::Token::CLOSE_CURLY);
            break;
        case ('"'):
            mTokenStack.push(JSON::Token::QUOTE);
            break;
        case ('\\'):
            mTokenStack.push(JSON::Token::FORWARD_SLASH);
            break;
        case (':'):
            mTokenStack.push(JSON::Token::COLON);
            break;
        case ('['):
            mTokenStack.push(JSON::Token::OPEN_BRACKET);
            break;
        case (']'):
            mTokenStack.push(JSON::Token::CLOSE_BRACKET);
            break;
        case (','):
            mTokenStack.push(JSON::Token::COMMA);
            break;
        default:
            mTokenStack.push(JSON::Token::NONE);
    }
    return mTokenStack.top();
}

JSONParser::~JSONParser() {}

}  // namespace RCU
