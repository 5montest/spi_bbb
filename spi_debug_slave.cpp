#include <stdio.h>
#include "wiringBBB.hpp"
// #include <time.h>
#include <unistd.h>
#define SLEEP_TIME 1.7e-07

/*
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

*/


/*-----2sinsuu-----*/

int count_bits(unsigned x)
{
    int count = 0;
    while (x){
        if (x & 1U) count++;
        x >>= 1;
    }
    return (count);
}

int int_bits(void)
{
    return (count_bits(~0U));
}

int print_bits(unsigned x,unsigned n)
{
    int i = int_bits();
    i = (n < i) ? n -1 : i - 1;
    for ( ; i >= 0; i--)
        putchar(((x >> i) & 1U) ? '1' : '0');
}

/*-------------*/

int main(void)
{
    /*--spi_setup--*/
    int SCK = 30;
    int MOSI = 31;
    int MISO = 48;
    int SS1 = 3;
    unsigned char Writedata[7];
    unsigned char Readdata[7];
    unsigned char write_data;
    unsigned char read_data;
    // scanf("%d",&write_data);

    write_data = 0b00001111;
    printf("Write_data=");
    print_bits(write_data,8);
    putchar('\n');

    pinMode(SCK,INPUT);
    pinMode(MOSI,INPUT);
    pinMode(MISO,OUTPUT);
    pinMode(SS1,INPUT);

    /*-----Write and Reads-----*/
    
    Writedata[0] = write_data & 0b10000000 >> 7;
    Writedata[1] = write_data & 0b01000000 >> 6;
    Writedata[2] = write_data & 0b00100000 >> 5;
    Writedata[3] = write_data & 0b00010000 >> 4;
    Writedata[4] = write_data & 0b00001000 >> 3;
    Writedata[5] = write_data & 0b00000100 >> 2;
    Writedata[6] = write_data & 0b00000010 >> 1;
    Writedata[7] = write_data & 0b00000001;
    
    int n;

    while(digitalRead(SS1) == LOW){
        for(n=7;n >= 0;n--){
            while(digitalRead(SCK) == LOW){
            }
            if(Writedata[n] == 1)
                digitalWrite(MISO,HIGH);
            else
                digitalWrite(MISO,LOW);
            while(digitalRead(SCK) == HIGH){
            }
            Readdata[n] = digitalRead(MOSI);

            if(Readdata[n] = HIGH)
                Readdata[n] == 1;
            else
                Readdata[n] == 0;
        }

        printf("Read_data=");
        for(int i=7;i >= 0;i--)
        {
            printf("%d",Readdata[i]);
        }
        puts("");

    }
    return 0;
}

