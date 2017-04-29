//Andrew Butler
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int placeShip(int size, int ** board);
void playerMove(int ** board);

int numShots;

int main(){
  srand(time(NULL));
  int ** board;
  board=(int **)malloc(10*sizeof(int *));
  int x, y;
  for(x=0;x<10;x++){
    board[x]=(int *)malloc((10)*sizeof(int));
  }
  for(x=0;x<10;x++){
    for(y=0;y<10;y++){
      board[x][y]=0;
    }
  }

  //calls the placeShip function until each ship is placed successfully
  while(!placeShip(5, board));
  while(!placeShip(4, board));
  while(!placeShip(3, board));
  while(!placeShip(3, board));
  while(!placeShip(2, board));
  //prints initial board configuration for testing purposes
  /*printf("[ ]A B C D E F G H I J\n");
  for(x=0;x<10;x++){
    printf("%02i|", x+1);
    for(y=0;y<10;y++){
      printf("%i ", board[x][y]);
    }
    printf("\n");
  }*/
  numShots=0;
  printf("Welcome to Battleship! Board configuration will be printed as follows:\n");
  printf("An empty space indicates that no shot has been fired at that location.\n");
  printf("An X indicates shot and hit, an O indicates shot and missed. Enjoy!\n");
  playerMove(board);
  printf("All ships sunk after %i shots. Congratulations!\n", numShots);

}

//Input: the board matrix
//Output: prompts the user to shoot, displays hit or miss data
//then prints board configuration and loops until all ships destroyed
void playerMove(int ** board){
  char column;
  int row, columnN, x, y, numLeft;
  while(1){
    numShots++;
    printf("Enter square to shoot(example format: A9):\n");
    scanf("%1s%i", &column, &row);
    columnN=((int)column)-65;
    if(board[row-1][columnN]==1){
      numLeft=0;
      board[row-1][columnN]=3;
      printf("Hit on square %c%i!\n", column, row);

      //checks if any undestroyed ships exist
      for(x=0;x<10;x++){
        for(y=0;y<10;y++){
          if(board[x][y]==1){
            numLeft++;
          }
        }
      }
      if(numLeft==0){
        return;
      }
    }
    else{
      board[row-1][columnN]=2;
      printf("Miss on square %c%i.\n", column, row);
    }

    //prints current state of the board, as seen from hit/miss results
    printf("Current board configuration:\n");
    printf("[ ]A B C D E F G H I J\n");
    for(x=0;x<10;x++){
      printf("%02i|", x+1);
      for(y=0;y<10;y++){
        if(board[x][y]==2){
          printf("O ");
        }
        else if(board[x][y]==3){
          printf("X ");
        }
        else{
          printf("  ");
        }
      }
      printf("\n");
    }
  }
}

//places a ship on the board
//Input: size of the ship, board matrix
int placeShip(int size, int ** board){
  int tempx, tempy, direction, x, y;
  direction=rand()%2;

  //ship is placed vertically
  if(direction==0){
    tempx=rand()%(10-size);
    srand(rand());
    tempy=rand()%10;
    int lowerCheck=(tempx-1>=0) ? tempx-1 : 0;
    int upperCheck=(tempx+size+1<=10) ? tempx+size+1 : 10;
    for(x=lowerCheck;x<upperCheck;x++){

      //ensures ships cannot be vertically or horizontally adjacent
      if(x>=tempx&&x<tempx+size){
        if(tempy>0&&board[x][tempy-1]){
          return 0;
        }
        if(tempy<9&&board[x][tempy+1]){
          return 0;
        }
      }
      //detects if a ship is already in the path of where this ship is to be placed
      if(board[x][tempy]){
        return 0;
      }
    }
    for(x=tempx;x<tempx+size;x++){
      board[x][tempy]=1;
    }
  }

  //ship is placed horizontally
  else{
    tempx=rand()%10;
    srand(rand());
    tempy=rand()%(10-size);
    int lowerCheck=(tempy-1>=0) ? tempy-1 : 0;
    int upperCheck=(tempy+size+1<=10) ? tempy+size+1 : 10;
    for(y=lowerCheck;y<upperCheck;y++){

      //ensures ships cannot be vertically or horizontally adjacent
      if(y>=tempy&&y<tempy+size){
        if(tempx>0&&board[tempx-1][y]){
          return 0;
        }
        if(tempx<9&&board[tempx+1][y]){
          return 0;
        }
      }
      if(board[tempx][y]){
        return 0;
      }
    }
    for(y=tempy;y<tempy+size;y++){
      board[tempx][y]=1;
    }
  }
}
