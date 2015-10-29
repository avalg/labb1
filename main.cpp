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
            matrix[i][j] = round(distance);
            matrix[j][i] = round(distance);
        }
    }

/*    int hash[n];
    int totlegth = 0;
    int a = 0;
    int b = 1;
    while (b < n) {
        hash[a] = b;
        totlegth += matrix[a][b];
        a += 1;
        b += 1;
    }
    hash[n - 1] = 0;
    totlegth += matrix[n - 1][0];
    */
    int hash[n];
    bool used[n];
    used[0] = true;
    int index = 0;
    for (int c = 0;c<n-1;c++){
        int best = -1;
        cout << index << "i"<< endl;
        for (int j = 1; j< n; j++){
            if (!used[j] && (best == -1 || matrix[hash[index]][j] < matrix[hash[index]][best])) {
                best = j;
                cout << j << "j" << endl;
            }
            cout << j << " j utanför" <<endl;
        }
        hash[index] = best;
        used[best] = true;
        index = best;
        cout << best <<"best" <<endl;
    }
    hash[index]=0;

    int totlegth;
    int a = 0;
    while(a < n){
        totlegth = totlegth + matrix[a][hash[a]];
    }

    int r1;
    int r2;
    int swap;
    int newdist;
    int go = 0;
    int fu = 100;
    while (go < fu) {
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