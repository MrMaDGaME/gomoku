#include "gomoku.hh"
#include "tree.hh"

void Gomoku::play(bool is_player1_bot, bool is_player2_bot) {
    Tree *tree = new Tree();
    Tree *new_tree;
    int player = 0;
    while (tree->getGame().nb_mandatory_moves > 0) {
        player = tree->getGame().getPlayer();
        if (player == 1 && !is_player1_bot) {
        }
        else if (player == 2 && !is_player2_bot) {
        }
        else {
            new_tree = tree->find_best_move();
            tree->gamePrettyPrinter();
            std::cout << "choosed children:" << std::endl;
            new_tree->getGame().display();
            tree->setKeeper(new_tree);
            delete (tree);
            tree = new_tree;
            /*std::cout << "Player " << player << " plays "
                      << tree->getGame().getLastMove() % BOARD_SIZE << " "
                      << tree->getGame().getLastMove() / BOARD_SIZE << std::endl;
            tree->getGame().display();
            std::cout << "Count: " << tree->count << std::endl;*/
        }
    }
    std::cout << "Player " << player << " won the game!" << std::endl;
}
