#ifndef GAMEGEN_H
#define GAMEGEN_H

#include <random>
#include <vector>

// This is type is in dot grid coordinates to simplify the generation algorithm
// If the place in the grid is a valid place for a new dot to be in, it is marked with 0
// Otherwise it is marked with 1
typedef std::vector<std::vector<unsigned int>> DotSpace;
typedef std::pair<unsigned int, unsigned int> UIntPair;

class GameGen
{
private:
    unsigned int getEmptySpacesFromSpace(DotSpace space);
    int calculateNeighborPenalty(DotSpace space, int x, int y, int x_size, int y_size);
    UIntPair generateNextDot(DotSpace space, std::default_random_engine gen);
    UIntPair generateRandomDotInEmptySpace(DotSpace space, std::default_random_engine gen);
    DotSpace regenerateSpaceWithDot(DotSpace space, UIntPair dot, std::default_random_engine gen);
    DotSpace addFieldToGalaxy(DotSpace space, UIntPair dot, std::default_random_engine gen);
    DotSpace markAsOccupied(DotSpace space, UIntPair dot);
    void printDotSpace(DotSpace space);
    void printDotSpaceCandidates(DotSpace space, std::vector<UIntPair> candidates);

public:
    void generateSpace(int x_size, int y_size);
};

#endif // GAMEGEN_H
