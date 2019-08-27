#pragma once

template <int M, int K, int S>
struct MksUnit
{
  enum { metre = M, kilogram = K, second = S };
};

template <typename MksUnit>
class Value
{
public:
  constexpr explicit Value(const long double magnitude) noexcept : _magnitude(magnitude) {}

  constexpr long double getMagnitude() const noexcept { return _magnitude; }

private:
  long double _magnitude{ 0.0 };
};

using DimensionlessQuantity = Value<MksUnit<0, 0, 0>>;
using Length = Value<MksUnit<1, 0, 0>>;
using Area = Value<MksUnit<2, 0, 0>>;
using Volume = Value<MksUnit<3, 0, 0>>;
using Mass = Value<MksUnit<0, 1, 0>>;
using Time = Value<MksUnit<0, 0, 1>>;
using Speed = Value<MksUnit<1, 0, -1>>;
using Acceleration = Value<MksUnit<1, 0, -2>>;
using Frequency = Value<MksUnit<0, 0, -1>>;
using Force = Value<MksUnit<1, 1, -2>>;
using Pressure = Value<MksUnit<-1, 1, -2>>;
using Momentum = Value<MksUnit<1, 1, -1>>;

constexpr Acceleration gravitationalAccelerationOnEarth{ 9.80665 };
constexpr Pressure standardPressureOnSeaLevel{ 1013.25 };
constexpr Speed speedOfLight{ 299792458.0 };
constexpr Frequency concertPitchA{ 440.0 };
constexpr Mass neutronMass{ 1.6749286e-27 };
