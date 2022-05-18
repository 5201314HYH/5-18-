#include <REGX52.H>
void Delay(unsigned int ms)		//@11.0592MHz @0-65535
{
    unsigned int i,j;
    for(j=ms;j>0;j--)
    for(i=111;i>0;i--);
}
