#ifndef GAMEGEN_H
#define GAMEGEN_H

#include <memory>
#include <random>
#include <vector>

// This is type is in dot grid coordinates to simplify the generation algorithm
// If the place in the grid is a valid place for a new dot to be in, it is marked with 0
// Otherwise it is marked with 1
typedef std::vector<int> DotSpaceColumn;
typedef std::vector<DotSpaceColumn> DotSpace;
typedef std::pair<unsigned int, unsigned int> DotPosition;
typedef std::vector<DotPosition> DotPositionList;

class GameGen
{
private:
    unsigned int countEmptySpots(DotSpace space);
    int calculateNeighborPenalty(DotSpace space, int x, int y, int x_size, int y_size);
    std::vector<DotSpace> getPatterns();
    DotSpace addBorder(DotSpace space, int filler);
    std::pair<DotPositionList, DotSpace> generateNextDotsByPattern(DotSpace space, std::vector<DotSpace> pattern_list);
    std::pair<DotPositionList, DotSpace> generateNextDots(DotSpace space, std::default_random_engine gen);
    DotPosition generateRandomDotInEmptySpot(DotSpace space, std::default_random_engine gen);
    DotSpace generateGalaxyFromDot(DotSpace space, DotPosition dot, std::default_random_engine gen);
    DotSpace addFieldToGalaxy(DotSpace space, DotPosition dot, std::default_random_engine gen);
    DotSpace markAsOccupied(DotSpace space, DotPosition dot, int filler);
    void printDotSpace(DotSpace space);
    void printDotSpaceCandidates(DotSpace space, DotPositionList candidates);

public:
    DotPositionList generateDots(int x_size, int y_size);
};

#endif // GAMEGEN_H
