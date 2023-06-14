#include <cmath>

enum class Color { WHITE, BLACK };

class ChessPiece {
protected:
    Color color;
public:
    
    ChessPiece(Color c) : color(c) {}
    virtual ~ChessPiece() {}
    virtual bool isValidMove(int x1, int y1, int x2, int y2) = 0;
    virtual char getSymbol() = 0;
    Color getColor(){ return color;}
};

class King : public ChessPiece {
public:
    King(Color c) : ChessPiece(c) {}
    bool isValidMove(int x1, int y1, int x2, int y2) {
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        return (dx <= 1 && dy <= 1);
    }
    char getSymbol() {
        return (color == Color::WHITE) ? 'K' : 'k';
    }

    /* bool isKnightNearby(Board board, int x, int y) {
    // Проверка наличия коней вокруг указанных координат
        
        int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
        int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
        
        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < 8 && ny >= 0 && ny < 8 && board.getPiece(nx,ny)->getSymbol() == 'N') {
                return true; // Конь найден
            }
        }
        
        return false; // Конь не найден
    }
    bool isInCheck(Board board, int x, int y) {
    // Проверка атакующих фигур по вертикали и горизонтали
        for (int i = 0; i < 8; i++) {
            char xi = board.getPiece(x,i)->getSymbol();
            if (xi == 'R' || xi == 'Q') {
                return true; // Шах по горизонтали
            }
            char iy = board.getPiece(i,y)->getSymbol();
            if (iy == 'R' || iy == 'Q') {
                return true; // Шах по вертикали
            }
        }
        
        // Проверка атакующих фигур по диагоналям
        for (int i = 1; i < 8; i++) {
            if (x + i < 8 && y + i < 8 && (board.getPiece(x + i, y + i) == 'B' ||  == 'Q')) {
                return true; // Шах по диагонали (право-низ)
            }
            if (x - i >= 0 && kingY - i >= 0 && (board.getPiece(x - i, y - i) == 'B' ||  == 'Q')) {
                return true; // Шах по диагонали (лево-верх)
            }
            if (x + i < 8 && kingY - i >= 0 && (board.getPiece(x + i, y - i) == 'B' ||  == 'Q')) {
                return true; // Шах по диагонали (право-верх)
            }
            char left_bottom = board.getPiece(x - i, y + i)->getSymbol();
            if (x - i >= 0 && kingY + i < 8 && (left_bottom == 'B' || left_bottom == 'Q')) {
                return true; // Шах по диагонали (лево-низ)
            }
        }
        
        // Проверка наличия коней поблизости
        if (isKnightNearby(board, kingX, kingY)) {
            return true; // Шах от коня
        }
        
        return false; // Шах не обнаружен
}; */
};

class Queen : public ChessPiece {
public:
    Queen(Color c) : ChessPiece(c) {}
    bool isValidMove(int x1, int y1, int x2, int y2) {
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        return (dx == dy || x1 == x2 || y1 == y2);
    }
    char getSymbol() {
        return (color == Color::WHITE) ? 'Q' : 'q';
    }
};

class Rook : public ChessPiece {
public:
    Rook(Color c) : ChessPiece(c) {}
    bool isValidMove(int x1, int y1, int x2, int y2) {
        return (x1 == x2 || y1 == y2);
    }
    char getSymbol() {
        return (color == Color::WHITE) ? 'R' : 'r';
    }
};

class Bishop : public ChessPiece {
public:
    Bishop(Color c) : ChessPiece(c) {}
    bool isValidMove(int x1, int y1, int x2, int y2) {
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        return (dx == dy);
    }
    char getSymbol() {
        return (color == Color::WHITE) ? 'B' : 'b';
    }
};

class Knight : public ChessPiece {
public:
    Knight(Color c) : ChessPiece(c) {}
    bool isValidMove(int x1, int y1, int x2, int y2) {
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);
        return ((dx == 1 && dy == 2) || (dx == 2 && dy == 1));
    }
    char getSymbol() {
        return (color == Color::WHITE) ? 'N' : 'n';
    }
};

class Pawn : public ChessPiece {
public:
    Pawn(Color c) : ChessPiece(c) {}
    bool isValidMove(int x1, int y1, int x2, int y2) {
        int dx = abs(x2 - x1);
        int dy = abs(y2 - y1);

        if(color == Color::WHITE && dx == 2 && dy == 0 && x1 == 6) return true;
        if(color == Color::BLACK && dx == 2 && dy == 0 && x1 == 1) return true;
        if(color == Color::BLACK && x1 - x2 == -1 && dy == 1) return true;
        if(color == Color::WHITE && x1 - x2 == 1 && dy == 1) return true;

        return (dx == 1 && dy == 0);
    }
    char getSymbol(){
        return (color == Color::WHITE) ? 'P' : 'p';
    }
};

class Board {
private:
    ChessPiece* squares[8][8];  // array of pointers on figures (nullptr by default)

public:

    // constructor
    Board() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                squares[i][j] = nullptr;
            }
        }
    }

    // destructor
    ~Board() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                squares[i][j] = nullptr;
            }
        }
    }

    // method for placing a figure on board
    void placePiece(ChessPiece* piece, int x, int y) {
        squares[x][y] = piece;
    }

    // method for removing a figure from board
    void removePiece(int x, int y) {
        squares[x][y] = nullptr;
    }

    // method for geting figure from coords
    ChessPiece* getPiece(int x, int y) {
        return squares[x][y];
    }


    // method for check obstacle on path
    bool isObstacleOnPath(int x0, int y0, int x1, int y1) {
        int dx = abs(x1 - x0), dy = abs(y1 - y0);
        if(sqrt(pow(x1-x0, 2) + pow(y1 - y0, 2)) < 2) return false;

        int xInc;
        if(x0 < x1) xInc = 1;
        else if(x0 == x1) xInc = 0;
        else xInc = -1; 

        int yInc;
        if(y0 < y1) yInc = 1;
        else if(y0 == y1) yInc = 0;
        else yInc = -1; 

        int cx = x0 + xInc; int cy = y0 + yInc;
        int tx = x1; int ty = y1;

        if (cx == tx - xInc && cy == ty - yInc) return squares[cx][cy] != nullptr;

        while (cx != tx || cy != ty) {
            if (squares[cx][cy] != nullptr) return true;
            cx += xInc;
            cy += yInc;
        }
        
        return false;
    }

    // method for checking if figure can move from one cell to another
    bool isValidMove(int from_x, int from_y, int to_x, int to_y) {

        // check for out-of-bounds board
        if (from_x < 0 || from_x > 7 || from_y < 0 || from_y > 7 || to_x < 0 || to_x > 7 || to_y < 0 || to_y > 7) {
            return false;
        }

        // getting pointer to figure located on source cell
        ChessPiece* piece = squares[from_x][from_y];
        if (piece == nullptr) {
            return false;
        }

        // checking for valid move
        if (!piece->isValidMove(from_x, from_y, to_x, to_y)) {
            return false;
        }

        // checking for obstacle on path (if knight - ignore)
        if (piece->getSymbol() != 'N' && piece->getSymbol() != 'n'){
            if (isObstacleOnPath(from_x, from_y, to_x, to_y)){
                return false;
            }
        }

        // checking the cell for empty or figure of the opposite color
        if (squares[to_x][to_y] == nullptr || squares[to_x][to_y]->getColor() != piece->getColor()) {
            return true;
        }

        return false;
    }
};
