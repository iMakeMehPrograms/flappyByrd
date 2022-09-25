#include "byrd.hpp"

Screen output("output.txt");

std::mutex renlock; // mutex so no render weirdness

std::string ans = "";

int cheight = 5;

void inputLoop() {

    while(!end) {

        std::cin >> ans;
        std::cout << "                                              \r" << std::flush;
        if( (ans.compare("quit")) == 0) { // quit without control c
            end = true;
        }
        if( (instate.compare("game")) == 0) { // if cin ever returns, then it means that anything was entered, so jump
            jframe = 2;
        }

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(TICKRATE * 2)); // give ticker time to end first (two frames if the ticker is caught at a bad time)
}

std::vector<std::string> startingAnim = {

    "   __ _                         ____                _ \n"
    "  / _| |                       |  _ \\              | |\n"
    " | |_| | ____ ____  ____  _   _| |_) |_   _ _.__ __| |\n"
    " |  _| |/ _  |  _ \\|  _ \\| | | |  _ <| | | |  __/ _  |\n"
    " | | | | (_| | |_) | |_) | |_| | |_) | |_| | | | (_| |\n"
    " |_| |_|\\__,_| .__/| .__/ \\__, |____/ \\__, |_|  \\__,_|\n"
    "             |_|   |_|     __/ |       __/ |          \n"
    "                          |___/       |___/           \n"
    "-Loading- Good things come to those who wait -Loading-\n",

    "   __ _                         ____                _ \n"
    "  / _| |                       |  _ \\              | |\n"
    " | |_| | ____ ____  ____  _   _| |_) |_   _ _.__ __| |\n"
    " |  _| |/ _  |  _ \\|  _ \\| | | |  _ <| | | |  __/ _  |\n"
    " | | | | (_| | |_) | |_) | |_| | |_) | |_| | | | (_| |\n"
    " |_| |_|\\__,_| .__/| .__/ \\__, |____/ \\__, |_|  \\__,_|\n"
    "             | |   | |      _/ |        _/ |          \n"
    "             |_|   |_|     |__/        |__/           \n"
    "-Loading- Good things come to those who wait -Loading-\n"

};

std::vector<std::deque<std::string>> rengrid = {};

Animation sanim(startingAnim, fpsToTbf(1), output);

void shift() {

    // shift rengrid
    std::vector<std::string> pipe = addpipe(false);

    if( (getTick() % 5) == 0) {
        pipe = addpipe(true);
    }

    for(int i = 0; i < (int)rengrid.size(); i++) {
        rengrid[i].pop_front();
        rengrid[i].push_back(pipe[i]);
    }

    // update angrid
    for (int e = 0; e < (int)rengrid.size(); e++)
    {
        angrid.push_front(rengrid[e][PWIDTH + 1]);
    }

    rengrid[cheight][PWIDTH] = "#>"; // angrid before this because of how detect works
    rengrid[cheight][PWIDTH - 1] = "~~";

}

void render() {

    // for loop over rengrid

    std::string tempout;

    for(int i = 0; i < (int)rengrid.size(); i++) {
        for(int e = 0; e < (int)rengrid[i].size(); e++) {
            tempout.push_back(rengrid[i][e][0]); // uhh bad code ahhh
            tempout.push_back(rengrid[i][e][1]);
        }
        tempout.push_back('\n');
    }

}

void generate(bool start) {

    std::string temp = "~~";

    for(int i = 0; i < HEIGHT; i++) {

        if(start) {
        
        rengrid.push_back({});

        }

        for(int e = 0; e < WIDTH; e++) {

            if(e == PWIDTH) {
                if(i == SHEIGHT && start) {
                    rengrid[i].push_back("#>");
                } else if (i == cheight) {
                    rengrid[i].push_back("#>");
                }
                
            } 
            rengrid[i].push_back(temp);

        }
    }



}

void gameover()
{

    std::string etemp{
        "   _____                         ____                 _ \n"
        "  / ____|                       / __ \\               | |\n"
        " | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __| |\n"
        " | | |_ |/ _` | \'_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ \'__| |\n"
        " | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |  |_|\n"
        "  \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|  (_)\n"
        "-Better luck next time! Rerun the program to play again!-\n"
    };

    output.Display(etemp); 

}

void startingAnimation() 
{

    std::thread load([](int rt) { // lambda to wrap func

        renlock.lock(); // probably the only time this mutex is used

        sanim.Play(rt);

        renlock.unlock();

    }, 3);

    log("Game: Loading and generating vector-deque thing\n");

    generate(true); // generate while anim

    log("Game: Generated vector-deque, now waiting for anim join\n");

    load.join(); // wait for join after

    log("Game: Anim joined\n");

    output.Display(startingAnim[0]);

    std::string temp{
        "flappyByrd!\n"
        "First use of the cbyrd engine! (made by me)\n"
        "Tips: say \"quit\" (all lowercase and no spaces) to, well... quit\n"
        "Also don't ever say \"ignore\"\n, it will be well... ignored\n"
        "Enter anything into the terminal to start!\n"
    };

    output.Display(temp);

    ans = "ignore";

    while(ans.compare("ignore") != 0) {} // stall

    instate = "game";

    //return (duh)

}