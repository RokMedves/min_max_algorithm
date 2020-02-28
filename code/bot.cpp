#include "functions.hpp"
#include <iostream>

//The bot methods

void printCharArray(char boardState[][3]){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      std::cout << boardState[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << "---" << std::endl;
}


int** getLocalAvailableSpaces(char theBoard[][3], int moveCount){
  unsigned int sizeOfSides = 3;
  unsigned int rows = 2;
  unsigned int columns = sizeOfSides * sizeOfSides - moveCount;

  //first, create that will be storing the available pairs
  int** pairs = new int*[rows];
  for(int i = 0; i < rows; i++){
    pairs[i] = new int[columns];
  }
  
  //fill up the array
  unsigned int counter = 0;
  for(int i = 0; i < sizeOfSides; i++){
    for(int j = 0; j < sizeOfSides; j++){
      if(theBoard[i][j] == '*'){
	pairs[0][counter] = i;
	pairs[1][counter] = j;
	counter++;
      }
    }
  }

  //return the result
  return pairs;
}

//local game over function:
int localGameOver(char boardState[][3]){
  //check if the board is already full

  unsigned int sizeOfSides = 3;
    
  //check rows
  bool isWinner = false;
  char activeLookFor = 'x';
  for(int i = 0; i < sizeOfSides; i++){
    activeLookFor = 'x';
    isWinner = true;
    for(int j = 0; j < sizeOfSides; j++){
      if(boardState[i][j] != activeLookFor) {
	  
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
      return (activeLookFor == 'x' ?  1 :   -1);
    }
  }

  //check columns [JUST BY CHANGING i AND j]
  isWinner = false;
  activeLookFor = 'x';
  for(int i = 0; i < sizeOfSides; i++){
    activeLookFor = 'x';
    isWinner = true;
    for(int j = 0; j < sizeOfSides; j++){
      if(boardState[j][i] != activeLookFor) {
	  
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
      return (activeLookFor == 'x' ?  1 :  -1);
   
    }
  }

  //check the diagonals as well
  activeLookFor = 'x';
  isWinner = true;
  for(int i = 0; i < sizeOfSides; i++){
    if(boardState[i][i] != activeLookFor) {

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
    return (activeLookFor == 'x' ?  1 : -1);
  }

  //lastly, check the other diagonal
  activeLookFor = 'x';
  isWinner = true;
  for(int i = 0; i < sizeOfSides; i++){
    if(boardState[i][sizeOfSides - 1 - i] != activeLookFor) {

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
    return (activeLookFor == 'x' ?  1 :  -1);
  }
    
  //if there are no three in a rows, the game is not over yet
  return 0;
  
}

char getPlayer(char board[][3], int &moves){
  int xs = 0, os = 0;
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < 3; j++){
      switch(board[i][j]){
      case 'x': xs++; break;
      case 'o': os++; break;
      }
    }
  }
  moves = (xs + os);
  return (xs == os ? 'x' : 'o');
}

int Board::botCalculateMove(char boardState[][3], int &xmove, int &ymove){
  int boardResult = localGameOver(boardState);
  if(boardResult !=0){
    return boardResult; //if game over return the result
  }else{
    int move_count = 0;
    char player = getPlayer(boardState, move_count);
    if(move_count == Board::sizeOfSides * Board::sizeOfSides){return 0;} //if all moves placed & not game over it's a tie

    //clone the boardState
    char clonedBoard[3][3];

    for(int i = 0; i < Board::sizeOfSides; i++){
      for(int j = 0; j < Board::sizeOfSides; j++){
	clonedBoard[i][j] = boardState[i][j];
      }
    }
    
    //find the available moves
    int** availableSpaces = getLocalAvailableSpaces(boardState, move_count);
    unsigned int length = sizeOfSides * sizeOfSides - move_count; //length of availableSpaces
    int min_max_flag = (player == 'x' ? 1 : -1); //if x wins, game over returns 1. 
    
    int bestResult = -2;
    int tempResult;
    int tempVar; //this will make sure that only the first call of bot calc move gets stored
    int bestx = 0, besty = 0;
    for(unsigned int i = 0; i < length; i++){
      clonedBoard[availableSpaces[0][i]][availableSpaces[1][i]] = player;

      tempResult = min_max_flag * Board::botCalculateMove(clonedBoard, bestx, besty); 

      if(tempResult > bestResult){
	xmove = availableSpaces[0][i];
	ymove = availableSpaces[1][i];
	bestResult = tempResult;
      }
      
      clonedBoard[availableSpaces[0][i]][availableSpaces[1][i]] = '*';
    }
    
    delete[] availableSpaces[0];
    delete[] availableSpaces[1];
    delete[] availableSpaces;
    return min_max_flag * bestResult; //if you are x, then you got the bet result for yourself. * (-1) for o
  }
}


