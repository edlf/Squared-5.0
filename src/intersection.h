#include <pebble.h>

#define	DONT_INTERSECT    0
#define	DO_INTERSECT      1
#define COLLINEAR         2

#define SAME_SIGNS( a, b )	\
		(((long) ((unsigned long) a ^ (unsigned long) b)) >= 0 )

int lines_intersect(
  x1, y1,
  x2, y2,
  x3, y3,
  x4, y4,
  x,
  y
)
  
long  x1, y1, x2, y2, x3, y3, x4, y4, *x, *y;

{
  long a1, a2, b1, b2, c1, c2; /* Coefficients of line eqns. */
  long r1, r2, r3, r4;         /* 'Sign' values */
  long denom, offset, num;     /* Intermediate values */

  a1 = y2 - y1;
  b1 = x1 - x2;
  c1 = x2 * y1 - x1 * y2;
  
  r3 = a1 * x3 + b1 * y3 + c1;
  r4 = a1 * x4 + b1 * y4 + c1;
  
  if ( r3 != 0 &&
      r4 != 0 &&
      SAME_SIGNS( r3, r4 ))
    return ( DONT_INTERSECT );

  a2 = y4 - y3;
  b2 = x3 - x4;
  c2 = x4 * y3 - x3 * y4;

  r1 = a2 * x1 + b2 * y1 + c2;
  r2 = a2 * x2 + b2 * y2 + c2;

  if ( r1 != 0 &&
      r2 != 0 &&
      SAME_SIGNS( r1, r2 ))
    return ( DONT_INTERSECT );

  denom = a1 * b2 - a2 * b1;
  if ( denom == 0 )
    return ( COLLINEAR );
  offset = denom < 0 ? - denom / 2 : denom / 2;

  num = b1 * c2 - b2 * c1;
  *x = ( num < 0 ? num - offset : num + offset ) / denom;

  num = a2 * c1 - a1 * c2;
  *y = ( num < 0 ? num - offset : num + offset ) / denom;

  return ( DO_INTERSECT );
}

#define INTERSECTION_NONE 0
#define INTERSECTION_PARTIAL 1
#define INTERSECTION_FULL 2

typedef struct {
  uint8_t success;
  GPoint p1;
  GPoint p2;
} Intersection;

Intersection rectintersect(GPoint p1, GPoint p2, GRect rect) {
  long x,y;
  long x1=0,y1=0,x2=0,y2=0;
  bool intersection = false, final_intersection = false;
  if (lines_intersect(p1.x, p1.y, p2.x, p2.y, rect.origin.x, rect.origin.y, rect.origin.x, rect.origin.y+rect.size.h, &x, &y) == DO_INTERSECT) {
    x1 = x; y1 = y; intersection = true;
  }
  if (lines_intersect(p1.x, p1.y, p2.x, p2.y, rect.origin.x, rect.origin.y, rect.origin.x+rect.size.w, rect.origin.y, &x, &y) == DO_INTERSECT) {
    if (!intersection) {
      x1 = x; y1 = y; intersection = true;
    } else if (x != x1 && y != y1) {
      x2 = x; y2 = y; final_intersection = true;
    }
  }
  if (!final_intersection && lines_intersect(p1.x, p1.y, p2.x, p2.y, rect.origin.x, rect.origin.y+rect.size.h, rect.origin.x+rect.size.w, rect.origin.y+rect.size.h, &x, &y) == DO_INTERSECT) {
    if (!intersection) {
      x1 = x; y1 = y; intersection = true;
    } else if (x != x1 && y != y1) {
      x2 = x; y2 = y; final_intersection = true;
    }
  }
  if (!final_intersection && lines_intersect(p1.x, p1.y, p2.x, p2.y, rect.origin.x+rect.size.w, rect.origin.y, rect.origin.x+rect.size.w, rect.origin.y+rect.size.h, &x, &y) == DO_INTERSECT) {
    if (!intersection) {
      x1 = x; y1 = y;
    } else if (x != x1 && y != y1) {
      x2 = x; y2 = y; final_intersection = true;
    }
  }
  if(final_intersection) {
    return (Intersection) { .success = INTERSECTION_FULL, .p1 = (GPoint) { .x = x1, .y = y1 }, .p2 = (GPoint) { .x = x2, .y = y2 } };
  } else if (intersection) {
    return (Intersection) { .success = INTERSECTION_PARTIAL, .p1 = (GPoint) { .x = x1, .y = y1 }, .p2 = (GPoint) { .x = x2, .y = y2 } };
  } else {
    return (Intersection) { .success = INTERSECTION_NONE, .p1 = (GPoint) { .x = x1, .y = y1 }, .p2 = (GPoint) { .x = x2, .y = y2 } };
  }
}