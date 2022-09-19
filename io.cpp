#include "byrd.hpp"

Screen output("output.txt");

std::string ans = "";

void inputLoop() {

    while(!end) {

        std::cin >> ans;
        std::cout << "                                              \r" << std::flush;
        if( (ans.compare("quit")) == 0) {
            end = true;
        }

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(TICKRATE)); // give ticker time to end first
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

void render() {

    // figure it out


}

void generate() {

    std::string temp = "~~";

    for(int i = 0; i < HEIGHT; i++) {
        
        rengrid.push_back({});

        for(int e = 0; e < WIDTH; e++) {

            if(i == SHEIGHT && e == PWIDTH) {
                rengrid[i].push_back("#>");
            } 
            rengrid[i].push_back(temp);
            std::this_thread::sleep_for(std::chrono::milliseconds(50));

        }
    }

}

void startingAnimation() 
{

    sanim.Play(3);

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

    int scount = 0;

    while(ans.compare("ignore") != 0 && scount < 10) {
        scount++;
    }

    generate();

    //return (duh)

}