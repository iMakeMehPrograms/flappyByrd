#include "byrd.hpp"

int yforce = 0;

int jframe = 3;

int lheight = SHEIGHT;

std::string air = "  ";

std::string instate = "start";

std::vector<void (*)()> tickCalls = {physcal, shift, detect, render}; // order is first -> last

void (*starter)() = start;

void(* inputer)() = inputLoop;

void(* ender)() = gameover;

std::deque<std::string> angrid = {};

void start()
{
    
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

}

std::vector<std::string> addpipe(bool attime) {

    std::vector<std::string> outvec;

    if(attime == true) {

    // no idea how I'll do this

    // well kind of an idea

    // rand for height, 3 tall opening, shift and detect will move and detect it. simple!

    // also modulus the tickcount with getTick so that it isn't a tunnel of pipes. maybe every 5 columns?

    // return before end of if statement
    }

    for(int i = 0; i < HEIGHT; i++) {
        outvec.push_back(air);
    } 

    return outvec;

}