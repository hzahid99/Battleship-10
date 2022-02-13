#ifndef GAME_H
#define GAME_H
#include <iostream>
#include "Player.h"

class Game
{
private:
	// The player currently taking their turn.
	int currentPlayer;

	// The limit used to compare the total number of spaces that the ships are sunk on a board
	int totalXs;

	// Number of ships for the game
	int numShips;

	// A heap allocated object of the player class
	// The first player of the game
	Player *player1;
	// Second player of the game
	Player *player2;

public:
	/*
	 * @pre none
	 * @post Initializes both the players and sets totalXs to zero.
	 * @param none
	 * @return None
	 */
	Game();

	/*
	 * @pre none
	 * @post deletes both players
	 * @param none
	 * @return None
	 */
	~Game();

	void setup();
	void setupPlayer(Player *currentPlayer);
	int getInt();
	bool isDigit(string str);
	char getChar();

	/*
	 * @pre none
	 * @post Confirms the current player is done with their turn and clears the screen.
	 * 	Double checks with the next person if they are ready for their turn.
	 * @param none
	 * @return None
	 */
	void clear();

	/*
	 * @pre none
	 * @post The player played their turn.
	 * @param an int representing whose turn it was
	 * @return None
	 */
	void turn(int currentPlayer);

	/*
	 * @pre none
	 * @post Actually goes through a player's turn where they see their board and ships lives, attack, and
	 * 	see whether their attack missed or hit
	 * @param Two player objects- the one taking their turn and the other player
	 * @return None
	 */
	void takeTurn(Player *currentPlayer, Player *otherPlayer);
	void attack(Player *attackingPlayer, Player *defendingPlayer, int row, int col);

	/*
	 * @pre row and col values between 0 and 9 (representing the indexes of the board 2d array)
	 * @post Tells whether or not a player has already fired at that location.
	 * @param the row and col of the attack location and the player firing the attack
	 * @return a bool representing if that target can be fired upon
	 */
	bool validAttack(Player *attackingPlayer, int row, int col);

	/*
	 * @pre none
	 * @post Goes through the currentPlayer's firing board tallying the number of sunk spots.
	 * 	If they sunk all their opponent's ships, it's the end of the game.
	 * @param none
	 * @return a bool representing whether the game is over or not
	 */
	bool gameover();

	/*
	 * @pre none
	 * @post runs the entire game and calls upon a host of functions to do so.
	 * @param none
	 * @return None
	 */
	void play();
};
#endif
