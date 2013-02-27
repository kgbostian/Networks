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
      //if(validMove(row,col))
      board[row][col] = piece;
      return;
   }

   void makeMove(char move[4])
   {
      int row;
      int col;
      char rs[2];
      char cs[2];

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
         printf("row: %d, col = %d\n", row, col);
         if(validMove(row, col))
         {
            placeMove(row, col, playerPiece);
            showBoard();
            move[0] = 'm';
            //sprintf(rs, "%d", row);
            //sprintf(cs, "%d", col);
            move[1] = rs[0];
            move[2] = cs[0];
            return;
         }
         else 
            printf("Invalid piece placement. Please enter a valid move.");
      }
   }

   bool validMove(int row, int col)
   {
      printf("row = %d, col = %d\n", row, col);
      if(board[row][col] == ' ')
      {
         printf("Valid Move.");
         return true;
      }
      printf("Invalid Move.");
      return false;
   }

   void showBoard()
   {
      printf("%c|%c|%c\n-----\n%c|%c|%c\n-----\n%c|%c|%c\n", board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
      return;
   }
};
