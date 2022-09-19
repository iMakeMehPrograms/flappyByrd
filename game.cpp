#include "byrd.hpp"

std::vector<void (*)()> tickCalls = {physcal, detect, addpipe, render}; // order is first -> last

void (*starter)() = start;

void(* inputer)() = inputLoop;

void start()
{
    
    startingAnimation();
    
}

void physcal() {



}

void detect() {



}

void addpipe() {

}