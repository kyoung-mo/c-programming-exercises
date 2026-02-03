#include <stdio.h>
#include <stdint.h>
#define MAX 100

typedef struct 
{
    uint32_t addr;
    char text[MAX];
    int size;

}SensorData;

void hexdump();
    
int main(){

    // 테스트 1: 단순 문자열 
    char my_text[] = "Hello Embedded World! This is Hexdump.";
    hexdump("String Dump", my_text, sizeof(my_text));
  
    // 테스트 2: 구조체 (엔디안 확인 가능)
    SensorData sensor = { 0x12345678, "Sensor A", 3.14f };
    hexdump("Struct Dump", &sensor, sizeof(sensor));


    return 0;
}

void hexdump(char str[12], unsigned char* addr, int size){
    printf("%s:\n",str);

    uint16_t line=0x0000;
    int count=0;
    for(int cnt=0;cnt<size;cnt+=16)
    {
        printf("  %04x  ",line);

        int bytes_left = size - count;
        int print_count = bytes_left < 16 ? bytes_left : 16;
        
        for(int i=0;i<print_count;i++)
        {
            printf("%02x ",addr[i+count]);
        }
        
        printf(" ");
        
        for(int i=0;i<print_count;i++){
            unsigned char c = addr[i+count];
            if(c >= 0x20 && c <= 0x7E)
                printf("%c", c);
            else
                printf(".");
        }
        printf("\n");
        line+=0x0010;
        count+=16;
    }

}