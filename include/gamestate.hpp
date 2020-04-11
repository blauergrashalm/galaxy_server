#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>
#include <map>
#include <memory>
#include <random>
#include "field.hpp"
#include "dot.hpp"
#include "position_type.hpp"
#include "nlohmann/json.hpp"
#include "gamechange.hpp"

using json = nlohmann::json;

class GameState
{
private:
    unsigned int x_size, y_size;

    std::map<pos_type, std::shared_ptr<Field>> fields;
    std::map<pos_type, std::shared_ptr<Dot>> dots;
    std::map<unsigned int, std::shared_ptr<Dot>> dots_by_id;
    std::map<unsigned int, std::shared_ptr<Field>> fields_by_id;

    void addField(pos_type position);
    void addDot(pos_type position);

    void generateRandomDots();

public:
    GameState(unsigned int x_size, unsigned int y_size);
    json toJson();

    void applyGameChange(const GameChange &change);
    std::shared_ptr<Dot> operator()(const unsigned int &i)
    {
        return dots_by_id[i];
    };

    std::shared_ptr<Dot> operator()(const pos_type &p)
    {
        return dots[p];
    };

    std::shared_ptr<Field> operator[](const unsigned int &i)
    {
        return fields_by_id[i];
    };

    std::shared_ptr<Field> operator[](const pos_type &p)
    {
        return fields[p];
    };
};

#endif // GAMESTATE_H
