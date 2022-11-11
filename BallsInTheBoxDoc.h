
// BallsInTheBoxDoc.h : interface of the CBallsInTheBoxDoc class
//


#pragma once

#include <vector>

#include "Ball.h"

class CBallsInTheBoxDoc : public CDocument
{
protected: // create from serialization only
	CBallsInTheBoxDoc();
	DECLARE_DYNCREATE(CBallsInTheBoxDoc)

// Attributes
public:

  std::vector<Ball> m_balls;

// Operations
public:

  void initBalls(CRect rect)
  {
    int N = 5;
    m_balls.resize(N);
    int index = 1;
    for (Ball& b : m_balls)
    {
      b.init(rect);
    }
  }

  void step(CRect walls, float dt)
  {
    for (Ball& b : m_balls)
    {
      b.p += b.v * dt;
    }
    for (Ball& b : m_balls)
    {
      if (b.p.x - b.radius < walls.left)
        b.reflect(Vector2<float>(-1, 0));

      if (b.p.x + b.radius > walls.right)
        b.reflect(Vector2<float>(1, 0));

      if (b.p.y - b.radius < walls.top)
        b.reflect(Vector2<float>(0, -1));

      if (b.p.y + b.radius > walls.bottom)
        b.reflect(Vector2<float>(0, 1));
    }

    std::vector<int> collided; collided.resize(m_balls.size(), 0);
    for (unsigned int i = 0; i < m_balls.size(); ++i)
      for (unsigned int j = i+1; j < m_balls.size(); ++j)
        m_balls[i].collide(m_balls[j]);
  }


// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CBallsInTheBoxDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
