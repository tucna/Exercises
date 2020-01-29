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
  static double Fade(double t) noexcept { return t * t * t * (t * (t * 6 - 15) + 10); }
  static double Lerp(double t, double a, double b) noexcept { return a + t * (b - a); }
  static double Grad(std::uint8_t hash, double x, double y, double z) noexcept
  {
    const std::uint8_t h = hash & 15;
    // Convert lower 4 bits of hash into 12 gradient directions
    const double u = h < 8 ? x : y;
    const double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
  }

  std::array<uint8_t, 512> p;

  float m_frequency;
};

