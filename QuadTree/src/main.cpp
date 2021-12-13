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
    m_quadtree = std::make_unique<Quadtree>(0, Quadtree::Rectangle({ {0,0},{static_cast<uint16_t>(ScreenWidth() - 1),static_cast<uint16_t>(ScreenHeight() - 1) } }));

    uint16_t numPoints = 90;

    for (uint16_t i = 0; i < numPoints; i++)
      m_objects.push_back({ static_cast<uint16_t>(rand() % (ScreenWidth() - 1)), static_cast<uint16_t>(rand() % (ScreenHeight() - 1)) });

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override
  {
    DrawBoundaries(*m_quadtree);

    m_quadtree->Clear();

    tDX::HWButton leftM = GetMouse(0);

    if (leftM.bPressed)
      m_objects.push_back({static_cast<uint16_t>(GetMouseX()), static_cast<uint16_t>(GetMouseY())});

    for (Quadtree::Point& object : m_objects)
    {
      Draw(object.x, object.y, tDX::RED);
      m_quadtree->Insert(object);
    }

    Quadtree::Point selected = { GetMouseX(), GetMouseY() };

    std::vector<Quadtree::Point> closest;
    m_quadtree->Retrieve(closest, selected);

    for (Quadtree::Point& object : closest)
      Draw(object.x, object.y, tDX::BLUE);

    return true;
  }

private:
  void DrawBoundaries(Quadtree& node)
  {
    const std::array<std::shared_ptr<Quadtree>, 4>& nodes = node.GetNodes();

    if (!nodes[0])
      return;

    for (const std::shared_ptr<Quadtree>& node : nodes)
    {
      const Quadtree::Rectangle& rect = node->GetBoundaries();

      DrawRect(rect.topLeft.x, rect.topLeft.y, rect.Width(), rect.Height(), tDX::GREY);
      DrawBoundaries(*node);
    }
  }

  std::unique_ptr<Quadtree> m_quadtree;
  std::vector<Quadtree::Point> m_objects;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  Demo demo;
  if (demo.Construct(200, 150, 4, 4))
    demo.Start();

  return 0;
}