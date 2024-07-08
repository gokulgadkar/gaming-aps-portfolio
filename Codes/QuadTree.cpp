#include <iostream>
#include <vector>

using namespace std;


class Point {
public:
    double x;
    double y;

    Point(double x, double y) : x(x), y(y)
    {}

    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y);
    }
};

class Rectangle {
public:
    double x, y, width, height;

    Rectangle(double x, double y, double width, double height)
        : x(x), y(y), width(width), height(height) {}

    bool contains(const Point &point) const {
        return (point.x >= x - width &&
                point.x <= x + width &&
                point.y >= y - height &&
                point.y <= y + height);
    }

    bool intersects(const Rectangle &range) const {
        return !(range.x - range.width > x + width ||
                 range.x + range.width < x - width ||
                 range.y - range.height > y + height ||
                 range.y + range.height < y - height);
    }
};


class Quadtree {
private:
    Rectangle boundary;
    int capacity;
    vector<Point> points;
    bool divided;


    Quadtree *northeast;
    Quadtree *northwest;
    Quadtree *southeast;
    Quadtree *southwest;

    void subdivide() {
        double x = boundary.x;
        double y = boundary.y;
        double w = boundary.width / 2;
        double h = boundary.height / 2;

        northeast = new Quadtree(Rectangle(x + w, y - h, w, h), capacity);
        northwest = new Quadtree(Rectangle(x - w, y - h, w, h), capacity);
        southeast = new Quadtree(Rectangle(x + w, y + h, w, h), capacity);
        southwest = new Quadtree(Rectangle(x - w, y + h, w, h), capacity);

        divided = true;
    }

public:
    Quadtree(Rectangle boundary, int capacity)
        : boundary(boundary), capacity(capacity), divided(false),
          northeast(nullptr), northwest(nullptr),
          southeast(nullptr), southwest(nullptr) {}

    ~Quadtree() {
        delete northeast;
        delete northwest;
        delete southeast;
        delete southwest;
    }

    bool insert(Point point) {
        if (!boundary.contains(point)) {
            return false;
        }

        if (points.size() < capacity) {
            points.push_back(point);
            return true;
        } else {
            if (!divided) {
                subdivide();
            }

            if (northeast->insert(point)) return true;
            if (northwest->insert(point)) return true;
            if (southeast->insert(point)) return true;
            if (southwest->insert(point)) return true;
        }

        return false;
    }

    void query(Rectangle range, vector<Point> &found) {
        if (!boundary.intersects(range)) {
            return;
        }

        for (const auto &point : points) {
            if (range.contains(point)) {

                found.push_back(point);
            }
        }

        if (divided) {
            northeast->query(range, found);
            northwest->query(range, found);
            southeast->query(range, found);
            southwest->query(range, found);
        }
    }
    void show() const {
        cout << "Boundary: (" << boundary.x << ", " << boundary.y << ", "
                  << boundary.width << ", " << boundary.height << ")\n";
        for (const auto &point : points) {
            cout << "Point: (" << point.x << ", " << point.y << ")\n";
        }
        if (divided) {
            northeast->show();
            northwest->show();
            southeast->show();
            southwest->show();
        }
    }
};

int main() {
    Rectangle boundary(0, 0, 200, 200);
    Quadtree qt(boundary, 4);

    qt.insert(Point(-50, -50));
    qt.insert(Point(-190, -190));
    qt.insert(Point(50, -50));
    qt.insert(Point(-50, 50));
    qt.insert(Point(50, 50));
    qt.insert(Point(0, 0));

    vector<Point> found;
    Rectangle range(0, 0, 100, 100);
    qt.query(range, found);

    cout << "Points within range (" << range.x << ", " << range.y << ", "
              << range.width << ", " << range.height << "):\n";
    for (const auto &point : found) {
        cout << "(" << point.x << ", " << point.y << ")\n";
    }

    cout << "How quadtree stores info\n";
    qt.show();

    return 0;
}

