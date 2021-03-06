#include "gamegen.hpp"
#include <iostream>
#include <iomanip>
#include "debug_functions.hpp"
#include <sstream>

/**
 * Calculates for a field in DotSpace a weight for the choosing algorithm
 */
int GameGen::calculateNeighborWeight(DotSpace space, int x, int y, int x_size, int y_size, int neighbor_span)
{
    for (int i = 1; i <= neighbor_span; i++)
    {
        for (int j = -i; j <= i; j++)
        {
            auto x2 = x + j;
            auto y2_1 = y - (i - abs(j));
            auto y2_2 = y + (i - abs(j));

            // First y
            if (x2 < 0 || x2 >= x_size ||
                y2_1 < 0 || y2_1 >= y_size ||
                space[x2][y2_1] == 1)
            {
                return 1;
            };
            // Second y, if existing
            if (y2_1 != y2_2 &&
                (x2 < 0 || x2 >= x_size ||
                 y2_2 < 0 || y2_2 >= y_size ||
                 space[x2][y2_2] == 1))
            {
                return 1;
            }
        }
    }

    return 0;
}

PatternList GameGen::getPatterns()
{
    // Patterns
    // 0: content irrelevant
    // 1: occupied
    // 2: free
    // 3: free / center of a new galaxy
    PatternList pattern_list;

    // Most important pattern has to be first in pattern list
    // □ □ □
    // □ ▣ □
    // □ □ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 3, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □ □
    // □ ▣ □
    //   □ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 0, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1, 0, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 3, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 1, 1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    //   □ □
    // □ ▣ □
    // □ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 0, 0, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 3, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1, 0, 0});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0, 0, 0});
        pattern_list.push_back(pattern);
    }

    // □ □ □
    //   ▣
    // □ □ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 2, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 3, 1, 0, 0});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 2, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □   □
    // □ ▣ □
    // □   □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 0, 0, 0, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 1, 0, 1, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 1, 1, 1, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 3, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 1, 1, 1, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 1, 0, 1, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 0, 0, 0, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □ □
    // □ □
    // □ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 3, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □ □ □
    // □ □ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 3, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    //   □ □
    //   ▣
    // □ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 0, 0, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 2, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 3, 1, 0, 0});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 2, 1, 0, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1, 0, 0});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0, 0, 0});
        pattern_list.push_back(pattern);
    }

    // □ □
    //   ▣
    //   □ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0, 0, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1, 0, 0});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 2, 1, 0, 0});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 3, 1, 0, 0});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 2, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □
    // □ ▣ □
    //     □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 0, 0, 0, 0, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 1, 0, 0, 0, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 1, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 3, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 0, 0, 0, 1, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 0, 0, 0, 0, 1, 0});
        pattern_list.push_back(pattern);
    }

    //     □
    // □ ▣ □
    // □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 0, 0, 0, 0, 1, 0});
        pattern.push_back(DotSpaceColumn{0, 0, 0, 0, 1, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 3, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 1, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 1, 0, 0, 0, 0});
        pattern.push_back(DotSpaceColumn{0, 1, 0, 0, 0, 0, 0});
        pattern_list.push_back(pattern);
    }

    //   □ □
    // □ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 0, 0, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 3, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1, 0, 0});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0, 0, 0});
        pattern_list.push_back(pattern);
    }

    // □ □
    //   □ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0, 0, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1, 0, 0});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 3, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 0, 1, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □
    // □ □
    //   □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 0, 0, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 0, 0, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 3, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 0, 0, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 0, 0, 1, 0});
        pattern_list.push_back(pattern);
    }

    //   □
    // □ □
    // □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 0, 0, 0, 0, 1, 0});
        pattern.push_back(DotSpaceColumn{0, 0, 0, 0, 1, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 3, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 1, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 1, 0, 0, 0, 0});
        pattern.push_back(DotSpaceColumn{0, 1, 0, 0, 0, 0, 0});
        pattern_list.push_back(pattern);
    }

    // □ □
    // □ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 3, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □ ▣ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 3, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □
    // ▣
    // □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 3, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □ □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 3, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □
    // □
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 3, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 0});
        pattern_list.push_back(pattern);
    }

    // ▣
    {
        Pattern pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 3, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 0});
        pattern_list.push_back(pattern);
    }

    return pattern_list;
}

DotSpace GameGen::addBorder(DotSpace space, int filler)
{
    auto x_size = space.size();
    auto y_size = space[0].size();

    DotSpace newSpace;
    // Create border line
    DotSpaceColumn occupiedLine;
    for (int i = 0; i < y_size + 2; i++)
    {
        occupiedLine.push_back(filler);
    }

    // Create space
    newSpace.push_back(occupiedLine);
    for (int x = 0; x < x_size; x++)
    {
        DotSpaceColumn line;
        line.push_back(filler);
        for (int y = 0; y < y_size; y++)
        {
            line.push_back(space[x][y]);
        }
        line.push_back(filler);
        newSpace.push_back(line);
    }
    newSpace.push_back(occupiedLine);

    return newSpace;
}

std::pair<DotPositionList, DotSpace> GameGen::generateNextDotsByPattern(DotSpace space, std::vector<DotSpace> pattern_list)
{
    // Prepare patterns and space by adding occupied border
    auto tmpSpace = addBorder(space, 1);

    auto x_size = tmpSpace.size();
    for (int x = 0; x < x_size; x++)
    {
        auto y_size = tmpSpace[x].size();
        for (int y = 0; y < y_size; y++)
        {
            auto value = tmpSpace[x][y];

            // Iterate through all patterns
            auto pattern_size = pattern_list.size();
            for (int i = 0; i < pattern_size; i++)
            {
                auto pattern = pattern_list[i];

                DotPositionList new_dot_list;

                // Check if pattern matches
                auto px_size = pattern.size();
                auto py_size = pattern[0].size();
                for (int px = 0; px < px_size; px++)
                {
                    for (int py = 0; py < py_size; py++)
                    {
                        auto x2 = x + px;
                        auto y2 = y + py;

                        if (x2 < x_size && y2 < y_size &&
                            (pattern[px][py] == 0 ||
                             tmpSpace[x2][y2] == 1 && pattern[px][py] == 1 ||
                             tmpSpace[x2][y2] == 0 && pattern[px][py] > 1))
                        {
                            if (pattern[px][py] == 3)
                            {
                                new_dot_list.push_back(DotPosition(x2 - 1, y2 - 1));
                            }
                        }
                        else
                        {
                            goto nextPattern; // continue 3
                        }
                    }
                }

                // Found a matching pattern! Occupy space
                {
                    auto occupiedSpace = false;
                    for (int px = 0; px < px_size; px++)
                    {
                        for (int py = 0; py < py_size; py++)
                        {
                            auto x2 = x - 1 + px;
                            auto y2 = y - 1 + py;
                            if (x2 % 2 == 0 && y2 % 2 == 0 &&
                                x2 >= 0 && y2 >= 0 &&
                                x2 < x_size - 2 && y2 < y_size - 2 &&
                                pattern[px][py] > 1)
                            {
                                space = markAsOccupied(space, DotPosition(x2, y2), 1);
                                occupiedSpace = true;
                            }
                        }
                    }
                    if (!occupiedSpace)
                        throw "Did not occupy space!";
                }
                return std::pair<DotPositionList, DotSpace>(new_dot_list, space);
            nextPattern:;
            }
        }
    }
    throw "No pattern found :(";
}

std::pair<DotPositionList, DotSpace> GameGen::generateNextDots(DotSpace space, PatternList pattern_list, std::default_random_engine gen)
{
    try
    {
        // First try pattern matching
        return generateNextDotsByPattern(space, pattern_list);
    }
    catch (...)
    {
        // If that doesn't work, generate random dot
        auto new_dot = generateRandomDotInEmptySpot(space, gen);
        space = generateGalaxyFromDot(space, new_dot, gen);

        DotPositionList new_dot_list;
        new_dot_list.push_back(new_dot);
        return std::pair<DotPositionList, DotSpace>(new_dot_list, space);
    }
}

DotPositionList GameGen::getRandomDotCandidates(DotSpace space, int min_distance_to_filled)
{
    // Determine possible candidates
    DotPositionList candidates;
    auto x_size = space.size();
    for (int x = 0; x < x_size; x++)
    {
        auto y_size = space[x].size();
        for (int y = 0; y < y_size; y++)
        {
            // Calculate neighbor score
            auto penalty = calculateNeighborWeight(space, x, y, x_size, y_size, min_distance_to_filled);
            auto neighbor_score = 1 - penalty;

            if (space[x][y] == 0 && neighbor_score > 0)
            {
                auto dotPos = DotPosition(x, y);
                candidates.push_back(dotPos);
            }
        }
    }
    return candidates;
}

/**
 * Generates a random dot in the empty spots. Tries to use a weight function
 * to prefer spaces which allow bigger galaxies.
 *
 * @return generatedDot
 */
DotPosition GameGen::generateRandomDotInEmptySpot(DotSpace space, std::default_random_engine gen)
{
    DotPositionList candidates;
    auto search_radius = 3;
    for (int i = search_radius; i >= 0; i--)
    {
        candidates = getRandomDotCandidates(space, i);

        printDotSpaceCandidates(space, candidates);

        if (candidates.size() > 0)
        {
            break;
        }
    }
    if (candidates.size() == 0)
    {
        throw "Found no candidates!";
    }

    // Choose one candidate randomly
    // Assert: There MUST be candidates if this function is called
    std::uniform_int_distribution<unsigned int> gen_pos_index(0, candidates.size() - 1);
    auto new_dot_index = gen_pos_index(gen);

    return candidates[new_dot_index];
}

/**
 * Helper function which counts the empty spots in a DotSpace.
 *
 * @return number of empty spots
 */
unsigned int GameGen::countEmptySpots(DotSpace space)
{
    auto x_size = space.size();
    unsigned int empty_spaces_total = 0;

    // Determine which y values have empty places for the dots to go to
    // Save y index and amount of empty spaces
    for (auto x = 0; x < x_size; x++)
    {
        auto y_size = space[x].size();
        // Simply counts the empty spaces
        for (auto y = 0; y < y_size; y++)
        {
            if (space[x][y] == 0)
            {
                ++empty_spaces_total;
            }
        }
    }

    return empty_spaces_total;
}

/**
 * Takes a space and a dot and places the dot in the space.
 * For this dot a randomised galaxy is created and the space for that gets
 * occupied.
 *
 * @return DotSpace after adding dot
 */
DotSpace GameGen::generateGalaxyFromDot(DotSpace space, DotPosition dot, std::default_random_engine gen)
{
    space = markAsOccupied(space, dot, 2);

    // Add fields to galaxy/
    auto field = 0;
    std::uniform_int_distribution<unsigned int> gen_pos_index(1, 100);
    int probability;
    unsigned int dice;
    int mid_of_bell = (space.size() * space[0].size()) / 40 - 1;
    auto steepness = 10;

    do
    {
        auto result = addFieldToGalaxy(space, dot, gen);
        space = result.first;
        ++field;
        // There are no fields to add anymore... :(
        if (!result.second)
            break;

        probability = (-50 * (field - mid_of_bell)) / (sqrt(steepness + pow(field - mid_of_bell, 2))) + 50;
        dice = gen_pos_index(gen);
    } while (dice <= probability);

    // Normalize entries in space
    auto x_size = space.size();
    for (auto x = 0; x < x_size; x++)
    {
        auto y_size = space[x].size();
        for (auto y = 0; y < y_size; y++)
        {
            if (space[x][y] == 2)
            {
                space[x][y] = 1;
            }
        }
    }

    return space;
}

/**
 * Takes a DotSpace with 2s where the current galaxy is generated and the
 * center of the galaxy and tries to add another field to this galaxy.
 *
 * @return DotSpace after addition of field
 */
std::pair<DotSpace, bool> GameGen::addFieldToGalaxy(DotSpace space, DotPosition dot, std::default_random_engine gen)
{
    // Determine possible candidates
    DotPositionList candidates;

    auto x_size = space.size();
    for (auto x = 0; x < x_size; x += 2)
    {
        auto y_size = space[x].size();
        for (auto y = 0; y < y_size; y += 2)
        {
            // Check if field is adjacent
            auto left = x > 0 && space[x - 1][y] == 2;
            auto right = x + 1 < x_size && space[x + 1][y] == 2;
            auto top = y > 0 && space[x][y - 1] == 2;
            auto bottom = y + 1 < y_size && space[x][y + 1] == 2;

            if (space[x][y] == 0 && (left || right || top || bottom))
            {
                // Check if corresponding field is free too
                auto x2 = 2 * dot.first - x;
                auto y2 = 2 * dot.second - y;
                if (x2 >= 0 && y2 >= 0 && x2 < x_size && y2 < y_size && space[x2][y2] == 0)
                {
                    auto dot_pos = DotPosition(x, y);
                    auto penalty1 = 4 * calculateNeighborWeight(space, x, y, x_size, y_size, 2) + 1;
                    auto penalty2 = 4 * calculateNeighborWeight(space, x2, y2, x_size, y_size, 2) + 1;
                    for (int i = 0; i < std::max(penalty1, penalty2); i++)
                    {
                        candidates.push_back(dot_pos);
                    }
                }
            }
        }
    }

    printDotSpaceCandidates(space, candidates);

    // Choose one candidate randomly
    if (candidates.size() > 0)
    {
        std::uniform_int_distribution<unsigned int> gen_pos_index(0, candidates.size() - 1);
        auto new_field_index = gen_pos_index(gen);

        auto winner = candidates[new_field_index];

        space = markAsOccupied(space, winner, 2);

        // Mark corresponding field as well
        auto x2 = 2 * dot.first - winner.first;
        auto y2 = 2 * dot.second - winner.second;
        if (x2 >= 0 && y2 >= 0 && x2 < x_size && y2 < space[x2].size())
        {
            space = markAsOccupied(space, DotPosition(x2, y2), 2);
        }
    }

    return std::pair<DotSpace, bool>(space, candidates.size() > 0);
}

/**
 * Marks a field in DotSpace as occupied and marks all newly not possible
 * spots as occupied as well.
 *
 * @return DotSpace after occupation
 */
DotSpace GameGen::markAsOccupied(DotSpace space, DotPosition dot, int filler)
{
    auto x_size = space.size();
    auto y_size = space[0].size();

    auto dot_x = dot.first;
    auto dot_y = dot.second;

    // Is a dot on an edge or corner even more places are not available anymore
    auto x_diff = dot_x % 2 == 1 ? 2 : 1;
    auto y_diff = dot_y % 2 == 1 ? 2 : 1;

    // Every place around the dot is not available anymore
    for (auto i = -x_diff; i <= x_diff; i++)
    {
        for (auto j = -y_diff; j <= y_diff; j++)
        {
            auto x = dot_x + i;
            auto y = dot_y + j;

            if (x >= 0 && y >= 0 && x < x_size && y < y_size && space[x][y] == 0)
            {
                space[x][y] = filler;
            }
        }
    }

    return space;
}

/**
 * Helper for debugging purposes.
 * Prints out a DotSpace.
 */
void GameGen::printDotSpace(DotSpace space)
{
    auto x_size = space.size();
    auto y_size = space[0].size();
    std::stringstream s;
    // Print Header
    s << "   ";
    for (int i = 0; i < x_size; i++)
    {
        s << std::setw(2) << std::setfill('0') << i << " ";
    }
    s << std::endl;

    // Every place around the dot is not available anymore
    for (auto i = 0; i < y_size; i++)
    {
        s << std::setw(2) << std::setfill('0') << i << " ";
        for (auto j = 0; j < x_size; j++)
        {
            s << " " << space[j][i] << " ";
        }
        s << std::endl;
    }
    DBG_LOG(HIGH, s.str());
}

/**
 * Helper for debugging purposes.
 * Prints out a DotSpace and the amount of candidates for a single spot.
 */
void GameGen::printDotSpaceCandidates(DotSpace space, DotPositionList candidates)
{
    auto x_size = space.size();
    auto y_size = space[0].size();
    std::stringstream s;
    // Print Header
    s << "    ";
    for (int i = 0; i < x_size; i++)
    {
        s << std::setw(3) << std::setfill('0') << i << " ";
    }
    s << std::endl;

    // Every place around the dot is not available anymore
    for (auto i = 0; i < y_size; i++)
    {
        s << std::setw(3) << std::setfill('0') << i << " ";
        for (auto j = 0; j < x_size; j++)
        {
            auto amount = 0;
            for (int k = 0; k < candidates.size(); k++)
            {
                auto candidate = candidates[k];
                if (candidate.first == j && candidate.second == i)
                {
                    ++amount;
                }
            }
            s << std::setw(3) << std::setfill(' ') << amount << " ";
        }
        s << std::endl;
    }
    DBG_LOG(HIGH, s.str());
}

/**
 * Entrypoint into dot generation.
 * Takes the size of the field and generates dots in it which are then returned.
 *
 * @return List of generated dots
 */
DotPositionList GameGen::generateDots(int x_size, int y_size)
{
    // Generate empty space
    DotSpace space;
    for (auto i = 0; i < x_size * 2 - 1; i++)
    {
        DotSpaceColumn column;
        for (auto j = 0; j < y_size * 2 - 1; j++)
        {
            column.push_back(0);
        }
        space.push_back(column);
    }

    // Generate dots in space
    PatternList pattern_list = getPatterns();
    DotPositionList new_dot_list;
    unsigned int empty_spaces;
    std::random_device rd;
    std::default_random_engine gen(rd());
    do
    {
        auto result = generateNextDots(space, pattern_list, gen);
        for (int i = 0; i < result.first.size(); i++)
        {
            new_dot_list.push_back(result.first[i]);
        }
        space = result.second;
        empty_spaces = countEmptySpots(space);
        // Debugging statements
        printDotSpace(space);
    } while (empty_spaces > 0);

    return new_dot_list;
}
