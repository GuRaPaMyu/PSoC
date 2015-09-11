/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>
#include <stdio.h>

int readRE(void);

int main()
{
    CyGlobalIntEnable;      /* Enable global interrupts */
    UART_Start();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    int cnt = 0;
    char hoge[20];
    
    for(;;)
    {
        cnt += readRE();
        sprintf(hoge, "%d\r\n", cnt/2);
        UART_UartPutString(hoge);
    }
}

int readRE(void)
{
  static int RE_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static char RE_old = 0;               // 共通変数（値は保存）
  char RE_now;
  RE_now = Pin_1_Read() * 2 + Pin_2_Read();           // 今回情報の読取 
  RE_old <<= 2;                         // 前回の読取値と
  RE_old |= RE_now & 0x03;          // 今回の読取値を組合わせる
  return RE_states[RE_old & 0x0F];  // 変化分を戻り値をする
}