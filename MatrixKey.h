#ifndef _MATRIXKEY_H_
#define _MATRIXKEY_H_


unsigned char MatrixKey();   //定时器扫描到后返回
unsigned char MatrixKey_Private();  //定时器扫描私有函数
void MK_TimerScan();   //定时器扫描判断是否按下

#endif