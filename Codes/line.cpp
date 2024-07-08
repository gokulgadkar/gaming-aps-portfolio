#include <iostream>
#include <vector>
#include <optional>

struct Point {
    double x, y;
};

double lerp(double A, double B, double t) {
    return A + (B - A) * t;
}

Point * getIntersection(const Point& A, const Point& B, const Point& C, const Point& D) {
    double tTop = (D.x - C.x) * (A.y - C.y) - (D.y - C.y) * (A.x - C.x);
    double uTop = (C.y - A.y) * (A.x - B.x) - (C.x - A.x) * (A.y - B.y);
    double bottom = (D.y - C.y) * (B.x - A.x) - (D.x - C.x) * (B.y - A.y);

    if (bottom != 0) {
        double t = tTop / bottom;
        double u = uTop / bottom;

        if (t >= 0 && t <= 1 && u >= 0 && u <= 1) {
            return new Point{lerp(A.x, B.x, t), lerp(A.y, B.y, t)};
        }
    }

    return NULL;
}

bool polysIntersect(const std::vector<Point>& poly1, const std::vector<Point>& poly2) {
    for (size_t i = 0; i < poly1.size(); ++i) {
        for (size_t j = 0; j < poly2.size(); ++j) {
            auto touch = getIntersection(
                poly1[i],
                poly1[(i + 1) % poly1.size()],
                poly2[j],
                poly2[(j + 1) % poly2.size()]
            );
            if (touch) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    std::vector<Point> poly1 = {{0, 0}, {2, 0}, {1, 2}};
    std::vector<Point> poly2 = {{1, 1}, {3, 1}, {3, 3}, {1, 3}};

    if (polysIntersect(poly1, poly2)) {
        std::cout << "Polygons intersect!" << std::endl;
    } else {
        std::cout << "Polygons do not intersect." << std::endl;
    }

    return 0;
}

