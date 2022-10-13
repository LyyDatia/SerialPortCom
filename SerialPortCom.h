#ifndef SERIALPORTCOM_H
#define SERIALPORTCOM_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include "SerialPortParameter.h"
#include "win_qextserialport.h"

class SerialPortCom : public QObject
{
	Q_OBJECT

public:
	//SerialPortCom(QObject *parent);
	SerialPortCom(QString ComName="COM1");
	~SerialPortCom();

private:
	struct PortSettings myComSetting;
	Win_QextSerialPort* myCom;
	int StationName;

	bool ComReadIs;
	bool ComWriteIs;
	/*����͵ı��Ķ�Ӧ��������Ӧ�Ĳ�����һ����Ϊ����*/
	int LastStationName;
	int LastNum;
	int LastRegisterAddH;
	int LastRegisterAddL;
	int LastRegisterNumH;
	int LastRegisterNumL;
	int MsgType;/*���������=0 ������=1*/
	/*���󱨾�*/
	bool IsError;
	QString LastErrorMsg;
	/*��Ӧ��ʱ*/
	QTimer *t;
	int WaitTime;
	bool IsWait;
public:

	bool ComOpen(QIODevice::OpenModeFlag model=QIODevice::ReadWrite);	//������
	bool ComClose();													//�ر�����

	QByteArray ComGetMsg();												//��������
	void ComPutMsg(QByteArray);											//��������
		
	//��ȡʵʱ����
	void Get_RealTimeDate(int StationName_=-1);
	int RealTimeDate;
	//����/ֹͣ
	void Ctl_Jogging(int StationName_=-1,bool start=true);
	//�����˶�����
	void Set_Position(int StationName_=-1,GoPosition p=GoPosition::Absolute);
	//�ٶȿ������̡�����վ�������ٶȡ����ٶ�
	void SET_SpeedControl(int StationName_=-1,int AddSpeed=100,int SubSpeed=100,int Speed=10);
	//λ�ÿ������̡�����վ����Ŀ��λ�á����ٶȡ����ٶȡ��ٶ�
	void SET_GoPosition(int StationName_=-1,int Position=200000,int AddSpeed=100,int SubSpeed=100,int Speed=1);
	//��ԭ��������̡�����վ����ԭ��ƫ��������ԭ���/���ٶȡ���һ���ٶ��ٶȡ��ڶ����ٶȺͣ��Լ�ʹ��Ӳ��λ��ԭ�㷽ʽ��ת����ֵ
	void SET_ReToPhotography(int StationName_=-1,int Position=5000,int SpeedChange=20,int FirstSpeed=5,int SecondSpeed=1,int Ratio=70);
private:
	void Set_LastResponse(int,int,int,int,int,int);
	bool Get_IsError(){return IsError;}
	void ComGetMsgError(QString setError);
signals:
	void readyRead(SerialPortCom* my);
	void abnormalReturn();
	void sendMsg(QByteArray);
private slots:
	void _readyRead()
	{
		emit readyRead(this);
	}
	void _timeOut()
	{
		MsgType=0;
		ComGetMsgError("Recive time out");
	}
/*���׽ӿ�*/
public:
	/*��������*/
	void ComSetting(BaudRateType BaudRate=BAUD9600,DataBitsType DataBits=DATA_8,ParityType Parity=PAR_NONE,	
		StopBitsType StopBits=STOP_1,FlowType FlowControl=FLOW_OFF,long Timeout_Millisec=500);
	QString Get_LastErrorMsg(){
		if(IsError)
			return LastErrorMsg;
		else
			return "No";
	}
	/*���ö�ʱ��ʱ��*/
	void setWaitTime(int time)
	{
		WaitTime=time;
	}
	/*����վ��*/
	void setStationName(int name)
	{
		StationName=name;
	}
	/*���ô�����*/
	void setPortName(QString name)
	{
		if(!myCom)
			return;
		myCom->setPortName(name);
	}
	/*���ò�����*/
	void setBaudRate(BaudRateType BaudRate)
	{
		if(!myCom)
			return;
		myCom->setBaudRate(BaudRate);
	}
	/*��������λ*/
	void setDataBits(DataBitsType DataBits)
	{
		if(!myCom)
			return;
		myCom->setDataBits(DataBits);
	}
	/*У��λ*/
	void setParity(ParityType Parity)
	{
		if(!myCom)
			return;
		myCom->setParity(Parity);
	}
	/*ֹͣλ*/
	void setStopBits(StopBitsType StopBits)
	{
		if(!myCom)
			return;
		myCom->setStopBits(StopBits);
	}
	/*����������λ*/
	void setFlowControl(FlowType Flow)
	{
		if(!myCom)
			return;
		myCom->setFlowControl(Flow);
	}
	/*��ʱʱ��*/
	void setTimeout_Millisec(long time)
	{
		if(!myCom)
			return;
		myCom->setTimeout(time);
	}
};

#endif // SERIALPORTCOM_H
