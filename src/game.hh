#pragma once

#include <iostream>
#include <array>
#include "check_5.hh"

#define BOARD_SIZE 20

class Game {
public:
    Game();

    Game(Game previous, int move);

    const int *getBoard() const;

    int getPlayer() const;

    int get_index(int x, int y) const;

    int check(t_dim dim, t_point p, t_vec vec) const;

    int precheck(t_dim dim, t_point p, int size) const;

    // check the alignement of size tales for the current_player
    bool check_success(int current_player);

    // testing purpose
    void set_piece(int player, int x, int y);

    int mandatory_moves[BOARD_SIZE * BOARD_SIZE];

    int nb_mandatory_moves = 0;

    int set_mandatory_moves();

    bool check_around(int x, int y) const;

    int getLastMove() const;

    void display();

protected:
    // player who have to play
    int player;

    // display purpose
    int last_move;

    // board represented by a list :
    // 0 for empty
    // 1 for player 1
    // 2 for player 2
    int board[BOARD_SIZE * BOARD_SIZE];
};
