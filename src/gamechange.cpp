#include "gamechange.hpp"
#include "debug_functions.hpp"

GameChange::~GameChange()
{
    DBG_LOG(HIGH, "GameChange wurde gelöscht");
}

GameChange::GameChange(GameChange &&other)
{
    new_assoziation = std::move(other.new_assoziation);
    old_assoziation = std::move(other.old_assoziation);
    player = std::move(other.player);
    affected_field = std::move(other.affected_field);
}

GameChange &GameChange::operator=(GameChange &&other)
{
    new_assoziation = std::move(other.new_assoziation);
    old_assoziation = std::move(other.old_assoziation);
    player = std::move(other.player);
    affected_field = std::move(other.affected_field);
    return *this;
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

void GameChange::set_dot(const d_ptr &d)
{
    new_assoziation = d;
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
