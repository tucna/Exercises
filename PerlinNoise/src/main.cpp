#define T_PGE_APPLICATION
#include "../engine/tPixelGameEngine.h"

#include "PerlinNoise.h"

class Demo : public tDX::PixelGameEngine
{
public:
  Demo() :
    m_noise(666)
  {
    sAppName = "Demo";

    m_noise.SetFrequency(10);
  }

  bool OnUserCreate() override
  {
    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override
  {
    //m_noise.SetFrequency(fElapsedTime * 1000);

    for (int x = 0; x < ScreenWidth(); x++)
      for (int y = 0; y < ScreenHeight(); y++)
      {
        uint8_t color = static_cast<uint8_t>(floor(255 * m_noise.GetValue((float)x / ScreenWidth(), (float)y / ScreenHeight(), 0.8f)));
        Draw(x, y, tDX::Pixel(color, color, color));
      }

    return true;
  }

private:
  PerlinNoise m_noise;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  Demo demo;
  if (demo.Construct(257, 257, 1, 1))
    demo.Start();

  return 0;
}