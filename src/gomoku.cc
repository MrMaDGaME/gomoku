#include "gomoku.hh"
#include "tree.hh"

void Gomoku::play(bool is_player1_bot, bool is_player2_bot) {
    Tree *tree = new Tree();
    int player = 0;
    while (tree->getGame().nb_possible_move > 0) {
        player = tree->getGame().getPlayer();
        if (player == 1 && !is_player1_bot) {
        }
        else if (player == 2 && !is_player2_bot) {
        }
        else {
            Tree *new_tree = tree->find_best_move();
            tree->setKeeper(new_tree);
            delete (tree);
            tree = new_tree;
            std::cout << "Player " << player << " plays "
                      << tree->getGame().getLastMove() % BOARD_SIZE << " "
                      << tree->getGame().getLastMove() / BOARD_SIZE << std::endl;
            tree->getGame().display();
            std::cout << "Count: " << tree->count << std::endl;
        }
    }
    std::cout << "Player " << player << " won the game!" << std::endl;
}
