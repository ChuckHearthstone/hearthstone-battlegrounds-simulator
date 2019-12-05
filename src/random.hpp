#pragma once

#include <cstdint>
#include <utility>

// -----------------------------------------------------------------------------
// Random number generator
// -----------------------------------------------------------------------------

class RNG {
private:
  uint64_t s[2] = {1234567891234567890u,9876543210987654321u};
public:
  RNG() {}
  RNG(uint64_t s[2]) : s{s[0],s[1]} {}

  uint64_t next();
  void jump();
  void long_jump();

  inline uint64_t random(uint64_t range) {
    // TODO: make sure range evenly divides 2^64
    return next() % range;
  }

  inline int random(int range) {
    return (int)random((uint64_t)range);
  }

  inline RNG next_rng() {
    RNG out = {s};
    jump();
    return out;
  }

  template <typename T>
  void shuffle(T* data, int n) {
    for (int i=1; i<n; ++i) {
      int j = random(i+1);
      if (i != j) std::swap(data[i], data[j]);
    }
  }
};

extern RNG global_rng;
