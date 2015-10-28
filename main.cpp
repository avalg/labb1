//
// Created by Sara Feychting on 28-10-2015.
//

#include "main.h"

#include <iostream>
using namespace std;

int main() {

    int n;
    cin >> n; //number of elements

    int x[n];
    int y[n];

    int i = 0;
    int temp;

    while(i<n) {
        cin >> temp;
        x[i] = temp;
        cin >> temp;
        y[i] = temp;
        i++;
    }

    cout << x[n-1];

};