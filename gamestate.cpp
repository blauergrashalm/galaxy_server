#include "gamestate.h"
#include <random>
#include <iostream>

GameState::GameState(unsigned int x_size, unsigned int y_size) : x_size{x_size}, y_size{y_size}
{
    fields.resize(x_size);
    for(int i =0; i < x_size; i++){
        fields[i].resize(y_size);
        for(int j = 0; j < y_size; j++){
            fields[i][j] =  std::make_shared<Field>(i,j);
        }
    }
    generateRandomDots();
}

json GameState::toJson()
{
    json game_state;
    for(int i = 0; i < fields.size(); i++){
        for(int j = 0; j < fields[i].size();j++){
            game_state["fields"].push_back(fields[i][j]->toJson());
            
        }
    }
    for (auto &&pair : dots){
        game_state["dots"].push_back(pair.second->toJson());
    }
    return game_state;
}

void GameState::generateRandomDots()
{
    std::default_random_engine gen;
    std::uniform_int_distribution<unsigned int> dist_x(0, x_size-1);
    std::uniform_int_distribution<unsigned int> dist_y(0, y_size-1);
    
    int count = (x_size * y_size) / 12;
    
    for(int i = 0; i < count; i++){
        pos_type p{dist_x(gen), dist_y(gen)};
        dots.insert( std::pair<pos_type, std::shared_ptr<Dot> >( p, std::make_shared<Dot>( p.x,p.y ) ) );
    }
    
}

