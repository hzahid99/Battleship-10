#include <iostream>
#include "Game.h"
#include <limits>
#include "AI.h"

using namespace std;

int main()
{
    int mode = 0;
    cout << "*** Welcome to Battleship ***\nEnter game mode to play: \n";
    do
    {
        cout << "1 for Player VS. AI mode \n";
        cout << "2 for Player1 VS Player2 mode\nMode: ";
        cin >> mode;

        cout << "";
        while (std::cin.fail()) //Data Type Validation
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid data type entered. Mode must be an integer value.\nEnter again: ";
			std::cin >> mode;
		}
        cout << "\n";
    } while (mode != 1 && mode != 2);

    if (mode == 1)
    {
        AI battleship;
        battleship.play();
    }

    else
    {
        Game battleship;
        battleship.play();  
    }

    return(0);
}
