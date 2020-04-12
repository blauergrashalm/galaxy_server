#ifndef DOT_H
#define DOT_H

#include "position_type.hpp"

#include <set>
#include <map>
#include <memory>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
//forward declarations:
class Field;

// typedefs
typedef std::shared_ptr<Field> field_ptr_t;

static unsigned int dot_id = 0;

/**
 * @brief Represents the center of the galaxy
 *
 */
class Dot
{
private:
    /**
     * @brief all the fields that are assigned this dot
     *
     */
    std::set<field_ptr_t> fields;
    /**
     * @brief position of this dot in DOT Space
     *
     */
    pos_type position;

public:
    /**
     * @brief Construct a new Dot object with its coordinates
     *
     * @param x x coordinate
     * @param y y coordinate
     */
    Dot(unsigned int x, unsigned int y) : position{x, y}, id{dot_id++} {};

    /**
     * @brief checks if the assigned fields to this dot are mirrored around the dot
     *
     * @return true all fields are symetrical
     * @return false not symetrical
     */
    bool areFieldsSymetrical();
    /**
     * @brief checks if the assigned fields are valid (symetrical and connected)
     *
     * @return true
     * @return false
     */
    bool isValid();

    /**
     * @brief register a new field to be assigned to this dot
     *
     * @param f the field to be assigned
     */
    void registerField(field_ptr_t f) { fields.insert(f); };
    /**
     * @brief remove a field assoziation from this dot
     *
     * @param f field to remove
     */
    void removeField(field_ptr_t f) { fields.erase(f); };

    /**
     * @brief the id of this dot
     *
     */
    const unsigned int id;

    /**
     * @brief generates a json representation of this dot
     *
     * @return json
     */
    json toJson();
};

#endif // DOT_H
