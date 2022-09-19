#include "byrd.hpp"

int yforce = 0;

int jframe = 0;

std::string instate = "start";

std::vector<void (*)()> tickCalls = {physcal, detect, addpipe, render}; // order is first -> last

void (*starter)() = start;

void(* inputer)() = inputLoop;

void(* ender)() = gameover;

std::vector<char> angrid = {};

void start()
{
    
    startingAnimation(); // do that
    
}

void physcal() {

    if(jframe > 0) { // if jumping

        yforce = 1; // add one to yforce

        jframe - 1; // minus one to jframe

    } else { // else pull down

        yforce--;

    }
    cheight += yforce; // manip height (width is constant)

}

void detect() {

    if (cheight <= 0) // check if hit the floor
    {
        // game over
    }

    // detect height vs pipe positions

}

void addpipe() {

    // no idea how I'll do this

    // well kind of an idea

    // rand for height, 3 tall opening, shift and detect will move and detect it. simple!

    // also modulus the tickcount with getTick so that it isn't a tunnel of pipes. maybe every 5 columns?

}