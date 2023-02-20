/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library ����RT1064DVL6A ��Դ�⣩��һ�����ڹٷ� SDK �ӿڵĵ�������Դ��
* Copyright (c) 2022 SEEKFREE ��ɿƼ�
* 
* ���ļ��� RT1064DVL6A ��Դ���һ����
* 
* RT1064DVL6A ��Դ�� ��������
* �����Ը��������������ᷢ���� GPL��GNU General Public License���� GNUͨ�ù������֤��������
* �� GPL �ĵ�3�棨�� GPL3.0������ѡ��ģ��κκ����İ汾�����·�����/���޸���
* 
* ����Դ��ķ�����ϣ�����ܷ������ã�����δ�������κεı�֤
* ����û�������������Ի��ʺ��ض���;�ı�֤
* ����ϸ����μ� GPL
* 
* ��Ӧ�����յ�����Դ���ͬʱ�յ�һ�� GPL �ĸ���
* ���û�У������<https://www.gnu.org/licenses/>
* 
* ����ע����
* ����Դ��ʹ�� GPL3.0 ��Դ���֤Э�� �����������Ϊ���İ汾
* �������Ӣ�İ��� libraries/doc �ļ����µ� GPL3_permission_statement.txt �ļ���
* ���֤������ libraries �ļ����� �����ļ����µ� LICENSE �ļ�
* ��ӭ��λʹ�ò����������� ���޸�����ʱ���뱣����ɿƼ��İ�Ȩ����������������
* 
* �ļ�����          main
* ��˾����          �ɶ���ɿƼ����޹�˾
* �汾��Ϣ          �鿴 libraries/doc �ļ����� version �ļ� �汾˵��
* ��������          IAR 8.32.4 or MDK 5.33
* ����ƽ̨          RT1064DVL6A
* ��������          https://seekfree.taobao.com/
* 
* �޸ļ�¼
* ����              ����                ��ע
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"

// ���µĹ��̻��߹����ƶ���λ�����ִ�����²���
// ��һ�� �ر��������д򿪵��ļ�
// �ڶ��� project->clean  �ȴ��·�����������

// �������ǿ�Դ����ֲ�ÿչ���



int main(void)
{
    clock_init(SYSTEM_CLOCK_600M);  // ����ɾ��
    debug_init();                   // ���Զ˿ڳ�ʼ��

    gpio_init(B9,GPO,0,GPO_PUSH_PULL);
    // �˴���д�û����� ���������ʼ�������
    func_soft_delay(300);
		tft180_init();
		tft180_show_string (0, 0, "TFT180 Init!");
		if(mpu6050_init()){tft180_show_string (0, 0, "MPU6050 Init Failure");}	
		else tft180_show_string (0, 0, "MPU6050 Init OK");
    // �˴���д�û����� ���������ʼ�������
    while(1)
    {
        gpio_set_level(B9,1);
        system_delay_ms(100);
        gpio_set_level(B9,0);
        system_delay_ms(100);
        // gpio_set_level(B9,1)
        // �˴���д��Ҫѭ��ִ�еĴ���
        mpu6050_get_acc();                                     // ��ȡ MPU6050 ���ٶȼ�����
				mpu6050_get_gyro();																		 // ��ȡ MPU6050 ����������
			   
			  tft180_show_int (0,1, mpu6050_gyro_x,4 );
			  tft180_show_int (0,2, mpu6050_gyro_y,4);
			  tft180_show_int (0,3, mpu6050_gyro_z,4);
			  tft180_show_int (0,4, mpu6050_acc_x,4);
			  tft180_show_int (0,5, mpu6050_acc_y,4);
			  tft180_show_int (0,6, mpu6050_acc_z,4);
      
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}




