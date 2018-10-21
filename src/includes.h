#ifndef INCLUDES_H
#define INCLUDES_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <random>
#include <chrono>
#include <time.h>

#include <QtWidgets>

#if (defined (_WIN32) || defined (_WIN64))
    #include <windows.h>
#elif (defined (LINUX) || defined (__linux__))
    #include <unistd.h>
    #define RESET "\033[0m"
    #define RED "\033[91m"
#endif

int randInt(int minvalue, int maxvalue);
int getLines(std::fstream& file);

typedef struct Victim Victim;
struct Victim
{
    std::string fname;
    std::string lname;
};

#endif // INCLUDES_H
