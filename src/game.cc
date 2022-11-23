#include "game.hh"

Game::Game() : player(1), last_move(0), nb_mandatory_moves(1) {
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        board[i] = 0;
        mandatory_moves[i] = 0;
    }
    mandatory_moves[0] = get_index(10, 10);
}

Game::Game(Game previous, int move) : last_move(move) {
    const int *prev = previous.getBoard();
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        board[i] = prev[i];
        mandatory_moves[i] = 0;
    }
    player = 3 - previous.getPlayer();
    board[move] = player;
    nb_mandatory_moves = set_mandatory_moves();
}

int Game::getPlayer() const {
    return player;
}

int Game::get_index(int x, int y) const {
    return y * BOARD_SIZE + x;
}

void Game::set_piece(int current_player, int x, int y) {
    board[get_index(x, y)] = current_player;
}

const int *Game::getBoard() const {
    return board;
}

int Game::getLastMove() const {
    return last_move;
}

void Game::display() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            std::cout << board[get_index(i, j)] << " ";
        }
        std::cout << std::endl;
    }
}

bool Game::check_around(int x, int y) const {
    bool result = false;
    if (x > 0) {
        if (y > 0) {
            result = board[get_index(x - 1, y - 1)];
        }
        if (y < BOARD_SIZE - 1) {
            result = result || board[get_index(x - 1, y + 1)];
        }
        result = result || board[get_index(x - 1, y)];
    }
    if (x < BOARD_SIZE - 1) {
        if (y > 0) {
            result = board[get_index(x + 1, y - 1)];
        }
        if (y < BOARD_SIZE - 1) {
            result = result || board[get_index(x + 1, y + 1)];
        }
        result = result || board[get_index(x + 1, y)];
    }
    if (y > 0) {
        result = result || board[get_index(x, y - 1)];
    }
    if (y < BOARD_SIZE - 1) {
        result = result || board[get_index(x, y + 1)];
    }
    return result;
}

int Game::set_mandatory_moves() {
    int nb_moves = 0;
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (!board[get_index(x, y)] && check_around(x, y)) {
                mandatory_moves[nb_moves++] = get_index(x, y);
            }
        }
    }
    return nb_moves;
}

/*int Game::set_mandatory_moves() {
    int nb_moves = 0;
    t_dim dim = {.columns = BOARD_SIZE, .lines = BOARD_SIZE};
    size_t row = 0;
    t_point p;
    bool success = false;
    while (!success && row < BOARD_SIZE) {
        for (size_t col = 0; !success && col < BOARD_SIZE; col++) {
            if (board[get_index(row, col)] == current_player) {
                p.col = col;
                p.row = row;
                success = precheck(dim, p, 4);
            }
        }
        row++;
    }
    return nb_moves;
}*/
