#include "stdafx.h"
#include "Ball.h"

void Ball::init(CRect walls)
{
  p.x = walls.left + radius + walls.Width() * float(rand()) / RAND_MAX;
  p.y = walls.top + radius + walls.Height() * float(rand()) / RAND_MAX;
  v.x = 2 * float(rand()) / RAND_MAX;
  v.y = 2 * float(rand()) / RAND_MAX;
}


// uppercase letter - vector, lowercase letter - its length 
// (V, A) =  v * a * cos(alfa) => v * cos(alfa) = (V, A) / a 
// P = (A/a) * v * cos(alfa) => P = (V, A) * A / (a * a)
void Ball::reflect(Vector2<float> a)
{
  float scalar = v * a;
  if (scalar < 0.0)
    return;

  float coeff = scalar / (a * a);

  v -= 2 * coeff * a;

  float scalarNEW = v * a;

  scalar = scalarNEW;

  // test perpendicular
  //    float pp = vx * ax + vy * ay;
  //    scalar = pp;
}

bool Ball::collide(Ball& otherBall)
{
  Vector2<float> axis = p - otherBall.p;
  float dist = radius + otherBall.radius;
  if (axis * axis < dist * dist)
  {
    Vector2<float> vc = 0.5f * (v + otherBall.v);

    // convert absolute velocities to velocities relative to the center
    v -= vc;
    otherBall.v -= vc;

    reflect(otherBall.p - p);
    otherBall.reflect(p - otherBall.p);

    // convert velocities back to the absolute
    v += vc;
    otherBall.v += vc;

    return true;
  }
  else
  {
    return false;
  }
}


