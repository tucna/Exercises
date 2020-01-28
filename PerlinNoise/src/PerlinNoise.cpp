#include <algorithm>
#include <numeric>
#include <random>

#include "PerlinNoise.h"

using namespace std;

PerlinNoise::PerlinNoise(std::uint32_t seed)
{
  iota(p.begin(), p.end(), 0);
  shuffle(p.begin(), p.begin() + 256, default_random_engine(seed));
  copy(p.begin(), p.begin() + 256, p.begin() + 256);
}

float PerlinNoise::GetValue(float x, float y, float z)
{
  const int32_t X = static_cast<int32_t>(floor(x)) & 255; // TUCNA 0xFF
  const int32_t Y = static_cast<int32_t>(floor(y)) & 255;
  const int32_t Z = static_cast<int32_t>(floor(z)) & 255;

  x -= floor(x);
  y -= floor(y);
  z -= floor(z);

  double u = Fade(x);
  double v = Fade(y);
  double w = Fade(z);

  uint32_t A  = p[X] + Y;
  uint32_t AA = p[A] + Z;
  uint32_t AB = p[A + 1] + Z;
  uint32_t B  = p[X + 1] + Y;
  uint32_t BA = p[B] + Z;
  uint32_t BB = p[B + 1] + Z;

  double res = Lerp(w, Lerp(v, Lerp(u, Grad(p[AA], x, y, z), Grad(p[BA], x - 1, y, z)), Lerp(u, Grad(p[AB], x, y - 1, z), Grad(p[BB], x - 1, y - 1, z))), Lerp(v, Lerp(u, Grad(p[AA + 1], x, y, z - 1), Grad(p[BA + 1], x - 1, y, z - 1)), Lerp(u, Grad(p[AB + 1], x, y - 1, z - 1), Grad(p[BB + 1], x - 1, y - 1, z - 1))));
  return (res + 1.0) / 2.0;
}