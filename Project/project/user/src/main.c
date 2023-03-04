/*********************************************************************************************************************
* RT1064DVL6A Opensourec Library 即（RT1064DVL6A 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
* 
* 本文件是 RT1064DVL6A 开源库的一部分
* 
* RT1064DVL6A 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
* 
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
* 
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
* 
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
* 
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 版本信息          查看 libraries/doc 文件夹内 version 文件 版本说明
* 开发环境          IAR 8.32.4 or MDK 5.33
* 适用平台          RT1064DVL6A
* 店铺链接          https://seekfree.taobao.com/
* 
* 修改记录
* 日期              作者                备注
* 2022-09-21        SeekFree            first version
********************************************************************************************************************/

#include "zf_common_headfile.h"

// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完
// 本例程是开源库移植用空工程

/*声明总初始化函数*/
void InitAll();
/*声明四个编码器的数值变量*/
int16 encoder1;
int16 encoder2;
int16 encoder3;
int16 encoder4;
/*声明偏航角*/
float YawAxis;
int main(void)
{
	
	InitAll();
	while(1)
    {
        // 此处编写需要循环执行的代码
		pit_enable(PIT_CH1);									// pit通道1开始计时
		mpu6050_get_acc(); 										// 获取 MPU6050 加速度
		mpu6050_get_gyro();										// 获取 MPU6050 陀螺仪数据
	
		tft180_show_int (0,2, mpu6050_gyro_x,5);
		tft180_show_int (0,3, mpu6050_gyro_y,5);
		tft180_show_int (0,4, mpu6050_gyro_z,5);
		tft180_show_int (0,5, mpu6050_acc_x,5);
		tft180_show_int (0,6, mpu6050_acc_y,5);
		// tft180_show_int (0,7, mpu6050_acc_z,5);
		tft180_show_int(0, 7, YawAxis, 5);

		// 此处编写需要循环执行的代码
    }
}




void InitAll(void){
	// 此处编写用户代码 例如外设初始化代码等
	DisableGlobalIRQ();			   // 初始化阶段关闭总中断
	clock_init(SYSTEM_CLOCK_600M); // 不可删除
	debug_init();				   // 调试端口初始化
	system_delay_ms(300);		   // 延时等待外设上电

	tft180_init(); // 屏幕初始化
	tft180_show_string(0, 0, "TFT180Init!");
	if (mpu6050_init() == 1)
	{ // MPU陀螺仪初始化结果判断
		tft180_show_string(0, 1, "MPU6050Fail");
	}
	else
		tft180_show_string(0, 1, "MPU6050InitOK");
	/*电机驱动控制信号接口初始化配置*/
	pwm_init(PWM2_MODULE3_CHA_D2, 17000, 0);											  // 驱动控制信号1右侧下方，右电机正转引脚
	pwm_init(PWM2_MODULE3_CHB_D3, 17000, 0);											  // 驱动控制信号1右侧上方，右电机反转引脚
	pwm_init(PWM1_MODULE3_CHA_D0, 17000, 0);											  // 驱动控制信号1左侧下方,左电机正转引脚
	pwm_init(PWM1_MODULE3_CHB_D1, 17000, 0);											  // 驱动控制信号1左侧上方，左电机反转引脚
	pwm_init(PWM1_MODULE1_CHB_D15, 17000, 0);											  // 驱动控制信号2右侧上方,右电机正转引脚
	pwm_init(PWM1_MODULE1_CHA_D14, 17000, 0);											  // 驱动控制信号2右侧下方，右电机反转引脚
	pwm_init(PWM1_MODULE0_CHB_D13, 17000, 0);											  // 驱动控制信号2左侧上方，左电机正转引脚
	pwm_init(PWM1_MODULE0_CHA_D12, 17000, 0);											  // 驱动控制信号2左侧下方，左电机反转引脚
	encoder_dir_init(QTIMER1_ENCODER1, QTIMER1_ENCODER1_CH1_C0, QTIMER1_ENCODER1_CH2_C1); // 初始化四路编码器
	encoder_dir_init(QTIMER1_ENCODER2, QTIMER1_ENCODER2_CH1_C2, QTIMER1_ENCODER2_CH2_C24);
	encoder_dir_init(QTIMER2_ENCODER1, QTIMER2_ENCODER1_CH1_C3, QTIMER2_ENCODER2_CH2_C25);
	encoder_dir_init(QTIMER2_ENCODER2, QTIMER3_ENCODER2_CH1_B18, QTIMER3_ENCODER2_CH2_B19);
	pit_ms_init(PIT_CH1, 5); // 初始化pit通道1，周期为5毫秒，采集编码器数据，刷新偏航角
	EnableGlobalIRQ(0);		 // 总中断最后开启
}