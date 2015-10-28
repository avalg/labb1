//
// Created by Sara Feychting on 28-10-2015.
//

#include "main.h"

#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;

int main() {

    int n;
    cin >> n; //number of elements

    long x[n];
    long y[n];

    int i = 0;
    long temp;

    while (i < n) {
        cin >> temp;
        x[i] = temp;
        cin >> temp;
        y[i] = temp;
        i++;
    }

    //cout << x[n-1];
    //cout << y[n-1];

    int matrix[n][n];
    long distance;
    long xdist;
    long ydist;
    long sqrtval;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            xdist = x[i] - x[j];
            ydist = y[i] - y[j];
            //cout << pow(xdist, 2);
            sqrtval = (pow(xdist, 2) + pow(ydist, 2));
            distance = sqrt(sqrtval);
            matrix[i][j] = round(distance);
            matrix[j][i] = round(distance);
        }
    }

    int hash[n];
    int totlegth = 0;
    i = 0;
    int j = 1;
    while (j < n - 1) {
        hash[i] = j;
        totlegth += matrix[i][j];
        i = j + 1;
        hash[j] = i;
        totlegth += matrix[j][i];
        j = i + 1;
    }
    hash[n - 1] = 0;
    totlegth += matrix[n - 1][0];

    int r1;
    int r2;
    int swap;
    int newdist;
    int go = 0;
    int fu = n*n;
    while (go<fu) {
        go++;
        r1 = rand() % n;
        r2 = rand() % n;
        if (r1 == r2) continue;
        if (hash[r1] == r2) continue;
        swap = hash[r1];
        newdist = matrix[r2][swap] + matrix[swap][hash[r2]] + matrix[r1][hash[swap]]
              - matrix[r1][swap] - matrix[r2][hash[r2]];
        if (newdist < 0) {
        hash[r1] = hash[swap];
        hash[swap] = hash[r2];
        hash[r2] = swap;
    }
        totlegth += newdist;
    }
    int order[n];
    int counter = 0;
    int stop = hash[0];
    order[0] = counter;
    while(stop!=0) {
        counter++;
        order[stop]=counter;
        stop = hash[stop];
    }


    //TODO utskrifter
    //cout << matrix[n-1][n-2];
    for(int i = 0; i<n; i++){
        cout << order[i];
        cout << endl;
    }
};