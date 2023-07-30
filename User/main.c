#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

float Voltage;
int main(void)
{
	OLED_Init();
	AD_Init();
	OLED_ShowString(1,1,"AD Outcome:");
	OLED_ShowString(2,1,"Voltage:0.00V");
	while (1)
	{
		OLED_ShowNum(1,12,Get_Outcome(),4);
		Voltage=(float)Get_Outcome()/4095*3.3;//12位AD，最大值4095，电压最大值3.3V
		OLED_ShowNum(2,9,Voltage,1);
		OLED_ShowNum(2,11,(uint16_t)(Voltage*100)%100,2);
	}
}
/*如果要避免由于波动导致AD值在判断阈值附近抖动进而影响输出，可迟滞比较。
例如，当AD值大于阈值时，输出高电平，当AD值小于阈值减去一个迟滞值时，输出低电平。
与GPIO的施密特触发器类似
为了避免抖动还可以使用软件滤波，即对AD值进行多次采样，取平均值作为最终结果。
或者裁剪分辨率，例如将12位的AD值裁剪为8位，去掉数据尾数，这样也可以避免抖动。
*/