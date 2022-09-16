#include "cengine.hpp"
#define TICKRATE 100
#define TIMEOUT 36000

bool end = false;

void ticker(std::vector<void (*)()> funcs) {

    for (int e = 0; e < (int)funcs.size(); e++) { // check for null pointers

        if(funcs[e] == nullptr) {

            std::cerr << "Null pointer exception in the ticker function! AUGHHHHHH! CLOSING!\n";
            return;

        }

    }

    int tcount = 0; 

    while(!end && tcount < TIMEOUT) {

        for (int i = 0; i < (int)funcs.size(); i++)
        {

            funcs[i]();
        }

        //std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(TICKRATE));
        tcount++;

    }



}

int main() {

    if(starter == nullptr) {
        std::cerr << "Null pointer exception in the starter function! AUGHHHHHH! CLOSING!\n";
        return 1;
    } 

    starter();

    std::thread tick(ticker, tickCalls);

    tick.join();

    return 0;
}