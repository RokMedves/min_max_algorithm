
## How to use:
    - cd into code/
    - run make
    - run ./output to play against a bot
    - running ./output 0 to play with 2 players

## 18. 12. 2019 
   - DONE: still need to program the gameOver() function to make it game over when someone gets 3 in a row
   - still need to program a minimax algorithm to win every time

## 23. 12. 2019 
   - DONE: there is no garbage collection implemented in the program; but getAvailableSpaces() constantly creates a new pointer; should probably be implemented in Board::getMove() 

## 28. 02. 2020
   - DONE: Program works after rewriting bot function from scratch
   - Don't understant fully still why it works with the given min_max_flag
   - Code to allow the bot to go as 'x'
