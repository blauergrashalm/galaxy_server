#ifndef FIELD_H
#define FIELD_H

#include "position_type.hpp"

#include "nlohmann/json.hpp"

#include <memory>

using json = nlohmann::json;

class GameChange;
class Dot;

static unsigned int f_id;

/**
 * @brief represents a Field in the game
 *
 */
class Field
{
private:
    /**
     * @brief position of the field in field coordinated
     *
     */
    pos_type position;

public:
    /**
     * @brief the last change that was made to the field
     *
     */
    std::weak_ptr<GameChange> last_change;
    /**
     * @brief the dot that field belongs to
     *
     */
    std::weak_ptr<Dot> assigned_dot;
    /**
     * @brief unique id of this field
     *
     */
    const unsigned int id;

    /**
     * @brief Construct a new Field object at coordinates x, y
     *
     * @param x
     * @param y
     */
    Field(unsigned int x, unsigned int y) : position{x, y}, id{f_id++} {};

    /**
     * @brief builds the JSON representation of a field
     *
     * @return json
     */
    json toJson();
};

#endif // FIELD_H
