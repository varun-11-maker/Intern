#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

// Enum for piece color
enum Color { WHITE, BLACK };

// Base class for all pieces
class Piece {
public:
    Color color;

    Piece(Color c) : color(c) {}

    virtual ~Piece() {}

    virtual char getSymbol() const = 0;
    virtual bool isValidMove(int srcX, int srcY, int destX, int destY) const = 0;
};

// Derived classes for each piece type
class King : public Piece {
public:
    King(Color c) : Piece(c) {}

    char getSymbol() const override {
        return color == WHITE ? 'K' : 'k';
    }

    bool isValidMove(int srcX, int srcY, int destX, int destY) const override {
        return abs(destX - srcX) <= 1 && abs(destY - srcY) <= 1;
    }
};

class Queen : public Piece {
public:
    Queen(Color c) : Piece(c) {}

    char getSymbol() const override {
        return color == WHITE ? 'Q' : 'q';
    }

    bool isValidMove(int srcX, int srcY, int destX, int destY) const override {
        return srcX == destX || srcY == destY || abs(destX - srcX) == abs(destY - srcY);
    }
};

class Rook : public Piece {
public:
    Rook(Color c) : Piece(c) {}

    char getSymbol() const override {
        return color == WHITE ? 'R' : 'r';
    }

    bool isValidMove(int srcX, int srcY, int destX, int destY) const override {
        return srcX == destX || srcY == destY;
    }
};

class Bishop : public Piece {
public:
    Bishop(Color c) : Piece(c) {}

    char getSymbol() const override {
        return color == WHITE ? 'B' : 'b';
    }

    bool isValidMove(int srcX, int srcY, int destX, int destY) const override {
        return abs(destX - srcX) == abs(destY - srcY);
    }
};

class Knight : public Piece {
public:
    Knight(Color c) : Piece(c) {}

    char getSymbol() const override {
        return color == WHITE ? 'N' : 'n';
    }

    bool isValidMove(int srcX, int srcY, int destX, int destY) const override {
        return (abs(destX - srcX) == 2 && abs(destY - srcY) == 1) || (abs(destX - srcX) == 1 && abs(destY - srcY) == 2);
    }
};

class Pawn : public Piece {
public:
    Pawn(Color c) : Piece(c) {}

    char getSymbol() const override {
        return color == WHITE ? 'P' : 'p';
    }

    bool isValidMove(int srcX, int srcY, int destX, int destY) const override {
        if (color == WHITE) {
            return (srcX == destX && destY == srcY + 1) || (srcX == destX && srcY == 1 && destY == 3);
        } else {
            return (srcX == destX && destY == srcY - 1) || (srcX == destX && srcY == 6 && destY == 4);
        }
    }
};

// Class representing the chess board
class Board {
private:
    vector<vector<unique_ptr<Piece>>> board;

public:
    Board() : board(8, vector<unique_ptr<Piece>>(8, nullptr)) {
        setupPieces();
    }

    void setupPieces() {
        // Add pawns
        for (int i = 0; i < 8; ++i) {
            board[1][i] = make_unique<Pawn>(WHITE);
            board[6][i] = make_unique<Pawn>(BLACK);
        }

        // Add other pieces
        board[0][0] = board[0][7] = make_unique<Rook>(WHITE);
        board[0][1] = board[0][6] = make_unique<Knight>(WHITE);
        board[0][2] = board[0][5] = make_unique<Bishop>(WHITE);
        board[0][3] = make_unique<Queen>(WHITE);
        board[0][4] = make_unique<King>(WHITE);

        board[7][0] = board[7][7] = make_unique<Rook>(BLACK);
        board[7][1] = board[7][6] = make_unique<Knight>(BLACK);
        board[7][2] = board[7][5] = make_unique<Bishop>(BLACK);
        board[7][3] = make_unique<Queen>(BLACK);
        board[7][4] = make_unique<King>(BLACK);
    }

    void display() const {
        cout << "  a b c d e f g h" << endl;
        for (int y = 7; y >= 0; --y) {
            cout << y + 1 << " ";
            for (int x = 0; x < 8; ++x) {
                if (board[y][x]) {
                    cout << board[y][x]->getSymbol() << " ";
                } else {
                    cout << ". ";
                }
            }
            cout << y + 1 << endl;
        }
        cout << "  a b c d e f g h" << endl;
    }

    bool movePiece(int srcX, int srcY, int destX, int destY) {
        if (!isValidPosition(srcX, srcY) || !isValidPosition(destX, destY) || !board[srcY][srcX]) {
            return false;
        }

        Piece* piece = board[srcY][srcX].get();
        if (piece->isValidMove(srcX, srcY, destX, destY) && (!board[destY][destX] || board[destY][destX]->color != piece->color)) {
            board[destY][destX] = move(board[srcY][srcX]);
            return true;
        }
        return false;
    }

private:
    bool isValidPosition(int x, int y) const {
        return x >= 0 && x < 8 && y >= 0 && y < 8;
    }
};

int main() {
    Board board;
    string move;
    int turn = 0;

    while (true) {
        board.display();
        cout << (turn % 2 == 0 ? "White" : "Black") << "'s move (e.g., e2e4): ";
        cin >> move;

        if (move.length() != 4) {
            cout << "Invalid move format!" << endl;
            continue;
        }

        int srcX = move[0] - 'a';
        int srcY = move[1] - '1';
        int destX = move[2] - 'a';
        int destY = move[3] - '1';

        if (board.movePiece(srcX, srcY, destX, destY)) {
            turn++;
        } else {
            cout << "Invalid move!" << endl;
        }
    }

    return 0;
}
