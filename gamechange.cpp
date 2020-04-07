#include "gamechange.h"

GameChange::~GameChange()
{
    std::cout << "Game Change gelöscht" << std::endl;
}

void GameChange::apply(std::shared_ptr<GameChange> self)
{
    if(auto dot = affected_field->assigned_dot.lock()){
        old_assoziation = dot;
        dot->removeField(affected_field);
    }
    affected_field->assigned_dot = new_assoziation;
    new_assoziation->registerField(affected_field);
    affected_field->last_change = self;
}

void GameChange::revert()
{
    affected_field->assigned_dot = old_assoziation;
}

nlohmann::json GameChange::toJson()
{
    nlohmann:json result;
    result["type"] = "game_change";
    result["player"] = player->id;
    result["field"] = affected_field->id;
    result["dot"] = new_assoziation->id;
    return result;
}

