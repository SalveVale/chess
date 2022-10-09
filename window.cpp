#include "window.hpp"
#include "piece.cpp"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include <iostream>

const int WINDOW_SIZE = 800;
GameBoard board;

Window::Window()
{
  this->initVariables();
  this->initWindow();
}

Window::~Window()
{
  delete this->window;
}

void Window::initVariables()
{
  // board.printBoard();
  this->winner = 'N';
  this->toMove = 'W';

  this->window = nullptr;
  //grid
  this->grid.push_back(this->grid0);
  this->grid.push_back(this->grid1);
  this->grid.push_back(this->grid2);
  this->grid.push_back(this->grid3);
  this->grid.push_back(this->grid4);
  this->grid.push_back(this->grid5);
  this->grid.push_back(this->grid6);
  this->grid.push_back(this->grid7);
  this->box.setSize(sf::Vector2f(WINDOW_SIZE/8.f, WINDOW_SIZE/8.f));
  for (int i=0; i<8; i++)
  {
    if (i%2 == 0)
    {
      for (int j=0; j<8; j++)
      {
        this->box.setPosition(sf::Vector2f((WINDOW_SIZE/8.f)*i, (WINDOW_SIZE/8.f)*j));
        if (j%2 == 0)
          this->box.setFillColor(sf::Color(this->colWhite));
        else
          this->box.setFillColor(sf::Color(this->colBlack));
    
        this->grid[i].push_back(this->box);
      }
    }
    else
    {
      for (int j=0; j<8; j++)
      {
        this->box.setPosition(sf::Vector2f((WINDOW_SIZE/8.f)*i, (WINDOW_SIZE/8.f)*j));
        if (j%2 == 0)
          this->box.setFillColor(sf::Color(colWhite));
        else
          this->box.setFillColor(sf::Color(colBlack));
    
        this->grid[i].push_back(this->box);
      }
    }
  }
  //sprites
  if (!this->texture.loadFromFile("pieces.png")) std::cout << "could not load texture file" << std::endl;
  //pawn
  this->wPawn.setTexture(this->texture);
  this->wPawn.setTextureRect(sf::IntRect(1667, 0, 333, 333));
  this->wPawn.scale(0.3, 0.3);
  for (int i=0; i<8; i++)
  {
    this->wPawn.setPosition(i*100.f, 600.f);
    this->sprites.push_back(this->wPawn);
  }
  this->bPawn.setTexture(this->texture);
  this->bPawn.setTextureRect(sf::IntRect(1667, 333, 333, 333));
  this->bPawn.scale(0.3, 0.3);
  for (int i=0; i<8; i++)
  {
    this->bPawn.setPosition(i*100.f, 100.f);
    this->sprites.push_back(this->bPawn);
  }
  //rook
  this->wRook.setTexture(this->texture);
  this->wRook.setTextureRect(sf::IntRect(1333, 0, 333, 333));
  this->wRook.scale(0.3, 0.3);
  this->wRook.setPosition(0.f, 700.f);
  this->sprites.push_back(this->wRook);
  this->wRook.setPosition(700.f, 700.f);
  this->sprites.push_back(this->wRook);
  this->bRook.setTexture(this->texture);
  this->bRook.setTextureRect(sf::IntRect(1333, 333, 333, 333));
  this->bRook.scale(0.3, 0.3);
  this->sprites.push_back(this->bRook);
  this->bRook.setPosition(700.f, 0.f);
  this->sprites.push_back(this->bRook);
  //knight
  this->wKnight.setTexture(this->texture);
  this->wKnight.setTextureRect(sf::IntRect(1000, 0, 333, 333));
  this->wKnight.scale(0.3, 0.3);
  this->wKnight.setPosition(100.f, 700.f);
  this->sprites.push_back(this->wKnight);
  this->wKnight.setPosition(600.f, 700.f);
  this->sprites.push_back(this->wKnight);
  this->bKnight.setTexture(this->texture);
  this->bKnight.setTextureRect(sf::IntRect(1000, 333, 333, 333));
  this->bKnight.scale(0.3, 0.3);
  this->bKnight.setPosition(100.f, 0.f);
  this->sprites.push_back(this->bKnight);
  this->bKnight.setPosition(600.f, 0.f);
  this->sprites.push_back(this->bKnight);
  //bishop
  this->wBishop.setTexture(this->texture);
  this->wBishop.setTextureRect(sf::IntRect(667, 0, 333, 333));
  this->wBishop.scale(0.3, 0.3);
  this->wBishop.setPosition(200.f, 700.f);
  this->sprites.push_back(this->wBishop);
  this->wBishop.setPosition(500.f, 700.f);
  this->sprites.push_back(this->wBishop);
  this->bBishop.setTexture(this->texture);
  this->bBishop.setTextureRect(sf::IntRect(667, 333, 333, 333));
  this->bBishop.scale(0.3, 0.3);
  this->bBishop.setPosition(200.f, 0.f);
  this->sprites.push_back(this->bBishop);
  this->bBishop.setPosition(500.f, 0.f);
  this->sprites.push_back(this->bBishop);
  //queen
  this->wQueen.setTexture(this->texture);
  this->wQueen.setTextureRect(sf::IntRect(333, 0, 333, 333));
  this->wQueen.scale(0.3, 0.3);
  this->wQueen.setPosition(300.f, 700.f);
  this->sprites.push_back(this->wQueen);
  this->bQueen.setTexture(this->texture);
  this->bQueen.setTextureRect(sf::IntRect(333, 333, 333, 333));
  this->bQueen.scale(0.3, 0.3);
  this->bQueen.setPosition(400.f, 0.f);
  this->sprites.push_back(this->bQueen);
  //king
  this->wKing.setTexture(this->texture);
  this->wKing.setTextureRect(sf::IntRect(0, 0, 333, 333));
  this->wKing.scale(0.3, 0.3);
  this->wKing.setPosition(400.f, 700.f);
  this->sprites.push_back(this->wKing);
  this->bKing.setTexture(this->texture);
  this->bKing.setTextureRect(sf::IntRect(0, 333, 333, 333));
  this->bKing.scale(0.3, 0.3);
  this->bKing.setPosition(300.f, 0.f);
  this->sprites.push_back(this->bKing);
  
  this->isOccupied = false;
}

void Window::initWindow()
{
  this->videoMode.width = WINDOW_SIZE;
  this->videoMode.height = WINDOW_SIZE;
  
  this->window = new sf::RenderWindow(this->videoMode, "Chess");
  this->window->setFramerateLimit(60);
}

const bool Window::running() const
{
  return this->window->isOpen();
}

void Window::drawGrid()
{
  for (int i=0; i<8; i++)
  {
    for (int j=0; j<8; j++)
    {
      this->window->draw(this->grid[i][j]);
    }
  }
}

void Window::drawSprites()
{
  for (int i=0; i<this->sprites.size(); i++)
  {
    this->window->draw(this->sprites[i]);
  }
}

void Window::pollEvents()
{
  while (this->window->pollEvent(this->event))
  {
    switch (this->event.type)
    {
      case sf::Event::Closed:
        this->window->close();
        break;
      case sf::Event::KeyPressed:
        if (this->event.key.code == sf::Keyboard::Escape) this->window->close();
        break;
      default:
        break;
    }
  }
}

void Window::updateMousePos()
{
  this->mousePosView = sf::Mouse::getPosition(*this->window);
  this->mousePosWindow = this->window->mapPixelToCoords(this->mousePosView);
}

void Window::updateGrid()
{
  if (!this->isOccupied)
  {
    for (int i=0; i<8; i++)
    {
      if (i%2 == 0)
      {
        for (int j=0; j<8; j++)
        {
          if (this->grid[i][j].getGlobalBounds().contains(this->mousePosWindow))
          {
            if (j%2 == 0) this->grid[i][j].setFillColor(this->colWhiteHover);
            else this->grid[i][j].setFillColor(this->colBlackHover);
          }
          else
          {
            if (j%2 == 0) this->grid[i][j].setFillColor(this->colWhite);
            else this->grid[i][j].setFillColor(this->colBlack);
          }
        }
      }
      else
      {
        for (int j=0; j<8; j++)
        {
          if (this->grid[i][j].getGlobalBounds().contains(this->mousePosWindow))
          {
            if (j%2 == 0) this->grid[i][j].setFillColor(this->colBlackHover);
            else this->grid[i][j].setFillColor(this->colWhiteHover);
          }
          else
          {
            if (j%2 == 0) this->grid[i][j].setFillColor(this->colBlack);
            else this->grid[i][j].setFillColor(this->colWhite);
          }
        }
      }
    }
  }
}

void Window::updateSprites()
{
  if (!this->isOccupied)
  {
    for (int i=0; i<this->sprites.size(); i++)
    {
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      {
        if (!this->isOccupied && this->sprites[i].getGlobalBounds().contains(this->mousePosWindow))
        {
          this->startx = this->mousePosWindow.x;
          this->starty = this->mousePosWindow.y;
          int xRemainder = this->startx%100;
          int yRemainder = this->starty%100;
          this->startx -= xRemainder;
          this->starty -= yRemainder;
          
          std::vector<std::vector<int>> legalSquares = board.calcLegalSquares(this->starty/100, this->startx/100);
          for (int i=0; i<legalSquares.size(); i++)
            if (this->grid[legalSquares[i][0]][legalSquares[i][1]].getFillColor() == this->colWhite)
              this->grid[legalSquares[i][0]][legalSquares[i][1]].setFillColor(this->colWhiteRed);
            else
              this->grid[legalSquares[i][0]][legalSquares[i][1]].setFillColor(this->colBlackRed);

          this->isOccupied = true;
          this->selectedSprite = i;
        }
      }
    }
  }
  else
  {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
      this->sprites[this->selectedSprite].setPosition(this->mousePosWindow.x-50, this->mousePosWindow.y-50);
    else
    {
        this->endx = this->mousePosWindow.x;
        this->endy = this->mousePosWindow.y;
        int xRemainder = this->endx%100;
        int yRemainder = this->endy%100;
        this->endx -= xRemainder;
        this->endy -= yRemainder;
      if (board.isLegalMove(this->starty/100, this->startx/100, this->endy/100, this->endx/100) && this->toMove == board.getColor(this->starty/100, this->startx/100))
      {
        if (this->startx == this->endx && this->starty == this->endy)
          this->sprites[this->selectedSprite].setPosition(this->endx, this->endy);
        else
        {
          this->toggleMove();
          for (int i=0; i<this->sprites.size(); i++)
          {
            if (this->sprites[i].getPosition().x == this->endx && this->sprites[i].getPosition().y == this->endy) this->sprites[i].setPosition(sf::Vector2f(1000.f, 1000.f));
          }
          this->sprites[this->selectedSprite].setPosition(this->endx, this->endy);
          switch (board.updateBoard(this->startx/100, this->starty/100, this->endx/100, this->endy/100))
          {
            case 'N':
              break;
            case 'W':
              this->winner = 'W';
              break;
            case 'B':
              this->winner = 'B';
              break;
            default:
              break;
          }
          // board.updateBoard(this->startx/100, this->starty/100, this->endx/100, this->endy/100);
          // board.printBoard();
        }
      }
      else
      {
        this->sprites[this->selectedSprite].setPosition(this->startx, this->starty);
      }
      this->isOccupied = false;
    }
  }
}

void Window::toggleMove()
{
  if (this->toMove == 'W') this->toMove = 'B';
  else this->toMove = 'W';
}

char Window::getWinner()
{
  return this->winner;
}

bool Window::checkmate()
{
  if (this->winner == 'N') return false;
  else return true;
}

void Window::update()
{
  this->pollEvents();
  this->updateMousePos();
  this->updateGrid();
  this->updateSprites();
}

void Window::render()
{
  this->window->clear(sf::Color::White);
  this->drawGrid();
  this->drawSprites();
  this->window->display();
}