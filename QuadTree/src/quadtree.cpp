#include "quadtree.h"

void Quadtree::Insert(Point object)
{
  if (m_nodes[Node::UpLeft])
  {
    Node node = GetNode(object);

    if (node != Node::None)
    {
      m_nodes[node]->Insert(object);
      return;
    }
  }

  m_objects.push_back(object);

  if (m_objects.size() > m_maxObjects && m_level < m_maxLevels)
  {
    if (!m_nodes[Node::UpLeft])
      Split();

    size_t i = 0;
    while (i < m_objects.size())
    {
      Node node = GetNode(m_objects[i]);
      if (node != Node::None)
      {
        m_nodes[node]->Insert(m_objects[i]);
        m_objects.erase(m_objects.begin() + i);
      }
      else
        i++;
    }
  }
}

void Quadtree::Retrieve(std::vector<Point>& returnObjects, Point object)
{
  returnObjects.clear();

  Node node = GetNode(object);

  if (node != Node::None && m_nodes[Node::UpLeft])
    m_nodes[node]->Retrieve(returnObjects, object);

  returnObjects.insert(returnObjects.end(), m_objects.begin(), m_objects.end());
}

void Quadtree::Clear()
{
  m_objects.clear();

  for (Quadtree* node : m_nodes)
  {
    if (node)
    {
      node->Clear();
      //delete node;
    }
  }

  /* tucna
  if (m_nodes[UpLeft]) delete m_nodes[UpLeft];
  if (m_nodes[UpRight]) delete m_nodes[UpRight];
  if (m_nodes[DownLeft]) delete m_nodes[DownLeft];
  if (m_nodes[DownRight]) delete m_nodes[DownRight];
  */
}

void Quadtree::Split()
{
  if (m_boundaries.downRight.x < m_boundaries.topLeft.x)
  {
    int i = 120;
  }

  uint16_t x = m_boundaries.topLeft.x;
  uint16_t y = m_boundaries.topLeft.y;
  uint16_t widthHalf = m_boundaries.Width() / 2;
  uint16_t heightHalf = m_boundaries.Height() / 2;

  Point tl = { x,y }; // top left
  Point m = { x + widthHalf, y + heightHalf }; // middle
  Point br = { x + m_boundaries.Width(), y + m_boundaries.Height() }; // bottom right

  m_nodes[UpLeft] = new Quadtree(m_level + 1, { tl, m });
  m_nodes[UpRight] = new Quadtree(m_level + 1, { {m.x, tl.y}, {br.x, m.y} });
  m_nodes[DownLeft] = new Quadtree(m_level + 1, { {tl.x, m.y}, {m.x,br.y} });
  m_nodes[DownRight] = new Quadtree(m_level + 1, { m, br });
}

Quadtree::Node Quadtree::GetNode(const Point& object)
{
  Node node = Node::None;

  uint16_t verticalMidpoint = m_boundaries.topLeft.x + (m_boundaries.Width() / 2);
  uint16_t horizontalMidpoint = m_boundaries.topLeft.y + (m_boundaries.Height() / 2);

  // Object can completely fit within the left quadrants
  if (object.x < verticalMidpoint)
  {
    if (object.y < horizontalMidpoint)
      node = Node::UpLeft;
    else if (object.y > horizontalMidpoint)
      node = Node::DownLeft;
  }
  // Object can completely fit within the right quadrants
  else if (object.x > verticalMidpoint) {
    if (object.y < horizontalMidpoint)
      node = Node::UpRight;
    else if (object.y > horizontalMidpoint)
      node = Node::DownRight;
  }

  return node;
}
