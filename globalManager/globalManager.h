#ifndef GLOBALMANAGER_H
#define GLOBALMANAGER_H
#include "../common/common.h"
#include "../motorManager/motorManager.h"
#include "../adcManager/adcManager.h"
#include "../gsmManager/gsmManager.h"
#include "./DH11.h"
#include "./EEPROM.h"
/*******************************************************************************
*说明:全局管理结构体
*******************************************************************************/
typedef struct _GlobalManager{
	/**
 * @brief 控制电机1的转动状态，状态值,
 * @param status:参考MotorStatus枚举
 * @return true:成功,false:失败
 */
	const bool (*controlMotor1StatusFunc)(const MotorStatus status);
	/**
 * @brief 控制电机2的转动状态，状态值,参考MotorStatus枚举
 * @param status:参考MotorStatus枚举
 * @return true:成功,false:失败
 */
	const bool (*controlMotor2StatusFunc)(const MotorStatus status);
/**
 * @brief handleSensorDataFunc:判断各个传感器是否达到阈值
 * @return true:收衣服,false:晒衣服
 */	
	const bool (*handleSensorDataFunc)(void);
/**
 * @brief handleSendSmsInfoFunc:发送短信给gsm模块
 * @return true:成功:false:失败
 */
	const bool (*handleSendSmsInfoFunc)(void);
	/**
 * @brief handleControlMagnet:控制电磁铁开关函数
 * @param isOpen:true:开,false:关
 * @return true:成功,false:失败
 */
const bool (*handleControlMagnetFunc)(const bool isOpen);
}GlobalManager;
/*******************************************************************************
*说明:所有传感器的实时数据结构体
*******************************************************************************/
typedef struct _SensorValue{
	uint8_t	PhotosensitiveValue;//光敏实时数据
	uint8_t	HumidityValue;//湿度值
	uint8_t	TemperatureValue;//温度值
	uint8_t	RaindropValue;//雨滴值
	uint8_t	WindSpeedValue;//风速值	
}SensorValue;
/*******************************************************************************
*说明:以下是公有调用部分函数
*******************************************************************************/
/**
 * @brief 获取全局管理对象
 * @return 全局管理对象
 */
_public_ extern const GlobalManager g_getGlobalManagerObj();
/**
 * @brief 上电的时候初始化整个单片机所有的参数函数
 */
_public_ extern	void	g_initSystemParameter(); 
/**
* @brief :延时函数
* @param one_1ms:1个1ms
 */
_public_ extern void g_delay(const uint32_t one_1ms);
/*******************************************************************************
*说明:以下是私有部分函数
*******************************************************************************/
_private_	static const bool controlMotor1Status(const MotorStatus status);
_private_	static const bool controlMotor2Status(const MotorStatus status);
_private_	static const bool handleSensorData(void);
_private_	static const bool handleSendSmsInfo(void);
_private_	static const bool handleControlMagnet(const bool isOpen);
const int handleSensorDataAnalysis(void);
/*******************************************************************************
*说明:以下是内部使用的函数
*******************************************************************************/
_private_	static void  interrupt1Init(); 
_private_ static void  uartInit();
/*******************************************************************************
*说明:以下是私有变量
*******************************************************************************/
_private_ static int32_t g_EndCount=0;
_private_ static int32_t g_CurrentCount=0;


void Motor3MakeATurn(bool const direction,const uint32_t speed);
#endif