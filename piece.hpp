#include <vector>

class GamePiece
{
private:
  char pieceColor;
public:
  GamePiece();
  ~GamePiece();
  virtual char getPiece() = 0;
  virtual char getColor() = 0;
  virtual std::vector<std::vector<int>> calcLegalSquares(int starty, int startx, GamePiece *board[8][8]) = 0;
  virtual bool isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8]) = 0;
};


class PawnPiece : public GamePiece
{
private:
  char color;
  virtual char getColor();
  virtual char getPiece();
  virtual std::vector<std::vector<int>> calcLegalSquares(int starty, int startx, GamePiece *board[8][8]);
  virtual bool isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8]);
public:
  PawnPiece(char color);
  ~PawnPiece();
};

class RookPiece : public GamePiece
{
private:
  virtual char getPiece();
  virtual char getColor();
  char color;
  virtual std::vector<std::vector<int>> calcLegalSquares(int starty, int startx, GamePiece *board[8][8]);
  virtual bool isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8]);
public:
  RookPiece(char color);
  ~RookPiece();
};

class KnightPiece : public GamePiece
{
private:
  virtual char getPiece();
  virtual char getColor();
  char color;
  virtual std::vector<std::vector<int>> calcLegalSquares(int starty, int startx, GamePiece *board[8][8]);
  virtual bool isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8]);
public:
  KnightPiece(char color);
  ~KnightPiece();
};

class BishopPiece : public GamePiece
{
private:
  virtual char getPiece();
  virtual char getColor();
  char color;
  virtual std::vector<std::vector<int>> calcLegalSquares(int starty, int startx, GamePiece *board[8][8]);
  virtual bool isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8]);
public:
  BishopPiece(char color);
  ~BishopPiece();
};

class QueenPiece : public GamePiece
{
private:
  virtual char getPiece();
  virtual char getColor();
  char color;
  virtual std::vector<std::vector<int>> calcLegalSquares(int starty, int startx, GamePiece *board[8][8]);
  virtual bool isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8]);
public:
  QueenPiece(char color);
  ~QueenPiece();
};

class KingPiece : public GamePiece
{
private:
  virtual char getPiece();
  virtual char getColor();
  char color;
  virtual std::vector<std::vector<int>> calcLegalSquares(int starty, int startx, GamePiece *board[8][8]);
  virtual bool isLegalMove(int starty, int startx, int endy, int endx, GamePiece *board[8][8]);
public:
  KingPiece(char color);
  ~KingPiece();
};

class GameBoard
{
private:
  void initBoard();
  GamePiece *board[8][8];
public:
  GameBoard();
  ~GameBoard();
  void printBoard();
  char updateBoard(int startx, int starty, int endx, int endy);
  std::vector<std::vector<int>> calcLegalSquares(int starty, int startx);
  bool isLegalMove(int starty, int startx, int endy, int endx);
  char getColor(int y, int x);
};
