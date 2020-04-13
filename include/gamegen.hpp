#ifndef GAMEGEN_H
#define GAMEGEN_H

#include <memory>
#include <random>
#include <vector>

/**
 * @brief This type is a representation of a column of spots in dot grid coordinates
 */
typedef std::vector<int> DotSpaceColumn;

/**
 * @brief This type is a representation of all spots in dot grid coordinates
 */
typedef std::vector<DotSpaceColumn> DotSpace;
typedef std::pair<unsigned int, unsigned int> DotPosition;
typedef std::vector<DotPosition> DotPositionList;

typedef DotSpace Pattern;
typedef std::vector<DotSpace> PatternList;

/**
 * @brief Generates a solvable game_state
 */
class GameGen
{
private:
    int calculateNeighborWeight(DotSpace space, int x, int y, int x_size, int y_size, int neighbor_span);
    std::vector<DotSpace> getPatterns();
    DotSpace addBorder(DotSpace space, int filler);
    DotPositionList getRandomDotCandidates(DotSpace space, int min_distance_to_filled);
    std::pair<DotPositionList, DotSpace> generateNextDotsByPattern(DotSpace space, std::vector<DotSpace> pattern_list);
    std::pair<DotPositionList, DotSpace> generateNextDots(DotSpace space, PatternList pattern_list, std::default_random_engine gen);
    DotPosition generateRandomDotInEmptySpot(DotSpace space, std::default_random_engine gen);
    DotSpace generateGalaxyFromDot(DotSpace space, DotPosition dot, std::default_random_engine gen);
    std::pair<DotSpace, bool> addFieldToGalaxy(DotSpace space, DotPosition dot, std::default_random_engine gen);
    DotSpace markAsOccupied(DotSpace space, DotPosition dot, int filler);
    void printDotSpace(DotSpace space);
    void printDotSpaceCandidates(DotSpace space, DotPositionList candidates);

public:
    unsigned int countEmptySpots(DotSpace space);

    DotPositionList generateDots(int x_size, int y_size);
};

#endif // GAMEGEN_H
