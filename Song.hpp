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
Song::Song(std::string name, std::string artist, std::string album, unsigned int duration, bool explicit_lyrics) {
  name_ = name;
  artist_ = artist;
  album_ = album;
  duration_ = duration;
  explicit_lyrics_ = explicit_lyrics;
}
std::string Song::name() { return name_; }
std::string Song::artist() { return artist_; }
std::string Song::album() { return album_; }
// function returns only the minutes portion.
unsigned int Song::minutes() {
  int minutes = duration_ / 60;
  return minutes;
}
// funtion return only the seconds portion.
unsigned int Song::seconds() {
  int seconds = duration_ % 60;
  return seconds;
}
bool Song::explicit_lyrics() { return explicit_lyrics_; }
