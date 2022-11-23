#pragma once

#include <iostream>
#include <vector>
#include <math.h>
#include "game.hh"

#define MAX_NODES 5000000

class Tree {
public:
    Tree();

    Tree(Game *config, int depth);

    virtual ~Tree();

    int getTotalVisit() const;

    Game &getGame() const;

    Tree &getChildren(int i) const;

    // add child to child list
    Tree &createChild(int move);

    // find the best move to play
    Tree *find_best_move();

    // select the node recursively and return the winner of the simulation
    int select();

    float value() const;

    void setKeeper(Tree *keeper);

    float confidence;

    // debuging display
    void gamePrettyPrinter();

    inline static long count = 0;

    int depth;

protected:
    long id;

    std::vector<Tree *> children;

    int total_visit = 0;

    int success_visit = 0;

    inline static Game *games[MAX_NODES];

    Tree *keeper = nullptr;
};
