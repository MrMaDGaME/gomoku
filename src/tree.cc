#include "tree.hh"

#define DURATION 4

Tree::Tree() : id(count++ % MAX_NODES) {
    games[id] = new Game();
}

Tree::Tree(Game *config) : id(count++ % MAX_NODES) {
    games[id] = config;
}

Tree &Tree::getChildren(int i) const {
    return *children.at(i);
}

Game &Tree::getGame() const {
    return *games[id];
}

Tree &Tree::createChild(int move) {
    children.push_back(new Tree(new Game(getGame(), move)));
    return *children.at(children.size() - 1);
}

Tree *Tree::find_best_move() {
    std::time_t start_time = std::time(nullptr);
    std::time_t now = std::time(nullptr);
    while (now - start_time < DURATION) {
        select();
        now = std::time(nullptr);
    }
    if (children.empty()) {
        throw std::out_of_range("No children found");
    }
    Tree *best_move = children.at(0);
    float best_ratio = 0;
    for (Tree *move: children) {
        if (move->value() > best_ratio) {
            best_ratio = move->value();
            best_move = move;
        }
    }
    return best_move;
}

int Tree::select() {
    int winner;
    // Select
    int T = 2;
    if (!children.empty() && total_visit < T) {
        float confidence_max = 0;
        int max_index = 0;
        for (size_t i = 0; i < children.size(); i++) {
            float temp = (getTotalVisit() > 0 && getChildren(i).getTotalVisit() > 0) ?
                         log(getTotalVisit()) / getChildren(i).getTotalVisit() : 0;
            getChildren(i).confidence = getChildren(i).value() + 0.7 * sqrt(temp);
            if (getChildren(i).confidence > confidence_max) {
                confidence_max = getChildren(i).confidence;
                max_index = i;
            }
        }
        winner = getChildren(max_index).select();
    }
        // Simulate expand and check_success
    else if (getGame().nb_possible_move > 0) {
        if (getGame().check_success(1)) {
            winner = 1;
        }
        else if (getGame().check_success(2)) {
            winner = 2;
        }
        else {
            std::srand(std::time(nullptr));
            int move;
            // mandatory moves
            if (getGame().nb_mandatory_moves) {
                move = getGame().mandatory_moves[std::rand() % getGame().nb_mandatory_moves];
            }
                // random moves
            else {
                move = getGame().possible_move[std::rand() % getGame().nb_possible_move];
            }
            winner = createChild(move).select();
        }
    }
        // end of the game
    else {
        winner = 0;
    }
    // backpropagation
    total_visit += 1;
    if (getGame().getPlayer() == winner) {
        success_visit += 1;
    }
    return winner;
}

int Tree::getTotalVisit() const {
    return total_visit;
}

float Tree::value() const {
    return (total_visit > 0) ? success_visit / (total_visit) : 0;
}

Tree::~Tree() {
    for (Tree *child: children) {
        if (child != keeper) {
            delete (child);
        }
    }
    count--;
}

void Tree::setKeeper(Tree *keeper_) {
    Tree::keeper = keeper_;
}
