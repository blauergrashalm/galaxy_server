#ifndef JSON_SCHEMAS
#define JSON_SCHEMAS
#include <nlohmann/json-schema.hpp>

typedef nlohmann::json json;
typedef nlohmann::json_schema::json_validator validator;

struct ValidationSchemas
{
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
    json register_player_schema = R"(
{
    "$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Player Register",
    "description": "Registration Information of Player",
    "type":"object",
    "properties": {
        "name":{
            "type":"string",
            "maxLength": 40,
            "pattern": "^[a-zA-Z0-9\\ ]*$"
        },
        "passphrase":{
            "type":"string",
            "maxLength": 20
        }
    },
    "required":["name", "passphrase"]
}
)"_json;
    json game_change_schema = R"(
{"$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Game Change",
    "description": "A Game Change",
    "type":"object",
    "properties": {
        "field":{
            "type":"integer",
            "minimum": 0
        },
        "dot":{
            "type":["integer", "null"],
            "minimum": 0
        }
    },
    "required": ["field", "dot"]
}
)"_json;

    json new_game_schema = R"(
{"$schema": "http://json-schema.org/draft-07/schema#",
    "title": "New Game",
    "description": "Beschreibt wie ein neues Spiel aussehen soll",
    "type":"object",
    "properties": {
        "height":{
            "type":"integer",
            "minimum": 0,
            "maximum": 20
        },
        "width":{
            "type":"integer",
            "minimum": 0,
            "maximum": 20
        }
    },
    "required": ["height", "width"]
}
)"_json;
    json cast_vote_schema = R"(
{"$schema": "http://json-schema.org/draft-07/schema#",
    "title": "Casting a vote",
    "description": "Gibt eine Stimme ab",
    "type":"object",
    "properties": {
        "vote":{
            "type":"string",
            "enum": ["positive", "negative"]
        }
    },
    "required": ["vote"]
}
)"_json;
};

#endif