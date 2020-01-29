#include <algorithm>
#include <numeric>
#include <random>

#include "PerlinNoise.h"

using namespace std;

PerlinNoise::PerlinNoise(std::uint32_t seed) :
  m_frequency(0.1f)
{
  iota(p.begin(), p.end(), 0);
  shuffle(p.begin(), p.begin() + 256, default_random_engine(seed));
  copy(p.begin(), p.begin() + 256, p.begin() + 256);
}

float PerlinNoise::GetValue(float x, float y, float z)
{
  x *= m_frequency;
  y *= m_frequency;
  z *= m_frequency;

  const int32_t X = static_cast<int32_t>(floor(x)) & 0xFF;
  const int32_t Y = static_cast<int32_t>(floor(y)) & 0xFF;
  const int32_t Z = static_cast<int32_t>(floor(z)) & 0xFF;

  x -= floor(x);
  y -= floor(y);
  z -= floor(z);

  float u = Fade(x);
  float v = Fade(y);
  float w = Fade(z);

  uint32_t A = p[X] + Y;
  uint32_t AA = p[A] + Z;
  uint32_t AB = p[A + 1] + Z;
  uint32_t B = p[X + 1] + Y;
  uint32_t BA = p[B] + Z;
  uint32_t BB = p[B + 1] + Z;

  float res = Lerp(w, Lerp(v, Lerp(u, Grad(p[AA], x, y, z), Grad(p[BA], x - 1, y, z)), Lerp(u, Grad(p[AB], x, y - 1, z), Grad(p[BB], x - 1, y - 1, z))), Lerp(v, Lerp(u, Grad(p[AA + 1], x, y, z - 1), Grad(p[BA + 1], x - 1, y, z - 1)), Lerp(u, Grad(p[AB + 1], x, y - 1, z - 1), Grad(p[BB + 1], x - 1, y - 1, z - 1))));
  return (res + 1.0f) * 0.5f;
}