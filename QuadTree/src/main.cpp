#define T_PGE_APPLICATION
#include "../engine/tPixelGameEngine.h"

class Demo : public tDX::PixelGameEngine
{
public:
  Demo()
  {
    sAppName = "Demo";
  }

public:
  bool OnUserCreate() override
  {
    // Called once at the start, so create things here
    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override
  {
    // called once per frame
    for (int x = 0; x < ScreenWidth(); x++)
      for (int y = 0; y < ScreenHeight(); y++)
        Draw(x, y, tDX::Pixel(rand() % 255, rand() % 255, rand() % 255));

    DrawString(5, 5, "TUCNA");

    return true;
  }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  Demo demo;
  if (demo.Construct(250, 250, 4, 4))
    demo.Start();

  return 0;
}