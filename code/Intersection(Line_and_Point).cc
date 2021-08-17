#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

// 確定點在線的上面或下面假設有一直線通過點 P ，且方向向量為 v，求某一點 Q 在線的上部分或下部分或點上
// 公式：−−→
//      PQ   × v
// 結果：
// 負數->上部分
// 正數->下部分
// 0 -> 線上
// 可利用此公式當跨立實驗的判斷基準

// 快速排斥實驗
// 若兩線段四方形區域未重疊則此兩線段必不相交
// 求 $\overline {P_1P_2}$ 及 $\overline {Q_1Q_2}$
// 設 $Q_1(q1x,q1y)$ .... 以此類推
// - 程式碼：
// min(p1x,p2x) <= max(q1x,q2x) \&\& min(q1x,q2x) <= max(p1x,p2x) \&\& min(p1y,p2y) <= max(q1y,q2y) \&\& min(q1y,q2y) <= max(p1y,p2y)

// 跨立實驗
// 若有 $\overline {AB}$ 及 $\overline {CD}$
// $A$ 與 $B$ 在 $ \overleftrightarrow {CD}$ 兩側且 $C$ 與 $D$ 在 $ \overleftrightarrow {AB}$ 兩側，則通過跨立實驗
// 通過跨立實驗不代表兩線相交，需要同時通過快速排斥實驗才是兩線段相交

class Point {
   private:
    int _x, _y;

   public:
    Point(int x, int y) : _x(x), _y(y){};
    int getX() const { return _x; }
    int getY() const { return _y; }
    Point& operator-(const Point& other_point) const {
        return *(new Point(_x - other_point.getX(), _y - other_point.getY()));
    }
    int cross(const Point& other_point) {
        return _x * other_point.getY() - _y * other_point.getX();
    }
};

class Line {
   private:
    Point _p1, _p2;

   public:
    Line(Point p1, Point p2) : _p1(p1), _p2(p2){};
    Point Point1() const {
        return _p1;
    }
    Point Point2() const {
        return _p2;
    }
    bool isIntersect(const Line& other_line) const {
        int max_other_x = max(other_line.Point1().getX(), other_line.Point2().getX());
        int max_other_y = max(other_line.Point1().getY(), other_line.Point2().getY());
        int min_other_x = min(other_line.Point1().getX(), other_line.Point2().getX());
        int min_other_y = min(other_line.Point1().getY(), other_line.Point2().getY());
        int max_self_x = max(_p1.getX(), _p2.getX());
        int max_self_y = max(_p1.getY(), _p2.getY());
        int min_self_x = min(_p1.getX(), _p2.getX());
        int min_self_y = min(_p1.getY(), _p2.getY());

        if ((max_self_x >= min_other_x) && (max_other_x >= min_self_x) && (max_self_y >= min_other_y) && (max_other_y >= min_self_y)) {
            if ((_p1 - other_line.Point1()).cross(_p1 - _p2) * (_p1 - other_line.Point2()).cross(_p1 - _p2) <= 0) {
                if ((other_line.Point1() - _p1).cross(other_line.Point1() - other_line.Point2()) * (other_line.Point1() - _p2).cross(other_line.Point1() - other_line.Point2()) <= 0) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x_s, y_s, x_e, y_e;
        cin >> x_s >> y_s >> x_e >> y_e;
        Line line(Point(x_s, y_s), Point(x_e, y_e));

        int x_1, x_2, y_1, y_2;
        cin >> x_1 >> y_1 >> x_2 >> y_2;
        int x_l = max(x_1, x_2), x_r = min(x_1, x_2), y_t = max(y_1, y_2), y_b = min(y_1, y_2);

        if (x_s < x_l && x_e < x_l && x_s > x_r && x_e > x_r && y_s < y_t && y_e < y_t && y_s > y_b && y_e > y_b) {
            cout << "T" << endl;
        } else {
            Point left_top(x_l, y_t);
            Point right_top(x_r, y_t);
            Point left_bottom(x_l, y_b);
            Point right_bottom(x_r, y_b);

            Line left(left_top, left_bottom);
            Line right(right_top, right_bottom);
            Line top(left_top, right_top);
            Line bottom(left_bottom, right_bottom);

            if (left.isIntersect(line) || right.isIntersect(line) || top.isIntersect(line) || bottom.isIntersect(line)) {
                cout << "T" << endl;

            } else {
                cout << "F" << endl;
            }
        }
    }

    return 0;
}