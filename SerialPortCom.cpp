#include "serialportcom.h"

SerialPortCom::SerialPortCom(QString ComName)
	:ComReadIs(false)
	,ComWriteIs(false)
	,StationName(0x01)
	,WaitTime(1000)
	,IsWait(false)
	,IsError(false)
	,MsgType(0)
{
	myComSetting.BaudRate=BAUD9600;
	myComSetting.DataBits=DATA_8;
	myComSetting.Parity=PAR_NONE;
	myComSetting.StopBits=STOP_1;
	myComSetting.FlowControl=FLOW_OFF;
	myComSetting.Timeout_Millisec=500;


	myCom = new Win_QextSerialPort(ComName,myComSetting,QextSerialBase::EventDriven);
	connect(myCom,SIGNAL(readyRead()),this,SLOT(_readyRead()));


	t=new QTimer(this);
	connect(t,SIGNAL(timeout()),this,SLOT(_timeOut()));
}

SerialPortCom::~SerialPortCom()
{
	delete myCom;
}

void SerialPortCom::Get_RealTimeDate(int StationName_/*=-1*/)
{
	if(IsWait)
		return;
	QByteArray msg;
	if(StationName_==-1)
		msg.push_back(StationName);					
	else	
		msg.push_back(StationName_);
	msg.push_back(FCT_REALTIMEDATA_NUM);			
	msg.push_back(FCT_REALTIMEDATA_ADDH);			
	msg.push_back(FCT_REALTIMEDATA_ADDL);			
	msg.push_back(FCT_REALTIMEDATA_READH);			
	msg.push_back(FCT_REALTIMEDATA_READL);			
	QByteArray crc=ModbusCRC16(msg,msg.size());
	msg.push_back(crc[0]);							//12:CRC校验码高位
	msg.push_back(crc[1]);							//13:CRC校验码低位
	ComPutMsg(msg);
	MsgType=1;
	Set_LastResponse(msg[0],msg[1],msg[2],msg[3],msg[4],msg[5]);
	emit sendMsg(msg);
}

void SerialPortCom::Ctl_Jogging(int StationName_/*=-1*/,bool start)
{
	if(IsWait)
		return;
	QByteArray msg;
	if(StationName_==-1)
		msg.push_back(StationName);					//1:站号
	else	
		msg.push_back(StationName_);
	msg.push_back(CTL_JOGGING_NUM);					//2:功能码
	msg.push_back(CTL_JOGGING_ADDH);				//3:寄存器地址高位
	msg.push_back(CTL_JOGGING_ADDL);				//4:寄存器地址低位
	msg.push_back(START_ADD);							
	if(start)
		msg.push_back(CTL_STARTJOGGING_DATA);				//5:数据内容
	else
		msg.push_back(CTL_STOPJOGGING_DATA);				//5:数据内容
	QByteArray crc=ModbusCRC16(msg,msg.size());
	msg.push_back(crc[0]);							//12:CRC校验码高位
	msg.push_back(crc[1]);							//13:CRC校验码低位
	ComPutMsg(msg);
	Set_LastResponse(msg[0],msg[1],msg[2],msg[3],msg[4],msg[5]);
	emit sendMsg(msg);
}

void SerialPortCom::Set_Position(int StationName_/*=-1*/,GoPosition p/*=GoPosition::Absolute*/)
{
	if(IsWait)
		return;
	QByteArray msg;
	if(StationName_==-1)
		msg.push_back(StationName);					//1:站号
	else	
		msg.push_back(StationName_);
	msg.push_back(SET_POSITION_NUM);				//2:功能码
	msg.push_back(SET_POSITION_ADDH);				//3:起始地址高位
	msg.push_back(SET_POSITION_ADDL);				//4:起始地址低位
	msg.push_back(START_ADD);						//5:数据内容
	switch(p)
	{
	case GoPosition::Absolute:msg.push_back(SET_POSITION_ABSOLUTE);break;
	case GoPosition::Relative:msg.push_back(SET_POSITION_RELATIVE);break;
	}
	QByteArray crc=ModbusCRC16(msg,msg.size());
	msg.push_back(crc[0]);							//12:CRC校验码高位
	msg.push_back(crc[1]);							//13:CRC校验码低位
	ComPutMsg(msg);
	Set_LastResponse(msg[0],msg[1],msg[2],msg[3],msg[4],msg[5]);
	emit sendMsg(msg);
}

void SerialPortCom::SET_SpeedControl(int StationName_/*=-1*/,int AddSpeed,int SubSpeed/*=100*/,int Speed/*=1*/)
{
	if(IsWait)
		return;
	QByteArray msg;
	if(StationName_==-1)
		msg.push_back(StationName);						//1:站号
	else	
		msg.push_back(StationName_);
	msg.push_back(FCT_SPEEDCONTROL_NUM);				//2:功能码
	msg.push_back(FCT_SPEEDCONTROL_ADDH);				//3:起始地址高位
	msg.push_back(FCT_SPEEDCONTROL_ADDL);				//4:起始地址低位
	msg.push_back(START_ADD);							//5:寄存器总数高位
	msg.push_back(FCT_SPEEDCONTROL_REGISTER_SUM);		//6:寄存器总数低位
	msg.push_back(FCT_SPEEDCONTROL_BIT);				//7:总字节数
	Data_(msg,AddSpeed*UNITS_RPS_SEC);							
	Data_(msg,SubSpeed*UNITS_RPS_SEC);
	Data_(msg,Speed*UNITS_RPS);
	QByteArray crc=ModbusCRC16(msg,msg.size());
	msg.push_back(crc[0]);							//12:CRC校验码高位
	msg.push_back(crc[1]);							//13:CRC校验码低位

	ComPutMsg(msg);
	Set_LastResponse(msg[0],msg[1],msg[2],msg[3],msg[4],msg[5]);
	emit sendMsg(msg);
}

void SerialPortCom::SET_GoPosition(int StationName_/*=-1*/,int Position,int AddSpeed/*=100*/,int SubSpeed/*=100*/,int Speed/*=10*/)
{
	if(IsWait)
		return;
	QByteArray msg;
	if(StationName_==-1)
		msg.push_back(StationName);					//1:站号
	else	
		msg.push_back(StationName_);
	msg.push_back(FCT_GO_POSITION_NUM);				//2:功能码
	msg.push_back(FCT_GO_POSITION_ADDH);			//3:起始地址高位
	msg.push_back(FCT_GO_POSITION_ADDL);			//4:起始地址低位
	msg.push_back(START_ADD);						//5:寄存器总数高位
	msg.push_back(FCT_GO_POSITION_REGISTER_SUM);	//6:寄存器总数低位
	msg.push_back(FCT_GO_POSITION_BIT);				//7:总字节数
	Data_(msg,AddSpeed*UNITS_RPS_SEC);							
	Data_(msg,SubSpeed*UNITS_RPS_SEC);
	Data_(msg,Speed*UNITS_RPS);
	Data_(msg,Position,32);
	QByteArray crc=ModbusCRC16(msg,msg.size());
	msg.push_back(crc[0]);							//12:CRC校验码高位
	msg.push_back(crc[1]);							//13:CRC校验码低位

	ComPutMsg(msg);
	Set_LastResponse(msg[0],msg[1],msg[2],msg[3],msg[4],msg[5]);
	emit sendMsg(msg);
}

void SerialPortCom::SET_ReToPhotography(int StationName_/*=-1*/,int Position/*=5000*/,int SpeedChange/*=20*/,int FirstSpeed/*=5*/,int SecondSpeed/*=1*/,int Ratio/*=70*/)
{
	if(IsWait)
		return;
	QByteArray msg;
	if(StationName_==-1)
		msg.push_back(StationName);						//1:站号
	else	
		msg.push_back(StationName_);
	msg.push_back(FCT_RE_TO_PHOTOGRAPHY_NUM);			//2:功能码
	msg.push_back(FCT_RE_TO_PHOTOGRAPHY_ADDH);			//3:起始地址高位
	msg.push_back(FCT_RE_TO_PHOTOGRAPHY_ADDL);			//4:起始地址低位
	msg.push_back(START_ADD);							//5:寄存器总数高位
	msg.push_back(FCT_RE_TO_PHOTOGRAPHY_REGISTER_SUM);	//6:寄存器总数低位
	msg.push_back(FCT_RE_TO_PHOTOGRAPHY_BIT);			//7:总字节数
	Data_(msg,SpeedChange*UNITS_RPS_SEC,32);
	Data_(msg,0,32);
	Data_(msg,FirstSpeed*UNITS_RPS,32);
	Data_(msg,SecondSpeed*UNITS_PULSES,32);
	Data_(msg,Position,32);
	QByteArray crc=ModbusCRC16(msg,msg.size());
	msg.push_back(crc[0]);							//12:CRC校验码高位
	msg.push_back(crc[1]);							//13:CRC校验码低位

	ComPutMsg(msg);
	Set_LastResponse(msg[0],msg[1],msg[2],msg[3],msg[4],msg[5]);
	emit sendMsg(msg);
}

void SerialPortCom::ComSetting(BaudRateType BaudRate/*=BAUD9600*/,DataBitsType DataBits/*=DATA_8*/,ParityType Parity/*=PAR_NONE*/, StopBitsType StopBits/*=STOP_1*/,FlowType FlowControl/*=FLOW_OFF*/,long Timeout_Millisec/*=500*/)
{
	setBaudRate(BaudRate);
	setDataBits(DataBits);
	setParity(Parity);
	setStopBits(StopBits);
	setFlowControl(FlowControl);
	setTimeout_Millisec(Timeout_Millisec);
}

bool SerialPortCom::ComOpen(QIODevice::OpenModeFlag model/*=QIODevice::ReadWrite*/)
{
	if(!myCom)
		return false;
	if(myCom->isOpen())
		ComClose();
	if(myCom->open(model))
	{
		ComReadIs=(model==QIODevice::ReadOnly||model==QIODevice::ReadWrite);
		ComWriteIs=(model==QIODevice::WriteOnly||model==QIODevice::ReadWrite);
		return true;
	}
	else
	{
		ComWriteIs=false;
		ComReadIs=false;
		return false;
	}
}

bool SerialPortCom::ComClose()
{
	if(!myCom||myCom->isOpen()==false)
		return false;
	ComReadIs=false;
	ComWriteIs=false;
	myCom->close();
	return true;
}

QByteArray SerialPortCom::ComGetMsg()
{
	if(IsWait=true)
	{
		t->stop();
		IsWait=false;
	}
	QByteArray res;
	if(ComReadIs)
	{
		res=myCom->readAll();
	}
	if(res.size()==0)
		return res;
	if(MsgType)
	{
		MsgType=0;
		if(res.size()<2)
			return res;
		QByteArray data;
		for(int i=1;i<=(int)res[2];i++)
		{
			if(i+2<res.size())
				data.push_back(res[i+2]);
			else
				return data;
		}
		return data;
	}
	/*异常返回的数据格式为：0A 90 XX CRC_L CRC_H
	其中，XX = 01H：不支持写入功能码10H
	XX = 02H：不合法的寄存器
	XX = 03H：不合法的数据区
	XX = 11H：寄存器不支持读取
	XX = 12H：寄存器不支持写入
	XX = 13H：设定值超范围*/
	//res[1]也就是功能码位，0x90对应写多个寄存器，0x86对应写单个寄存器，0x83对应读取保持寄存器
	if(res.size()==5)
	{
		IsError=true;
		switch(res[2])
		{
		case 0x01:ComGetMsgError("Function code writing is not supported");return res;
		case 0x02:ComGetMsgError("Illegal register");return res;
		case 0x03:ComGetMsgError("Illegal data area");return res;
		case 0x11:ComGetMsgError("Register does not support reading");return res;
		case 0x12:ComGetMsgError("Register does not support writing");return res;
		case 0x13:ComGetMsgError("Set value out of range");return res;
		}
	}

	if(LastStationName!=(int)res[0])
	{
		ComGetMsgError("StationId is Error");//站号不符
	}
	else if(LastNum!=(int)res[1])
	{
		ComGetMsgError("Function Code Is Error");//功能码不符
	}
	else if(LastRegisterAddH!=(int)res[2])
	{
		ComGetMsgError("Register Address Is Error");//地址高位不符
	}
	else if(LastRegisterAddL!=(int)res[3])
	{
		ComGetMsgError("Register Address Is Error");//地址低位不符
	}
	else if(LastRegisterNumH!=(int)res[4])
	{
		ComGetMsgError("Number of registers is Error");//寄存器数量高位不符
	}
	else if(LastRegisterNumL!=(int)res[5])
	{
		ComGetMsgError("Number of registers is Error");//寄存器数量低位不符
	}
	return res;
}

void SerialPortCom::ComPutMsg(QByteArray msg)
{
	if(ComWriteIs)
	{
		myCom->write(msg);
	}
}

void SerialPortCom::Set_LastResponse(int Id,int Num,int AddH,int AddL,int NumH,int NumL)
{
	(int)LastStationName=Id;
	(int)LastNum=Num;
	(int)LastRegisterAddH=AddH;
	(int)LastRegisterAddL=AddL;
	(int)LastRegisterNumH=NumH;
	(int)LastRegisterNumL=NumL;

	t->start(WaitTime);
	IsWait=true;
}

void SerialPortCom::ComGetMsgError(QString setError)
{
	IsWait=false;
	t->stop();
	IsError=true;
	LastErrorMsg=setError;
	emit abnormalReturn();
}
