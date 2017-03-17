#include "board.h"

int main() {
    unsigned x, y;
    cin >> x >> y;
    Board board(x, y);
    board.readInput();
    board.findNeighbors();
    return 0;
}
