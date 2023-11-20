#include<iostream>
#include<string>

using namespace std;

char Board[3][3];
class Game{
    private:
        int row, col;
    public:
        Game();
        void DataWinner(string Player);
        void display();
        bool isWinner();
        void input(int row, int col, char c, int tempr, int tempc);
        void instructions();
        void Moves(string Player1, string Player2);  
        bool Player();
        int counter = 1, pc1 = 0, pc2 = 0;
}TTT;

Game::Game(){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            Board[i][j] = ' ';
}            

void Game::display(){
    for(int i = 0; i <= 2; i++){
        for(int k = 0; k <= 2; k++){
            cout << static_cast<char>(201);
            for(int j = 1; j <= 3; j++)
                cout << static_cast<char>(205);
            cout << static_cast<char>(187);
        }
        cout << endl; 

        for(int j = 0; j <= 2; j++)
            cout << static_cast<char>(186) << " " << Board[i][j] << " " << static_cast<char>(186);
        cout << endl;

        for(int k = 0; k <= 2; k++){
            cout << static_cast<char>(200);
            for(int j = 1; j <= 3; j++)
                cout << static_cast<char>(205);
            cout << static_cast<char>(188);
        }
        cout << endl;
    } 
    cout << endl;
}

bool Game::isWinner(){
    for(int i = 0; i < 3; i++){//Row Check
        if((Board[i][0] == Board[i][1]) && (Board[i][0] == Board[i][2]) && Board[i][0] != ' ')
            return true;
    }
    for(int i = 0; i < 3; i++){// Column Check
        if((Board[0][i] == Board[1][i]) && (Board[0][i] == Board[2][i]) && Board[0][i] != ' ')
            return true;
    }
    // Diagonal Check
    if((Board[0][0] == Board[1][1]) && (Board[1][1] == Board[2][2]) && (Board[1][1] != ' '))
        return true;
    if((Board[0][2] == Board[1][1]) && (Board[2][0] == Board[1][1]) && (Board[1][1] != ' '))
        return true;
    return false;
}

void Game::input(int row, int col, char c, int tempr, int tempc){
    if(row >= 1 && row <= 3 && col >= 1 && col <= 3){
        if(Board[row-1][col-1] == ' '){
            Board[row-1][col-1] = c;
            if(Player() == 1)
                pc1++;
            else    
                pc2++;
            cout << endl;
            display();
            cout << endl;
        }
        else{
            cout << "Position Already Captured" << endl;
            counter--;
        }
    }
    else{
        cout << "Please Enter Correct Position Carefully." << endl;
        counter--;
    }
}

void Game::instructions(){
    cout << "INSTRUCTIONS :" << endl;
    cout << "Enter Row Number and Column Number of the Block"<< endl;
    cout << "Enter only One word name." << endl;
}

void Game::Moves(string Player1, string Player2){
    cout << "Moves Used by " << Player1 << " " << pc1 << endl;
    cout << "Moves Used by " << Player2 << " " << pc2 << endl;
}

bool Game::Player(){
    return counter % 2;
}

int main(){
    Game();
    TTT.instructions();
    TTT.display();
    string Player1, Player2;
    int row, col, tempr = 1, tempc = 1;
    cout << "Player 1 : "; 
    getline(cin, Player1);
    cout << "Player 2 : "; 
    getline(cin, Player2);
    for (; TTT.counter <= 9; TTT.counter++){
        
        if(TTT.counter % 2 == 1){
            cout << Player1 << " Enter Position : "; cin >> row >> col;
            TTT.input(row, col, 'X', tempr, tempc);
        }
        else{
            cout << Player2 << " Enter Position : "; cin >> row >> col;  
            TTT.input(row, col, 'O', tempr, tempc);
        }
        
        if(TTT.isWinner()){
            if(Board[row-1][col-1] == 'X'){
                cout << endl << "Hurray! " << Player1 << " Won The Game." << endl;
            }
            else if(Board[row-1][col-1] == 'O'){
                cout << endl << "Hurray! " << Player2 << " Won The Game." << endl;
            }
            break;
        }
        tempr = row;
        tempc = col;
    }
    if(TTT.counter == 10){
        cout << "Draw! No Wins No Lose" << endl;
    }
    TTT.Moves(Player1 , Player2);
    char ch;
    cin >> ch;
    return 0;
}