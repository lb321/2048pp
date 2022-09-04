#ifndef __TEST_TILE_H__
#define __TEST_TILE_H__

class Tile {

public:
  Tile(int value): _value {value} {}
  Tile(): Tile(nullptr, nullptr, nullptr, nullptr){}
  Tile(const Tile *left, const Tile *right, const Tile *up, const Tile *down);
  ~Tile();
  Tile(const Tile &other) = delete;
  Tile(Tile &&) = delete;
  Tile &operator=(const Tile &other) = delete;

  const int& getValue() const;
  void setValue(const int &value);

  void setLeft(const Tile* tile);
  void setRight(const Tile* tile);
  void setUp(const Tile* tile);
  void setDown(const Tile* tile);

private:
  int _value;
  const Tile *_left;
  const Tile *_right;
  const Tile *_up;
  const Tile *_down;
};

#endif // __TEST_TILE_H__