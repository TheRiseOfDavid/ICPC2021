#include <iomanip>
#include <iostream>
using namespace std;

// 斜率一樣代表平行或重合
// m=dy/dx

// 求兩直線交點
// 利用正弦定理可知
// - a/sin a = b/sin b=c/sin c = 2R
//   a=(c * sin a) / sinc
// 又 T=|u * b| / |a * b|}=|u|sin theta / |a|sin beta (sin theta=sin a)
// 故 T* a= EB

class Vector {
   private:
    double _x;
    double _y;

   public:
    Vector(double x, double y) : _x(x), _y(y) {}
    double cross(const Vector& other_vector) const {
        return _x * other_vector._y - _y * other_vector._x;
    }
    double getX() { return _x; }
    double getY() { return _y; }

    Vector operator*(double k) const {
        return *(new Vector(k * _x, k * _y));
    }
};

Vector findIntersectionVector(const Vector& a, const Vector& b, const Vector& u) {
    return a * (u.cross(b) / a.cross(b));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    cout << "INTERSECTING LINES OUTPUT" << endl;

    for (int i = 0; i < n; i++) {
        double x1, y1, x2, y2, x3, y3, x4, y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4;
        if ((x1 - x2) * (y3 - y4) == (x3 - x4) * (y1 - y2)) {
            if (Vector(x1 - x3, y1 - y3).cross(Vector(x1 - x2, y1 - y2)) == 0) {
                cout << "LINE" << endl;
            } else {
                cout << "NONE" << endl;
            }
        } else {
            Vector intersectionVector = findIntersectionVector(Vector(x2 - x1, y2 - y1), Vector(x4 - x3, y4 - y3), Vector(x2 - x4, y2 - y4));
            cout << "POINT " << fixed << setprecision(2) << x2 - intersectionVector.getX() << " " << fixed << setprecision(2) << y2 - intersectionVector.getY() << endl;
        }
    }

    cout << "END OF OUTPUT" << endl;

    return 0;
}