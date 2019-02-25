#pragma once

#include <fstream>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>

#include "Song.hpp"

class RadList {
private:
    std::list<Song> queue_;
    std::list<Song>::iterator nowPlaying_;
public:
    void loadPlaylist(const std::string&);
    void next();
    void prev();
    Song nowPlaying();
    void addToQueue(const Song&);
    void playNext(const Song&);
};

void RadList::loadPlaylist(const std::string& filename) {
    std::ifstream playlist(filename);

    if (playlist.is_open()) {
        std::string name, artist, album, duration, explicit_lyrics, toss;

        // Read in everything from comma seperated values file
        while (std::getline(playlist, name, ',')) {
            std::getline(playlist, toss, ' ');           // ignore leading space
            std::getline(playlist, artist, ',');
            std::getline(playlist, toss, ' ');           // ignore leading space
            std::getline(playlist, album, ',');
            std::getline(playlist, toss, ' ');           // ignore leading space
            std::getline(playlist, duration, ',');
            std::getline(playlist, toss, ' ');           // ignore leading space
            std::getline(playlist, explicit_lyrics);

            // Construct Song and add to queue
            queue_.push_back(Song(name, artist, album, stoi(duration), explicit_lyrics == "true"));
        }

        playlist.close();
        nowPlaying_ = queue_.begin();
    } else {
        throw std::invalid_argument("Could not open " + filename);
    }
}
void RadList::next(){
  nowPlaying_++;
}
void RadList::prev(){
  nowPlaying_--;
}
Song RadList::nowPlaying(){
  return *nowPlaying_;
}
void RadList::addToQueue(const Song& song){
  queue_.push_back(song);
}
void RadList::playNext(const Song& song){
  queue_.push_front(song);
}
