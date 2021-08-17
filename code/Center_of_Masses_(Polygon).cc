#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// 求重心
// 把多邊形切開成許多個三角形，分別計算各個三角形的重心。然後以三角形面積作為權重，計算三角形重心的加權平均值，就得到多邊形的重心

class Point {
   private:
   public:
    double x, y;
    Point() : x(0), y(0) {}
    Point(double X, double Y) : x(X), y(Y) {}
    ~Point() {}

    bool operator<(Point const& r) const {
        return x < r.x || (x == r.x && y < r.y);
    }

    bool operator==(Point const& r) const {
        return x == r.x && y == r.y;
    }

    Point& operator+(Point const& r) const {
        return *(new Point(x + r.x, y + r.y));
    }

    Point& operator-(Point const& r) const {
        return *(new Point(x - r.x, y - r.y));
    }

    double cross(Point const& r) const {
        return x * r.y - y * r.x;
    }
};

Point massCenter(vector<Point> polygon) {
    if (polygon.size() == 1) {
        return polygon[0];
    } else if (polygon.size() == 2) {
        return Point((polygon[0].x + polygon[1].x) / 2, (polygon[0].y + polygon[1].y));
    }
    double cx = 0, cy = 0, w = 0;
    for (int i = polygon.size() - 1, j = 0; j < polygon.size(); i = j++) {
        double a = polygon[i].cross(polygon[j]);
        cx += (polygon[i].x + polygon[j].x) * a;
        cy += (polygon[i].y + polygon[j].y) * a;
        w += a;
    }

    return Point(cx / 3 / w, cy / 3 / w);
}