#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Point {
public:
    double x;
    double y;
    int priority;

    Point(double x, double y, int priority) : x(x), y(y), priority(priority) {}

    bool operator<(const Point& other) const {
        return priority < other.priority;
    }
    bool operator>(const Point& other) const {
        return priority > other.priority;
    }

    bool operator==(const Point& other) const {
        return (x == other.x && y == other.y && priority == other.priority);
    }
};

// Define a 2D Rectangle (used for the bounding box and query range)
class Rectangle {
public:
    double x, y, width, height;

    Rectangle(double x, double y, double width, double height)
        : x(x), y(y), width(width), height(height) {}

    // Methods
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


class PriorityVector {
private:
    vector<Point> data;

public:
    void push(const Point& point) {
        data.push_back(point);
        push_heap(data.begin(), data.end(), greater<Point>());
    }

    void pop() {
        pop_heap(data.begin(), data.end(), greater<Point>());
        data.pop_back();
    }


    const Point& top() const {
        return data.front();
    }
    const Point& bottom() const {
        return data.back();
    }

    bool empty() const {
        return data.empty();
    }

    size_t size() const {
        return data.size();
    }

    const vector<Point>& get_data() const {
        return data;
    }
};

class Quadtree {
private:
    Rectangle boundary;
    int capacity;
    PriorityVector points;
    bool divided;

    // Children
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
            points.push(point);
            return true;
        } else {
            if (!divided) {
                subdivide();
            }

            // If the new point has higher priority than the lowest priority point in this node
            if (point > points.top()) {
                Point lowest = points.top();
                points.pop();
                points.push(point);



                // Move the lowest priority point to a child node
                if (northeast->insert(lowest)) return true;
                if (northwest->insert(lowest)) return true;
                if (southeast->insert(lowest)) return true;
                if (southwest->insert(lowest)) return true;
            } else {
                // Insert the new point into a child node
                if (northeast->insert(point)) return true;
                if (northwest->insert(point)) return true;
                if (southeast->insert(point)) return true;
                if (southwest->insert(point)) return true;
            }
        }

        return false;
    }

    void query(Rectangle range, vector<Point> &found) {
        if (!boundary.intersects(range)) {
            return;
        }

        for (const auto& point : points.get_data()) {
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

        for (const auto& point : points.get_data()) {
            cout << "Point: (" << point.x << ", " << point.y << "), Priority: " << point.priority << "\n";
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

    qt.insert(Point(-50, 50, 4));
    qt.insert(Point(50, 50, 5));

    qt.insert(Point(50, -50, 3));

    qt.insert(Point(0, 0, 6));
    qt.insert(Point(-50, -50, 1));
    qt.insert(Point(-190, -190, 2));

    vector<Point> found;
    Rectangle range(0, 0, 100, 100);
    qt.query(range, found);

    cout << "Points within range (" << range.x << ", " << range.y << ", "
         << range.width << ", " << range.height << "):\n";
    for (const auto &point : found) {
        cout << "(" << point.x << ", " << point.y << "), Priority: " << point.priority << "\n";
    }

    cout << "Quadtree structure:\n";
    qt.show();

    return 0;
}
