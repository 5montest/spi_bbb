#include <stdio.h>
#include <time.h>

int sleep(int time)
{
    clock_t s = clock();
    clock_t c;

    do{
        if((c = clock()) == (clock_t)-1)
            return 0;
    }while(1000UL * (c - s) / CLOCKS_PER_SEC <= time);
    return 1;
}

int main(void)
{
    int num[3];
    num[0] = 1;
    num[1] = 2;
    num[2] = 3;
    num[3] = 4;

    sleep(1000);
    printf("%d%d%d%d\n",num[0],num[1],num[2],num[3]);
    return 0;
}

