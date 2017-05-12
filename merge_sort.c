#include <stdio.h>
#define max 3

int global_PULSE[4]     = {4,3,2,1};
int order[4]            = {0,1,2,3};
int buffer[4]           = {0,0,0,0};
int buffer2[4]          = {0,0,0,0};

void merging(int low, int mid, int high) {
    int l1, l2, i;


    for(l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++) {
        if(global_PULSE[l1] <= global_PULSE[l2])
        {
            buffer[i] = global_PULSE[l1];
            buffer2[i] = order[l1];
            l1++;
        }
        else
        {
            buffer[i] = global_PULSE[l2];
            buffer2[i] = order[l2];
            l2++;
        }
    }

    while(l1 <= mid)
    {
        buffer[i] = global_PULSE[l1];
        buffer2[i]= order[l1];
        i++;l1++;
    }
    while(l2 <= high)
    {
        buffer[i] = global_PULSE[l2];
        buffer2[i] = order[l2];
        i++;l2++;
    }

    for(i = low; i <= high; i++)
    {
        global_PULSE[i] = buffer[i];
        order[i] = buffer2[i];
    }
}

void sort(int low, int high) {
    int mid;

    if(low < high)
    {
        mid = (low + high) / 2;
        sort(low, mid);
        sort(mid+1, high);
        merging(low, mid, high);
   }
   else
   {
      return;
   }
}

int main() {
    int i = 0;


    printf("List before sorting\n");


    for(i = 0; i <= max; i++)
        printf("%d ", global_PULSE[i]);
    printf("\n");
    for(i = 0; i <= max; i++)
        printf("%d ", order[i]);



    sort(0, max);

    printf("\n\n\nList after sorting\n");

    for(i = 0; i <= max; i++)
        printf("%d ", global_PULSE[i]);
    printf("\n");
    for(i = 0; i <= max; i++)
        printf("%d ", order[i]);

    printf("\n");
}
