#include "cengine.hpp"

bool end = false;

std::string tempstring;

std::ofstream debugout("debug.txt", std::ofstream::out | std::ofstream:: trunc);

void ticker(std::vector<void (*)()> funcs) {

    for (int e = 0; e < (int)funcs.size(); e++) { // check for null pointers

        if(funcs[e] == nullptr) {

            std::cerr << "\a Null pointer exception in the ticker function! AUGHHHHHH! CLOSING!\n";
            return;

        }

    }

    int tcount = 0; 

    while(!end && tcount < TIMEOUT) {

        if ((tcount % 3000) == 0) {

            tempstring = "5 minutes passed, # of minutes: " + (tcount / 600);

            log(tempstring);

        }

            for (int i = 0; i < (int)funcs.size(); i++)
            {
                funcs[i]();
            }

        //std::cout << "Tick\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(TICKRATE));
        tcount++;

    }



}

template <typename T> void log(T data) {

    if(debugout.is_open()) {

        debugout << data << std::flush;

    } else {

        debugout.open("debug.txt", std::ofstream::out | std::ofstream::trunc);

        if(debugout.is_open()) {

            log("Successfully reopened debugout");
            debugout << data << std::flush;

        } else {

            std::cerr << "\a Debug file not opening on log function!";
            return;

        }

    }

}

int main() {

    if(starter == nullptr) {
        std::cerr << "\a Null pointer exception in the starter function! AUGHHHHHH! CLOSING!\n";
        log("Null pointer exception in the starter function! AUGHHHHHH! CLOSING!\n");
        return 1;
    } 

    log("Test log to open file\n"); 

    starter();
    log("Starter func ran, starting tickthread.\n");

    std::thread tickthread(ticker, tickCalls);

    log("Tickthread init, waiting for join, will occur in ~1 hour");

    tickthread.join();

    return 0;
}