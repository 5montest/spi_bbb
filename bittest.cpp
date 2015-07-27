#include <stdio.h>

int main(){

    int raw  = 0xa;

    int num[3];
    num[0] = raw / 0x8;
    raw -= num[0] * 0x8;
    num[1] = raw / 0x4;
    raw -= num[1] * 0x4;
    num[2] = raw / 0x2;
    raw -= num[2] * 0x2;
    num[3] = raw;

    for(int i=0;i < 4;i++){

        printf("%d",num[i]);
    }

    return 0;
    
}



