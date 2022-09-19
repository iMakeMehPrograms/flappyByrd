#include "cengine.hpp"

bool end = false;

int tickcount = 0;

std::string tempstring;

std::ofstream debugout("debug.txt", std::ofstream::out | std::ofstream:: trunc);

void ticker(std::vector<void (*)()> funcs) {

    for (int e = 0; e < (int)funcs.size(); e++) { // check for null pointers

        if(funcs[e] == nullptr) {

            std::cerr << "\a Null pointer exception in the ticker function! AUGHHHHHH! CLOSING!\n";
            return;

        }

    }

    tickcount = 0; // reset to 0

    while(!end && tickcount < TIMEOUT) {

        if ((tcount % 3000) == 0 && tcount != 0) {

            log("5 minutes have passed, # of minutes: ");
            log(tcount / 600);
            log("\n");

        }

            for (int i = 0; i < (int)funcs.size(); i++)
            {
                funcs[i]();
            }

        //std::cout << "Tick\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(TICKRATE));
        tcount++;

    }

    if(!end) {
        end = true;
    }

}

int getTick()
{ // use instead of direct acess so timeout check doesn't get fucked up
    return tickcount;
}

template <typename T> void log(T data) {

    if(debugout.is_open()) {

        debugout << data << std::flush;

    } else {

        debugout.open("debug.txt", std::ofstream::out | std::ofstream::trunc);

        if(debugout.is_open()) {

            debugout << "Successfully reopened debugout\n" << std::flush;
            debugout << data << std::flush;

        } else {

            std::cerr << "\a Debug file not opening on log function!";
            return;

        }

    }

}

int main()
{

    if(starter == nullptr) {
        std::cerr << "\a Null pointer exception in the starter function! AUGHHHHHH! CLOSING!\n";
        log("Null pointer exception in the starter function! AUGHHHHHH! CLOSING!\n");
        return 1;
    }

    if(inputer == nullptr)
    {
        std::cerr << "\a Null pointer exception in the inputer function! AUGHHHHHH! CLOSING!\n";
        log("Null pointer exception in the inputer function! AUGHHHHHH! CLOSING!\n");
        return 1;
    }

    if(ender == nullptr) {
        std::cerr << "\a Null pointer exception in the ender function! AUGHHHHHH! CLOSING!\n";
        log("Null pointer exception in the ender function! AUGHHHHHH! CLOSING!\n");
        return 1;
    }

    log("Test log to open file\n"); 

    starter();
    log("Starter func ran, starting tickthread.\n");

    std::thread tickthread(ticker, tickCalls);

    log("Tickthread init, waiting for join, will occur in ~1 hour if not ended\n");

    std::thread iothread(inputer);

    log("Iothread init, waiting for join, will occur when tickthread joins\n");

    tickthread.join();

    log("Tickthread joined\n");

    iothread.join();

    log("Iothread joined\n");

    log("Running ender function...\n");

    ender();

    log("Ender function done, closing procces aka quiting.");

    return 0;
}