//
// Created by Sara Feychting and Katja Röös on 28-10-2015.
//
#include <iostream>
#include <cmath>
using namespace std;
int n;
long distm[1000][1000];

void opttwoandahalf(int *tour, int *points){
    srand(time(NULL));
    int loops = 1000000;
    for (int go = 0; go < loops; go++){
        /*int miss = 0;
        while(miss < (n)){*/
        int r1 = rand() % n;
        int r2 = rand() % n;
        //miss++;

        int swap = points[r1];
        if(swap == r2 || points[swap] == r2 || points[r2] == swap){
            continue;
        }

        long olddist = distm[r1][swap]+distm[swap][points[swap]]+distm[r2][points[r2]];
        long newdist = distm[r1][points[swap]]+distm[r2][swap]+distm[swap][points[r2]];

        if(newdist < olddist){
            //miss--;
            int temp = points[r2];
            points[r2] = swap;
            points[r1] = points[swap];
            points[swap] = temp;
        }
    }

    int v = 0;
    for (int i = 0; i < n; i++) {
        tour[i] = v;
        v = points[v];
    }
}

void twoOpt(int *tour, int *pointer){
    short r1 = rand() % n;
    short r2 = rand() % n;

    short ph1 = r1;
    short ph2 = r2;

    if(ph1 > ph2){
        short tmp = ph1;
        ph1 = ph2;
        ph2 = tmp;
    }

    short l = ph2- ph1;


    r1 = tour[r1];
    r2 = tour[r2];

    short oldDist1 = distm[r1][pointer[r1]];
    short oldDist2 = distm[r2][pointer[r2]];

    short newDist1 = distm[r1][r2];
    short newDist2 = distm[pointer[r2]][pointer[r1]];

    if((oldDist1+oldDist2)>(newDist1+newDist2)){
        short tmp;
        for(int i = 0; i < (l/2); i++){
            tmp = tour[ph1+1+i];
            tour[ph1+i+1] = tour[ph2-i];
            tour[ph2-i] = tmp;
        }

        pointer[r1] = r2;
        tmp = r2;
        for(int i = ph1; i < l+ph1; i++){
            pointer[tmp] = tour[i];
        }

    }
}

void shuffle(int *tour, int *points){

    int loops = 1;
    for (int go = 0; go < loops; go++){
        int r1 = rand() % n;
        int r2 = rand() % n;

        int swap = points[r1];
        if(swap == r2 || points[swap] == r2 || points[r2] == swap){
            continue;
        }

        int temp = points[r2];
        points[r2] = swap;
        points[r1] = points[swap];
        points[swap] = temp;
    }

    int v = 0;
    for (int i = 0; i < n; i++) {
        tour[i] = v;
        v = points[v];
    }
}

int lengthOfTour(int *tour){
    int length = distm[0][tour[n-1]];
    for(int i = 0;i < n-1; i++){
        length = length + distm[tour[i]][tour[i+1]];
    }
    return length;
}

int main() {
    srand(time(NULL));
    cin >> n; // number of elements

    double x[n];
    double y[n];

    //save x and y for every point.
    for(int i = 0; i < n; i++){
        cin >> x[i];
        cin >> y[i];
    }

    //build distmatrix
    double xdist;
    double ydist;
    for(int i = 0; i<n; i++){
        for(int j = 0; j<n; j++){
            xdist = x[i]-x[j];
            ydist = y[i] - y[j];

            distm[i][j] = round(sqrt(pow(xdist,2)+(pow(ydist,2))));
            //cout << distm[i][j] <<endl;
        }
    }


    //sort list the naive way
    int tour[n];
    bool used[n];

    int b = 0;
    while(b<n){
        used[b] = false;
        b++;
    }

    tour[0] = 0;
    used[0] = true;
    int best;
    for(int i = 1; i < n; i++){
        best = -1;
        for(int j = 0; j < n; j++){
            if(not used[j] and (best == -1 or (distm[tour[i-1]][j] < distm[tour[i-1]][best]))){
                best = j;
            }
        }
        tour[i] = best;
        used[best] = true;
    }
    //remake list to pointer list
    int points[n];
    for(int i = 0; i < n-1;i++ ){
        points[tour[i]] = tour[i+1];
        //cout << points[tour[i]] << " points" <<endl;
    }
    points[tour[n-1]] = 0;

    /*for(int i = 0; i<n; i++){
        cout <<points[i];
    }*/


    //implement 2-opt OBS do not use tour after this, its old

    opttwoandahalf(tour, points);
    int tmpTour[n];
    for(int i = 0; i <n ; i++){
        tmpTour[i] = tour[i];
    }
    int length1 = lengthOfTour(tour);
    //shuffle(tour, points);
    opttwoandahalf(tour,points);
    int length2 = lengthOfTour(tour);

    //cout << length1 << " " << length2 << endl;

    if(length1 > length2){
        for(int i = 0; i<n; i++){
            cout<<tmpTour[i]<<endl;
        }
    }
    else{
        for(int i = 0; i<n; i++){
            cout<<tour[i]<<endl;
        }
    }

}
