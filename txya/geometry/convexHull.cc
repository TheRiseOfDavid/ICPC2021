#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// 首先升序排序将所有点按x升序（x相同按y升序），删除重复点后得到序列p1,p2...，然后将p1和p2放到凸包中。 从p3开始，当新点在凸包“前进”方向的左边（叉积为正）时继续，否则（叉积为负或0）依次删除最近加入到凸包的点，直到新点在左边。
// 从左到右做一次之后得到的是“下凸包”，然后从右向左做一次得到“上凸包”，合起来就是完整的凸包。复杂度O(nlogn)。

class Point {
   private:
    double x, y;

   public:
    Point() : x(0), y(0) {}
    Point(double X, double Y) : x(X), y(Y){};
    ~Point(){};

    bool operator<(Point const& r) {
        return x < r.x || (x == r.x && y < r.y);
    }

    bool operator==(Point const& r) {
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

    Point& rotate(double degree) const {
        return *(new Point(x * cos(degree) - y * sin(degree), x * sin(degree) + y * cos(degree)));
    }
};

vector<Point> convexHull(vector<Point>::iterator first, vector<Point>::iterator last) {
    vector<Point> p(first, last);
    sort(p.begin(), p.end());
    p.resize(unique(p.begin(), p.end()) - p.begin());
    if (p.size() < 3) return p;

    vector<Point> result;
    for (int i = 0; i < p.size(); i++) {
        while (result.size() >= 2 && (result.back() - result[result.size() - 2]).cross(p[i] - result.back()) <= 0) result.pop_back();
        result.push_back(p[i]);
    }

    int k = result.size();
    for (int i = p.size() - 2; i >= 0; i--) {
        while (result.size() >= k + 1 && (result.back() - result[result.size() - 2]).cross(p[i] - result.back()) <= 0) result.pop_back();
        result.push_back(p[i]);
    }
    result.pop_back();
    return result;
}

double area(vector<Point>::iterator first, vector<Point>::iterator last) {
    double ans = 0;
    for (auto i = first + 1; i + 1 < last; i++) {
        ans += (*i - *first).cross(*(i + 1) - *first);
    }
    return ans / 2;
}
