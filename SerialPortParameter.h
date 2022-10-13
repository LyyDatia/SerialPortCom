#pragma once
#include<QString>
#include<stdint.h>
#include<QByteArray>
#pragma execution_character_set("utf-8")

extern QString IntToBinary(int);
extern QString ZeroFill(QString,int);
extern uint16_t ModbusCRC16(QByteArray);
extern QByteArray ModbusCRC16(QByteArray,int);
extern QString ModbusCRC16(QString);
extern void Data_(QByteArray&,int,int bit_=16);

extern int START_ADD;//0x00
/*启动/停止*/
extern int CTL_JOGGING_NUM;
extern int CTL_JOGGING_ADDH;
extern int CTL_JOGGING_ADDL;
extern int CTL_STARTJOGGING_DATA;
extern int CTL_STOPJOGGING_DATA;
/*位置控制例程*/
extern int FCT_GO_POSITION_NUM;				//(运行到)绝对位置功能码
extern int FCT_GO_POSITION_ADDH;			//绝对位置起始地址高位
extern int FCT_GO_POSITION_ADDL;			//绝对位置起始地址低位
extern int FCT_GO_POSITION_REGISTER_SUM;	//绝对位置寄存器总数 
extern int FCT_GO_POSITION_BIT;				//绝对位置总字节数
/*返回原点例程*/
extern int FCT_RE_TO_PHOTOGRAPHY_NUM;			//返回原点功能码
extern int FCT_RE_TO_PHOTOGRAPHY_ADDH;			//返回原点地址高位
extern int FCT_RE_TO_PHOTOGRAPHY_ADDL;			//返回原点地址低位
extern int FCT_RE_TO_PHOTOGRAPHY_REGISTER_SUM;	//返回原点寄存器总数
extern int FCT_RE_TO_PHOTOGRAPHY_BIT;			//返回原点字节数
/*运动方式*/
extern int SET_POSITION_NUM;		//设置执行运动方式功能码
extern int SET_POSITION_ADDH;		//设置执行运动方式寄存器地址高位	
extern int SET_POSITION_ADDL;		//设置执行运动方式寄存器地址低位
extern int SET_POSITION_ABSOLUTE;	//设置执行绝对运动数据内容
extern int SET_POSITION_RELATIVE;	//设置执行相对运动数据内容
/*速度控制例程*/
extern int FCT_SPEEDCONTROL_NUM;			
extern int FCT_SPEEDCONTROL_ADDH;			
extern int FCT_SPEEDCONTROL_ADDL;			
extern int FCT_SPEEDCONTROL_REGISTER_SUM;	
extern int FCT_SPEEDCONTROL_BIT;			
/*读取实时数据*/
extern int FCT_REALTIMEDATA_NUM;
extern int FCT_REALTIMEDATA_ADDH;
extern int FCT_REALTIMEDATA_ADDL;
extern int FCT_REALTIMEDATA_READH;
extern int FCT_REALTIMEDATA_READL;



extern int UNITS_RPS_SEC;					
extern int UNITS_RPS;
extern int UNITS_PULSES;
extern int UNITS_RATIO;


/*相对运动*/
enum GoPosition
{
	Relative=0,
	Absolute,
};
