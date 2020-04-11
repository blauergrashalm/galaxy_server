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

// This is type is in dot grid coordinates to simplify the generation algorithm
// If the place in the grid is a valid place for a new dot to be in, it is marked with 0
// Otherwise it is marked with 1
typedef std::vector<std::vector<unsigned int>> DotSpace;
typedef std::pair<unsigned int, unsigned int> UIntPair;

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

    unsigned int getEmptySpacesFromSpace(DotSpace space);
    int calculateNeighborPenalty(DotSpace space, int x, int y, int x_size, int y_size);
    UIntPair GameState::generateNextDot(DotSpace space, std::default_random_engine gen);
    UIntPair GameState::generateRandomDotInEmptySpace(DotSpace space, std::default_random_engine gen);
    DotSpace regenerateSpaceWithDot(DotSpace space, UIntPair dot, std::default_random_engine gen);
    DotSpace addFieldToGalaxy(DotSpace space, UIntPair dot, std::default_random_engine gen);
    DotSpace markAsOccupied(DotSpace space, UIntPair dot);
    void generateSpace();
    void generateRandomDots();
    void printDotSpace(DotSpace space);
    void printDotSpaceCandidates(DotSpace space, std::vector<UIntPair> candidates);

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
