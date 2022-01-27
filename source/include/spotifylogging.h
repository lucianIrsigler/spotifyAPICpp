#pragma once
#include <string>
#include <fstream>

static void spotifyLogToFile(std::string message) {
    char filename[] = "SPOTIFYLOG.txt";
    std::ofstream file;
    file.open(filename, std::fstream::app);
    file << "\n" << message << "\n";
    file.close();
}
