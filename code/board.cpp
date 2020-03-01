#include <iostream>
#include "functions.hpp"
#include <bits/stdc++.h> //for INT_MAX -- used in Board::getMove() to flush cin 

using namespace std;

Board::Board(bool useAI): useBot {useAI}
{
  for(int i = 0; i < sizeOfSides; i++){
    for(int j = 0; j < sizeOfSides; j++){
      theBoard[i][j] = '*';
    }
  }
  Board::draw();
}

Board::~Board(){
  cout << "deleting all objects" << endl;
}

void  Board::draw(){
  cout << endl;
  Board::drawBoard();
  cout << "Current Player: " << activePlayer << endl;
  //NOTE HOW WE CAN JUST USE ACTIVEPLAYER AND NOT BOARD::ACTIVEPLAYER
}

void Board::drawBoard(){
  for(int i = 0; i < sizeOfSides; i++){
    for(int j = 0; j < sizeOfSides; j++){
      cout << theBoard[i][j] << " ";
    }
    cout << endl;
  }  
}


void Board::getMove(){

  //check whether the move is being made by the bot or by the player
  
  //if bot is active and move is being made by o
  if(Board::useBot == true && Board::activePlayer == 'o'){
    int xmove = -1, ymove = -1;
    Board::botCalculateMove(Board::theBoard, xmove, ymove);
    //Board::activePlayer = 'o'; //the algorithm changes the active player variable, so let's reset it, just in
    placeMove(xmove, ymove);
  }
  //otherwise the player picks
  else{
    int x = -1, y = -1;
    bool isValidSpace = false;
    //get the input
    while(!isValidSpace){
      cout << "Please enter coordinates: ";
      cin >> x; x--;
      cin >> y; y--;
      //flush cin after input was received
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
    
      //check if in bounds
      if(x > -1 && y > -1 && x < 3 && y < 3){
	//check if space is free; if so, place move. Otherwise, redo.
	if(theBoard[x][y] == '*'){
	  Board::placeMove(x, y); //updates theBoard[][] and changes the player
	  isValidSpace = true;
	}
	else{
	  cout << "That space is already taken! Try another!" << endl;
	  isValidSpace = false;
	}
      }
      else{
	cout << "Coordinates are not in bounds. Please retry." << endl;
	isValidSpace = false;
      }
    }
  }
}

inline void Board::placeMove(int x, int y){
  theBoard[x][y] = activePlayer;
  changePlayer();
}

inline void Board::changePlayer(){
  activePlayer = (activePlayer=='x' ? 'o' : 'x');
}

bool Board::gameOver(){
  //check if the board is already full
  if(Board::moveCount < Board::sizeOfSides * Board::sizeOfSides){

    //check if we have 3 in a row anywhere
    
    //check rows
    bool isWinner = false;
    char activeLookFor = 'x';
    for(int i = 0; i < sizeOfSides; i++){
      activeLookFor = 'x';
      isWinner = true;
      for(int j = 0; j < sizeOfSides; j++){
	if(theBoard[i][j] != activeLookFor) {
	  
	  if(j == 0 && activeLookFor == 'x'){
	    activeLookFor = 'o';
	    j = -1;
	    continue;
	  }
	  
	  isWinner = false;
	  break;
	}
      }
      if(isWinner){
	(activeLookFor == 'x' ? winner = 1 : winner = -1);
	return true;
      }
    }

    //check columns [JUST BY CHANGING i AND j]
    isWinner = false;
    activeLookFor = 'x';
    for(int i = 0; i < sizeOfSides; i++){
      activeLookFor = 'x';
      isWinner = true;
      for(int j = 0; j < sizeOfSides; j++){
	if(theBoard[j][i] != activeLookFor) {
	  
	  if(j == 0 && activeLookFor == 'x'){
	    activeLookFor = 'o';
	    j = -1;
	    continue;
	  }
	  
	  isWinner = false;
	  break;
	}
      }
      if(isWinner){
	(activeLookFor == 'x' ? winner = 1 : winner = -1);
	return true;
      }
    }

    //check the diagonals as well
    activeLookFor = 'x';
    isWinner = true;
    for(int i = 0; i < sizeOfSides; i++){
	if(theBoard[i][i] != activeLookFor) {

	  //if this is the first time going around and we didn't find an x, then look for an o
	  if(i == 0 && activeLookFor == 'x'){
	    activeLookFor = 'o';
	    i = -1;
	    continue;
	  }
	  
	  isWinner = false;
	}      
    }
    
    if(isWinner){
      (activeLookFor == 'x' ? winner = 1 : winner = -1);
      return true;
    }

    //lastly, check the other diagonal
    activeLookFor = 'x';
    isWinner = true;
    for(int i = 0; i < sizeOfSides; i++){
	if(theBoard[i][sizeOfSides - 1 - i] != activeLookFor) {

	  //if this is the first time going around and we didn't find an x, then look for an o
	  if(i == 0 && activeLookFor == 'x'){
	    activeLookFor = 'o';
	    i = -1;
	    continue;
	  }
	  
	  isWinner = false;
	}  
    }
    
    if(isWinner){
      (activeLookFor == 'x' ? winner = 1 : winner = -1);
      return true;
    }
    
    //if there are no three in a rows, the game is not over yet
    return false;
  }
  //if no more moves can be made - the game is over
  return true;
}

void Board::playGame(){

  while(!Board::gameOver()){
    Board::getMove();
    //no game state is updated after here in the loop
    Board::moveCount++;
    Board::draw();
  }

  //display end of game message
  cout << "The game is over" << endl;
  if(Board::winner == 1){
    cout << "x has won" << endl;
  }
  if(Board::winner == -1){
    cout << "o has won" << endl;
  }
  if(Board::winner == 0){
    cout << "it was a tie" << endl;
  }
}




