#include<iostream>
#include "functions.hpp"


int main(int argc, char* argv[]){

  bool useBot {true};
  if(argc == 2){ //if there was an input
    useBot = (argv[1][0] == '0' ? false : true);
  }

  Board ticTacToe {useBot};

  ticTacToe.playGame();
  
  return 0;
}
