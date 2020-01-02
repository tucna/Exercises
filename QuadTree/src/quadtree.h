#pragma once

#include <array>
#include <cstdint>
#include <vector>

class Quadtree
{
public:
  enum Node { UpLeft, UpRight, DownLeft, DownRight, None };

  struct Point
  {
    uint16_t x;
    uint16_t y;
  };

  struct Rectangle
  {
    Point topLeft;
    Point downRight;

    uint16_t Width() const { return downRight.x - topLeft.x; }
    uint16_t Height() const { return downRight.y- topLeft.y; }
  };

  Quadtree(uint16_t level, Rectangle bounds) : m_level(level), m_boundaries(bounds) {}

  void Insert(Point object);
  void Clear();

  void Retrieve(std::vector<Point>& returnObjects, Point object);

  const Rectangle& GetBoundaries() const { return m_boundaries; }

  const std::array<Quadtree*, 4>& GetNodes() { return m_nodes; };

private:
  void Split();
  Node GetNode(const Point& object);

  static constexpr uint16_t m_maxObjects = 4;
  static constexpr uint16_t m_maxLevels = 5;

  uint16_t m_level;
  std::array<Quadtree*, 4> m_nodes;
  Rectangle m_boundaries;
  std::vector<Point> m_objects;
};
