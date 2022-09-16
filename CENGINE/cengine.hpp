#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

extern std::vector<void (*)()> tickCalls;

extern void (* starter)();