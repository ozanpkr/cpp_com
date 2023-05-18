#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

struct DynamicStruct {
    // Empty struct for dynamic creation
};

DynamicStruct createDynamicStruct(const Json::Value& jsonData) {
    DynamicStruct dynamicStruct;

    for (const auto& key : jsonData.getMemberNames()) {
        std::string attributeName = key;
        std::string attributeValue = jsonData[key].asString();

        dynamicStruct.__setattr(attributeName, attributeValue);
    }

    return dynamicStruct;
}

int main() {
    // Example usage
    std::string jsonStr = R"(
        {
            "key1": "value1",
            "key2": "value2",
            "key3": "value3"
        }
    )";

    Json::Value jsonData;
    Json::Reader reader;
    reader.parse(jsonStr, jsonData);

    DynamicStruct myStruct = createDynamicStruct(jsonData);

    // Accessing attributes
    std::cout << "key1: " << myStruct.key1 << std::endl;
    std::cout << "key2: " << myStruct.key2 << std::endl;
    std::cout << "key3: " << myStruct.key3 << std::endl;

    return 0;
}
