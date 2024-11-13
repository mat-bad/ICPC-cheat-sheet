//In the name of God.
#include <bits/stdc++.h>
using namespace std;

int r(int a, int b) {
    return rand() % (b - a + 1) + a;
}

int r(int n) {
    return rand() % n + 1;
}


int main() {
    int c;
	cin >> c;
    srand(c);
}