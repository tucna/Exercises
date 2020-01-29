#pragma once

#include <array>
#include <cstdint>

class PerlinNoise
{
public:
  PerlinNoise(std::uint32_t seed);
  ~PerlinNoise() {}

  void SetFrequency(float f) { m_frequency = f; }

  float GetValue(float x, float y, float z = 0);

private:
  static float Fade(float t) noexcept { return t * t * t * (t * (t * 6 - 15) + 10); }
  static float Lerp(float t, float a, float b) noexcept { return a + t * (b - a); }
  static float Grad(std::uint8_t hash, float x, float y, float z) noexcept
  {
    const std::uint8_t h = hash & 15;

    const float u = h < 8 ? x : y;
    const float v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
  }

  std::array<uint8_t, 512> p;

  float m_frequency;
};

