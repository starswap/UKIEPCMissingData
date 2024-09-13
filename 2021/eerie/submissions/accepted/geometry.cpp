#include <bits/stdc++.h>
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

bool areParallel(line l1, line l2) {             // check a & b
  return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS);
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

typedef vector<point> polygon; // Note that the first and last points must be the same

double polygonArea(const polygon &P) {
  double ans = 0.0;
  for (int i = 0; i < (int)P.size()-1; ++i)      // Shoelace formula
    ans += (P[i].x*P[i+1].y - P[i+1].x*P[i].y);
  return fabs(ans)/2.0;                          // only do / 2.0 here
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cout << fixed << setprecision(10);

    double W, L; cin >> W >> L;
    int N; cin >> N;
    
    vector<tuple<line, line, line, line>> columns;
    int s, e;

    point O{-L, 0};
    point M{L + 2 * W, 0};

    for (int n = 0; n < N; ++n) {
        cin >> s >> e;
        columns.emplace_back(
            line{O, point{0, (double) s}},
            line{O, point{0, (double) e}},
            line{M, point{2 * W, (double) s}},
            line{M, point{2 * W, (double) e}}
        );
    }

    line left{point{0, 0}, point{0, 1}};
    line midl{point{W, 0}, point{W, 1}};
    line right{point{2 * W, 0}, point{2 * W, 1}};

    double area = 0;
    for (const auto& [start, end, rstart, rend]: columns) {
        point p, q, r;
        assert (findIntersect(midl, end, p));
        area += 0.5 * p.y * (L + p.x);
        assert (findIntersect(midl, start, p));
        area -= 0.5 * p.y * (L + p.x);
        assert (findIntersect(left, end, p));
        area -= 0.5 * p.y * (L + p.x);
        assert (findIntersect(left, start, p));
        area += 0.5 * p.y * (L + p.x);

        assert (findIntersect(right, end, p));
        area += 0.5 * p.y * (L + p.x);
        assert (findIntersect(right, start, p));
        area -= 0.5 * p.y * (L + p.x);
        assert (findIntersect(midl, end, p));
        area -= 0.5 * p.y * (L + p.x);
        assert (findIntersect(midl, start, p));
        area += 0.5 * p.y * (L + p.x);

        // remove double counted "half intersection"
        assert (findIntersect(end, rstart, p));
        double h = W - p.x;
        assert (findIntersect(midl, start, r));
        assert (findIntersect(midl, end, q));
        area -= 0.5 * h * (q.y - r.y);

        if (p.x < 0) { // account for potential triangle that we subtracted off unnecessarily
            double h = 0 - p.x;
            assert (findIntersect(left, rstart, r));
            assert (findIntersect(left, end, q));
            area += 0.5 * h * (q.y - r.y);
        }
    }

    // All good except double counted some intersections between two chunks
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            point p, q, r, s, t, u; 
            const auto &[is, ie, irs, ire] = columns[i];
            const auto &[js, je, jrs, jre] = columns[j];
            
            assert (findIntersect(ie, jrs, p));
            assert (findIntersect(ie, jre, q));
            assert (findIntersect(is, jre, r));
            assert (findIntersect(is, jrs, s));

            if (r.x < 2 * W + EPS && q.x < 2 * W && s.x < 2 * W && p.x < 2 * W) {
                area -= polygonArea({p, q, r, s, p}); // full quadrilateral area
            } else if (2 * W < r.x && q.x < 2 * W + EPS && s.x < 2 * W + EPS && p.x < 2 * W) { // only up to intersection with jre and is
                assert (findIntersect(right, jre, t));
                assert (findIntersect(right, is, u));
                area -= polygonArea({p, q, t, u, s, p});
            } else if (2 * W < r.x && 2 * W < q.x && s.x < 2 * W + EPS && p.x < 2 * W) { // only up to intersection with ie and is
                assert (findIntersect(right, ie, t));
                assert (findIntersect(right, is, u));
                area -= polygonArea({p, t, u, s, p});
            } else if (2 * W < r.x && 2 * W < s.x && q.x < 2 * W + EPS && p.x < 2 * W) { // only up to intersection with jrs and jre
                assert (findIntersect(right, jre, t));
                assert (findIntersect(right, jrs, u));
                area -= polygonArea({p, q, t, u, p});
            } else if (2 * W < r.x && 2 * W < s.x && 2 * W < q.x && p.x < 2 * W) { // only up to intersection with jrs and ie
                assert (findIntersect(right, ie, t));
                assert (findIntersect(right, jrs, u));
                area -= polygonArea({p, t, u, p});
            } else {
                area -= 0;
            }

        }
    }

    area *= 2;
    cout << area << endl; 
    return 0;
}
