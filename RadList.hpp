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
// function plays the next song in the queue. Making sure it's not the last in
// the list, otherwise it throws an exception..
void RadList::next(){
  if (nowPlaying_ != queue_.end())
    nowPlaying_++;
  else
    throw std::out_of_range("Error: Out of Range.");
}
// function plays the previous song in the queue. Making sure it's not the first 
// song in the list, otherwise it throws an exception.
void RadList::prev(){
  if (nowPlaying_ != queue_.begin())
    nowPlaying_--;
  else
    throw std::out_of_range("Error: Out of Range.");
}
// function returns the current song in the queue.
Song RadList::nowPlaying(){
  return *nowPlaying_;
}
// function adds a new song to the playlist, placing it at the end of the queue.
void RadList::addToQueue(const Song& song){
  queue_.push_back(song);
}
/* function adds a new song right after the song that is currently playing.
It checks to see if it's the last item in the queue, where it'll be added
at the end. If not, it adds the song into the queue and updates the iterator
accordingly. */
void RadList::playNext(const Song& song){
  if (nowPlaying_ == queue_.end())
    addToQueue(song);
  else {
    nowPlaying_++;
    queue_.insert(nowPlaying_, song);
    nowPlaying_--;
    nowPlaying_--;
  }
}
