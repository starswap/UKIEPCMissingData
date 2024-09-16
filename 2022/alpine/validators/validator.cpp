#include <bits/stdc++.h>
#include "testlib.h"

#define M_PI   3.14159265358979323846264338327950288

using namespace std;

const double INF = 1e20;
const double EPS = 1e-6; // consider e-9 depending on how large the numbers can get

struct point {
  double x, y;                                   // if need more precision
  point() { x = y = 0.0; }                       // default constructor
  point(double _x, double _y) : x(_x), y(_y) {}  // constructor
  bool operator < (point other) const {          // override < operator
    if (fabs(x-other.x) > EPS)                   // useful for sorting
      return x < other.x;                        // by x-coordinate
    return y < other.y;                          // if tie, by y-coordinate
  }
  bool operator == (point other) const {
   return (fabs(x-other.x) < EPS && (fabs(y-other.y) < EPS));
  }
};

struct line { 
  double a, b, c;
  line() {a = b = c = 0.0;}
  line(double a, double b, double c):a(a), b(b), c(c) {}
  line(point p1, point p2) {
    if (fabs(p1.x-p2.x) < EPS) {
      a = 1.0; b = 0.0; c = -p1.x;
    }
    else {
      a = -(p1.y-p2.y) / (p1.x-p2.x);
      b = 1.0;
      c = -(a*p1.x) - p1.y;      // NOTE: b always 1.0
    }
  }
  line(point p1, double m) {
    a = -m; b = 1; c = -((a * p1.x) + (b * p1.y));
  }
  double get_m() { return (b == 0) ? INF : -a / b;} // NOTE: may return INF
  double get_c() { return (b == 0) ? INF : -c / b;} // NOTE: may return INF
  double get_y(double x) {
    return get_m() * x + get_c();
  }
};


struct vec {
  double x, y;
  vec(double _x, double _y) : x(_x), y(_y) {}
  vec(point p): x(p.x), y(p.y) {}
  vec(const point&a, const point &b):x(b.x - a.x), y(b.y - a.y) {}
  vec operator - (vec other) const {
    return vec(x - other.x, y - other.y);
  }
  vec operator + (vec other) const {
    return vec(x + other.x, y + other.y);
  }
  vec operator * (double scalar) {
    return vec(x * scalar, y * scalar);
  }
  vec operator / (double scalar) {
    return vec(x / scalar, y / scalar);
  }
};


// POINT ROUTINES
double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x-p2.x, p1.y-p2.y);            // return double
}


vec toVec(const point &a, const point &b) {      // convert 2 points
  return vec(b.x-a.x, b.y-a.y);                  // to vector a->b
}

vec scale(const vec &v, double s) {              // s = [<1..1..>1]
  return vec(v.x*s, v.y*s);                      // shorter/eq/longer
}                                                // return a new vec

double norm_sq(vec v) {
  return v.x*v.x + v.y*v.y;
}

vec set_norm(const vec &v, double new_norm) {
  double new_dx = v.x*new_norm/(sqrt(norm_sq(v)));
  double new_dy = v.y*new_norm;
  return vec(new_dx, new_dy);
}

point translate(const point &p, const vec &v) {  // translate p
  return point(p.x+v.x, p.y+v.y);                // according to v
}                                                // return a new point

double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

double cross(vec a, vec b) { return a.x*b.y - a.y*b.x; }


// note: to accept collinear points, we have to change the `> 0' to > -EPS
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return cross(vec(p, q), vec(p, r)) > 0;
}

double angle(const point &a, const point &o, const point &b) { // angle aob in rad
  vec oa = toVec(o, a), ob = toVec(o, b);        // a != o != b
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}

bool areParallel(line l1, line l2) {             // check a & b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
}

bool areSame(line l1, line l2) {                 // also check  c
  return areParallel(l1 ,l2) && (fabs(l1.c-l2.c) < EPS);
}

// returns true (+ intersection point p) if two lines are intersect
bool findIntersect(line l1, line l2, point &p) {
  if (areParallel(l1, l2)) return false;         // no intersection
  // solve system of 2 linear algebraic equations with 2 unknowns
  p.x = (l2.b*l1.c - l1.b*l2.c) / (l2.a*l1.b - l1.a*l2.b);
  // special case: test for vertical line to avoid division by zero
  if (fabs(l1.b) > EPS) p.y = -(l1.a*p.x + l1.c);
  else                  p.y = -(l2.a*p.x + l2.c);
  return true;
}

typedef vector<point> polygon;


// returns 1/0/-1 if point p is inside/on (vertex/edge)/outside of
// either convex/concave polygon P
int insidePolygon(point pt, const polygon &P) {
  int n = (int)P.size();
  if (n <= 3) return -1;                         // avoid point or line
  bool on_polygon = false;
  for (int i = 0; i < n-1; ++i)                  // on vertex/edge?
    if (fabs(dist(P[i], pt) + dist(pt, P[i+1]) - dist(P[i], P[i+1])) < EPS)
      on_polygon = true;
  if (on_polygon) return 0;                      // pt is on polygon
  double sum = 0.0;                              // first = last point
  for (int i = 0; i < n-1; ++i) {
    if (ccw(pt, P[i], P[i+1]))
      sum += angle(P[i], pt, P[i+1]);            // left turn/ccw
    else
      sum -= angle(P[i], pt, P[i+1]);            // right turn/cw
  }
  return fabs(sum) > M_PI ? 1 : -1;              // 360d->in, 0d->out
}

bool segIntersect(point p, point q, point r, point s, point &i) {
    if (p == r || p == s) { i = p; return true; }
    else if (q == r || q == s) { i = q; return true; }
    const line l1(p, q);
    const line l2(r, s);

    bool same_case = areSame(l1, l2) && ((p.x < r.x + EPS && r.x < q.x + EPS && p.y < r.y + EPS && r.y < q.y + EPS) || 
                                         (q.x < r.x + EPS && r.x < p.x + EPS && q.y < r.y + EPS && r.y < p.y + EPS) || 
                                         (p.x < s.x + EPS && s.x < q.x + EPS && p.y < s.y + EPS && s.y < q.y + EPS) || 
                                         (q.x < s.x + EPS && s.x < p.x + EPS && q.y < s.y + EPS && s.y < p.y + EPS) ||
                                         (s.x < p.x + EPS && p.x < r.x + EPS && s.y < p.y + EPS && p.y < r.y + EPS) || 
                                         (r.x < p.x + EPS && p.x < s.x + EPS && r.y < p.y + EPS && p.y < s.y + EPS) ||
                                         (s.x < q.x + EPS && q.x < r.x + EPS && s.y < q.y + EPS && q.y < r.y + EPS) || 
                                         (r.x < q.x + EPS && q.x < s.x + EPS && r.y < q.y + EPS && q.y < s.y + EPS));
    if (same_case) {
        vector<point> pts{p, q, r, s};
        sort(pts.begin(), pts.end());
        i = pts[1];
    }

    return same_case || (findIntersect(l1, l2, i) && 
           min(p.x, q.x) < i.x + EPS && max(p.x, q.x) > i.x - EPS &&
           min(r.x, s.x) < i.x + EPS && max(r.x, s.x) > i.x - EPS &&
           min(p.y, q.y) < i.y + EPS && max(p.y, q.y) > i.y - EPS &&
           min(r.y, s.y) < i.y + EPS && max(r.y, s.y) > i.y - EPS);
}


int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    point A, B;

    A.x = inf.readInt(-999'999, 999'999, "ax");
    inf.readSpace();
    A.y = inf.readInt(-999'999, 999'999, "ay");
    inf.readEoln();
    B.x = inf.readInt(-999'999, 999'999, "bx");
    inf.readSpace();
    B.y = inf.readInt(-999'999, 999'999, "by");
    inf.readEoln();
    
    int n = inf.readInt(1, 10'000, "n~"); // Bounds warnings suppressed because of 10000 total vertex limit
    inf.readEoln();

    
    vector<polygon> contours(n);
    for (int i = 0; i < n; ++i) {
        int v = inf.readInt(3, 10'000, "v");
        inf.readSpace();
        inf.readInt(0, 1'000'000, "h");
        inf.readSpace();
        contours[i].resize(v);
        for (int j = 0; j < v; ++j) {
            contours[i][j].x = inf.readInt(-1'000'000, 1'000'000, "x");
            inf.readSpace();
            contours[i][j].y = inf.readInt(-1'000'000, 1'000'000, "y");
            if (j != v - 1) inf.readSpace();
        }
        contours[i].push_back(contours[i][0]);
        inf.readEoln();
    }

    int containsAandB = 0;
    for (const polygon& poly : contours) {
        containsAandB += (insidePolygon(A, poly) == 1) && (insidePolygon(B, poly) == 1);
    }
    inf.readEof();

    ensuref(containsAandB >= 1, "Doesn't have at least 1 contour containing both points");

    int total_vert = 0;

    for (int i = 0; i < n; ++i) {
        total_vert += contours[i].size() - 1;
        for (int j = i + 1; j < n; ++j) {
            const polygon& poly1 = contours[i];
            const polygon& poly2 = contours[j]; 

            for (int k = 0; k < poly1.size() - 1; ++k) {
                for (int l = 0; l < poly2.size() - 1; ++l) {
                    point p;
                    bool intsct = segIntersect(poly1[k], poly1[k + 1], poly2[l], poly2[l + 1], p);
                    ensuref(!intsct, format("Contours {} and {} intersect at lines {} {}", i, j, k, l).c_str());
                }
            }
        
        }
    }

    ensuref(total_vert <= 10000, "Sum of all contours contains more than 10000 vertices.");

}