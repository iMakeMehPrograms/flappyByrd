#include "byrd.hpp"

int yforce = 0;

int jframe = 3;

int lheight = SHEIGHT;

int opening = 3;

std::string air = "  ";

std::string block = "[]";

std::string instate = "start";

std::vector<void (*)()> tickCalls = {physcal, shift, detect, render}; // order is first -> last

void (*starter)() = start;

void(* inputer)() = inputLoop;

void(* ender)() = gameover;

int randSet[35] = {4,7,6,3,6,2,5,3,5,4,2,5,2,4,7,4,5,7,2,3,2,4,1,5,4,6,5,4,2,4,6,4,3,3};

int incr = 0;

std::deque<std::string> angrid = {};

void start()
{
    incr = rand();
    startingAnimation(); // do that
    
}

int intClamp(int inp, int min, int max) {
    if(inp <= min) {
        return min;
    } else if(inp >= max) {
        return max;
    } else {
        return inp;
    }
}

void physcal() {

    lheight = cheight; // for clearing after the player

    if(jframe > 0) { // if jumping

        yforce = 1; // add one to yforce

        jframe--; // minus one to jframe

    } else { // else pull down

        yforce--;

    }
    
    intClamp(yforce, 0, 1);

    cheight -= yforce; // manip height (width is constant) -= bc cheight needs to be reversed
    cheight = intClamp(cheight, 0, HEIGHT - 1); // so no cheight = -1 issues
}

void detect() {

    if (cheight >= 9) // check if hit the floor
    {
        end = true;
        return;
    }

    // detect height vs pipe positions
    for(int i = 0; i < (int)angrid.size(); i++) {
        if(i == cheight) {
            if(angrid[i].compare("[]") == 0) {
                end = true;
            }
        }
    }

}

std::vector<std::string> addpipe(bool attime) {

    std::vector<std::string> outvec;

    int pheight = 1;

    if(attime == true) {

        pheight = randSet[(getTick() + incr) % 35];

        for (int e = 0; e < HEIGHT; e++)
        {
            if(e < pheight) {
                outvec.push_back(block);
            } else if(e > pheight + opening) {
                outvec.push_back(block);
            } else {
                outvec.push_back(air);
            }
            
        }

        return outvec;

    }

    for (int i = 0; i < HEIGHT; i++)
    {
        outvec.push_back(air);
    }

    return outvec;

}