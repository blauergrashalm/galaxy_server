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

/**
 * @brief Represents the current state of the game
 *
 */
class GameState
{
private:
    /**
     * @brief dimensions of the game
     *
     */
    unsigned int x_size, y_size;

    /**
     * @brief all fields in the game, ordered by position
     *
     */
    std::map<pos_type, std::shared_ptr<Field>> fields;
    /**
     * @brief all dots in the game, ordered by position
     *
     */
    std::map<pos_type, std::shared_ptr<Dot>> dots;
    /**
     * @brief all dots in the game, ordered by id
     *
     */
    std::map<unsigned int, std::shared_ptr<Dot>> dots_by_id;
    /**
     * @brief all fields in the game, ordered by id
     *
     */
    std::map<unsigned int, std::shared_ptr<Field>> fields_by_id;

    void addField(pos_type position);
    void addDot(pos_type position);

    /**
     * @brief deprecated, generates unsolvable State most of the times
     *
     */
    void generateRandomDots();

public:
    GameState(unsigned int x_size, unsigned int y_size);
    json toJson();

    /**
     * @brief applyies a gamechange
     *
     * @param change the change that should be applied
     */
    void applyGameChange(const GameChange &change);

    /**
     * @brief gets a dot by id
     *
     * @param i id to use
     * @return std::shared_ptr<Dot> dot with requested id
     */
    std::shared_ptr<Dot> operator()(const unsigned int &i)
    {
        return dots_by_id[i];
    };

    /**
     * @brief gets dot by position
     *
     * @param p position at which the requested dot lives
     * @return std::shared_ptr<Dot>
     */
    std::shared_ptr<Dot> operator()(const pos_type &p)
    {
        return dots[p];
    };

    /**
     * @brief gets a field by id
     *
     * @param i
     * @return std::shared_ptr<Field>
     */
    std::shared_ptr<Field> operator[](const unsigned int &i)
    {
        return fields_by_id[i];
    };

    /**
     * @brief gets a field by position
     *
     * @param p
     * @return std::shared_ptr<Field>
     */
    std::shared_ptr<Field> operator[](const pos_type &p)
    {
        return fields[p];
    };
};

#endif // GAMESTATE_H
