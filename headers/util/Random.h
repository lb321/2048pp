#ifndef RANDOM_H
#define RANDOM_H

#pragma once

class Random {
  public:
    Random();
    ~Random();
    template <typename T>
    T between(const T& min, const T& max) const {
        return GetRandomValue(min, max);
    }

  private:
};

#endif