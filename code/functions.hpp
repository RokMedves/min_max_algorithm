#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

//let's define here all the data types we will be using for our project

class Board{

 public:
  
  Board(bool useBot);
  ~Board();

  void draw();
  void playGame();
  
 private:

  unsigned int sizeOfSides = 3;
  //char theBoard[sizeOfSides][sizeOfSides];
  char theBoard[3][3];
  char activePlayer = 'x';
  unsigned int moveCount = 0;
  bool useBot = false;
  int winner = 0; // -1 == o wins, 0 == is a tie, 1 == x wins
  
  void drawBoard();
  bool gameOver();
  void placeMove(int a, int b);
  void getMove(); 
  void changePlayer();

  //bot methods
  int** getAvailableSpaces();
  int botCalculateMove(char board[][3], int &xmove, int &ymove);

};

#endif //FUNCTIONS_HPP
