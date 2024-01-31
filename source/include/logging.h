#pragma once
#include <string>
#include <fstream>

#define loggingFile "SPOTIFYLOG.txt";

/*
    Logs text to fix
*/
static void spotifyLogToFile(std::string message) {
    char filename[] = loggingFile;
    std::ofstream file;
    file.open(filename, std::fstream::app);
    file << message << "\n";
    file.close();
}