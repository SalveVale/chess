#include "piece.hpp"

#include <iostream>
#include <tuple>
#include <vector>

GameBoard::GameBoard()
{
  for (int i=0; i<8; i++)
    for (int j=0; j<8; j++)
      this->board[i][j] = 0;
  
  for (int i=0; i<8; i++) this->board[1][i] = new PawnPiece('B');
  for (int i=0; i<8; i++) this->board[6][i] = new PawnPiece('W');
  this->board[0][0] = new RookPiece('B');
  this->board[0][7] = new RookPiece('B');
  this->board[7][0] = new RookPiece('W');
  this->board[7][7] = new RookPiece('W');
  this->board[0][1] = new KnightPiece('B');
  this->board[0][6] = new KnightPiece('B');
  this->board[7][1] = new KnightPiece('W');
  this->board[7][6] = new KnightPiece('W');
  this->board[0][2] = new BishopPiece('B');
  this->board[0][5] = new BishopPiece('B');
  this->board[7][2] = new BishopPiece('W');
  this->board[7][5] = new BishopPiece('W');
  this->board[0][4] = new QueenPiece('B');
  this->board[7][3] = new QueenPiece('W');
  this->board[0][3] = new KingPiece('B');
  this->board[7][4] = new KingPiece('W');
}
GameBoard::~GameBoard()
{
  for (int i=0; i<8; i++)
    for (int j=0; j<8; j++)
    {
      delete this->board[i][j];
      this->board[i][j] = 0;
    }
}
void GameBoard::printBoard()
{
  using namespace std;
  for (int i=0; i<8; i++)
  {
    for (int j=0; j<8; j++)
    {
      if (board[i][j] == 0) cout << this->board[i][j] << " ";
      else cout << this->board[i][j]->getPiece() << " ";
    }
    cout << endl;
  }
  cout << endl;
}
char GameBoard::getColor(int y, int x)
{
  return this->board[y][x]->getColor();
}
std::vector<std::vector<int>> GameBoard::calcLegalSquares(int starty, int startx)
{
  return this->board[starty][startx]->calcLegalSquares(starty, startx, this->board);
}
char GameBoard::updateBoard(int startx, int starty, int endx, int endy)
{
  // if (this->board[starty][startx] != 0)
  // {
    this->board[endy][endx] = this->board[starty][startx];
    this->board[starty][startx] = 0;
  // }
  int numKings = 0;
  GamePiece *king1;
  GamePiece *king2;
  for (int i=0; i<8; i++)
  {
    for (int j=0; j<8; j++)
    {
      if (this->board[i][j] != 0)
      {
        if (this->board[i][j]->getPiece() == 'K')
        {
          numKings++;
          if (numKings < 2) king1 = board[i][j];
          else king2 = board[i][j];
        }
      }
    }
  }
  if (numKings < 2) return king1->getColor();
  return 'N';
}
bool GameBoard::isLegalMove(int starty, int startx, int endy, int endx)
{
  return this->board[starty][startx]->isLegalMove(starty, startx, endy, endx, this->board);
}


GamePiece::GamePiece() {}
GamePiece::~GamePiece() {}

PawnPiece::PawnPiece(char color)
{
  this->color = color;
}
char PawnPiece::getColor()
{
  return this->color;
}
char PawnPiece::getPiece()
{
  return 'P';
}
std::vector<std::vector<int>> PawnPiece::calcLegalSquares(int starty, int startx, GamePiece *board[8][8])
{
  std::vector<std::vector<int>> legalSquares;

  if (board[starty][startx]->getColor() == 'W')
  {
    if (board[starty-1][startx] == 0)
    {
      std::vector<int> square;
      square.push_back(startx);
      square.push_back(starty-1);
      legalSquares.push_back(square);
      if (starty == 6 && board[starty-2][startx] == 0)
      {
        std::vector<int> square2;
        square2.push_back(startx);
        square2.push_back(starty-2);
        legalSquares.push_back(square2);
      }
    }
    if (board[starty-1][startx+1] != 0)
    {
      if (board[starty-1][startx+1]->getColor() == 'B')
      {
        std::vector<int> square3;
        square3.push_back(startx+1);
        square3.push_back(starty-1);
        legalSquares.push_back(square3);
      }
    }
    if (board[starty-1][startx-1] != 0)
    {
      if (board[starty-1][startx-1]->getColor() == 'B')
      {
        std::vector<int> square4;
        square4.push_back(startx-1);
        square4.push_back(starty-1);
        legalSquares.push_back(square4);
      }
    }
  }
  else
  {
    if (board[starty+1][startx] == 0)
    {
      std::vector<int> square;
      square.push_back(startx);
      square.push_back(starty+1);
      legalSquares.push_back(square);
      if (starty == 1 && board[starty+2][startx] == 0)
      {
        std::vector<int> square2;
        square2.push_back(startx);
        square2.push_back(starty+2);
        legalSquares.push_back(square2);
      }
    }
    if (board[starty+1][startx+1] != 0)
    {
      if (board[starty+1][startx+1]->getColor() == 'W')
      {
        std::vector<int> square3;
        square3.push_back(startx+1);
        square3.push_back(starty+1);
        legalSquares.push_back(square3);
      }
    }
    if (board[starty+1][startx-1] != 0)
    {
      if (board[starty+1][startx-1]->getColor() == 'W')
      {
        std::vector<int> square4;
        square4.push_back(startx-1);
        square4.push_back(starty+1);
        legalSquares.push_back(square4);
      }
    }
  }
  return legalSquares;
}
bool PawnPiece::isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8])
{
  if (board[endy][endx] == 0)
  {
    if (endx == startx)
    {
      if (board[starty][startx]->getColor() == 'W')
      {
        if (starty == 6)
        {
          if (endy == 5 || endy == 4) return true;
        }
        else
        {
          if (endy == starty-1) return true;
        }
      }
      else
      {
        if (starty == 1)
        {
          if (endy == 2 || endy == 3) return true;
        }
        else
        {
          if (endy == starty+1) return true;
        }
      }
    }
  }
  else
  {
    if (endx == startx+1 || endx == startx-1)    
    {
      if (board[starty][startx]->getColor() == 'W') 
      {
        if (endy == starty-1 && board[endy][endx]->getColor() == 'B') return true;  
      }
      else
      {
        if (endy == starty+1 && board[endy][endx]->getColor() == 'W') return true;
      }
    }
  }
  return false;
}

RookPiece::RookPiece(char color)
{
  this->color = color;
}
char RookPiece::getColor()
{
  return this->color;
}
char RookPiece::getPiece()
{
  return 'R';

}
std::vector<std::vector<int>> RookPiece::calcLegalSquares(int starty, int startx, GamePiece *board[8][8])
{
  std::vector<std::vector<int>> legalSquares;
  for (int i=0; i<starty; i++)
  {
    if (board[starty-i-1][startx] != 0)
    {
      if (board[starty-i-1][startx]->getColor() != board[starty][startx]->getColor())
      {
        std::vector<int> square;
        square.push_back(startx);
        square.push_back(starty-i-1);
        legalSquares.push_back(square);
      }
      break;
    }
    std::vector<int> square;
    square.push_back(startx);
    square.push_back(starty-i-1);
    legalSquares.push_back(square);
  }
  for (int i=0; i<startx; i++)
  {
    if (board[starty][startx-i-1] != 0)
    {
      if (board[starty][startx-i-1]->getColor() != board[starty][startx]->getColor())
      {
        std::vector<int> square;
        square.push_back(startx-i-1);
        square.push_back(starty);
        legalSquares.push_back(square);
      }
      break;
    }
    std::vector<int> square;
    square.push_back(startx-i-1);
    square.push_back(starty);
    legalSquares.push_back(square);
  }
  int yloops = 0;
  for (int i=7; i>starty; i--)
  {
    if (board[starty+yloops+1][startx] != 0)
    {
      if (board[starty+yloops+1][startx]->getColor() != board[starty][startx]->getColor())
      {
        std::vector<int> square;
        square.push_back(startx);
        square.push_back(starty+yloops+1);
        legalSquares.push_back(square);
      }
      break;
    }
    std::vector<int> square;
    square.push_back(startx);
    square.push_back(starty+yloops+1);
    legalSquares.push_back(square);
    yloops++;
  }
  int xloops = 0;
  for (int i=7; i>startx; i--)
  {
    if (board[starty][startx+xloops+1] != 0)
    {
      if(board[starty][startx+xloops+1]->getColor() != board[starty][startx]->getColor())
      {
        std::vector<int> square;
        square.push_back(startx+xloops+1);
        square.push_back(starty);
        legalSquares.push_back(square);
      }
      break;
    }
    std::vector<int> square;
    square.push_back(startx+xloops+1);
    square.push_back(starty);
    legalSquares.push_back(square);
    xloops++;
  }
  return legalSquares;
}
bool RookPiece::isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8])
{
  if (starty == endy)
  {
    int offset = (endx - startx > 0) ? 1 : -1;
    for (int i=startx+offset; i != endx; i+=offset)
    {
      if (board[starty][i] != 0)
      {
        if (board[starty][i]->getColor() != board[starty][startx]->getColor()) return true;
        else return false;
      }
    }
    return true;
  }
  else if (startx == endx)
  {
    int offset = (endy - starty > 0) ? 1 : -1;
    for (int i=starty+offset; i != endy; i+=offset)
    {
      if (board[i][startx] != 0)
      {
        if (board[i][startx]->getColor() != board[starty][startx]->getColor()) return true;
        else return false;
      }
    }
    return true;
  }
  return false;
}

KnightPiece::KnightPiece(char color)
{
  this->color = color;
}
char KnightPiece::getColor()
{
  return this->color;
}
char KnightPiece::getPiece()
{
  return 'N';

}
std::vector<std::vector<int>> KnightPiece::calcLegalSquares(int starty, int startx, GamePiece *board[8][8])
{
  std::vector<std::vector<int>> legalSquares;
  char currentColor = board[starty][startx]->getColor();
  if (starty > 0)
  {
    if (startx > 1)
    {
      GamePiece *to7 = board[starty-1][startx-2];
      if (to7 == 0 || to7->getColor() != currentColor)
      {
        std::vector<int> square7 = { startx-2, starty-1 };
        legalSquares.push_back(square7);
      }
    }
    if (startx < 6)
    {
      GamePiece *to8 = board[starty-1][startx+2];
      if (to8 == 0 || to8->getColor() != currentColor)
      {
        std::vector<int> square8 = { startx+2, starty-1 };
        legalSquares.push_back(square8);
      }
    }
    if (starty > 1)
    {
      if (startx > 0)
      {
        GamePiece *to5 = board[starty-2][startx-1];
        if (to5 == 0 || to5->getColor() != currentColor)
        {
          std::vector<int> square5 = { startx-1, starty-2 };
          legalSquares.push_back(square5);
        }
      }
      if (startx > 1)
      {
        GamePiece *to6 = board[starty-2][startx+1];
        if (to6 == 0 || to6->getColor() != currentColor)
        {
          std::vector<int> square6 = { startx+1, starty-2 };
          legalSquares.push_back(square6);
        }
      }
    }
  }
  if (starty < 7)
  {
    if (startx < 6)
    {
      GamePiece *to3 = board[starty+1][startx+2];
      if (to3 == 0 || to3->getColor() != currentColor)
      {
        std::vector<int> square3 = { startx+2, starty+1 };
        legalSquares.push_back(square3);
      }
    }
    if (startx > 1)
    {
      GamePiece *to4 = board[starty+1][startx-2];
      if (to4 == 0 || to4->getColor() != currentColor)
      {
        std::vector<int> square4 = { startx-2, starty+1 };
        legalSquares.push_back(square4);
      }
    }
    if (starty < 6)
    {
      if (startx < 7)
      {
        GamePiece *to1 = board[starty+2][startx+1];
        if (to1 == 0 || to1->getColor() != currentColor)
        {
          std::vector<int> square1 = { startx+1, starty+2 };
          legalSquares.push_back(square1);
        }
      }
      if (startx > 0)
      {
        GamePiece *to2 = board[starty+2][startx-1];
        if (to2 == 0 || to2->getColor() != currentColor)
        {
          std::vector<int> square2 = { startx-1, starty+2 };
          legalSquares.push_back(square2);
        }
      }
    }
  }
  return legalSquares;
}
bool KnightPiece::isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8])
{
  if (board[endy][endx] == 0)
  {
    if (starty == endy + 1 || starty == endy - 1)
    {
      if (startx == endx + 2 || startx == endx - 2)
      {
        return true;
      }
    }
    if (starty == endy + 2 || starty == endy - 2)
    {
      if (startx == endx + 1 || startx == endx - 1)
      {
        return true;
      }
    }
  }
  else if (board[endy][endx]->getColor() != board[starty][startx]->getColor())
  {
    if (starty == endy + 1 || starty == endy - 1)
    {
      if (startx == endx + 2 || startx == endx - 2)
      {
        return true;
      }
    }
    if (starty == endy + 2 || starty == endy - 2)
    {
      if (startx == endx + 1 || startx == endx - 1)
      {
        return true;
      }
    }
  }
  return false;
}

BishopPiece::BishopPiece(char color)
{
  this->color = color;
}
char BishopPiece::getColor()
{
  return this->color;
}
char BishopPiece::getPiece()
{
  return 'B';
}
std::vector<std::vector<int>> BishopPiece::calcLegalSquares(int starty, int startx, GamePiece *board[8][8])
{
  std::vector<std::vector<int>> legalSquares;
  // if (startx <= abs(starty - startx))
  // {
  //   if (startx < starty)
  //   {
  //     for (int i=0; i<startx; i++)
  //     {
  //       std::vector<int> square = { startx-i-1, starty-i-1 };
  //       legalSquares.push_back(square);
  //     }
  //   }  
  //   else if (starty <= abs(starty - startx))
  //   {
  //     for (int i=0; i<starty; i++)
  //     {
  //       std::vector<int> square = { startx-i-1, starty-i-1 };
  //       legalSquares.push_back(square);
  //     }
  //   }
  // }
  // else
  // {
  //   for (int i=0; i<abs(starty - startx); i++)
  //   {
  //     std::vector<int> square = { startx-i-1, starty-i-1 };
  //     legalSquares.push_back(square);
  //   }
  // }
  // for (int i=0; i<starty; i++)
  // {
  //   std::vector<int> square = { starty+i+1, startx+i+1 };
  //   legalSquares.push_back(square);
  // }
  return legalSquares;
}
bool BishopPiece::isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8])
{
  if (abs(endy-starty) == abs(endx-startx))
  {
    if (board[endy][endx] == 0) return true;
    else if (board[endy][endx]->getColor() != board[starty][startx]->getColor()) return true;
  }
  return false;
}

QueenPiece::QueenPiece(char color)
{
  this->color = color;
}
char QueenPiece::getColor()
{
  return this->color;
}
char QueenPiece::getPiece()
{
  return 'Q';
}
std::vector<std::vector<int>> QueenPiece::calcLegalSquares(int starty, int startx, GamePiece *board[8][8])
{
  std::vector<std::vector<int>> legalSquares;
  for (int i=0; i<starty; i++)
  {
    if (board[starty-i-1][startx] != 0)
    {
      if (board[starty-i-1][startx]->getColor() != board[starty][startx]->getColor())
      {
        std::vector<int> square;
        square.push_back(startx);
        square.push_back(starty-i-1);
        legalSquares.push_back(square);
      }
      break;
    }
    std::vector<int> square;
    square.push_back(startx);
    square.push_back(starty-i-1);
    legalSquares.push_back(square);
  }
  for (int i=0; i<startx; i++)
  {
    if (board[starty][startx-i-1] != 0)
    {
      if (board[starty][startx-i-1]->getColor() != board[starty][startx]->getColor())
      {
        std::vector<int> square;
        square.push_back(startx-i-1);
        square.push_back(starty);
        legalSquares.push_back(square);
      }
      break;
    }
    std::vector<int> square;
    square.push_back(startx-i-1);
    square.push_back(starty);
    legalSquares.push_back(square);
  }
  int yloops = 0;
  for (int i=7; i>starty; i--)
  {
    if (board[starty+yloops+1][startx] != 0)
    {
      if (board[starty+yloops+1][startx]->getColor() != board[starty][startx]->getColor())
      {
        std::vector<int> square;
        square.push_back(startx);
        square.push_back(starty+yloops+1);
        legalSquares.push_back(square);
      }
      break;
    }
    std::vector<int> square;
    square.push_back(startx);
    square.push_back(starty+yloops+1);
    legalSquares.push_back(square);
    yloops++;
  }
  int xloops = 0;
  for (int i=7; i>startx; i--)
  {
    if (board[starty][startx+xloops+1] != 0)
    {
      if(board[starty][startx+xloops+1]->getColor() != board[starty][startx]->getColor())
      {
        std::vector<int> square;
        square.push_back(startx+xloops+1);
        square.push_back(starty);
        legalSquares.push_back(square);
      }
      break;
    }
    std::vector<int> square;
    square.push_back(startx+xloops+1);
    square.push_back(starty);
    legalSquares.push_back(square);
    xloops++;
  }
  return legalSquares;
}
bool QueenPiece::isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8])
{
  if (starty == endy)
  {
    int offset = (endx - startx > 0) ? 1 : -1;
    for (int i=startx+offset; i != endx; i+=offset)
    {
      if (board[starty][i] != 0)
      {
        if (board[starty][i]->getColor() != board[starty][startx]->getColor()) return true;
        else return false;
      }
    }
    return true;
  }
  else if (startx == endx)
  {
    int offset = (endy - starty > 0) ? 1 : -1;
    for (int i=starty+offset; i != endy; i+=offset)
    {
      if (board[i][startx] != 0)
      {
        if (board[i][startx]->getColor() != board[starty][startx]->getColor()) return true;
        else return false;
      }
    }
    return true;
  }
  else if (abs(endy-starty) == abs(endx-startx)) return true;
  return false;
}

KingPiece::KingPiece(char color)
{
  this->color = color;
}
char KingPiece::getColor()
{
  return this->color;
}
char KingPiece::getPiece()
{
  return 'K';
}
std::vector<std::vector<int>> KingPiece::calcLegalSquares(int starty, int startx, GamePiece *board[8][8])
{
  std::vector<std::vector<int>> legalSquares;
  char currentColor = board[starty][startx]->getColor();
  if (starty > 0)
  {
    if (startx > 0)
    {
      GamePiece *to1 = board[starty-1][startx-1];
      if (to1 == 0 || to1->getColor() != currentColor)
      {
        std::vector<int> square1 = { startx-1, starty-1 };
        legalSquares.push_back(square1);
      }
    }
    if (startx < 7)
    {
      GamePiece *to2 = board[starty-1][startx+1];
      if (to2 == 0 || to2->getColor() != currentColor)
      {
        std::vector<int> square2 = { startx+1, starty-1 };
        legalSquares.push_back(square2);
      }
    }
    GamePiece *to3 = board[starty-1][startx];
    if (to3 == 0 || to3->getColor() != currentColor)
    {
      std::vector<int> square3 = { startx, starty-1 };
      legalSquares.push_back(square3);
    }
  }
  if (startx > 0)
  {
    if (starty < 7 && startx < 7)
    {
      GamePiece *to4 = board[starty][startx+1];
      if (to4 == 0 || to4->getColor() != currentColor)
      {
        std::vector<int> square4 = { startx+1, starty };
        legalSquares.push_back(square4);
      }
    }
    if (starty > 0)
    {
      GamePiece *to5 = board[starty][startx-1];
      if (to5 == 0 || to5->getColor() != currentColor)
      {
        std::vector<int> square5 = { startx-1, starty };
        legalSquares.push_back(square5);
      }
    }
  }
  if (starty < 7)
  {
    if (startx > 0)
    {
      GamePiece *to6 = board[starty+1][startx-1];
      if (to6 == 0 || to6->getColor() != currentColor)
      {
        std::vector<int> square6 = { startx-1, starty+1 };
        legalSquares.push_back(square6);
      }
    }
    if (startx < 7)
    {
      GamePiece *to7 = board[starty+1][startx+1];
      if (to7 == 0 || to7->getColor() != currentColor)
      {
        std::vector<int> square7 = { startx+1, starty+1 };
        legalSquares.push_back(square7);
      }
    }
    GamePiece *to8 = board[starty+1][startx];
    if (to8 == 0 || to8->getColor() != currentColor)
    {
      std::vector<int> square8 = { startx, starty+1 };
      legalSquares.push_back(square8);
    }
  }
  return legalSquares;
}
bool KingPiece::isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8])
{
  if (board[endy][endx] == 0)
  {
    int deltay = endy-starty;
    int deltax = endx-startx;
    if ((deltay >= -1 && deltay <= 1) && (deltax >= -1 && deltax <= 1)) return true;
  }
  else if (board[endy][endx]->getColor() != board[starty][startx]->getColor())
  {
    int deltay = endy-starty;
    int deltax = endx-startx;
    if ((deltay >= -1 && deltay <= 1) && (deltax >= -1 && deltax <= 1)) return true;
  }
  return false;
}
