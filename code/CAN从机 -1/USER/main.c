/******************** (C) COPYRIGHT 2012 WildFire Team **************************
 * �ļ���  ��main.c
 * ����    ��˫CANͨѶʵ�飬�����������֣���ӻ�����ABCD         
 * ʵ��ƽ̨��Ұ��STM32������
 * ��汾  ��ST3.5.0
 *
 * ����    ��wildfire team 
 * ��̳    ��http://www.amobbs.com/forum-1008-1.html
 * �Ա�    ��http://firestm32.taobao.com
**********************************************************************************/
#include "stm32f10x.h"
#include "usart1.h"
#include "can.h"
#include "SysTick.h"
#include "DHT11.h"

DHT11_Data_TypeDef DHT11_Data;

__IO uint32_t flag = 0xff;		//���ڱ�־�Ƿ���յ����ݣ����жϺ����и�ֵ
CanTxMsg TxMessage;			    //���ͻ�����
CanRxMsg RxMessage; 			//���ջ�����

/* 
 * ��������main
 * ����  : ���ӻ�����������
 * ����  ����
 * ���  : ��
 */
int main(void)
{
	 /*��ʼ��SysTick��ʱ��*/
	 SysTick_Init();
	
	/* USART1 config */
	USART1_Config();
	
	/*��ʼ��DTT11������*/
	 DHT11_GPIO_Config(); 
	/* ����CANģ�� */
	CAN_Config();

	while(1){
		
	printf( "\r\n ���� ���ӻ���1�� �ķ�����Ϣ�� \r\n"); 
	while(1){
		Delay_ms(200);
	/*�ȴ������˵�����*/	
	while( flag == 0xff );
	printf( "\r\n �ɹ����յ������������ص�����\r\n ");	
	printf("\r\n ���յ��ı���Ϊ��\r\n"); 
	printf("\r\n ��չID��ExtId��0x%x",RxMessage.ExtId);	 
	printf("\r\n ���ݶε�����:Data[0]= 0x%x ��Data[1]=0x%x \r\n",RxMessage.Data[0],RxMessage.Data[1]);					

	//	///*����Read_DHT11��ȡ��ʪ�ȣ����ɹ����������Ϣ*/
	if(Read_DHT11(&DHT11_Data)==SUCCESS)										 //��\����ʾת��һ����
		printf("\r\n��ȡDHT11�ɹ�!\r\n\r\nʪ��Ϊ%d.%d ��RH ���¶�Ϊ %d.%d�� \r\n", 	DHT11_Data.humi_int,DHT11_Data.humi_deci,DHT11_Data.temp_int,DHT11_Data.temp_deci);
	else
		printf("Read DHT11 ERROR!\r\n");		
	/*����Ҫͨ��CAN���͵���Ϣ*/ 
	 CAN_SetMsg(DHT11_Data.humi_int,DHT11_Data.temp_int);			

	 printf("\r\n��Ҫ���͵ı�������Ϊ��\r\n");
	 printf("\r\n ��չID��ExtId��0x%x",TxMessage.ExtId);
	 printf("\r\n ���ݶε�����:Data[0]=%d ��Data[1]=%d \r\n",TxMessage.Data[0],TxMessage.Data[1]);
//	/*������Ϣ ��CDAB��**/
	CAN_Transmit(CAN1, &TxMessage);	
	Delay_ms(100);	

	
		
		


  	
		
  }
	
	}


}
/******************* (C) COPYRIGHT 2012 WildFire Team *****END OF FILE************/











