#include "gamestate.hpp"
#include <iostream>

GameState::GameState(unsigned int x_size, unsigned int y_size) : x_size{x_size}, y_size{y_size}
{
    for (unsigned int i = 0; i < x_size; i++)
    {
        for (unsigned int j = 0; j < y_size; j++)
        {
            addField({i, j});
        }
    }
    generateSpace();
}

json GameState::toJson()
{
    json game_state;
    game_state["size_x"] = x_size;
    game_state["size_y"] = y_size;
    for (auto &&pair : fields)
    {
        game_state["fields"].push_back(pair.second->toJson());
    }
    for (auto &&pair : dots)
    {
        game_state["dots"].push_back(pair.second->toJson());
    }
    return game_state;
}

std::pair<DotSpace, UIntPair> GameState::generateRandomDotInEmptySpace(DotSpace space, std::default_random_engine gen)
{
    // Determine possible candidates
    std::vector<UIntPair> candidates;

    auto x_size = space.size();
    for (auto x = 0; x < x_size; x++)
    {
        auto y_size = space[x].size();
        for (auto y = 0; y < y_size; y++)
        {
            // Check how many neighbors are filled
            int filled_neighbors = 0;
            filled_neighbors += x <= 0 || space[x - 1][y] == 1 ? 1 : 0;                                 // left
            filled_neighbors += x + 1 >= x_size || space[x + 1][y] == 1 ? 1 : 0;                        // right
            filled_neighbors += y <= 0 || space[x][y - 1] == 1 ? 1 : 0;                                 // top
            filled_neighbors += y + 1 >= y_size || space[x][y + 1] == 1 ? 1 : 0;                        // bottom
            filled_neighbors += x <= 0 || y <= 0 || space[x - 1][y - 1] == 1 ? 1 : 0;                   // top-left
            filled_neighbors += x + 1 >= x_size || y <= 0 || space[x + 1][y - 1] == 1 ? 1 : 0;          // top-right
            filled_neighbors += x <= 0 || y + 1 >= y_size || space[x - 1][y + 1] == 1 ? 1 : 0;          // bottom-left
            filled_neighbors += x + 1 >= x_size || y + 1 >= y_size || space[x + 1][y + 1] == 1 ? 1 : 0; // bottom-right

            auto neighbor_score = std::max(6 - filled_neighbors, 1);

            if (space[x][y] == 0)
            {
                // Give candidates with few filled neighbors a higher weight
                for (int i = 0; i < pow(neighbor_score, 2); i++)
                {
                    candidates.push_back(UIntPair(x, y));
                }
            }
        }
    }

    // Choose one candidate randomly
    // Assert: There MUST be candidates if this function is called
    std::uniform_int_distribution<unsigned int> gen_pos_index(0, candidates.size() - 1);
    auto new_dot_index = gen_pos_index(gen);

    auto winner = candidates[new_dot_index];

    pos_type new_dot_pos{winner.first, winner.second};
    addDot(new_dot_pos);

    return std::pair<DotSpace, UIntPair>(space, winner);
}

unsigned int GameState::getEmptySpacesFromSpace(DotSpace space)
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

DotSpace GameState::regenerateSpaceWithDot(DotSpace space, std::pair<unsigned int, unsigned int> dot, std::default_random_engine gen)
{
    space = markAsOccupied(space, dot);

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

DotSpace GameState::addFieldToGalaxy(DotSpace space, UIntPair dot, std::default_random_engine gen)
{
    // Determine possible candidates
    std::vector<UIntPair> candidates;

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
                    candidates.push_back(UIntPair(x, y));
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

        space = markAsOccupied(space, winner);

        // Mark corresponding field as well
        auto x2 = 2 * dot.first - winner.first;
        auto y2 = 2 * dot.second - winner.second;
        if (x2 >= 0 && y2 >= 0 && x2 < x_size && y2 < space[x2].size())
        {
            space = markAsOccupied(space, UIntPair(x2, y2));
        }
    }

    return space;
}

DotSpace GameState::markAsOccupied(DotSpace space, UIntPair dot)
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
                space[x][y] = 2;
            }
        }
    }

    return space;
}

// Helper for debugging purposes
void GameState::printDotSpace(DotSpace space)
{
    auto x_size = space.size();
    auto y_size = space[0].size();

    // Print Header
    std::cout << " ";
    for (int i = 0; i < x_size; i++)
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;

    // Every place around the dot is not available anymore
    for (auto i = 0; i < y_size; i++)
    {
        std::cout << i << " ";
        for (auto j = 0; j < x_size; j++)
        {
            std::cout << space[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

void GameState::generateSpace()
{
    // Generate empty space
    std::vector<std::vector<unsigned int>> space;
    for (auto i = 0; i < x_size * 2 - 1; i++)
    {
        std::vector<unsigned int> column;
        for (auto j = 0; j < y_size * 2 - 1; j++)
        {
            column.push_back(0);
        }
        space.push_back(column);
    }

    // Generate dots in space
    unsigned int empty_spaces;
    std::random_device rd;
    std::default_random_engine gen(rd());
    do
    {
        std::pair<DotSpace, std::pair<unsigned int, unsigned int>> result = generateRandomDotInEmptySpace(space, gen);
        space = result.first;
        space = regenerateSpaceWithDot(space, result.second, gen);
        empty_spaces = getEmptySpacesFromSpace(space);
        // Debugging statements
        printDotSpace(space);
        std::cout << std::endl;
    } while (empty_spaces > 0);
}

void GameState::generateRandomDots()
{
    std::random_device rd;
    std::default_random_engine gen(rd());
    std::uniform_int_distribution<unsigned int> dist_x(0, x_size * 2 - 1);
    std::uniform_int_distribution<unsigned int> dist_y(0, y_size * 2 - 1);

    int count = (x_size * y_size) / 12;

    for (int i = 0; i < count; i++)
    {
        pos_type p{dist_x(gen), dist_y(gen)};
        addDot(p);
    }
}

void GameState::addDot(pos_type position)
{
    auto dot = std::make_shared<Dot>(position.x, position.y);
    dots.insert(std::pair<pos_type, std::shared_ptr<Dot>>(position, dot));
    dots_by_id.insert(std::pair<unsigned int, std::shared_ptr<Dot>>(dot->id, dot));
}

void GameState::addField(pos_type position)
{
    auto field = std::make_shared<Field>(position.x, position.y);
    fields.insert(std::pair<pos_type, std::shared_ptr<Field>>(position, field));
    fields_by_id.insert(std::pair<unsigned int, std::shared_ptr<Field>>(field->id, field));
}
