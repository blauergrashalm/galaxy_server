#include "gamegen.h"
#include <iostream>
#include <iomanip>

// Calculates for a field in DotSpace a weight for the choosing algorithm
int GameGen::calculateNeighborPenalty(DotSpace space, int x, int y, int x_size, int y_size)
{
    auto neighbor_span = 5; // Has to be positive

    auto neighbor_penalty = 0;
    for (int i = 1; i <= neighbor_span; i++)
    {
        auto factor = pow(neighbor_span - i + 1, 2);

        for (int j = -i; j <= i; j++)
        {
            auto x2 = x + j;
            auto y2_1 = y - (i - abs(j));
            auto y2_2 = y + (i - abs(j));

            // First y
            neighbor_penalty += factor * (x2 < 0 || x2 >= x_size || y2_1 < 0 || y2_1 >= y_size || space[x2][y2_1] == 1 ? 1 : 0);
            // Second y, if existing
            if (y2_1 != y2_2)
            {
                neighbor_penalty += factor * (x2 < 0 || x2 >= x_size || y2_2 < 0 || y2_2 >= y_size || space[x2][y2_2] == 1 ? 1 : 0);
            }
        }
    }

    return neighbor_penalty;
}

std::vector<DotSpace> GameGen::getPatterns()
{
    // Patterns
    // 0: content irrelevant
    // 1: occupied
    // 2: free
    // 3: free / center of a new galaxy
    std::vector<DotSpace> pattern_list;

    // Most important pattern has to be first in pattern list
    // □ □ □
    // □ ▣ □
    // □ □ □
    {
        DotSpace pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 3, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □ □ □
    //   ▣
    // □ □ □
    {
        DotSpace pattern;
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
        DotSpace pattern;
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
        DotSpace pattern;
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
        DotSpace pattern;
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
        DotSpace pattern;
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
        DotSpace pattern;
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
        DotSpace pattern;
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
        DotSpace pattern;
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
        DotSpace pattern;
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
        DotSpace pattern;
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
        DotSpace pattern;
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
        DotSpace pattern;
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
        DotSpace pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 3, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □ ▣ □
    {
        DotSpace pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 2, 3, 2, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □
    // ▣
    // □
    {
        DotSpace pattern;
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
        DotSpace pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 3, 2, 1});
        pattern.push_back(DotSpaceColumn{0, 1, 1, 1, 0});
        pattern_list.push_back(pattern);
    }

    // □
    // □
    {
        DotSpace pattern;
        pattern.push_back(DotSpaceColumn{0, 1, 0});
        pattern.push_back(DotSpaceColumn{1, 2, 1});
        pattern.push_back(DotSpaceColumn{1, 3, 1});
        pattern.push_back(DotSpaceColumn{1, 2, 1});
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
                                new_dot_list.push_back(DotPosition(x, y));
                            }
                        }
                        else
                        {
                            goto nextPattern; // continue 3
                        }
                    }
                }

                // Found a matching pattern! Occupy space
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
                            space = markAsOccupied(space, DotPosition(x, y), 1);
                        }
                    }
                }
                return std::pair<DotPositionList, DotSpace>(new_dot_list, space);
            nextPattern:;
            }
        }
    }
    throw "No pattern found :(";
}

std::pair<DotPositionList, DotSpace> GameGen::generateNextDots(DotSpace space, std::default_random_engine gen)
{
    printDotSpace(space);
    std::cout << std::endl;

    // First try pattern matching
    auto pattern_list = getPatterns();

    try
    {
        return generateNextDotsByPattern(space, pattern_list);
    }
    catch (...)
    {
        auto new_dot = generateRandomDotInEmptySpot(space, gen);
        space = generateGalaxyFromDot(space, new_dot, gen);

        DotPositionList new_dot_list;
        new_dot_list.push_back(new_dot);
        return std::pair<DotPositionList, DotSpace>(new_dot_list, space);
    }
}

/**
 * Generates a random dot in the empty spots. Tries to use a weight function
 * to prefer spaces which allow bigger galaxies.
 *
 * @return generatedDot
 */
DotPosition GameGen::generateRandomDotInEmptySpot(DotSpace space, std::default_random_engine gen)
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
            auto penalty = calculateNeighborPenalty(space, x, y, x_size, y_size);
            // Depends on neighbor_span
            auto neighbor_score = std::max(261 - penalty, 1);

            if (space[x][y] == 0)
            {
                auto dotPos = DotPosition(x, y);
                // Give candidates with few filled neighbors a higher weight
                for (int i = 0; i < neighbor_score; i++)
                {
                    candidates.push_back(dotPos);
                }
            }
        }
    }

    //printDotSpaceCandidates(space, candidates);
    //std::cout << std::endl;

    // Choose one candidate randomly
    // Assert: There MUST be candidates if this function is called
    std::uniform_int_distribution<unsigned int> gen_pos_index(0, candidates.size());
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
    double probability;
    unsigned int dice;
    auto mid_of_bell = 7;
    auto steepness = 10;

    do
    {
        space = addFieldToGalaxy(space, dot, gen);
        ++field;

        probability = -50 * (field - mid_of_bell) / (sqrt(steepness + pow(field - mid_of_bell, 2))) + 50;
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
DotSpace GameGen::addFieldToGalaxy(DotSpace space, DotPosition dot, std::default_random_engine gen)
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
                    candidates.push_back(DotPosition(x, y));
                }
            }
        }
    }

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

    return space;
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

    // Print Header
    std::cout << "   ";
    for (int i = 0; i < x_size; i++)
    {
        std::cout << std::setw(2) << std::setfill('0') << i << " ";
    }
    std::cout << std::endl;

    // Every place around the dot is not available anymore
    for (auto i = 0; i < y_size; i++)
    {
        std::cout << std::setw(2) << std::setfill('0') << i << " ";
        for (auto j = 0; j < x_size; j++)
        {
            std::cout << " " << space[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

/**
 * Helper for debugging purposes.
 * Prints out a DotSpace and the amount of candidates for a single spot.
 */
void GameGen::printDotSpaceCandidates(DotSpace space, DotPositionList candidates)
{
    auto x_size = space.size();
    auto y_size = space[0].size();

    // Print Header
    std::cout << "    ";
    for (int i = 0; i < x_size; i++)
    {
        std::cout << std::setw(3) << std::setfill('0') << i << " ";
    }
    std::cout << std::endl;

    // Every place around the dot is not available anymore
    for (auto i = 0; i < y_size; i++)
    {
        std::cout << std::setw(3) << std::setfill('0') << i << " ";
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
            std::cout << std::setw(3) << std::setfill(' ') << amount << " ";
        }
        std::cout << std::endl;
    }
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
    DotPositionList new_dot_list;
    unsigned int empty_spaces;
    std::random_device rd;
    std::default_random_engine gen(rd());
    do
    {
        auto result = generateNextDots(space, gen);
        for (int i = 0; i < result.first.size(); i++)
        {
            new_dot_list.push_back(result.first[i]);
        }
        space = result.second;
        empty_spaces = countEmptySpots(space);
        // Debugging statements
        //printDotSpace(space);
        //std::cout << std::endl;
    } while (empty_spaces > 0);

    return new_dot_list;
}
