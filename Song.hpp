#pragma once

#include <string>

class Song {
private:
    std::string name_;
    std::string artist_;
    std::string album_;
    unsigned int duration_;
    bool explicit_lyrics_;

public:
    Song(std::string, std::string, std::string, unsigned int, bool);

    std::string name();
    std::string artist();
    std::string album();
    unsigned int minutes();
    unsigned int seconds();
    bool explicit_lyrics();
};
