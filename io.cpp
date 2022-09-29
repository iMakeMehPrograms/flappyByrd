#include "byrd.hpp"

Screen output("output.txt");

std::mutex renlock; // mutex so no render weirdness

char ans = 'i';

int cheight = SHEIGHT;

void inputLoop() {

    while(!end) {

        ans = getchar();
        std::cout << "                                              \r" << std::flush;
        if(ans == 'q') { // quit without control c
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

    if( (getTick() % 11) == 0) {
        pipe = addpipe(true);
    }

    for(int i = 0; i < (int)rengrid.size(); i++) {
        rengrid[i].pop_front();
        rengrid[i].push_back(pipe[i]);
    }

    // update angrid
    angrid = rengrid[cheight][PWIDTH + 1];
        
    
 
    // angrid before this because of how detect works
    rengrid[cheight][PWIDTH] = "#>";
    rengrid[lheight][PWIDTH - 1] = "--"; // trail

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
    for(int v = 0; v < WIDTH; v++) {
        tempout.push_back('=');
        tempout.push_back('=');
    }

    output.Display(tempout);

}

void generate() {

    std::string temp = air;

    for(int i = 0; i < HEIGHT; i++) {

        rengrid.push_back({});

        for(int e = 0; e < WIDTH; e++) {

            if (e == PWIDTH && i == SHEIGHT) {

                rengrid[i].push_back("#>");

            } else {
                
                rengrid[i].push_back(temp);
                
            }
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

    generate(); // generate while anim

    log("Game: Generated vector-deque, now waiting for anim join\n");

    load.join(); // wait for join after

    log("Game: Anim joined\n");

    output.Display(startingAnim[0]);

    std::string temp{
        "flappyByrd!\n"
        "First use of the cbyrd engine! (made by me!)\n"
        "Tips: say \'q\' (all lowercase and no spaces) to, well... quit\n"
        "Also don't ever say \'i\', it will be ignored\n"
        "Enter anything into the terminal or press return to jump!\n"
        "Wait a little for the game to start!\n"
        "Seconds until start = 6\n"
    };

    output.Display(temp);

    ans = 'i';

    std::this_thread::sleep_for(std::chrono::seconds(1));
    output.DisplayAdd("Seconds until start = 5\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    output.DisplayAdd("Seconds until start = 4\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    output.DisplayAdd("Seconds until start = 3\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    output.DisplayAdd("Seconds until start = 2\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    output.DisplayAdd("Seconds until start = 1\n");
    std::this_thread::sleep_for(std::chrono::seconds(1));
    output.DisplayAdd("Starting!\n");

    instate = "game";

    cheight = 0;

    //return (duh)

}