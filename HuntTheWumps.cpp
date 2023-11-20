#include "std_lib_facilities.h"


void intro(){
    cout << "\t\t\tSTORY" << endl;
    cout << "\tThe basic premise is that a rather smelly monster lives in a dark cave consisting of connected rooms.";
    cout << " Your job is to slay the wumpus using bow and arrow. In addition to the wumpus, the cave has two hazards: bottomless";
    cout << " pits and giant bats. If you enter a room with a bottomless pit, it's the end of the game for you. If you enter a ";
    cout << " room with a bat, the bat picks you up and drops you into another room. If you enter the room with the wumpus or ";
    cout << " he enters yours, he eats you. When you enter a room you will be told if a hazard is nearby:\n";
    cout << "\t\t\"I smell the wumpus\": It's in an adjoining room.\"\n";
    cout << "\t\t\"I feel a breeze\": One of the adjoining rooms is a bottomless pit.\"\n";
    cout << "\t\t\"I hear a bat\": A giant bat is in an adjoining room.\"\n";
    cout << " For your convenience, rooms are numbered. Every room is connected by tunnels to three other rooms. When entering";
    cout << " a room, you are told something like \"You are in room 12; there are tunnels to rooms 1, 13, and 4; move or shoot?\"\n\n";
    cout << " Possible answers are m13 (\"Move to room 13\") and s13-4-3 (\"Shoot an arrow through rooms 13, 4, and 3\"). The ";
    cout << "range of an arrow is three rooms. At the start of the game, you have five arrows. The snag about shooting is that ";
    cout << "it wakes up the wumpus and he moves to a room adjoining the one he was in — that could be your room." << endl;
}

int main(){
    intro();
    return 0;
}
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

// Function to check if the player won
bool playerWins(const vector<int>& caverns, int playerLocation) {
    for (int i : caverns) {
        if (i != playerLocation) {
            return false;
        }
    }
    return true;
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    const int numCaverns = 20;
    const int numBats = 2;
    const int numPits = 2;
    const int wumpusLocation = rand() % numCaverns;

    vector<int> caverns(numCaverns);
    for (int i = 0; i < numCaverns; ++i) {
        caverns[i] = i;
    }

    // Randomly place bats and pits in caverns
    for (int i = 0; i < numBats + numPits; ++i) {
        int randomCavern = rand() % numCaverns;
        caverns[randomCavern] = -1; // -1 represents a pit or a bat
    }

    int playerLocation = 0;
    int arrows = 5;

    cout << "Welcome to Hunt the Wumpus!" << endl;

    while (true) {
        cout << "You are in cavern " << playerLocation << ". ";
        if (playerLocation == wumpusLocation) {
            cout << "You smell a terrible stench!" << endl;
        } else {
            cout << "You don't smell anything unusual." << endl;
        }

        cout << "You have " << arrows << " arrows left." << endl;

        if (playerLocation == wumpusLocation) {
            cout << "You have been eaten by the Wumpus! Game over!" << endl;
            break;
        }

        if (playerWins(caverns, playerLocation)) {
            cout << "Congratulations! You've won the game!" << endl;
            break;
        }

        int choice;
        cout << "Choose your next move:" << endl;
        cout << "1. Move to an adjacent cavern" << endl;
        cout << "2. Shoot an arrow" << endl;
        cout << "3. Quit the game" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the cavern number to move to: ";
                cin >> playerLocation;
                break;
            case 2:
                if (arrows > 0) {
                    int targetCavern;
                    cout << "Enter the cavern number to shoot into: ";
                    cin >> targetCavern;
                    --arrows;
                    if (targetCavern == wumpusLocation) {
                        cout << "Congratulations! You've shot the Wumpus!" << endl;
                    } else {
                        cout << "You missed! The Wumpus is now in cavern " << wumpusLocation << "." << endl;
                        wumpusLocation = rand() % numCaverns;
                    }
                } else {
                    cout << "You're out of arrows!" << endl;
                }
                break;
            case 3:
                cout << "Thanks for playing. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}