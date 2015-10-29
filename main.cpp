//
// Created by Sara Feychting on 28-10-2015.
//

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int main() {

    int n;
    cin >> n; //number of elements

    double x[n];
    double y[n];

    int i = 0;
    double temp;

    while (i < n) {
        cin >> temp;
        x[i] = temp;
        cin >> temp;
        y[i] = temp;
        i++;
    }

    //cout << x[n-1];
    //cout << y[n-1];

    long matrix[n][n];
    double distance;
    double xdist;
    double ydist;
    double xsqrt;
    double ysqrt;
    double sqrtval;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            xdist = x[i] - x[j];
            ydist = y[i] - y[j];
            xsqrt = pow(xdist, 2);
            ysqrt = pow(ydist, 2);
            sqrtval = xsqrt + ysqrt;
            distance = sqrt(sqrtval);
            //cout << "distance " << distance << endl;
            matrix[i][j] = round(distance);
            matrix[j][i] = round(distance);
        }
    }

    cout << "matrix 1 4" << matrix[0][3] << endl;
    cout << "matrix 2 4" << matrix[1][3] << endl;

    int tour[n];
    int best;
    bool used[n];
    tour[0]=0;
    used[0]= true;
    for(int i = 1; i < n; i++) {
        best = -1;
        for(int j = 1; j < n; j++) {
            if(!used[j] && (best==-1 || (matrix[tour[i-1]][j] < matrix[tour[i-1]][best]))) {
                best = j;
            }
        }
        tour[i]=best;
        used[best]=true;
    }
    cout << tour[1] << " : nr 1" << endl;
    int totlegth = 0;
    int hash[n];
    int tar = 0;
    for (int i = 1; i<n; i++) {
        hash[tar] = tour[i];
        totlegth += matrix[tar][tour[i]];
        tar = tour[i];
    }
    hash[tar]=0;
    totlegth += matrix[0][tar];
    cout << totlegth << " tot" << endl;

    int r1;
    int r2;
    int swap;
    int newdist;
    int go = 0;
    int fu = n;
    while (go<fu) {
        go++;
        r1 = rand() % n;
        r2 = rand() % n;
        if (r1 != r2 && hash[r1] != r2) {
            swap = hash[r1];
            newdist = matrix[r2][swap] + matrix[swap][hash[r2]] + matrix[r1][hash[swap]]
                                                                  - matrix[r1][swap] - matrix[r2][hash[r2]];
            if (newdist < 0) {
                cout << "new dist";
                hash[r1] = hash[swap];
                hash[swap] = hash[r2];
                hash[r2] = swap;
                totlegth += newdist;
            }
        }
    }
    cout << "new totlegth " << totlegth << endl;

    int order[n];
    int counter = 0;
    int target = 0;
    for (int counter = 0; counter < n; counter++) {
        order[target]=counter;
        target = hash[target];
    }
    for(int i = 0; i<n; i++){
        cout << order[i];
        cout << endl;
    }
};