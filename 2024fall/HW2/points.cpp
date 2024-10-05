#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

struct Point {
    int x, y;
};

bool compareX(const Point &p1, const Point &p2) {
    return p1.x < p2.x;
}

bool compareY(const Point &p1, const Point &p2) {
    return p1.y < p2.y;
}

double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}

double closestPair(vector<Point> &points, int left, int right) {
    if (right - left <= 3) {
        double min_dist = numeric_limits<double>::max();
        for (int i = left; i < right; ++i) {
            for (int j = i + 1; j < right; ++j) {
                min_dist = min(min_dist, distance(points[i], points[j]));
            }
        }
        return min_dist;
    }

    int mid = left + (right - left) / 2;
    double mid_x = points[mid].x;

    double d_left = closestPair(points, left, mid);
    double d_right = closestPair(points, mid, right);
    double d = min(d_left, d_right);

    vector<Point> strip;
    for (int i = left; i < right; ++i) {
        if (abs(points[i].x - mid_x) < d) {
            strip.push_back(points[i]);
        }
    }

    sort(strip.begin(), strip.end(), compareY);

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < d; ++j) {
            d = min(d, distance(strip[i], strip[j]));
        }
    }

    return d;
}

int main() {
    int n;
    cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y;
    }

    sort(points.begin(), points.end(), compareX);

    double min_distance = closestPair(points, 0, n);

    cout << fixed << setprecision(4) << min_distance << endl;

    return 0;
}
