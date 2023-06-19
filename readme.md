### Example of using JSON
RCU::jObject rootJson;

rootJson["root"] = std::make_shared<RCU::JSONObject>();
rootJson["root"]->getObject()["bob"] = std::make_shared<RCU::JSONObject>();
rootJson["root"]->getObject()["bob"]->getObject()["hair"] = std::make_shared<RCU::JSONString>("White");
rootJson["root"]->getObject()["bob"]->getObject()["age"] = std::make_shared<RCU::JSONNumber>(53);
rootJson["root"]->getObject()["bob"]->getObject()["married"] = std::make_shared<RCU::JSONBool>(true);
rootJson["root"]->getObject()["bob"]->getObject()["spouse"] = std::make_shared<RCU::JSONObject>();
rootJson["root"]->getObject()["bob"]->getObject()["spouse"]->getObject()["name"] = std::make_shared<RCU::JSONString>("Wendy");
rootJson["root"]->getObject()["bob"]->getObject()["spouse"]->getObject()["hair"] = std::make_shared<RCU::JSONString>("Black");
rootJson["root"]->getObject()["bob"]->getObject()["kids"] = std::make_shared<RCU::JSONArray>();
rootJson["root"]->getObject()["bob"]->getObject()["kids"]->getArray().emplace_back(std::make_shared<RCU::JSONObject>());
rootJson["root"]->getObject()["bob"]->getObject()["kids"]->getArray()[0]->getObject()["name"] = std::make_shared<RCU::JSONString>("Joey");
rootJson["root"]->getObject()["bob"]->getObject()["kids"]->getArray()[0]->getObject()["age"] = std::make_shared<RCU::JSONNumber>(5);
rootJson["root"]->getObject()["bob"]->getObject()["kids"]->getArray().emplace_back(std::make_shared<RCU::JSONObject>());
rootJson["root"]->getObject()["bob"]->getObject()["kids"]->getArray()[1]->getObject()["name"] = std::make_shared<RCU::JSONString>("Trixy");
rootJson["root"]->getObject()["bob"]->getObject()["kids"]->getArray()[1]->getObject()["age"] = std::make_shared<RCU::JSONNumber>(10);

rootJson["root"]->printSelf();
