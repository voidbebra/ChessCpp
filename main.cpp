#include <iostream>
#include "class.cpp"
#include <map>

using namespace std;

/* pair<int, int> chessToNumeric(string chessCoord) {
    map<char, int> fileMap = {{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}};
    map<char, int> rankMap = {{'1', 0}, {'2', 1}, {'3', 2}, {'4', 3}, {'5', 4}, {'6', 5}, {'7', 6}, {'8', 7}};

    int file = fileMap[chessCoord[0]];
    int rank = rankMap[chessCoord[1]];

    return make_pair(file, rank);
} */
void getCoordinates(const string& input, pair<int, int>& startCoord, pair<int, int>& endCoord) {
    startCoord.first = input[0] - 'A';
    startCoord.second = input[1] - '1';
    endCoord.first = input[2] - 'A';
    endCoord.second = input[3] - '1';
}


char numericToLetter(int number) {
    return static_cast<char>('A' + number - 1);
}

void printChessboard(Board board) {
    cout << "    ";
    for (int i = 1; i <= 8; i++) {
        cout << numericToLetter(i) << ' ';
    }
    cout << endl << "   ----------------"<<endl;

    for (int i = 0; i < 8; i++) {
        cout << i + 1 << " | ";
        for (int j = 0; j < 8; j++) {
            if (board.getPiece(i, j) == nullptr) {
                cout << ". ";
            } else {
                cout << board.getPiece(i, j)->getSymbol() << ' ';
            }
        }
        cout << endl;
    }
}

int main() {    
    King white_king(Color::WHITE);
    King black_king(Color::BLACK);

    Queen white_queen(Color::WHITE);
    Queen black_queen(Color::BLACK);

    Rook white_rook1(Color::WHITE);
    Rook white_rook2(Color::WHITE);
    Rook black_rook1(Color::BLACK);
    Rook black_rook2(Color::BLACK);

    Bishop white_bishop1(Color::WHITE);
    Bishop white_bishop2(Color::WHITE);
    Bishop black_bishop1(Color::BLACK);
    Bishop black_bishop2(Color::BLACK);

    Knight white_knight1(Color::WHITE);
    Knight white_knight2(Color::WHITE);
    Knight black_knight1(Color::BLACK);
    Knight black_knight2(Color::BLACK);

    Pawn white_pawns[8] = { Pawn(Color::WHITE), Pawn(Color::WHITE), Pawn(Color::WHITE), Pawn(Color::WHITE), Pawn(Color::WHITE), Pawn(Color::WHITE), Pawn(Color::WHITE), Pawn(Color::WHITE) };
    Pawn black_pawns[8] = { Pawn(Color::BLACK), Pawn(Color::BLACK), Pawn(Color::BLACK), Pawn(Color::BLACK), Pawn(Color::BLACK), Pawn(Color::BLACK), Pawn(Color::BLACK), Pawn(Color::BLACK) };
    
    Board board;
    
    for(int i = 0; i < 8; i++){
        board.placePiece(&black_pawns[i], 1, i);
        board.placePiece(&white_pawns[i], 6, i);
    }
    board.placePiece(&white_king, 7, 4);
    board.placePiece(&black_king, 0, 4);

    board.placePiece(&white_queen, 7, 3);
    board.placePiece(&black_queen, 0, 3);

    board.placePiece(&white_bishop1, 7, 5); 
    board.placePiece(&white_bishop2, 7, 2); 
    board.placePiece(&black_bishop1, 0, 5);
    board.placePiece(&black_bishop2, 0, 2);

    board.placePiece(&white_knight1, 7, 6);
    board.placePiece(&white_knight2, 7, 1);
    board.placePiece(&black_knight1, 0, 6);
    board.placePiece(&black_knight2, 0, 1);

    board.placePiece(&white_rook1, 7, 7);
    board.placePiece(&white_rook2, 7, 0);
    board.placePiece(&black_rook1, 0, 7);
    board.placePiece(&black_rook2, 0, 0);

    int side = 0;
    string move = "";
    while(true){
        printChessboard(board);
        if(side == 0){
            cout<<"Хід білих: ";
        }else{
            cout<<"Хід чорних: ";
        }
        string userInput;
        cout << "Введіть рядок в форматі \"D4D5\": ";
        cin >> userInput;

        pair<int, int> startCoord, endCoord;
        getCoordinates(userInput, startCoord, endCoord);

        cout << "Початкові координати: " << startCoord.first << ", " << startCoord.second << endl;
        cout << "Кінцеві координати: " << endCoord.first << ", " << endCoord.second << endl;
        auto piece = board.getPiece(startCoord.second ,startCoord.first);
        cout << piece->getSymbol() << endl;
        if((piece->getColor() == Color::WHITE) & (side == 0)){
            if(board.isValidMove( startCoord.second, startCoord.first, endCoord.second, endCoord.first)){
                cout << "Хід білих можливо"<<endl;
                board.placePiece(piece, endCoord.second, endCoord.first);
                board.removePiece(startCoord.second, startCoord.first);
                side += 1;
            }else{
                cout<< "Хід білих неможливо"<<endl;
                continue;
            }
        }else if((piece->getColor() == Color::BLACK) & (side == 1)){
            if(board.isValidMove( startCoord.second, startCoord.first, endCoord.second, endCoord.first)){
                cout << "Хід чорних можливо"<<endl;
                board.placePiece(piece, endCoord.second, endCoord.first);
                board.removePiece(startCoord.second, startCoord.first);
                side -= 1;
            }else{
                cout<< "Хід чорних неможливо"<<endl;
                continue;
            }
            
        }else{
            cout << "Хід не вірний"<<endl;
        }
    }
    return 0;
}
