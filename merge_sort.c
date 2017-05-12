#include <stdio.h>
#define max 3

int global_PULSE[4]     = {4,3,2,1};
int order[4]            = {0,1,2,3};
int buffer[4]           = {0,0,0,0};
int buffer2[4]          = {0,0,0,0};

void merging(int *copy, int low, int mid, int high) {
    int l1, l2, i;


    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
        if(copy[l1] <= copy[l2])
        {
            buffer[i] = copy[l1];
            buffer2[i] = order[l1];
            l1++;
        }
        else
        {
            buffer[i] = copy[l2];
            buffer2[i] = order[l2];
            l2++;
        }
    }

    while(l1 <= mid)
    {
        buffer[i] = copy[l1];
        buffer2[i]= order[l1];
        i++;l1++;
    }
    while(l2 <= high)
    {
        buffer[i] = copy[l2];
        buffer2[i] = order[l2];
        i++;l2++;
    }

    for(i = low; i <= high; i++)
    {
        copy[i] = buffer[i];
        order[i] = buffer2[i];
    }
}

void sort(int *copy, int low, int high) {
    int mid;

    if(low < high)
    {
        mid = (low + high) / 2;
        sort(copy, low, mid);
        sort(copy, mid+1, high);
        merging(copy, low, mid, high);
   }
   else
   {
      return;
   }
}

int main() {
    int i = 0;


    printf("List before sorting\n");
    int copy[4]     = {4,3,2,1};

    for(i = 0; i <= max; i++)
        printf("%d ", copy[i]);
    printf("\n");
    for(i = 0; i <= max; i++)
        printf("%d ", order[i]);



    sort(copy,0, max);

    printf("\n\n\nList after sorting\n");

    for(i = 0; i <= max; i++)
        printf("%d ", copy[i]);
    printf("\n");
    for(i = 0; i <= max; i++)
        printf("%d ", order[i]);

    printf("\n");
}
