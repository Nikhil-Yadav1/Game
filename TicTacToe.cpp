#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#define ORDER 4
#define INNER 3

char Board[ORDER][ORDER];
class Game
{
private:
    int row, col;
    string passcode = "0101";

public:
    Game();
    ~Game();
    void DataWrite(int row, int col);
    void DataWinner(string Player);
    void display();
    void hint();
    bool isWinner();
    void input(int row, int col, char c, int tempr, int tempc);
    void instructions();
    void Moves(string Player1, string Player2);
    void OpenA();
    bool Player();
    void showData();
    void toss();
    void undo(int row, int col);
    fstream file;
    int counter = 1, pc1 = 0, pc2 = 0;
} TTT;

Game::Game()
{
    for (int i = 0; i < ORDER; i++)
        for (int j = 0; j < ORDER; j++)
            Board[i][j] = ' ';
    OpenA();
}

Game::~Game()
{
    file.close();
}

void Game::DataWrite(int r, int c)
{
    file << "( " << r << ", " << c << " )  ";
}

void Game::DataWinner(string Player)
{
    file << endl
         << "Congratulations! " << Player << ", You Won The Game." << endl;
}

void Game::display()
{
    for (int i = 0; i < ORDER; i++)
    {
        // Upper layer
        cout << "\t\t\t\t\t";
        for (int j = 0; j < ORDER; j++)
        {
            cout << static_cast<char>(201);// Left top corner
            for (int k = 1; k <= INNER; k++)
                cout << static_cast<char>(205);// Top layer
            cout << static_cast<char>(187);// Right top corner
        }
        cout << endl;

        // Middle layer
        cout << "\t\t\t\t\t";
        for (int j = 0; j < ORDER; j++)
            cout << static_cast<char>(186) << " " << Board[i][j] << " " << static_cast<char>(186);
        cout << endl;

        // Lower layer
        cout << "\t\t\t\t\t";
        for (int k = 0; k < ORDER; k++)
        {
            cout << static_cast<char>(200);//Lower left corner
            for (int j = 1; j <= INNER; j++)
                cout << static_cast<char>(205);// Lower layer
            cout << static_cast<char>(188);//Lower right corner
        }
        cout << endl;
    }
    cout << endl;
}

void Game::hint()
{
    short r = (rand() % ORDER) + 1, c = (rand() % ORDER) + 1;
    if (Board[r][c] != ' ')
        cout << "You can input " << r << " " << c << endl;
    else
        hint();
}

bool Game::isWinner()
{
    for (int i = 0; i < ORDER; i++){ // Row Check
        if ((Board[i][0] == Board[i][1]) && (Board[i][0] == Board[i][2]) && (Board[i][0] == Board[i][3]) && Board[i][0] != ' ')
            return true;
    }

    for (int i = 0; i < ORDER; i++){ // Column Check
        if ((Board[0][i] == Board[1][i]) && (Board[0][i] == Board[2][i]) && (Board[0][i] == Board[3][i]) && Board[0][i] != ' ')
            return true;
    }

    // Diagonal Check
    // if ((Board[0][0] == Board[1][1]) && (Board[1][1] == Board[2][2]) && (Board[2][2] == Board[3][3]) && (Board[1][1] != ' '))
    //     return true;
    char win = Board[0][0];
    for(int i = 0; i < ORDER; i++){
        if(Board[i][i] != win)  return false;
        if((i == ORDER-1) && (win != ' '))  return true;
    }

    // if ((Board[0][3] == Board[1][2]) && (Board[1][2] == Board[2][1]) && (Board[2][1] == Board[3][0]) && (Board[0][3] != ' '))
    //     return true;
    win = Board[0][ORDER-1];
    for(int i = 0, j = ORDER-1; i < ORDER; i++, j--){
        if(Board[i][j] != win)  return false;
        if((i == ORDER-1) && (win != ' '))  return true;
    }
    return false;
}

void Game::input(int row, int col, char c, int tempr, int tempc)
{
    if (row >= 1 && row <= ORDER && col >= 1 && col <= ORDER)
    {
        if (Board[row - 1][col - 1] == ' ')
        {
            Board[row - 1][col - 1] = c;
            if (Player() == 1)
                pc1++;
            else
                pc2++;
            cout << endl;
            display();
            cout << endl;
            DataWrite(row, col);
        }
        else
        {
            cout << "Position Already Captured" << endl;
            counter--;
        }
    }
    else
    {
        if (row == 0 && col == 0)
            hint();
        else if (row == -1 && col == 0)
            undo(tempr, tempc);
        else
            cout << "Please Enter Correct Position Carefully." << endl;
        counter--;
    }
}

void Game::instructions()
{
    cout << "INSTRUCTIONS :" << endl;
    cout << "Enter Row Number and Column Number of the Block" << endl;
    cout << "For Hint Press 0 0" << endl;
    cout << "For Undo Press -1 0" << endl;
    cout << "Enter only One word name." << endl;
}

void Game::Moves(string Player1, string Player2)
{
    cout << "Moves Used by " << Player1 << " " << pc1 << endl;
    cout << "Moves Used by " << Player2 << " " << pc2 << endl;
    file << "\nMoves Used by " << Player1 << " " << pc1;
    file << "\nMoves Used by " << Player2 << " " << pc2 << endl;
}

void Game::OpenA()
{
    file.open("Tic Tac Toe.txt", ios::app);
}

void Game::showData()
{
    string name, code;
    vector<char> data;
    cout << "Enter Name : ";
    cin >> name;
    cout << "Enter Code : ";
    cin >> code;
    if (code == passcode)
    {
        file.close();
        ifstream ifile{"Tic Tac Toe.txt"};
        char line;
        cout << "\t\t\t\tDATABASE" << endl;
        while (!ifile.eof())
        {
            ifile.get(line);
            cout << line;
        }
        ifile.close();
        OpenA();
        file << "\nDATABASE ACCESSED BY " << name << endl;
    }
    else
        cout << "Wrong Code." << endl;
}

void Game::toss()
{
    cout << "Choose HEAD or TAIL" << endl;
    cout << "To Toss Press Any Key\n";
    string c;
    cin >> c;
    if (rand() % 2 == 1)
        cout << "HEAD" << endl;
    else
        cout << "TAIL" << endl;
}

void Game::undo(int row, int col)
{
    Board[row - 1][col - 1] = ' ';
    counter--;
    if (Player() == 1)
        pc1--;
    else
        pc2--;
    display();
    file.close();
    ifstream ifile{"Tic Tac Toe.txt"};
    string contents = "";
    char ch;
    while (ifile.get(ch))
        contents += ch;
    // cout << contents;
    ifile.close();
    ofstream ofile;
    ofile.open("Tic Tac Toe.txt");
    // cout << contents.length() << contents;
    // contents[contents.length()-10] = '\0';
    // cout << contents.length() << contents;
    for (int i = 0; contents[i] != '\0'; i++)
        ofile << contents[i];
    ofile.close();
    OpenA();
    file << " UNDONE-> ( " << row << ", " << col << ")\n";
}

bool Game::Player()
{
    return counter % 2;
}

int main()
{
    int ch;
    cout << "1. To Play" << endl;
    cout << "2. Database Access" << endl;
    cin >> ch;
    if (ch == 1)
    {
        TTT.instructions();
        TTT.toss();
        TTT.display();
        string Player1, Player2;
        int row, col, tempr = 1, tempc = 1;
        cout << "Player 1 : ";
        cin >> Player1;
        cout << "Player 2 : ";
        cin >> Player2;
        TTT.file << "\t\t\tGame Started\n";
        TTT.file << "Player1 : " << Player1 << "\nPlayer2 : " << Player2 << "\n";
        for (; TTT.counter <= ORDER*ORDER; TTT.counter++)
        {

            if (TTT.counter % 2 == 1)
            {
                cout << Player1 << " Enter Position : ";
                cin >> row >> col;
                TTT.input(row, col, 'X', tempr, tempc);
            }
            else
            {
                cout << Player2 << " Enter Position : ";
                cin >> row >> col;
                TTT.input(row, col, 'O', tempr, tempc);
            }

            if (TTT.isWinner())
            {
                if (Board[row - 1][col - 1] == 'X')
                {
                    TTT.DataWinner(Player1);
                    cout << endl << "Hurray! " << Player1 << " Won The Game." << endl;
                }
                else if (Board[row - 1][col - 1] == 'O')
                {
                    TTT.DataWinner(Player2);
                    cout << endl << "Hurray! " << Player2 << " Won The Game." << endl;
                }
                break;
            }
            tempr = row;
            tempc = col;
        }
        if (TTT.counter == ORDER*ORDER + 1)
        {
            cout << "Draw! No Wins No Lose" << endl;
            TTT.file << "\nDraw! No Wins No Lose\n";
        }
        TTT.Moves(Player1, Player2);
    }
    else if (ch == 2)
    {
        TTT.showData();
    }
    else
    {
        cout << "Enter Proper Choice.";
        main();
    }
    cin >> ch;
    TTT.file << "\t\t\tGame Finished\n\n";
    TTT.~Game();
    return 0;
}