#include "game.hh"
#include <cstddef>

int Game::check(t_dim dim, t_point p, t_vec vec) const {
    if (vec.i == 1)
        return 1;
    if ((p.row + vec.y < 0 || (p.row + vec.y) >= dim.lines) || p.col + vec.x < 0
        || (p.col + vec.x) >= dim.columns)
        return 0;
    t_point new_p = {.col = p.col + vec.x, .row = p.row + vec.y};
    if (board[get_index(p.row, p.col)] == board[get_index(new_p.row, new_p.col)]) {
        t_vec new_vec = {.x = vec.x, .y = vec.y, .i = vec.i - 1};
        return check(dim, new_p, new_vec);
    }
    return 0;
}

int Game::precheck(t_dim dim, t_point p, int size) const {
    t_vec u = {.x = 0, .y = -1, .i = size};
    t_vec d = {.x = 0, .y = 1, .i = size};
    t_vec l = {.x = -1, .y = 0, .i = size};
    t_vec r = {.x = 1, .y = 0, .i = size};
    t_vec ul = {.x = -1, .y = -1, .i = size};
    t_vec ur = {.x = 1, .y = -1, .i = size};
    t_vec dl = {.x = -1, .y = 1, .i = size};
    t_vec dr = {.x = 1, .y = 1, .i = size};
    return check(dim, p, u) || check(dim, p, d)
           || check(dim, p, l) || check(dim, p, r)
           || check(dim, p, ul) || check(dim, p, ur)
           || check(dim, p, dl) || check(dim, p, dr);
}

bool Game::check_success(int current_player) {
    t_dim dim = {.columns = BOARD_SIZE, .lines = BOARD_SIZE};
    size_t row = 0;
    t_point p;
    bool success = false;
    while (!success && row < BOARD_SIZE) {
        for (size_t col = 0; !success && col < BOARD_SIZE; col++) {
            if (board[get_index(row, col)] == current_player) {
                p.col = col;
                p.row = row;
                success = precheck(dim, p, 5);
            }
        }
        row++;
    }
    if (success)
        nb_mandatory_moves = 0;
    return success;
}
