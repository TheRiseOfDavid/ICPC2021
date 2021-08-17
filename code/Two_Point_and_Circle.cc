#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;
// - 餘弦定理
//     - 設三角形三邊 A、B、C 與三對角 $\theta_a$、$\theta_b$、$\theta_c$
//     - $A^2=B^2+C^2-2BC\cos{\theta_a}$
//     - $\cos{\theta_a}=\frac{B^2+C^2-A^2}{2BC}$

class Vector {
   public:
    double x, y;
    Vector() : x(0), y(0) {}
    Vector(double X, double Y) : x(X), y(Y) {}
    Vector operator-(const Vector& other_point) const {
        return *(new Vector(x - other_point.x, y - other_point.y));
    }
    double dot(const Vector& other_point) const {
        return x * other_point.x + y * other_point.y;
    }

    double cross(const Vector& other_point) const {
        return x * other_point.y - y * other_point.x;
    }

    double square() const {
        return (x * x + y * y);
    }

    double distance() const {
        return sqrt(square());
    }
};

double p2l_dist(Vector A, Vector B, Vector O) {
    Vector AB = B - A;
    Vector dv(-AB.y, AB.x);
    if (A.cross(dv) * B.cross(dv) >= 0) {
        return min(A.distance(), B.distance());
    }

    Vector AO = O - A;
    return sqrt(AO.square() - pow(AO.dot(AB) / AB.distance(), 2));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    while (n--) {
        Vector A, B, O(0, 0);
        double r, ans;
        cin >> A.x >> A.y >> B.x >> B.y >> r;

        if (p2l_dist(A, B, O) + 1e-7 >= r) {
            ans = (A - B).distance();
        } else {
            double AO = A.distance();
            double BO = B.distance();
            double AB = (A - B).distance();
            double a3 = acos((AO * AO + BO * BO - AB * AB) / (2 * AO * BO)) - acos(r / AO) - acos(r / BO);
            ans = a3 * r + sqrt(AO * AO - r * r) + sqrt(BO * BO - r * r);
        }
        cout << fixed << setprecision(3) << ans << endl;
    }

    return 0;
}