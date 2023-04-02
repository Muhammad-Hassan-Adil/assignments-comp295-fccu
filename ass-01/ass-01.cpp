

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
