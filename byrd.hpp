#include <deque>
#include <mutex>
#include "CENGINE/cengine.hpp"
#include "TANIMLIB/canim.hpp"

#define WIDTH 100

#define HEIGHT 10

#define PWIDTH 6

#define SHEIGHT 4

extern void start();

extern void render();

extern Screen output;

void startingAnimation();

void inputLoop();

extern char ans;

extern std::vector<std::deque<std::string>> rengrid;

extern std::deque<std::string> angrid;

extern int cheight;

extern int lheight;

extern int cindex;

void gameover();

extern int jframe;

extern std::string instate;

void physcal();

void detect();

std::vector<std::string> addpipe(bool attime);

void shift();

extern std::string air;