#define T_PGE_APPLICATION
#include "../engine/tPixelGameEngine.h"

#include "quadtree.h"

class Demo : public tDX::PixelGameEngine
{
public:
  Demo()
  {
    sAppName = "Demo";
  }

  bool OnUserCreate() override
  {
    quadtree = new Quadtree(0, { {0,0},{static_cast<uint16_t>(ScreenWidth() - 1),static_cast<uint16_t>(ScreenHeight() - 1) } });

    uint16_t numPoints = 90;

    for (uint16_t i = 0; i < numPoints; i++)
      m_objects.push_back({ static_cast<uint16_t>(rand() % (ScreenWidth() - 1)), static_cast<uint16_t>(rand() % (ScreenHeight() - 1)) });

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override
  {
    quadtree->Clear();

    for (Quadtree::Point& object : m_objects)
    {
      Draw(object.x, object.y, tDX::RED);
      quadtree->Insert(object);
    }

    DrawBoundaries(quadtree);

    std::vector<Quadtree::Point> closest;
    quadtree->Retrieve(closest, m_objects[0]);

    return true;
  }

private:
  void DrawBoundaries(Quadtree* node)
  {
    const std::array<Quadtree*, 4>& nodes = node->GetNodes();

    if (!nodes[0])
      return;

    for (Quadtree* node : nodes)
    {
      const Quadtree::Rectangle& rect = node->GetBoundaries();

      DrawRect(rect.topLeft.x, rect.topLeft.y, rect.Width(), rect.Height(), tDX::GREY);
      DrawBoundaries(node);
    }
  }

  Quadtree* quadtree;

  std::vector<Quadtree::Point> m_objects;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  Demo demo;
  if (demo.Construct(200, 150, 4, 4))
    demo.Start();

  return 0;
}