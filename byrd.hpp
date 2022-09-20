#include <deque>
#include <mutex>
#include "CENGINE/cengine.hpp"
#include "TANIMLIB/canim.hpp"

#define WIDTH 30

#define HEIGHT 10

#define PWIDTH 6

#define SHEIGHT 5

extern void start();

extern void render();

extern Screen output;

void startingAnimation();

void inputLoop();

extern std::string ans;

extern std::vector<std::deque<std::string>> rengrid;

extern std::deque<char> angrid;

extern int cheight;

void gameover();

extern int jframe;

extern std::string instate;

void physcal();

void detect();

void addpipe();

void shift();