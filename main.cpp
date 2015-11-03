//
// Created by Sara Feychting and Katja Röös on 28-10-2015.
//
#include <iostream>
#include <cmath>
using namespace std;
int n;
long distm[1000][1000];

void opttwoandahalf(int *tour, int *points){

    /*int miss = 0;
    while(miss < (n)){*/
    int r1 = rand() % n;
    int r2 = rand() % n;
    //miss++;

    int swap = points[r1];
    if(swap == r2 || points[swap] == r2 || points[r2] == swap){
        return;
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
    int v = 0;
    for (int i = 0; i < n; i++) {
        tour[i] = v;
        v = points[v];
    }
}

void twoOpt(int *tour, int *pointer){
    short r1 = rand() % n;
    short r2 = rand() % n;

    //cout << r1 << "r1 "<<endl;
    //cout << r2 << "r2 "<<endl;

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
        /*for(int i = 0; i <n; i++){
            cout<<i<<" points on "<<pointer[i]<<endl;
        }*/
        for(int i = 0; i < (l/2); i++){
            tmp = tour[ph1+1+i];
            tour[ph1+i+1] = tour[ph2-i];
            tour[ph2-i] = tmp;
        }
        /*for(int i = 0; i <n; i++){
            cout<<tour[i]<<" is on place "<<i<<endl;
        }*/
        /*tmp = tour[0];
        for(int i = 1; i < n; i++){
            pointer[tmp] = tour[i];
            tmp = tour[i];
        }
        pointer[tour[n-1]] = tour[0];
        */

        tmp = tour[ph1];
        for(int i = 0; i<=l+1; i++){
            pointer[tmp] = tour[i+ph1];
            tmp = tour[i+ph1];
        }
        pointer[tour[n-1]] = tour[0];



        /*for(int i = 0; i <n; i++){
            cout<<i<<" points on "<<pointer[i]<<endl;
        }*/
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
    short length = distm[0][tour[n-1]];
    for(int i = 0;i < n-1; i++){
        length = length + distm[tour[i]][tour[i+1]];
    }
    return length;
}

void twoAlgLoop(int *tour, int *points, int timer){
    short timeLeft = timer;
    short times = 10;
    //cout << timeLeft;
    while(timeLeft > 0) {
        for (
                short i = 0; i < times; i++) {
            twoOpt(tour, points);
        }

        for (
                short i = 0; i < times; i++) {
            opttwoandahalf(tour, points);
        }
        timeLeft = timeLeft - 1;
    }
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

    short timer = 7000;
    twoAlgLoop(tour, points, timer);

    //save the first tour
    int tmpTour[n];
    for(int i = 0; i <n ; i++){
        tmpTour[i] = tour[i];
    }
    int length1 = lengthOfTour(tour);

    shuffle(tour, points);

    twoAlgLoop(tour, points, timer);

    int length2 = lengthOfTour(tour);
    //cout << length1 << " " << length2 << endl;

    //print the result
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
