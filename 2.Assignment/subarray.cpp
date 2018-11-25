/**********************************************************************
* Project           : Subarray
*
* Program name      : subarray.cpp
*
* Author            : Marco B. Grassler, Alexander Lerchbaumer
*
* Date created      : 2018-11-25
*
* Purpose           : Prints the number of subarrays having negative sums.
***********************************************************************/

#include <iostream>
#include <vector>

using namespace std;

long int SubArraySum(vector<int>, int);

int main()
{
    vector<int> arr = { 1, -2, 4, -5, 1 };
    cout << "Number of subarrays having negative sums: "
         << SubArraySum(arr, arr.size()) << endl;
    return 0;
}

long int SubArraySum(vector<int> arr, int n)
{
    int count = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += arr.at(j);
            if (sum < 0) {
                count++;
            }
        }
    }
    return count;
}
