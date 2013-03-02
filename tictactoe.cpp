#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class TicTacToe
{
public:
   char board[3][3];
   char playerPiece; 

   TicTacToe(char plyrpc)
   {
      initBoard();
      playerPiece = plyrpc;
   }
   TicTacToe()
   {
      initBoard();
   }

   void initBoard()
   {
      for(int i = 0; i < 3; i++)
      {
         for(int j = 0; j < 3; j++)
         {
            board[i][j] = ' ';
         }
      }
   }
   void setPlayerPiece(char p)
   {
      playerPiece = p;
   }

   void placeMove(int row, int col, char piece)
   {
      printf("Placing Move: %d, %d.\n", row, col);
      board[row][col] = piece;
      return;
   }

   void makeMove(char move[4])
   {
      int row;
      int col;
      char rs[2];
      char cs[2];

      memset(move, '\0', 4);

      printf("Your turn %c!\n", playerPiece);
      while(true)
      {
         printf("Enter row: ");
         //scanf("%d", &row);
         scanf("%s", rs);
         
         //Want to quit.
         if(rs[0] == 'q')
         {
            printf("Quit command found. In TTT.\n");
            move[0] = 'q';
            return;
         }

         printf("Enter column: ");
         scanf("%s", cs);

         row = (int)rs[0] - 48;
         col = (int)cs[0] - 48;
         //printf("row: %d, col = %d\n", row, col);
         if(validMove(row, col))
         {
            placeMove(row, col, playerPiece);
            showBoard();
            if(checkGameOver())
            {
               move[0] = 'w';
               printf("Game is over. %c won!!!\n", playerPiece);
            }
            else
               move[0] = 'm';
            move[1] = rs[0];
            move[2] = cs[0];
            return;
         }
         else 
            printf("Invalid piece placement. Please enter a valid move.\n");
      }
   }

   bool checkGameOver()
   {
      //printf("Checking for game over.");
      //Check Horizontal and Vertical.
      for(int i = 0; i < 3; i++)
      {
         //printf("Checking Horizontal.");
         //Horizontal
         if(board[i][0] == playerPiece && board[i][1] == playerPiece && board[i][2] == playerPiece)
            return true;

         //printf("Checking Vertical.");
         //Vertical
         if(board[0][i] == playerPiece && board[0][i] == playerPiece && board[2][i] == playerPiece)
            return true;
      }

      //printf("Checking left Cross.");
      //Cross Top->Bottom
      if(board[0][0] == playerPiece && board[1][1] == playerPiece && board[2][2] == playerPiece)
         return true;
      
      //printf("Checking right Cross.");
      if(board[2][0] == playerPiece && board[1][1] == playerPiece && board[0][2] == playerPiece)
         return true;

      for(int i = 0; i < 3; i++)
      {
         for(int j = 0; j < 3; j++)
         {
            if(board[i][j] == ' ')
               return false;
         }
      }

      return true;
   }

   bool validMove(int row, int col)
   {
      //printf("row = %d, col = %d\n", row, col);
      if(board[row][col] == ' ')
      {
         printf("Valid Move.\n");
         return true;
      }
      printf("Invalid Move.\n");
      return false;
   }

   void showBoard()
   {
      printf("%c|%c|%c\n-----\n%c|%c|%c\n-----\n%c|%c|%c\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
      return;
   }
};
