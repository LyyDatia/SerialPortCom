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
/*����/ֹͣ*/
extern int CTL_JOGGING_NUM;
extern int CTL_JOGGING_ADDH;
extern int CTL_JOGGING_ADDL;
extern int CTL_STARTJOGGING_DATA;
extern int CTL_STOPJOGGING_DATA;
/*λ�ÿ�������*/
extern int FCT_GO_POSITION_NUM;				//(���е�)����λ�ù�����
extern int FCT_GO_POSITION_ADDH;			//����λ����ʼ��ַ��λ
extern int FCT_GO_POSITION_ADDL;			//����λ����ʼ��ַ��λ
extern int FCT_GO_POSITION_REGISTER_SUM;	//����λ�üĴ������� 
extern int FCT_GO_POSITION_BIT;				//����λ�����ֽ���
/*����ԭ������*/
extern int FCT_RE_TO_PHOTOGRAPHY_NUM;			//����ԭ�㹦����
extern int FCT_RE_TO_PHOTOGRAPHY_ADDH;			//����ԭ���ַ��λ
extern int FCT_RE_TO_PHOTOGRAPHY_ADDL;			//����ԭ���ַ��λ
extern int FCT_RE_TO_PHOTOGRAPHY_REGISTER_SUM;	//����ԭ��Ĵ�������
extern int FCT_RE_TO_PHOTOGRAPHY_BIT;			//����ԭ���ֽ���
/*�˶���ʽ*/
extern int SET_POSITION_NUM;		//����ִ���˶���ʽ������
extern int SET_POSITION_ADDH;		//����ִ���˶���ʽ�Ĵ�����ַ��λ	
extern int SET_POSITION_ADDL;		//����ִ���˶���ʽ�Ĵ�����ַ��λ
extern int SET_POSITION_ABSOLUTE;	//����ִ�о����˶���������
extern int SET_POSITION_RELATIVE;	//����ִ������˶���������
/*�ٶȿ�������*/
extern int FCT_SPEEDCONTROL_NUM;			
extern int FCT_SPEEDCONTROL_ADDH;			
extern int FCT_SPEEDCONTROL_ADDL;			
extern int FCT_SPEEDCONTROL_REGISTER_SUM;	
extern int FCT_SPEEDCONTROL_BIT;			
/*��ȡʵʱ����*/
extern int FCT_REALTIMEDATA_NUM;
extern int FCT_REALTIMEDATA_ADDH;
extern int FCT_REALTIMEDATA_ADDL;
extern int FCT_REALTIMEDATA_READH;
extern int FCT_REALTIMEDATA_READL;



extern int UNITS_RPS_SEC;					
extern int UNITS_RPS;
extern int UNITS_PULSES;
extern int UNITS_RATIO;


/*����˶�*/
enum GoPosition
{
	Relative=0,
	Absolute,
};
