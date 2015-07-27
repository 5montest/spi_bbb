#include <stdio.h>
#include "wiringBBB.hpp"
#include <time.h>
//#include <unistd.h>
//#define SLEEP_TIME 1.7e-07
#define SLEEP_TIME 1


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
    int SCK = 66;
    int MOSI = 69;
    int MISO = 45;
    int SS1 = 23;
    int SS2 = 47;
    unsigned char writedata[7];
    unsigned char readdata[7];
    unsigned char raw_writedata;
    unsigned char raw_readdata;
    printf("Please raw_writedata:");
    scanf("%d",&raw_writedata);

    //raw_writedata = 0xaa;
    printf("Write_data=");
    print_bits(raw_writedata,8);
    putchar('\n');

    pinMode(SCK,OUTPUT);
    pinMode(MOSI,OUTPUT);
    pinMode(MISO,INPUT);
    pinMode(SS1,OUTPUT);
    pinMode(SS2,OUTPUT);

    digitalWrite(SCK,LOW);
    digitalWrite(SS1,HIGH);
    digitalWrite(SS2,HIGH);

    /*--------------------*/

    /*-----Write and Reads-----*/
    
  
    int i = 7,power_of_2 = 0x80;
    while(i != -1){
        writedata[i] = raw_writedata / power_of_2;
        raw_writedata -= writedata[i] * power_of_2;
        i--;
        power_of_2 /= 0x2;
    }
    
    digitalWrite(SS1,LOW);
    int n;
    for(int i=7;i >= 0;i--)
    {
        printf("writedata[%d]=%d\n",i,writedata[i]);
        printf("%d",writedata[i]);
    }
    puts("");
    while(true){
        for(n=7;n >= 0;n--)
        {
            digitalWrite(SCK,HIGH);
            if(writedata[n] == 1){
                digitalWrite(MOSI,HIGH);
             //   puts("\t\tHIGH");
            }
            else{
                digitalWrite(MOSI,LOW);
             //   puts("\t\tLOW");
            }

            sleep(SLEEP_TIME);

            digitalWrite(SCK,LOW);
            readdata[n] = digitalRead(MISO);

            if(readdata[n] == HIGH)
                readdata[n] == 1;
            else
                readdata[n] == 0;
            sleep(SLEEP_TIME);
        }
        digitalWrite(SS1,HIGH);

        printf("Read_data=");
        for(int i=7;i >= 0;i--)
        {
            printf("%d",readdata[i]);
        }
        puts("");

    }
    return 0;
}

