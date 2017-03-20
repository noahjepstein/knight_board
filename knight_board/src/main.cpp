/*  main.cpp
    Client of Board class.
    Represents the solution for the knight board challenge.
    Author: Noah J Epstein
            noahjepstein@gmail.com
*/


#include "board.h"

int main() {

    Move m;
    unsigned x, y;

    cout << "Start X Coord? " << endl;
    cin >> m.x1;
    cout << endl << "Start Y Coord? " << endl;
    cin >> m.y1;
    cout << "End X Coord? " << endl;
    cin >> m.x2;
    cout << endl << "End Y Coord? " << endl;
    cin >> m.y2;
    cin >> x >> y;

    Board board(x, y);
    board.readInput();
    board.printBoard();
    board.findNeighbors();

    /* level 2 */
    // vector<Move> ms1 = board.generateMoveSeq(m);
    // board.validateMoveSeq(ms1);

    /* level 3 */
    vector<Move> ms2 = board.generateOptimalMoveSeq(m);
    board.validateMoveSeq(ms2);

    // /* level 5 */
    // vector<Move> ms3 = board.generateLongestSeq(m);
    // board.validateMoveSeq(ms3);

    return 0;
}
