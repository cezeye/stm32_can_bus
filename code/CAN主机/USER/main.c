
#include "stm32f10x.h"
#include "usart1.h"
#include "can.h"
#include "SysTick.h"
#include "LCD9325.h"
#include "stm32f10x_fsmc.h"
#include "delay.h"
__IO uint32_t flag1 = 0xff;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ
__IO uint32_t flag2 = 0xff;		 //���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ
CanTxMsg TxMessage;			     //���ͻ�����
CanRxMsg RxMessage;				 //���ջ�����

/*
 *  CAN ����źŵı�ʾ
 *  1:���Ե�ƽ   H2.5v - L2.5v = 0v
 *  0:���Ե�ƽ   H3.5v - L1.5v = 2v
 */

/* 
 * ��������main
 * ����  : "����"��������
 * ����  ����
 * ���  : ��
 */
 
int node1_humi; //���1ʪ��
int node1_temp; //���1�¶�
int node2_humi;
int node2_temp;

int main(void)
{
	
	/*��ʼ��SysTick��ʱ��*/
	 SysTick_Init();
	
  delay_init();
	
	/*��ʼ������ģ��*/
 	USART1_Config();
  
  //LCD��ʼ��	
	LCD_Init();
  GUI_Show();
	printf( "\r\n ���� �������ˡ� �ķ�����Ϣ�� \r\n");
	
  /* ����CANģ�� */
 	CAN_Config();
  while(1){
		int count=0;
	for( count=0;count<2;count++)
		{
 		
	/*����Ҫͨ��CAN���͵���Ϣ*/
	 CAN_SetMsg(0x1314);

//	 printf("\r\n��Ҫ���͵ı�������Ϊ��\r\n");
//	 printf("\r\n ��չID��ExtId��0x%x",TxMessage.ExtId);
//	 printf("\r\n ���ݶε�����:Data[0]=0x%x ��Data[1]=0x%x \r\n",TxMessage.Data[0],TxMessage.Data[1]);
	 			
	 /*������Ϣ ��ABCD��**/
	CAN_Transmit(CAN1, &TxMessage);
	 		
	while( flag1 == 0xff );					//flag1 =0 ,success
	node1_humi=RxMessage.Data[0];
  node1_temp=RxMessage.Data[1];
		LCD_ShowNum(165, 90,node1_humi, 5, 16);
		LCD_ShowNum(165, 70,node1_temp, 5, 16);
//	printf( "\r\n �ɹ����յ����ӻ�1�����ص�����\r\n ");	
//	printf("\r\n ���յ��ı���Ϊ��\r\n"); 
//	printf("\r\n ��չID��ExtId��0x%x",RxMessage.ExtId);				
	printf("\r\n ���ݶε�����:���1ʪ�� Data[0]=%d �����1�¶� Data[1]=%d\r\n",RxMessage.Data[0],RxMessage.Data[1]);
	
//	Delay_ms(1000);


		}
 count=0;
	for(count=0;count<2;count++)
		{
	/*����Ҫͨ��CAN���͵���Ϣ*/
	 CAN_SetMsg(0x1315);

//	 printf("\r\n��Ҫ���͵ı�������Ϊ��\r\n");
//	 printf("\r\n ��չID��ExtId��0x%x",TxMessage.ExtId);
//	 printf("\r\n ���ݶε�����:Data[0]=0x%x ��Data[1]=0x%x \r\n",TxMessage.Data[0],TxMessage.Data[1]);
	 			
	 /*������Ϣ ��ABCD��**/
	CAN_Transmit(CAN1, &TxMessage);
	//Delay_ms(200); 		
	while( flag2 == 0xff );					//flag2 =0 ,success
  node2_humi=RxMessage.Data[0];
  node2_temp=RxMessage.Data[1];
  LCD_ShowNum(165, 175,node2_humi, 5, 16);
	LCD_ShowNum(165, 155,node2_temp, 5, 16);
//	printf( "\r\n �ɹ����յ����ӻ�2�����ص�����\r\n ");	
//	printf("\r\n ���յ��ı���Ϊ��\r\n"); 
//	printf("\r\n ��չID��ExtId��0x%x",RxMessage.ExtId);	 
	printf("\r\n ���ݶε�����:���2ʪ�� Data[0]=%d �����2�¶� Data[1]=%d\r\n",RxMessage.Data[0],RxMessage.Data[1]);
		
//  Delay_ms(1000);



	}	
	
 }
	
}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/


