#include "gamechange.h"

GameChange::~GameChange()
{
    std::cout << "Game Change gelöscht" << std::endl;
}

void GameChange::apply()
{
    if (auto dot = affected_field->assigned_dot.lock())
    {
        old_assoziation = dot;
        dot->removeField(affected_field);
    }
    if (new_assoziation)
    {
        affected_field->assigned_dot = new_assoziation;
        new_assoziation->registerField(affected_field);
    }
    affected_field->last_change = shared_from_this();
}

void GameChange::revert()
{
    affected_field->assigned_dot = old_assoziation;
}

nlohmann::json GameChange::toJson()
{
    nlohmann::json result;
    result["type"] = "game_change";
    if (auto p = player.lock())
        result["player"] = p->id;
    result["field"] = affected_field->id;
    if (!new_assoziation)
    {
        result["dot"] = nullptr;
    }
    else
    {
        result["dot"] = new_assoziation->id;
    }
    return result;
}
