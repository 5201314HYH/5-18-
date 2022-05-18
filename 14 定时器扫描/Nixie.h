#ifndef _NIXIE_H_
#define _NIXIE_H_

void Nixie(unsigned char num,number);//@11.0592MHz @0-65535

void Nixie_glint(unsigned char num);

//扫描显示0,
void Nixie_Time();   //定时器扫描数码管
//更改扫描显示
void Nixie_SetScan(unsigned char i,num);   //主函数用
#endif