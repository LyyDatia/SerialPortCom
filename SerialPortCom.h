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
	/*最后发送的报文对应参数，响应的参数其一致则为正常*/
	int LastStationName;
	int LastNum;
	int LastRegisterAddH;
	int LastRegisterAddL;
	int LastRegisterNumH;
	int LastRegisterNumL;
	int MsgType;/*电机驱动器=0 编码器=1*/
	/*错误报警*/
	bool IsError;
	QString LastErrorMsg;
	/*响应超时*/
	QTimer *t;
	int WaitTime;
	bool IsWait;
public:

	bool ComOpen(QIODevice::OpenModeFlag model=QIODevice::ReadWrite);	//打开连接
	bool ComClose();													//关闭连接

	QByteArray ComGetMsg();												//接受数据
	void ComPutMsg(QByteArray);											//发送数据
		
	//获取实时数据
	void Get_RealTimeDate(int StationName_=-1);
	int RealTimeDate;
	//启动/停止
	void Ctl_Jogging(int StationName_=-1,bool start=true);
	//设置运动方向
	void Set_Position(int StationName_=-1,GoPosition p=GoPosition::Absolute);
	//速度控制例程。设置站名、加速度、减速度
	void SET_SpeedControl(int StationName_=-1,int AddSpeed=100,int SubSpeed=100,int Speed=10);
	//位置控制例程。设置站名、目标位置、加速度、减速度、速度
	void SET_GoPosition(int StationName_=-1,int Position=200000,int AddSpeed=100,int SubSpeed=100,int Speed=1);
	//回原点控制例程。设置站名、原点偏移量、回原点加/减速度、第一档速度速度、第二档速度和，以及使用硬限位回原点方式的转矩限值
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
/*简易接口*/
public:
	/*整体配置*/
	void ComSetting(BaudRateType BaudRate=BAUD9600,DataBitsType DataBits=DATA_8,ParityType Parity=PAR_NONE,	
		StopBitsType StopBits=STOP_1,FlowType FlowControl=FLOW_OFF,long Timeout_Millisec=500);
	QString Get_LastErrorMsg(){
		if(IsError)
			return LastErrorMsg;
		else
			return "No";
	}
	/*设置定时器时间*/
	void setWaitTime(int time)
	{
		WaitTime=time;
	}
	/*设置站名*/
	void setStationName(int name)
	{
		StationName=name;
	}
	/*设置串口名*/
	void setPortName(QString name)
	{
		if(!myCom)
			return;
		myCom->setPortName(name);
	}
	/*设置波特率*/
	void setBaudRate(BaudRateType BaudRate)
	{
		if(!myCom)
			return;
		myCom->setBaudRate(BaudRate);
	}
	/*设置数据位*/
	void setDataBits(DataBitsType DataBits)
	{
		if(!myCom)
			return;
		myCom->setDataBits(DataBits);
	}
	/*校验位*/
	void setParity(ParityType Parity)
	{
		if(!myCom)
			return;
		myCom->setParity(Parity);
	}
	/*停止位*/
	void setStopBits(StopBitsType StopBits)
	{
		if(!myCom)
			return;
		myCom->setStopBits(StopBits);
	}
	/*数据流控制位*/
	void setFlowControl(FlowType Flow)
	{
		if(!myCom)
			return;
		myCom->setFlowControl(Flow);
	}
	/*延时时间*/
	void setTimeout_Millisec(long time)
	{
		if(!myCom)
			return;
		myCom->setTimeout(time);
	}
};

#endif // SERIALPORTCOM_H
