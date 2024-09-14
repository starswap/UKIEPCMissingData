#include <bits/stdc++.h>
using namespace std;

// As this problem has no data published by UKIEPC I used it to generate
// my own data, see https://github.com/starswap/UKIEPCMissingData

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

typedef vector<point> polygon;

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

double norm_sq(vec v) {
  return v.x*v.x + v.y*v.y;
}

double dot(vec a, vec b) { return (a.x*b.x + a.y*b.y); }

vec toVec(const point &a, const point &b) {      // convert 2 points
  return vec(b.x-a.x, b.y-a.y);                  // to vector a->b
}

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

double dist(point p1, point p2) {                // Euclidean distance
  return hypot(p1.x-p2.x, p1.y-p2.y);            // return double
}

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

struct contour {
    int h;
    polygon poly;
};

int main() {
    point A;
    point B;
    cin >> A.x >> A.y >> B.x >> B.y;
    int N; cin >> N;
    vector<contour> contours(N);

    for (int n = 0; n < N; ++n) {
        int v; 
        cin >> v;
        cin >> contours[n].h;
        for (int i = 0; i < v; ++i) {
            point p;
            cin >> p.x >> p.y;
            contours[n].poly.push_back(p);
        }
        contours[n].poly.push_back(contours[n].poly[0]);
    }


    vector<contour> containsA;
    vector<contour> containsB;
    vector<contour> containsAandB;

    for (const contour& c : contours) {
        if (insidePolygon(A, c.poly) == 1 && insidePolygon(B, c.poly) == 1) {
            containsAandB.push_back(c);
        } else if (insidePolygon(A, c.poly) == 1) {
            containsA.push_back(c);
        } else if (insidePolygon(B, c.poly) == 1) {
            containsB.push_back(c);
        }
    }

    sort(containsAandB.begin(), containsAandB.end(), [](const contour& a, const contour& b) {
        return insidePolygon(a.poly[0], b.poly) == 1;
    });

    int ans = containsAandB[0].h;
    for (const contour& c : containsA) {
      ans = max(ans, c.h);
    }
    for (const contour& c : containsB) {
      ans = max(ans, c.h);
    }

    cout << ans << endl;

    return 0;
}
