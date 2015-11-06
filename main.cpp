//
// Created by Sara Feychting and Katja Röös on 28-10-2015.
//
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

int n;
long distm[1000][1000];
double x[1000];
double y[1000];
short tour[1000];
short finalTour[1000];
int a;
int b;
void buildMatrix(){
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

}
void greedyTour(){
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

};

int lengthOfTour(short *tour){
    short length = distm[0][tour[n-1]];
    for(int i = 0;i < n-1; i++){
        length = length + distm[tour[i]][tour[i+1]];
    }
    return length;
}
void swapIt() {
    int l = (b-a)/2;
    int tmp;
    for(int i = 0; i < l; i++){
        tmp = tour[a+1+i];
        tour[a+1+i] = tour[b-i];
        tour[b-i] = tmp;
    }
}
void shuffle(){
    //cout<< "plats1"<<endl;
    clock_t start;
    double runtime = 0;

    start = clock();

    while(runtime < 10) {
        a = rand() % n;
        int le;
        if (a > 0) {
            le = n / a;
        } else {
            le = 1;
        }
        for (int i = 0; i < le; i++) {
            a = rand() % n;
            b = n-a-1;//rand() % n;
            if ((a + 1) == b || a == b || (a + 1) == b) {
                return;
            }
            swapIt();
        }
        runtime = ( clock() - start )/ (double)(CLOCKS_PER_SEC / 1000);
    }
}
void twoPointFiveOpt(){
    double finalTourDistance = lengthOfTour(tour);
    double currentTourDistance;
    memcpy(tour, finalTour, n* sizeof(short));

    clock_t start;
    double runtime = 0;

    start = clock();

    while(runtime < 50){
        int r1 = rand() % n;
        int r2 = rand() % n;
        //cout << " r1 "<<r1<<" r2 "<<r2<<endl;

        if((r1+1) == r2 || r1==r2 || (r2+1)==r1){
            return;
        }
        long olddist = distm[tour[r1]][tour[r1+1]]+distm[tour[r2]][tour[r2-1]]+distm[r2][tour[r2+1]];
        long newdist = distm[tour[r1]][tour[r2]]+distm[tour[r2]][tour[r1+1]]+distm[tour[r2-1]][tour[r2+1]];

        if(newdist < olddist){
            //cout << " r1 "<<r1<<" r2 "<<r2<<endl;
            /*for(int i = 0; i <n ; i++ ){
                cout<< tour[i];
            }
            cout<<endl;*/
            if (r1>r2) {
                int tmp = r1;
                r1 = r2;
                r2 = tmp;
                /*int tmp = r2;
                for (int i = r2; i<r1; i++) {
                    tour[i] = tour[i+1];
                }
                tour[r1] = tmp;
                cout<< "r1 > r2"<< endl;*/
            }
            //else {
            int temp = tour[r2];
            for (int i = r2; i > r1 + 1; i--) {
                tour[i] = tour[i - 1];
            }
            tour[r1 + 1] = temp;
            //cout<< "r2 > r1"<< endl;
            //}
        }
        runtime = ( clock() - start )/ (double)(CLOCKS_PER_SEC / 1000);
    }
    memcpy(finalTour, tour, n* sizeof(short));


}


void twoOpt(){

    memcpy(finalTour, tour, n* sizeof(short));
    double finalTourDistance = lengthOfTour(tour);
    bool swapped;
    double currentTourDistance;

    clock_t start;
    double runtime;

    start = clock();

    while (runtime < 100) {
        swapped = false;
        for (int i = 0; i < (n-1); i++) {
            for (int j = i+1; j < (n-1); j++) {
                double oldDistance =  distm[tour[i]][tour[i+1]] + distm[tour[j]][tour[j+1]];
                double newDistance =  distm[tour[i]][tour[j]] + distm[tour[j+1]][tour[i+1]];
                if (newDistance < oldDistance) {
                    // make swap
                    a = i;
                    b = j;
                    swapIt();
                    swapped = true;
                    //cout<< "plats3"<<endl;
                }
            }
        }
        runtime = ( clock() - start )/ (double)(CLOCKS_PER_SEC / 1000);
        if (!swapped) {
            currentTourDistance = lengthOfTour(tour);
            if (currentTourDistance < finalTourDistance) {
                memcpy(finalTour, tour, n* sizeof(short));
                finalTourDistance = currentTourDistance;
                //cout<< "plats5"<<endl;
            }
            shuffle();
        }
    }
    if ((currentTourDistance = lengthOfTour(tour)) < finalTourDistance) {
        memcpy(finalTour, tour, n*sizeof(short));
        finalTourDistance = currentTourDistance;
        //cout<< "plats1"<<endl;
    }
    //cout << finalTourDistance << endl;
}

int main() {

    cin >> n; // number of elements

    //save x and y for every point.
    for(int i = 0; i < n; i++){
        cin >> x[i];
        cin >> y[i];
    }

    buildMatrix();
    greedyTour();
    memcpy(finalTour, tour, n* sizeof(short));

    clock_t start;
    double runtime;
    start = clock();

    while(runtime <1200) {
        twoOpt();
        twoPointFiveOpt();
        runtime = ( clock() - start )/ (double)(CLOCKS_PER_SEC / 1000);
    }

    for(int i = 0; i<n; i++){
        cout<<finalTour[i]<<endl;
    }

}