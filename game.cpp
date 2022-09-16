#include "byrd.hpp"

std::vector<void (*)()> tickCalls = {render};

void(* starter)() = start;

void start() {

}
