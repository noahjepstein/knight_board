#include "board.h"

/* EQALITY OVERLOADING FOR NODE, MOVE OBJECTS */

bool operator==(const Node& lhs, const Node& rhs)
{
    return lhs.id == rhs.id;
}

bool operator==(const Move& m1, const Move& m2) {

    return (((m1.x1 == m2.x1) && (m1.x2 == m2.x2) && (m1.y1 == m2.y1) && (m1.y2 == m2.y2)) ||
            ((m1.x1 == m2.x2) && (m1.x2 == m2.x1) && (m1.y1 == m2.y2) && (m1.y2 == m2.y1)));
}

/* BOARD MEMBERS */

Board::Board(int x, int y) {
    x_dim = x;
    y_dim = y;
    n_nodes = x * y;
    Node placeholder_node;
    nodes.resize(n_nodes, placeholder_node);
    knight_pos.x = 0;
    knight_pos.y = 0;
}

Board::~Board() {

}

void Board::printBoard() {
    cout << "\033[2J\033[1;1H";
    cout << "BOARD DIMENSIONS -- X: " << x_dim << " Y: " << y_dim << endl;
    cout << "KNIGHT POSITION  -- X: " << knight_pos.x << " Y: " << knight_pos.y << endl;
    for (int i = 0; i < y_dim; ++i) {
        for (int j = 0; j < x_dim; ++j) {
            if ((j == knight_pos.x) && (i == knight_pos.y)) {
                cout << " K ";
            } else {
                switch (nodes[c2ID(j, i)].type){
                    case PLAIN :
                        cout << " . ";
                        break;

                    case WATER :
                        cout << " W ";
                        break;

                    case BARRIER :
                        cout << " B ";
                        break;

                    case ROCK :
                        cout << " R ";
                        break;

                    case TELEPORT :
                        cout << " T ";
                        break;

                    case LAVA :
                        cout << " L ";
                        break;

                    default:
                        exit(1);
                }
            }
        }
        cout << endl;
    }
}

Move Board::makeMove(Node n1, Node n2) {
    Move m;
    m = {n1.x, n1.y, n2.x, n2.y};
    return m;
}

void Board::readInput() {

    char node;

    int n_teleports_found = 0;

    for (int i = 0; i < y_dim; ++i) {
        for (int j = 0; j < x_dim; ++j) {
            cin >> node;
            Node new_node;
            new_node.id = i * x_dim + j;
            new_node.x = j;
            new_node.y = i;
            new_node.marked = false;
            switch (node){
                case '.' :
                    new_node.type = PLAIN;
                    new_node.weight = 1;
                    break;

                case 'W' :
                    new_node.type = WATER;
                    new_node.weight = 2;
                    break;

                case 'B' :
                    new_node.type = BARRIER;
                    break;

                case 'R' :
                    new_node.type = ROCK;
                    break;

                case 'T' :
                    new_node.type = TELEPORT;
                    new_node.weight = 1;
                    if (n_teleports_found == 0) {
                        tele.x1 = i;
                        tele.y1 = j;
                        n_teleports_found++;
                    } else if (n_teleports_found == 1){
                        tele.x2 = i;
                        tele.y2 = j;
                    } else {
                        cerr << "INVALID INPUT." << endl;
                        exit(1);
                    }
                    break;

                case 'L' :
                    new_node.type = LAVA;
                    new_node.weight = 5;
                    break;

                default:
                    exit(1);
            }
            nodes[new_node.id] = new_node;
        }
    }
}

bool Board::onBoard(int x1, int y1){
    return ((x1 >= 0) && (x1 < x_dim) && (y1 >= 0) && (y1 < y_dim));
}

bool Board::areNeighbors(NodeID nid1, NodeID nid2) {
    if ((nid1 >= 0) && (nid1 < n_nodes) && (nid2 >= 0) && (nid2 < n_nodes)) {
        Node n1 = nodes[nid1];
        auto neigh = find(begin(n1.neighbors), end(n1.neighbors), nid2);
        return (neigh != end(n1.neighbors));
    } else {
        return false;
    }
}

void Board::makeNeighbors(NodeID nid1, NodeID nid2) {
    nodes[nid1].neighbors.push_back(nid2);
    nodes[nid2].neighbors.push_back(nid1);
}

bool Board::validKnightMovePattern(Move m) {

    return ((((m.x2 - m.x1) == -1) && ((m.y2 - m.y1) == -2)) ||
            (((m.x2 - m.x1) == -1) && ((m.y2 - m.y1) ==  2)) ||
            (((m.x2 - m.x1) == -2) && ((m.y2 - m.y1) == -1)) ||
            (((m.x2 - m.x1) == -2) && ((m.y2 - m.y1) ==  1)) ||
            (((m.x2 - m.x1) ==  1) && ((m.y2 - m.y1) == -2)) ||
            (((m.x2 - m.x1) ==  1) && ((m.y2 - m.y1) ==  2)) ||
            (((m.x2 - m.x1) ==  2) && ((m.y2 - m.y1) == -1)) ||
            (((m.x2 - m.x1) ==  2) && ((m.y2 - m.y1) ==  1)));
}

int Board::c2ID(int x, int y) {
    return y * x_dim + x;
}

bool Board::validMove(int x1, int y1, int x2, int y2) {

    Move m;
    m.x1 = x1;
    m.y1 = y1;
    m.x2 = x2;
    m.y2 = y2;
    Node n1, n2;

    if ((onBoard(x1, y1)) && (onBoard(x2, y2))) {
        n1 = nodes[c2ID(x1, y1)];
        n2 = nodes[c2ID(x2, y2)];
        if (areNeighbors(c2ID(x1, y1), c2ID(x2, y2))) {
            return true;
        } else if   (((n1.type != ROCK)
                   && (n2.type != ROCK)
                   && validKnightMovePattern(m)
                   && !crossesBarriers(m))
                   || (m == tele)) {
            makeNeighbors(n1.id, n2.id);
            return true;
        }
    }
    return false;
}

bool Board::validMove(Move m) {

    Node n1, n2;

    if ((onBoard(m.x1, m.y1)) && (onBoard(m.x2, m.y2))) {
        n1 = nodes[c2ID(m.x1, m.y1)];
        n2 = nodes[c2ID(m.x2, m.y2)];
        if (areNeighbors(c2ID(m.x1, m.y1), c2ID(m.x2, m.y2))) {
            return true;
        } else if   (((n1.type != ROCK)
                   && (n2.type != ROCK)
                   && validKnightMovePattern(m)
                   && !crossesBarriers(m))
                   || (m == tele)) {
            makeNeighbors(n1.id, n2.id);
            return true;
        }
    }
    return false;
}

bool Board::crossesBarriers(Move m) {
    m.x1 = 0;
    return false;
}

void Board::findNeighbors() {
/*
    void Board::findNeighbors()
    args: none
    returns: none
    Used to call validMove for each node/move combo.
    Also initializes the edge for the teleport move.
*/

    Node n;

    for (int i = 0; i < y_dim; ++i) {
        for (int j = 0; j < x_dim; ++j) {

            validMove(j, i, j - 1, i - 2);
            validMove(j, i, j + 1, i - 2);
            validMove(j, i, j - 2, i - 1);
            validMove(j, i, j + 2, i - 1);
            validMove(j, i, j - 2, i + 1);
            validMove(j, i, j + 2, i + 1);
            validMove(j, i, j - 1, i + 2);
            validMove(j, i, j + 1, i + 2);
        }
    }
    validMove(tele.x1, tele.y1, tele.x2, tele.y2);
}

bool Board::validateMoveSeq(vector<Move> moveSeq) {

    if (moveSeq.empty()) {
        cout << "EMPTY SEQ?" << endl;
        return true;
    } else {

        Move prev_move = moveSeq[0];

        if (!validMove(prev_move)) {
            return false;
        }

        for (auto move_p = moveSeq.begin() + 1; move_p != moveSeq.end(); ++move_p) {
            knight_pos.x = prev_move.x1;
            knight_pos.y = prev_move.y1;
            if (!validMove(*move_p) || (move_p->x1 != prev_move.x2) || (move_p->y1 != prev_move.y2)) {
                return false;
            }
            prev_move = *move_p;
            printBoard();
        }
    }
    return true;
}


vector<Move> Board::DFSgenerateMoveSeq(Move start_end_positions) {

    vector<Move> seq;
    Node next;
    NodeID start_nid = c2ID(start_end_positions.x1, start_end_positions.y1);
    NodeID end_nid   = c2ID(start_end_positions.x2, start_end_positions.y2);
    Node start = nodes[start_nid];
    Node end   = nodes[end_nid];
    nodes[start_nid].marked = true;

    for (auto nextID_p = start.neighbors.begin(); nextID_p!= start.neighbors.end(); ++nextID_p) {
        next = nodes[*nextID_p];
        usleep(10000);

        if (!next.marked) {
            knight_pos.x = next.x;
            knight_pos.y = next.y;
            printBoard();

            if (next == end) {
                seq.push_back(makeMove(start, end));
                cout << "OMG WE FOUND IT" << endl;
                return seq;
            } else {
                seq = DFSgenerateMoveSeq(makeMove(next, end));
                if (seq.empty()) {
                    continue;
                } else {
                    seq.insert(seq.begin(), makeMove(start, next));
                    return seq;
                }
            }
        }
    }
    return seq;
}

vector<Move> Board::generateMoveSeq(Move start_end_positions) {
    vector<Move> seq = DFSgenerateMoveSeq(start_end_positions);
    if (seq.empty()) {
        cout << "NO POSSIBLE MOVE SEQUENCE TO ARRIVE AT (" << start_end_positions.x2
             << ", " << start_end_positions.y2 << ")" << endl;
    }
    return seq;
}

vector<Move> Board::DijkstraGenerateMoveSeq(Move start_end_positions) {

    vector<Move> seq = DijkstraGenerateMoveSeq(start_end_positions);
    if (seq.empty()) {
        cout << "NO POSSIBLE MOVE SEQUENCE TO ARRIVE AT (" << start_end_positions.x2
             << ", " << start_end_positions.y2 << ")" << endl;
    }
    return seq;
}

vector<Move> Board::generateOptimalMoveSeq(Move start_end_positions) {
    vector<Move> seq = DijkstraGenerateMoveSeq(start_end_positions);
    if (seq.empty()) {
        cout << "NO POSSIBLE MOVE SEQUENCE TO ARRIVE AT (" << start_end_positions.x2
             << ", " << start_end_positions.y2 << ")" << endl;
    }
    return seq;
}

vector<Move> Board::generateLongestSeq(Move start_end_positions) {
    vector<Move> seq;
    seq.push_back(start_end_positions);
    return seq;
}
