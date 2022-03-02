/** -----------------------------------------------------------------------------
 *
 * @file  Player.cpp
 * @authors Amith Panuganti, Jasem Ali, Ahmni Pang-Johnson
 * Assignment:   EECS-448 Project #1
 * @brief This file impliment the methods of Player
 * @date 2/13/22
 *
 ---------------------------------------------------------------------------- **/

#include "Player.h"
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

// Constructs Player without any parameters
Player::Player()
{
    // Set m_numberOfShips to be 0 to show that Ships will not be set up
    m_numberOfShips = 0;

    // Set m_shipCounter to be 0
    m_shipCounter = 0;

    // Set m_ships to be nullptr
    m_ships = nullptr;

    //Set both m_publicBoard and m_privateBoard to be nullptr
    m_publicBoard = nullptr;
    m_privateBoard = nullptr;
}

Player::Player(int size)
{
    m_numberOfShips = size;
    m_ships = new Ship *[m_numberOfShips];

    m_publicBoard = new Board();
    m_privateBoard = new Board();

    m_shipCounter = 0;
}

// Deconstructs Player
Player::~Player()
{
    // If m_ships is not set to nullptr
    if (m_ships != nullptr)
    {
        //For each m_ship* in m_ships, starting at index 0
        for (int i = 0; i < m_numberOfShips; i++)
            delete m_ships[i]; // Delete each heap allocated Ship object

        delete[] m_ships; // Delete the array that was containing the Ship objects
    }

    //Delete beoth m_publicBoard and m_privateBoard
    delete m_publicBoard;
    delete m_privateBoard;
}

// Setup functions:

bool Player::startValid(int row, int col)
{
    if (row < 0 || row > 9 || col < 0 || col > 9) // If out of bounds
        return false;

    return (m_privateBoard->at(row, col) == "*"); // Otherwise, true if the board is * at that position
}

bool Player::pathValid(int startRow, int startCol, int endRow, int endCol, int size)
{
    int temp;      // Controls whether we will traverse in the positive or negative direction
    string arr[5]; // To fill with the correct elements for the Ship's position array
                   // Always stack allocated with size 5 (maximum size for the position array) to avoid heap allocations

    if ((startRow == endRow) && (startCol != endCol)) // If the start and end row are the same, but the columns aren't
    {
        if (abs(endCol - startCol) == size - 1) // If the distance between the end and start column is exactly Ship's size - 1
                                                // Eg. size 3 takes up 3 spots, and the distance from the last to the first spot is 2
        {
            if (startCol > endCol) // If the starting column is greater than the ending column,
                temp = -1;         // We traverse the negative direction
            else                   // Otherwise traverse the positive direction
                temp = 1;

            goto traverseCol; // Go to where we traverse the columns, keeping the row constant (because each ship is necessarily 1 x size)
        }
        else
            return false; // If the distance between the end and start column is NOT size - 1
    }

    // Same logic applies here, but to equal columns and unequal rows:
    else if ((startRow != endRow) && (startCol == endCol))
    {
        if (abs(endRow - startRow) == size - 1)
        {
            if (startRow > endRow)
                temp = -1;
            else
                temp = 1;

            goto traverseRow;
        }
        else
            return false;
    }

    else if ((startRow == endRow) && (startCol == endCol) && (size == 1)) // If we are to place Ship 1 (size 1 x 1)
    {
        arr[0] = to_string(startRow);    // Set the first element in the dummy array equal to the string conversion of the row
        arr[0].push_back(startCol + 65); // Append said element with the correct column letter (in the ASCII table, capital A is index 65, B is index 66 and so on)

        m_ships[m_shipCounter] = new Ship(size, arr); // Create a new Ship objdect at the correct position in the array
        placeShip(m_ships[m_shipCounter]);            // Place that Ship on the Private Baord
        return true;
    }

    return false; // If none of the previous conditions check, the path is necessarily invalid

traverseCol: // Traverse the columns, keeping the row constant
    for (int i = 0; i <= size - 1; i++)
    {
        if (m_privateBoard->at(startRow, startCol) != "*") // Whenever the position is not *, the path is invalid
            return false;
        else // If the position is *, potentially allowing a Ship placement,
        {
            arr[i] = to_string(startRow);    // Set the i'th element in the dummy array equal to the string conversion of the starting row
            arr[i].push_back(startCol + 65); // Append said element with the correct column letter (in the ASCII table, capital A is index 65, B is index 66 and so on)

            startCol += temp; // Either increment or decrement the column, based on whether we are going in the positive or negative direction
        }
    }
    m_ships[m_shipCounter] = new Ship(size, arr);
    placeShip(m_ships[m_shipCounter]);
    return true;

traverseRow: // Traverse the rows, keeping the column constant
    for (int i = 0; i <= size - 1; i++)
    {
        if (m_privateBoard->at(startRow, startCol) != "*")
            return false;
        else
        {
            arr[i] = to_string(startRow);
            arr[i].push_back(startCol + 65);

            startRow += temp;
        }
    }
    m_ships[m_shipCounter] = new Ship(size, arr);
    placeShip(m_ships[m_shipCounter]);
    return true;
}

// Sinks a player's ship
void Player::sinkShip(int hitship)
{
    // access the position array of the ship that got hit
    string *arr = m_ships[hitship - 1]->getPositionArr();
    // mark each place the ship that got hit is positioned with an X
    for (int i = 0; i < m_ships[hitship - 1]->getSize(); i++)
    {
        m_privateBoard->setBoard("X", arr[i].at(0) - 48, arr[i].at(1) - 65);

    }
    std::cout << "\nShip " << hitship << " was sunk! \n";
}

void Player::markPublicSunk(string *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        // ark each place where ship was sunk with an x
        m_publicBoard->setBoard("X", arr[i].at(0) - 48, arr[i].at(1) - 65);
    }
}

string *Player::markPrivate(string strike, int row, int col, int hitship, bool isHit)
{

    if (isHit)
    {
        // checks if ship is sunk
        if (m_ships[hitship - 1]->loseLife())
        {
            sinkShip(hitship);
            // returns the array with all the positions of the ship to mark for other player
            return m_ships[hitship - 1]->getPositionArr();
        }
        else
        {
            // put an H on the board at row col
            m_privateBoard->setBoard(strike, row, col);
            std::cout << "\nShip " << hitship << " was hit \n\n";
        }
    }
    else
    {
        // puts an M on the board at row col
        m_privateBoard->setBoard(strike, row, col);
        std::cout << "\nAttack missed! \n\n";
    }
    // if wasn't sunk it will return an empty arr so nothing will get marked
    return {};
}

void Player::placeShip(Ship *someShip)
{
    int row, col;
    string symbol = "S" + to_string(someShip->getSize()); // Sets symbol equal to S followed by the Ship's size
    for (int i = 0; i < someShip->getSize(); i++)
    {
        row = someShip->getRow(i);    // Obtain the Ship's row in the position array at index i
        col = someShip->getColumn(i); // Obtain the Ship's column in the position array at index i

        m_privateBoard->setBoard(symbol, row, col); // Set the element in the Private Board at this index equal to symbol
    }
    //cout << "\nShip " << someShip->getSize() << " was placed!\n";
    m_shipCounter++;
}

void Player::printPrivateBoard()
{
    cout << "\nHere is your current board:\n\n";
    cout << "\tA\tB\tC\tD\tE\tF\tG\tH\tI\tJ\n";
    for (int i = 0; i < 10; i++)
    {
        cout << i + 1 << "\t";
        for (int j = 0; j < 10; j++)
            cout << m_privateBoard->at(i, j) << "\t";

        cout << endl;
    }
    cout << endl;
}

// Print the healthbar for each ship
void Player::shipHealthBar()
{
    // Example dislay
    //  Ships Health:
    //  1x1: 5     1x2: 0     1x3: 4

    // Firstly, tell the user that we are printing their ships helath
    std::cout << " Ships Health:\n ";

    // Next, we are goning to put everything in one line for now
    // Loop for each ship the player hass
    for (int i = 0; i < m_numberOfShips; i++)
    {
        // Print out the Ship with size 1x(i+1)
        std::cout << "1x" << (i + 1) << ": ";
        // Print the ships life
        std::cout << m_ships[i]->getLife() << "     ";
    }

    // Add the end of the loop, print a new line
    std::cout << "\n";
}

// Print the player's view during gameplay
void Player::view()
{
    // Example view
    //      A   B   C   D
    //  1   S1  S2  X   X
    //  2   *   *   *   *
    //  3   *   *   *   *
    //  4   *   *   *   *

    // Firstly, we need to print the player's view of their oponent's Board
    // Then, tell the user what board we are printing out
    std::cout << "Opponent's Board:\n\n";

    // Next, print the columns of the board into one line
    std::cout << "\tA\tB\tC\tD\tE\tF\tG\tH\tI\tJ\n";

    // Next, for loop 10 times for each row of the board
    for (int i = 0; i < 10; i++)
    {
        // Print the row number of the board
        std::cout << i + 1 << "\t";

        // Goes through each string of the row
        for (int j = 0; j < 10; j++)
        {
            // Print the string at row i and column j
            std::cout << m_publicBoard->at(i, j) << "\t";
        }

        // Print a new line to end the row
        std::cout << "\n";
    }

    // Print a new line
    std::cout << "\n";

    // Next, we print the player's view of their board
    // Tell the user that we are printing out their board
    std::cout << "Your Board:\n\n";

    // Next, print the cloumns of the board into one line
    std::cout << "\tA\tB\tC\tD\tE\tF\tG\tH\tI\tJ\n";
    // Next, for loop 10 times for each row of the board
    for (int i = 0; i < 10; i++)
    {
        // Print the row number of the board
        std::cout << i + 1 << "\t";

        // Goes through each string of the row
        for (int j = 0; j < 10; j++)
        {
            // Print the string at row i and column j
            std::cout << m_privateBoard->at(i, j) << "\t";
        }

        // Print a new line to end the row
        std::cout << "\n";
    }

    // Print a new line
    std::cout << "\n";

    // Next, print the ship's healthbar
    shipHealthBar();

    // Print a new line
    std::cout << "\n";
}

// Get the public board
Board *Player::getPublicBoard()
{
    // Return m_publicBoard
    return m_publicBoard;
}

// Get the private board
Board *Player::getPrivateBoard()
{
    // Return m_privateBoard
    return m_privateBoard;
}

void Player::markPublic(string strike, int row, int col)
{
    // Either marks as an H or M at row col depending on if there is a ship or not
    m_publicBoard->setBoard(strike, row, col);
}

// Get the Player's Ships
Ship **Player::getShips()
{
    // Return m_ships
    return m_ships;
}

bool Player::shipPresent(int row, int col)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if (m_privateBoard->at(row,col) == "M" || m_privateBoard->at(row,col) == "*" || m_privateBoard->at(row,col) == "H" || m_privateBoard->at(row,col) == "X")
            {
                return false;
            }
            
            return true;
        }

        return true;
        
    }
    
}