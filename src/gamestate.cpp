#include "gamegen.h"
#include "gamestate.hpp"
#include <iostream>
#include <iomanip>

GameState::GameState(unsigned int x_size, unsigned int y_size) : x_size{x_size}, y_size{y_size}
{
    for (unsigned int i = 0; i < x_size; i++)
    {
        for (unsigned int j = 0; j < y_size; j++)
        {
            addField({i, j});
        }
    }
    auto new_dot_list = GameGen().generateDots(x_size, y_size);
    for (int i = 0; i < new_dot_list.size(); i++)
    {
        auto new_dot = new_dot_list[i];

        pos_type dot_pos = {new_dot.first, new_dot.second};
        addDot(dot_pos);
    }
}

json GameState::toJson()
{
    json game_state;
    game_state["size_x"] = x_size;
    game_state["size_y"] = y_size;
    for (auto &&pair : fields)
    {
        game_state["fields"].push_back(pair.second->toJson());
    }
    for (auto &&pair : dots)
    {
        game_state["dots"].push_back(pair.second->toJson());
    }
    return game_state;
}

void GameState::generateRandomDots()
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<unsigned int> dist_x(0, x_size * 2 - 1);
    std::uniform_int_distribution<unsigned int> dist_y(0, y_size * 2 - 1);

    int count = (x_size * y_size) / 12;

    for (int i = 0; i < count; i++)
    {
        pos_type p{dist_x(gen), dist_y(gen)};
        addDot(p);
    }
}

void GameState::addDot(pos_type position)
{
    auto dot = std::make_shared<Dot>(position.x, position.y);
    dots.insert(std::pair<pos_type, std::shared_ptr<Dot>>(position, dot));
    dots_by_id.insert(std::pair<unsigned int, std::shared_ptr<Dot>>(dot->id, dot));
}

void GameState::addField(pos_type position)
{
    auto field = std::make_shared<Field>(position.x, position.y);
    fields.insert(std::pair<pos_type, std::shared_ptr<Field>>(position, field));
    fields_by_id.insert(std::pair<unsigned int, std::shared_ptr<Field>>(field->id, field));
}
