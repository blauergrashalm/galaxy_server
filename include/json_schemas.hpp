#include <nlohmann/json-schema.hpp>

typedef nlohmann::json json;
typedef nlohmann::json_schema::json_validator validator;

json basic_command_schema = R"(
    {
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Generic Command",
    "description": "Generic Schema for validating command messages",
    "type":"object",
    "properties": {
        "command":{
            "type":"string"
        },
        "payload":{
            "type":"object"
        }
    },
    "required": ["command", "payload"]
}
)"_json;
