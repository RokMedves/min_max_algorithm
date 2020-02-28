#include<iostream>
#include "functions.hpp"


int* getAvailOld(int anArray[]){
  std::cout << "hello" << std::endl;
  return anArray;
}
int** getAvail(int anArray[]){
  int** result = new int*[2];
  for(int i = 0; i < 2; i++){
    result[i] = new int[4];
  }
  for(int i = 0; i < 2; i++){
    for(int j = 0; j < 4; j++){
      result[i][j] = anArray[j];
    }
  }
  return result;
}

int main(int argc, char* argv[]){

  int array[] = {2, 3, 5, 7};
  int* array2;
  int** array3;
  array2 = getAvailOld(array);
  array3 = getAvail(array);
  for(int i = 0 ; i < 4; i++){
    std::cout << array2[i] << " ";
  }
  std::cout << std::endl;

  for(int j = 0; j < 2; j++){
    for(int i = 0 ; i < 4; i++){
      std::cout << array3[j][i] << " ";
    }
    std::cout << std::endl;
  }
  
  
  Board ticTacToe {true};

  //ticTacToe.playGame();
  
  return 0;
}
