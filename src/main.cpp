#include <SFML/Graphics.hpp>
#include <ostream>
#include <sstream>
#include <xmemory>
#include "lib.hpp"
 
using namespace std;
using namespace sf;

int markup1 = 40; 
int horizontalLine1 = 32;
int verticalLine1 = 16;

int main()
{
    RenderWindow window(VideoMode(markup1* horizontalLine1, markup1 * verticalLine1), "Ghost Game");
    gameRunning(window);
    return 0; 
} 
