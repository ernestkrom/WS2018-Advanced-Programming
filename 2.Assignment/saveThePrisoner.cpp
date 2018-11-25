/**********************************************************************
* Project           : Save the Prisoner!
*
* Program name      : saveThePrisoner.cpp
*
* Author            : Marco B. Grassler, Alexander Lerchbaumer
*
* Date created      : 2018-11-25
*
* Purpose           : Prints the ID number of the prisoner who receives the poisoned sweet.
***********************************************************************/

#include <iostream>

using namespace std;

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        int n, m, s;
        cin >> n >> m >> s;
        cout << (m - 1 + s - 1) % n + 1 << "\n";
    }
    return 0;
}
