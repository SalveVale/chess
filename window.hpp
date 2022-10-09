#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>

#include <vector>

class Window
{
private:
  //window
  sf::RenderWindow *window;
  sf::VideoMode videoMode;
  sf::Event event;
  
  //mouse
  sf::Vector2f mousePosWindow;
  sf::Vector2i mousePosView;
  
  //grid
  sf::RectangleShape box;
  std::vector<sf::RectangleShape> grid0;
  std::vector<sf::RectangleShape> grid1;
  std::vector<sf::RectangleShape> grid2;
  std::vector<sf::RectangleShape> grid3;
  std::vector<sf::RectangleShape> grid4;
  std::vector<sf::RectangleShape> grid5;
  std::vector<sf::RectangleShape> grid6;
  std::vector<sf::RectangleShape> grid7;
  std::vector<std::vector<sf::RectangleShape>> grid;
  
  sf::Color colWhite = sf::Color(166, 159, 141, 255);
  sf::Color colWhiteHover = sf::Color(104, 131, 161, 255);
  sf::Color colBlack = sf::Color(110, 85, 39, 255);
  sf::Color colBlackHover = sf::Color(46, 45, 82, 255);
  sf::Color colWhiteRed = sf::Color(209, 140, 147, 255);
  sf::Color colBlackRed = sf::Color(77, 26, 31, 255);
  
  //sprites
  sf::Texture texture;
  
  sf::Sprite wPawn;
  sf::Sprite wRook;
  sf::Sprite wKnight;
  sf::Sprite wBishop;
  sf::Sprite wQueen;
  sf::Sprite wKing;
  sf::Sprite bPawn;
  sf::Sprite bRook;
  sf::Sprite bKnight;
  sf::Sprite bBishop;
  sf::Sprite bQueen;
  sf::Sprite bKing;
  
  std::vector<sf::Sprite> sprites;
  
  bool isOccupied;
  int selectedSprite;
  
  //logic
  int startx; int starty; int endx; int endy;
  char toMove;
  char winner;
  
  //functions
  void initVariables();
  void initWindow();
  void pollEvents();
  void drawGrid();
  void updateMousePos();
  void updateGrid();
  void drawSprites();
  void updateSprites();
  void toggleMove();

public:
  Window();
  ~Window();
  
  const bool running() const;
  void update();
  void render();
  char getWinner();
  bool checkmate();
};
