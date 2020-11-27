// A Simple Tic-Tac-Toe game in C

#include <stdio.h>
#include <stdlib.h>

// Creates the board with all squares init to ' '

char** createGAMEboard() {
  char** B;
  B = (char **)malloc(3*sizeof(char*));
  for(int i = 0; i < 3; ++i) {
    B[i] = (char *)malloc(3*sizeof(char));
  }
  for(int j=0; j < 3; ++j) {
    for(int k=0; k < 3; ++k) {
      B[j][k] = ' ';
    }
  }
  return B;
}

// Prints the board

void printGAMEboard(char** Board) {
  printf(" |1|2|3|\n");
  for(int i = 0; i < 3; ++i) {
    printf("%c|", 'A' + i);
    for(int j = 0; j < 3; ++j) printf("%c|", Board[i][j]);
    printf("\n");
  }
}

// Returns true if the game is a draw

int isdraw(char** Board) {
  for(int i = 0; i < 3; ++i) {
    for(int j = 0; j < 3; ++j) {
      if (Board[i][j] == ' ') {
        return 0;  // empty square, so game ain't over yet
      }
    }
  }
  return 1;  // no empty squares, so it's a draw
}

// Returns 'X' if (i,j) was a winning move for X
// Returns 'Y' if (i,j) was a winning move for Y
// Retruns ASCII value 0 otherwise

char winningmove(char** Board, int i, int j) {
  if (Board[i][j] == Board[i][(j+1)%3] && Board[i][j] == Board[i][(j+2)%3]) {
    return Board[i][j]; // got a column
  }
  else if (Board[i][j] == Board[(i+1)%3][j] && Board[i][j] == Board[(i+2)%3][j]) {
    return Board[i][j];   // got a row
  }
  else if (i == j && Board[i][j] == Board[(i+1)%3][(j+1)%3] && Board[i][j] == Board[(i+2)%3][(j+2)%3]) {
    return Board[i][j];  // got the forward diagonal
  }
  else if (i+j == 2 && Board[i][j] == Board[(i+2)%3][(j+1)%3] && Board[i][j] == Board[(i+1)%3][(j+2)%3]) {
    return Board[i][j]; // got the reverse diagonal
  }
  else return 0; // got nothing  
}

// MAIN FUNCTION

int main() {
  char** Board = createGAMEboard();
  char winner = '\0';
  char row;
  char col;
  char turn = 'X';
  while(!winner && !isdraw(Board)){
    printGAMEboard(Board);
    printf("Player %c, make your move: ", turn);
    fflush(stdout);
    scanf(" %c %c", &row, &col);    // Read Move

    // Make move if square is free

    int rowind = row - 'A';
    int colind = col - '1';
    if (Board[rowind][colind] == ' ') {
      Board[rowind][colind] = turn;
      if (turn == 'X') turn = 'O';
      else turn = 'X';
      winner = winningmove(Board, rowind, colind);
    } else {
      printf("Block not available; try again.\n");
    }
  }

  // Game over - print board & declare finish

  printGAMEboard(Board);
  if (winner == 'X' || winner == 'O') {
    printf("Congratulations %c You Won!\n", winner);
  } else {
    printf("Game ends in a draw.\n");
  }
  return 0;
}