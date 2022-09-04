#ifndef __TEST_TILE_H__
#define __TEST_TILE_H__

class Tile {

public:
  Tile(): Tile(0) {}
  Tile(int value): Tile(value, -1) {}
  Tile(int value, int index): _value {value} , _index {index} { }
  ~Tile();
  Tile(const Tile &other) = delete;
  Tile(Tile &&) = delete;
  Tile &operator=(const Tile &other) = delete;

  const int& getValue() const;
  void setValue(const int &value);

  const int& getIndex() const;
  void setIndex(const int& i);

private:
  int _value;
  int _index;
};

#endif // __TEST_TILE_H__