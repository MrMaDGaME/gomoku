#include <gtest/gtest.h>
#include <iostream>
#include "../../src/game.hh"

TEST(test_check_5, zeros) {
    Game game;
    EXPECT_EQ(game.check_success(1), false);
    EXPECT_EQ(game.check_success(2), false);
}

TEST(test_check_5, player1) {
    Game game;
    game.set_piece(1, 0, 1);
    game.set_piece(1, 0, 2);
    game.set_piece(1, 0, 3);
    game.set_piece(1, 0, 4);
    game.set_piece(1, 0, 5);
    EXPECT_EQ(game.check_success(1), true);
    EXPECT_EQ(game.check_success(2), false);
}

TEST(test_check_5, player2) {
    Game game;
    game.set_piece(2, 0, 1);
    game.set_piece(2, 0, 2);
    game.set_piece(2, 0, 3);
    game.set_piece(2, 0, 4);
    game.set_piece(2, 0, 5);
    EXPECT_EQ(game.check_success(1), false);
    EXPECT_EQ(game.check_success(2), true);
}

TEST(test_check_5, cross) {
    Game game;
    game.set_piece(2, 1, 1);
    game.set_piece(2, 2, 2);
    game.set_piece(2, 4, 4);
    game.set_piece(2, 5, 5);
    game.set_piece(1, 1, 5);
    game.set_piece(1, 2, 4);
    game.set_piece(1, 3, 3);
    game.set_piece(1, 4, 2);
    game.set_piece(1, 5, 1);
    EXPECT_EQ(game.check_success(1), true);
    EXPECT_EQ(game.check_success(2), false);
}
