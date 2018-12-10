/**********************************************************************
* Project           :       Attending Workshops
*
* Program name      :       attendingWorkshops.cpp
*
* Author            :       Marco B. Grassler, Alexander Lerchbaumer
*
* Date created      :       2018-12-10
*
* Purpose           :       A student signed up for workshops and wants to attend the maximum number of workshops where no two workshops overlap
*
* Input             :       Number of courses
*                               Start time of course
*                               Duration of course
*
* Output            :       Number of courses the student can attend
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

struct Workshops {
    int s, d, e;
};

struct Available_Workshops {
    int n;
    Workshops* shops;
    Available_Workshops(int t)
    {
        n = t;
        shops = (Workshops*)malloc(t * sizeof(Workshops));
    }
};

bool comp(const Workshops& a, const Workshops& b)
{
    if (a.e < b.e)
        return true;
    return false;
}

int comp1(const void* ap, const void* bp)
{
    Workshops* a = (Workshops*)ap;
    Workshops* b = (Workshops*)bp;

    return (a->e - b->e);
}

Available_Workshops* initialize(int start_time[], int duration[], int N)
{
    Available_Workshops* node = new Available_Workshops(N);
    for (int i = 0; i < node->n; i++) {
        (node->shops)[i].s = start_time[i];
        (node->shops)[i].d = duration[i];
        (node->shops)[i].e = start_time[i] + duration[i];
    }
    return node;
}

int CalculateMaxWorkshops(Available_Workshops* ptr)
{
    qsort(ptr->shops, ptr->n, sizeof(Workshops), comp1);
    int ans = 1, t;
    for (int i = 0; i < ptr->n; i++) {
        if (i == 0) {
            t = (ptr->shops[i]).e;
            continue;
        }
        if ((ptr->shops[i]).s >= t) {
            ans++;
            t = (ptr->shops[i]).e;
        }
    }
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    int start_time[n], duration[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &start_time[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &duration[i]);
    }

    Available_Workshops* ptr;
    ptr = initialize(start_time, duration, n);
    printf("%d\n", CalculateMaxWorkshops(ptr));

    return 0;
}
