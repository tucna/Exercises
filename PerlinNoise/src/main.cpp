#define T_PGE_APPLICATION
#include "../engine/tPixelGameEngine.h"

class Demo : public tDX::PixelGameEngine
{
public:
  Demo()
  {
    sAppName = "Demo";
  }

  bool OnUserCreate() override
  {
    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override
  {
    return true;
  }

  bool OnUserUpdateEndFrame(float fElapsedTime) override
  {
    return true;
  }

private:
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  Demo demo;
  if (demo.Construct(200, 150, 4, 4))
    demo.Start();

  return 0;
}