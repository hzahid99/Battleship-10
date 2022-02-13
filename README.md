# Battleship-10
<h2> Installing the game </h2>
<ol>
  <li> Clone the directory using git clone https://github.com/samhut14/Battleship-10.git
  <li> Make sure g++ or GNU Make is installed so that you can run the makefile and build the C++ code</li>
  <li> Once installed, in the main directory run make in the terminal </li>
</ol>
<h2> Flow of the Game </h2>
  
  <p>After the main.cpp creates the game object, Battleship, it passes over control to game's method, play(). The first function play calls is setup, where it gives an introduction to the game and a legend for what M, H, X, and S mean. It will also ask the user how many ships they would like to play with. Afterwards, it will initialize two player objects and call the helper function setupPlayer. In setupPlayer, the user will place their ships, and it will call other functions to double check the validity of the placement. It will show the player the board after the placement, and it will repeat this process until all the ships are placed. After both players are setup, each player will have their turn starting off with Player 1.</p>
  
  <p>The turn method will print off whose turn it is and pass control over to the helper function takeTurn. Within it, it will print the player's view and proceed to ask them an attack location. It will continue to ask until a valid location is provided. That information is then passed over to the attack function. If the attack spot has no ships present, it will be marked as a miss. Otherwise, the ship will lose a life, and the spot will be marked as a hit; however, if the ship has lost all of its lives, all the spots associated with that ship will be marked with Xs indicating that it is sunk. A message for the user will display whether it was a hit, miss, or sunk. It will also tell the user which ship was sunk. </p>
    
  <p>After each turn, a clear function will confirm that the player is done with their turn and then clear the board. It will then ask the next player if they are ready for their turn. Between each turn, gameover is called which checks to see if all ships are sunk on the player's public board (their view of their opponent's board). If so, the game will be over and a message will be printed off saying who the winner is. </p>

