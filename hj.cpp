#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdlib>

long distances[1000][1000];
double x_vals[1000];
double y_vals[1000];
int n;

bool intersects(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    double k1 = dy / dx;
    double m1 = y1 - k1 * x1;

    dx = x4 - x3;
    dy = y4 - y3;
    double k2 = dy / dx;
    double m2 = y3 - k2 * x3;

    // parallel lines
    if (k1 == k2) {
        return false;
    }

    double x = (m2 - m1) / (k1 - k2);
    double y = m1 * x + m1;

    return x > x1 && x < x2 && y > y1 && y < y2;
}

/*
 * Solves the Euclidean Travelling Salesman Problem
 * outputs path solution in 'solution' array
 * */
void tsp(int *solution) {
    int next[1000];
    int prev[1000];

    bool visited[1000];
    for (int i = 0; i < n; i++) {
        visited[i] = false;
    }

    int c = 0;
    visited[c] = true;
    for (int i = 1; i < n; i++) {
        int best = -1;
        for (int j = 1; j < n; j++) {
            if (!visited[j] && (best == -1 || distances[c][j] < distances[c][best])) {
                best = j;
            }
        }

        next[c] = best;
        //std::cout<<next[c] << std::endl;
        prev[best] = c;
        visited[best] = true;
        c = best;
    }

    // path must be a cycle
    next[c] = 0;
    prev[0] = c;


    int iterations = n*4000;
    for (int i = 0; i < iterations; i++) {
        int v1 = rand() % n;
        int v2 = rand() % n;
        if (v1 == v2 || next[v1] == v2 || next[v2] == v1) {
            continue;
        }

        int v3 = prev[v1];

        int old_distances = distances[v1][next[v1]] + distances[v2][next[v2]] + distances[v3][next[v3]];
        int new_distances = distances[v1][next[v2]] + distances[v2][v1] + distances[v3][next[v1]];

        //std::cerr << v1 << " " << v2 << std::endl;
        //std::cerr << "oldDistance: " << old_distances << " " << "newDistance: " << new_distances << std::endl;

        if (new_distances < old_distances) {
            bool does_intersect = intersects(x_vals[v1], y_vals[v1], x_vals[next[v1]], y_vals[next[v1]],
                                             x_vals[v2], y_vals[v2], x_vals[next[v2]], y_vals[next[v2]]);
            if (does_intersect) {
                next[v3] = next[v1];
                prev[next[v1]] = v3;

                next[v1] = next[v2];
                prev[next[v2]] = v1;

                next[v2] = v1;
                prev[v1] = v2;
            }
        }

    }

    int v = 0;
    for (int i = 0; i < n; i++) {
        solution[i] = v;
        v = next[v];
    }
}

int main() {
    std::cin >> n;


    srand(time(NULL));

    for (int i = 0; i < n; i++) {
        double x, y;
        std::cin >> x;
        std::cin >> y;
        x_vals[i] = x;
        y_vals[i] = y;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            distances[i][j] = round(sqrt(pow(x_vals[i] - x_vals[j], 2) + pow(y_vals[i] - y_vals[j], 2)));
            //std::cout << distances[i][j]<< std::endl;
        }
    }

    int sol[1000];
    tsp(sol);

    for (int i = 0; i < n; i++) {
        std::cout << sol[i] << std::endl;
    }

    return 0;
}