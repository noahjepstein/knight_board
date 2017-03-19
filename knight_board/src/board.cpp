/* board.cpp
   Board class.
   Represents the solution for the knight board challenge.
   Author: Noah J Epstein
           noahjepstein@gmail.com
*/

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

/*
   Board
   Constructor for board class -- initializes private members.
   Args:    x and y dimensions of board.
   Returns: none
*/
Board::Board(int x, int y) {
    x_dim = x;
    y_dim = y;
    n_nodes = x * y;
    Node placeholder_node;
    nodes.resize(n_nodes, placeholder_node);
    knight_pos.x = 0;
    knight_pos.y = 0;
}

/*
   signMult
   Helper func for calculating knight move positions.
   Args:    integer x
   Returns: 1 if pos, -1 if neg
*/
int Board::signMult(int x) {
    return (x >= 0 ? 1 : -1);
}


/*
   printBoard
   Prints board and knight position.
   Args:    none
   Returns: none
*/
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


/*
   makeMove
   Makes a move from two nodes
   Args:    two nodes
   Returns: move struct
*/
Move Board::makeMove(Node n1, Node n2) {
    Move m;
    m = {n1.x, n1.y, n2.x, n2.y};
    return m;
}

/*
   makeMove
   Makes a move from two node ids
   Args:    two node ids
   Returns: move struct
*/
Move Board::makeMove(NodeID nid1, NodeID nid2) {
    return makeMove(nodes[nid1], nodes[nid2]);
}

/*
   readInput
   Reads board from standard input.
   Args:    none
   Returns: none
*/
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

/*
   onBoard
   Returns true if a coordinate is on the board
   Args:    coordinate x and y
   Returns: true if on board
*/
bool Board::onBoard(int x1, int y1){
    return ((x1 >= 0) && (x1 < x_dim) && (y1 >= 0) && (y1 < y_dim));
}

/*
   areNeighbors
   Returns true if the two nodes can be connected by a valid move
   Args:    node IDS for two nodes
   Returns: true if can be connected
*/
bool Board::areNeighbors(NodeID nid1, NodeID nid2) {
    if ((nid1 >= 0) && (nid1 < n_nodes) && (nid2 >= 0) && (nid2 < n_nodes)) {
        Node n1 = nodes[nid1];
        auto neigh = find(begin(n1.neighbors), end(n1.neighbors), nid2);
        return (neigh != end(n1.neighbors));
    } else {
        return false;
    }
}

/*
   makeNeighbors
   Adds other node to each nodes adjacency list
   Args:    node IDS for two nodes
   Returns: none
*/
void Board::makeNeighbors(NodeID nid1, NodeID nid2) {
    nodes[nid1].neighbors.push_back(nid2);
    nodes[nid2].neighbors.push_back(nid1);
}

/*
   validKnightMovePattern
   Returns true if a move is a valid knight move
   Args:    Move m
   Returns: true if valid
*/
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

/*
   c2id
   Gives a node id for coordinates of a node
   Args:    x and y position
   Returns: node id -- integer
*/
int Board::c2ID(int x, int y) {
    return y * x_dim + x;
}

/*
   validMove
   Returns true if a move between two coordinates is valid on our board.
   Args:    two x and y positions
   Returns: true if valid
*/
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
                   && (n1.type != BARRIER)
                   && (n2.type != BARRIER)
                   && validKnightMovePattern(m)
                   && !crossesBarriers(m))
                   || (m == tele)) {
            makeNeighbors(n1.id, n2.id);
            return true;
        }
    }
    return false;
}

/*
   validMove
   Returns true if a move between two coordinates is valid on our board.
   Overloaded from previous definition to accept a move
   Args:    move m
   Returns: true if valid
*/
bool Board::validMove(Move m) {

    Node n1, n2;

    if ((onBoard(m.x1, m.y1)) && (onBoard(m.x2, m.y2))) {
        n1 = nodes[c2ID(m.x1, m.y1)];
        n2 = nodes[c2ID(m.x2, m.y2)];
        if (areNeighbors(c2ID(m.x1, m.y1), c2ID(m.x2, m.y2))) {
            return true;
        } else if   (((n1.type != ROCK)
                   && (n2.type != ROCK)
                   && (n1.type != BARRIER)
                   && (n2.type != BARRIER)
                   && validKnightMovePattern(m)
                   && !crossesBarriers(m))
                   || (m == tele)) {
            makeNeighbors(n1.id, n2.id);
            return true;
        }
    }
    return false;
}

/*
   crossesBarriers
   Returns true if a move crosses a barrier (which makes it invalid)
   Args:    Move m
   Returns: true if crosses a barrier
*/
bool Board::crossesBarriers(Move m) {

    Node n1 = nodes[c2ID(m.x1, m.y1)];
    Node n2 = nodes[c2ID(m.x2, m.y2)];
    int dx = m.x2 - m.x1;
    int dy = m.y2 - m.y1;

    if (abs(dx) == 2) {
        return (((nodes[n1.id + signMult(dx) * 1].type == BARRIER)
              || (nodes[n1.id + signMult(dx) * 2].type == BARRIER))
           &&   ((nodes[n1.id + signMult(dy) * x_dim].type == BARRIER)
              || (nodes[n1.id + signMult(dy) * x_dim + signMult(dx)].type == BARRIER)));
    } else if (abs(dx) == 1) {
        return (((nodes[n1.id + signMult(dy) * x_dim * 1].type == BARRIER)
              || (nodes[n1.id + signMult(dy) * x_dim * 2].type == BARRIER))
           &&   ((nodes[n1.id + signMult(dx)].type == BARRIER)
              || (nodes[n1.id + signMult(dx) + x_dim * signMult(dy)].type == BARRIER)));
    }
    return false;
}

/*
   findNeighbors
   Initializes the adjacency list by finding all the neighbors of nodes in advance.
   This speeds path calculations becuase it doesn't have to calculate if a move
   is valid for each move check at runtime.
   Args:    none
   Returns: none
*/
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

/*
   validateMoveSeq
   Runs validMove for each move in the sequence.
   Also checks that the moves are contiguous with each other.
   Prints the board and sleeps on each iteration.
   Args:    sequence of moves
   Returns: true if valid sequence
*/
bool Board::validateMoveSeq(vector<Move> moveSeq) {

    if (moveSeq.empty()) {
        return true;
    } else {

        Move prev_move = moveSeq[0];

        if (!validMove(prev_move)) {
            return false;
        }

        for (auto move_p = moveSeq.begin() + 1; move_p != moveSeq.end(); ++move_p) {
            if (!validMove(*move_p) || (move_p->x1 != prev_move.x2) || (move_p->y1 != prev_move.y2)) {
                return false;
            }
            prev_move = *move_p;
            knight_pos.x = prev_move.x1;
            knight_pos.y = prev_move.y1;
            printBoard();
            usleep(SLEEP_INTERVAL);
        }
    }

    knight_pos.x = moveSeq.back().x2;
    knight_pos.y = moveSeq.back().y2;
    printBoard();
    return true;
}


/*
   DFSgenerateMoveSeq
   Finds a move sequence from a start to end position using DFS.
   Args:    A move representing start and end positions.
   Returns: Move sequence from start to end position
*/
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

        if (!next.marked) {
            knight_pos.x = next.x;
            knight_pos.y = next.y;

            if (next == end) {
                seq.push_back(makeMove(start, end));
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

/*
   generateMoveSeq
   Uses DFSgenerateMoveSeq to find a valid move sequence.
   Args:    A move representing start and end positions.
   Returns: Move sequence from start to end position
*/
vector<Move> Board::generateMoveSeq(Move start_end_positions) {
    vector<Move> seq = DFSgenerateMoveSeq(start_end_positions);
    if (seq.empty()) {
        cout << "NO POSSIBLE MOVE SEQUENCE TO ARRIVE AT (" << start_end_positions.x2
             << ", " << start_end_positions.y2 << ")" << endl;
    }
    return seq;
}

/*
   backTrackMoveSeq
   Takes the (node, prev_node) pairs stored from dijstra and works backwards to
   generate a vector of Moves.
   Args:    map of nodeIDs with their previous nodes, source and target node ids.
   Returns: Move sequence from start to end position
*/
vector<Move> Board::backTrackMoveSeq(unordered_map<NodeID, NodeID> &prev, NodeID src, NodeID last) {
    vector<Move> seq, empty;
    NodeID n = last;
    unordered_map<NodeID, NodeID>::const_iterator finder;
    while (n != src) {
        finder = prev.find(n);
        if (finder == prev.end()) {
            return empty;
        } else {
            seq.insert(seq.begin(), makeMove(finder->second, finder->first));
        }
        n = finder->second; // last thing this loop does is make a move to the source
    }
    return seq;
}

/*
   DijkstraGenerateShortestMoveSeq
   Finds the optimal move sequence from a start to end position using dijkstra.
   Args:    A move representing start and end positions.
   Returns: Move sequence from start to end position
*/
vector<Move> Board::DijkstraGenerateShortestMoveSeq(Move start_end_positions) {
    int top;
    Node node;
    vector<NodeID> neighbors;
    unordered_map<NodeID, NodeID> prev;
    NodeID start_nid = c2ID(start_end_positions.x1, start_end_positions.y1);
    NodeID end_nid   = c2ID(start_end_positions.x2, start_end_positions.y2);
    vector<int> dist (n_nodes, INF);
    priority_queue<dPair, vector<dPair>, greater<dPair> > pq;

    pq.push(make_pair(0, start_nid));
    dist[start_nid] = 0;

    while (!pq.empty()) {
        top = pq.top().second;
        if (top == end_nid) {
            break;
        }
        pq.pop();
        neighbors = nodes[top].neighbors;

        for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {

            node = nodes[*it];

            if (dist[node.id] > dist[top] + node.weight) {
                dist[node.id] = dist[top] + node.weight;

                pq.push(make_pair(dist[node.id], node.id));
                auto pre = prev.find(node.id);
                if (pre == prev.end()) {
                    prev.emplace(node.id, top);
                } else {
                    pre->second = top;
                }
            }
        }
    }
    return backTrackMoveSeq(prev, start_nid, end_nid);
}

/*
   generateOptimalMoveSeq
   Finds the optimal move sequence from a start to end position using dijkstra.
   Args:    A move representing start and end positions.
   Returns: Move sequence from start to end position
*/
vector<Move> Board::generateOptimalMoveSeq(Move start_end_positions) {
    vector<Move> seq = DijkstraGenerateShortestMoveSeq(start_end_positions);
    if (seq.empty()) {
        cout << "NO POSSIBLE MOVE SEQUENCE TO ARRIVE AT (" << start_end_positions.x2
             << ", " << start_end_positions.y2 << ")" << endl;
    }
    return seq;
}

/*
   dijkstraGenerateLongestMoveSeq
   Finds the longest move sequence from a start to end position using dijkstra
   with negative edge weights. Side effect: makes all edge weights negative.
   Args:    A move representing start and end positions.
   Returns: Move sequence from start to esnd position
*/
vector<Move> Board::dijkstraGenerateLongestMoveSeq(Move start_end_positions) {
    int top;
    Node node;
    vector<NodeID> neighbors;
    unordered_map<NodeID, NodeID> prev;
    NodeID start_nid = c2ID(start_end_positions.x1, start_end_positions.y1);
    NodeID end_nid   = c2ID(start_end_positions.x2, start_end_positions.y2);
    vector<int> dist (n_nodes, INF);
    priority_queue<dPair, vector<dPair>, greater<dPair> > pq;

    pq.push(make_pair(0, start_nid));
    dist[start_nid] = 0;

    for (int i = 0; i < n_nodes; ++i) {
        nodes[i].weight *= -1;
    }

    while (!pq.empty()) {
        top = pq.top().second;
        if (top == end_nid) {
            break;
        }
        pq.pop();
        neighbors = nodes[top].neighbors;

        for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
            if (nodes[*it].marked) {
                continue;
            } else {
                nodes[*it].marked = true;
            }

            node = nodes[*it];

            if (dist[node.id] > dist[top] + node.weight) {
                dist[node.id] = dist[top] + node.weight;

                pq.push(make_pair(dist[node.id], node.id));
                auto pre = prev.find(node.id);
                if (pre == prev.end()) {
                    prev.emplace(node.id, top);
                } else {
                    pre->second = top;
                }
            }
        }
    }
    return backTrackMoveSeq(prev, start_nid, end_nid);
}

/*
   generateLongestSeq
   Finds the longest move sequence from a start to end position
   using dijkstraGenerateLongestMoveSeq. 
   Args:    A move representing start and end positions.
   Returns: Move sequence from start to end position
*/
vector<Move> Board::generateLongestSeq(Move start_end_positions) {
    vector<Move> seq = dijkstraGenerateLongestMoveSeq(start_end_positions);
    if (seq.empty()) {
        cout << "NO POSSIBLE MOVE SEQUENCE TO ARRIVE AT (" << start_end_positions.x2
             << ", " << start_end_positions.y2 << ")" << endl;
    }
    return seq;
}
