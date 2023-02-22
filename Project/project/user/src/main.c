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


/*�����ĸ�������*/
int16 encoder1;
int16 encoder2;
int16 encoder3;
int16 encoder4;
int main(void)
{
	DisableGlobalIRQ();                                         //��ʼ���׶ιر����ж�
    clock_init(SYSTEM_CLOCK_600M);  							// ����ɾ��
    debug_init();                   							// ���Զ˿ڳ�ʼ��
	system_delay_ms(300);         								//��ʱ�ȴ������ϵ�

	tft180_init();												//��Ļ��ʼ��
	tft180_show_string (0, 0, "TFT180Init!");
	if(mpu6050_init()==1){										//MPU�����ǳ�ʼ������ж�
		tft180_show_string (0, 1, "MPU6050Fail");
	}	
	else tft180_show_string (0, 1, "MPU6050InitOK");
	encoder_dir_init(QTIMER1_ENCODER1, QTIMER1_ENCODER1_CH1_C0, QTIMER1_ENCODER1_CH2_C1);    //��ʼ����·������
	encoder_dir_init(QTIMER1_ENCODER2, QTIMER1_ENCODER2_CH1_C2, QTIMER1_ENCODER2_CH2_C24);
	encoder_dir_init(QTIMER2_ENCODER1, QTIMER2_ENCODER1_CH1_C3, QTIMER2_ENCODER2_CH2_C25);
	encoder_dir_init(QTIMER2_ENCODER2, QTIMER3_ENCODER2_CH1_B18, QTIMER3_ENCODER2_CH2_B19);
	pit_ms_init(PIT_CH1,5);                                    //��ʼ��pitͨ��1������Ϊ5���룬�ɼ�����������
	EnableGlobalIRQ(0);										   // ���ж������
	// �˴���д�û����� ���������ʼ�������
	while(1)
    {
        // �˴���д��Ҫѭ��ִ�еĴ���
		pit_enable(PIT_CH1);									// pitͨ��1��ʼ��ʱ
		mpu6050_get_acc(); 										// ��ȡ MPU6050 ���ٶ�
		mpu6050_get_gyro();										// ��ȡ MPU6050 ����������
	
		tft180_show_int (0,2, mpu6050_gyro_x,5);
		tft180_show_int (0,3, mpu6050_gyro_y,5);
		tft180_show_int (0,4, mpu6050_gyro_z,5);
		tft180_show_int (0,5, mpu6050_acc_x,5);
		tft180_show_int (0,6, mpu6050_acc_y,5);
		tft180_show_int (0,7, mpu6050_acc_z,5);
		
        // �˴���д��Ҫѭ��ִ�еĴ���
    }
}


void PIT_IRQHandler(void)
{
	if (PIT_FLAG_GET(PIT_CH0))
	{
		
		pit_flag_clear(PIT_CH0);							//���ͨ��1�жϱ�־λ
	}

	if (PIT_FLAG_GET(PIT_CH1))
	{
		//ͨ��1�����ж�,��ʼ�ɼ���ˢ�£�����������
		encoder1 = encoder_get_count(QTIMER1_ENCODER1);
		encoder1 = encoder_get_count(QTIMER1_ENCODER2);
		encoder1 = encoder_get_count(QTIMER2_ENCODER1);
		encoder1 = encoder_get_count(QTIMER2_ENCODER2);
		encoder_clear_count(QTIMER1_ENCODER1);
		encoder_clear_count(QTIMER1_ENCODER2);
		encoder_clear_count(QTIMER2_ENCODER1);
		encoder_clear_count(QTIMER2_ENCODER2);
		pit_flag_clear(PIT_CH1);
	}

	if (PIT_FLAG_GET(PIT_CH2))
	{
		// ͨ��2�����ж�
		pit_flag_clear(PIT_CH2);
	}

	if (PIT_FLAG_GET(PIT_CH3))
	{
		// ͨ��3�����ж�
		pit_flag_clear(PIT_CH3);
	}

	__DSB();
}