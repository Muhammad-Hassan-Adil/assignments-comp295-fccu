#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ROWS = 4;
const int COLS = 4;
int score;

void printBoard(int (&board)[ROWS][COLS]) {
    cout << "\033[31m|-----------------------|" << endl;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0){
                cout << "\033[31m|  " << "\033[36m" <<board[i][j] << "  ";
            }
            else if (board[i][j] >= 10 && board[i][j] < 100){
                cout << "\033[31m|  " << "\033[0;33m" <<board[i][j] << " ";
            }
            else if (board[i][j] >= 100 && board[i][j] < 1000){
                cout << "\033[31m| " << "\033[1;32m" <<board[i][j] << " ";
            }
            else if (board[i][j] >= 1000){
                cout << "\033[31m| " << "\033[32m" <<board[i][j] << "";
            }
            else{
                cout << "\033[31m|  " << "\033[38;5;208m" <<board[i][j] << "  ";
            }
        }
        cout << "\033[31m|" << endl;
        for (int j = 0; j < COLS; j++) {
            cout << "\033[31m|-----";
        }
        cout << "\033[31m|" << endl;
    }
    cout << "\033[1;36mScore: " << score << endl;
}

bool checkGameOver(int (&board)[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 2048) {
                cout << "\033[32mTile 2048 made!! You won!\n";
                return true;
            }
        }
    }
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (board[i][j] == 0) {
                return false;
            }
            if (i != ROWS - 1 && board[i][j] == board[i+1][j]) {
                return false;
            }
            if (j != COLS - 1 && board[i][j] == board[i][j+1]) {
                return false;
            }
        }
    }
    cout << "\033[31mNo more tiles left!\n";
    return true;
}

void addTile(int (&board)[ROWS][COLS]) {
    while (true) {
        int row = rand() % ROWS;
        int col = rand() % COLS;
        int num = rand() % 2;
        if (board[row][col] == 0) {
            if (num == 0){
                board[row][col] = 2;
                break;
            }
            else{
                board[row][col] = 4;
                break;
            }
        }
    }
}

void Shift(int (&board)[ROWS][COLS],char Move) {
    switch(Move){
        case 'w':
            for (int j = 0; j < COLS; j++) {
                int k = 0;
                for (int i = 0; i < ROWS; i++) {
                    if (board[i][j] != 0) {
                        if (k != i) {
                            board[k][j] = board[i][j];
                            board[i][j] = 0;
                        }
                        if (k > 0 && board[k][j] == board[k-1][j]) {
                            board[k-1][j] *= 2;
                            score += board[k-1][j];
                            board[k][j] = 0;
                        }
                        k++;
                    }
                }
            }
            break;
        case 's':
            for (int j = 0; j < COLS; j++) {
                int k = ROWS - 1;
                for (int i = ROWS - 1; i >= 0; i--) {
                    if (board[i][j] != 0) {
                        if (k != i) {
                            board[k][j] = board[i][j];
                            board[i][j] = 0;
                        }
                        if (k < ROWS - 1 && board[k][j] == board[k+1][j]) {
                            board[k+1][j] *= 2;
                            score += board[k+1][j];
                            board[k][j] = 0;
                        }
                        k--;
                    }
                }
            }
            break;
        case 'a':
            for (int i = 0; i < ROWS; i++) {
                int k = 0;
                for (int j = 0; j < COLS; j++) {
                    if (board[i][j] != 0) {
                        if (k != j) {
                            board[i][k] = board[i][j];
                            board[i][j] = 0;
                        }
                        if (k > 0 && board[i][k] == board[i][k-1]) {
                            board[i][k-1] *= 2;
                            score += board[i][k-1];
                            board[i][k] = 0;
                        }
                        k++;
                    }
                }
            }
            break;
    }
}

int main() {
    system("clear");
    int option;
    while (true){
        cout << "\033[1;36mPress 1 to Start game\nPress 2 to see instructions\nPress 3 to quit\nChoose Option: ";
        cin >> option;
        if (option == 1){
            score = 0;
            int board[ROWS][COLS] = {0};
            addTile(board);
            addTile(board);
            system("clear");
            printBoard(board);
            while (!checkGameOver(board)) {
                char move;
                cout << "\033[1;36mEnter move (W/A/S/D): ";
                cin >> move;
                switch (move) {
                    case 'w':
                    case 's':
                    case 'a':
                    case 'd':
                        Shift(board,move);
                        break;
                    default:
                        cout << "\033[1;31mInvalid move. Try again." << endl;
                        continue;
                }
                system("clear");
                printBoard(board);
            }
            cout << "\033[1;36mGame over! Final score: " << score << endl;
        }
        else if (option == 2){
            system("clear");
            cout << "\033[1;32m\t\t\tINSTRUCTIONS\n\033[1;33m1. This is 2048 Game, you are supposed to press W to move tiles up, S to move tiles down, A to move tiles left and D to move tiles right.\n2. The score shown will be a sum of total tiles you have merged.\n3. the game will end, if you there are no more moves left i.e there are no more tiles left to merge and there are no empty(0) spaces left.\n4. You will have won the game if you reach the tile 2048./n5. If you enter anything other than WASD, you will be asked to enter again.\n\033[1;31m6. MAKE SURE ALL YOUR INPUTS OF WASD ARE IN LOWERCASE OR IT WILL NOT BE ACCEPTED.\n\033[1;32m\t\t\tGOOD LUCK!!!" << endl;
        }
        else if (option == 3){
            cout << "Good Bye :)" << endl;
            return 0;
        }
        else{
            cout << "Please input a right option." << endl;
        }
    }
}
