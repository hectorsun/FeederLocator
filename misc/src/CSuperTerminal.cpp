#include "misc/CSuperTerminal.h"
//#include "misc/logging.h"

#include "../../GUI/src/CMainWindow.h"

//extern CMainWindow *mainWindowPtr;
SuperTerminal *Ptr;

char vv[4];

int feederFlag = 0;

SuperTerminal::SuperTerminal():pSerialPort(NULL),work(m_ios),
tt(boost::bind(&io_service::run,&m_ios))
  {
     pSerialPort = new serial_port(m_ios);
     if (pSerialPort)
     {
        //cout << "Initing... " ; 
        const anytype port_name = "COM3";
	 init_port(port_name,8);
	 //初始化，运行程序后先发送飞达连接指令
	 int RandNum;
     char RandCh;
     RandNum = rand()%128;
     RandCh = (char)RandNum;
     char string[4],stringKey[4];
	 string[0] = 0x27;
     string[1] = RandCh;//0x00 -
     string[2] = RandCh;//2mm
     string[3] = RandCh;
     /*指令加密……*/
     stringKey[0] = string[0]^string[3];
     stringKey[1] = string[0]^string[1]^string[3];
     stringKey[2] = string[0]^string[2]^string[3];
     stringKey[3] = string[3];
	 write_to_serial(stringKey,4);

	 async_read(*pSerialPort, buffer(vv,4), boost::bind(&SuperTerminal::handle_read,this,vv,_1, _2));
     }
 }
SuperTerminal::~SuperTerminal()
 {
    if (pSerialPort)
     {
	tt.join();
         delete pSerialPort;
     }
 }

 bool SuperTerminal::init_port(const anytype port, const unsigned int char_size)
 {
     if (!pSerialPort)
     {
        cout << "Open Failied: " ; 
	return false;
	 
     }
     pSerialPort->open(port,m_ec);

     pSerialPort->set_option(serial_port::baud_rate(115200),m_ec);
     pSerialPort->set_option(serial_port::flow_control(serial_port::flow_control::none),m_ec);
     pSerialPort->set_option(serial_port::parity(serial_port::parity::none),m_ec);
     pSerialPort->set_option(serial_port::stop_bits(serial_port::stop_bits::one),m_ec);
     pSerialPort->set_option(serial_port::character_size(char_size),m_ec);
     // cout << "Initing... " ; 
     return true;
 }


//void SuperTerminal::write_to_serial(const anytype data)
void SuperTerminal::write_to_serial(const char* data,const int num)
 {
     if (!pSerialPort)
     {
         return;
     }
     size_t len = write(*pSerialPort, buffer(data,num),m_ec);
     cout << len << "\t" <<  data << endl;
 }


 void SuperTerminal::handle_read(char buf[], boost::system::error_code ec,std::size_t bytes_transferred)
 {
     //cout << "\nhandle_read: " ;
     //cout.write(buf, bytes_transferred);
     //cout << "\nhandle_read: " << bytes_transferred << ec << endl;
     async_read(*pSerialPort, buffer(vv,4), boost::bind(&SuperTerminal::handle_read,this,vv,_1, _2));
     if(feederFlag == 0){
     if(buf[0]==0x57)
     {	
	        Ptr->print(0,0);
		feederFlag = 1;		
     }
     }
     else{
     if(buf[0]==0x63&&buf[1]==0x7F)
     {	
		Ptr->print(1,0);

     }
     if(buf[0]==0x63&&buf[1]==0x20)
     {	
	        Ptr->print(2,0);

     }
     if(buf[0]==0x63&&buf[1]==0x00)
     {	
	        Ptr->print(3,0);

     }
     if(buf[0]==0x64&&buf[1]==0x00)
     {	
	        Ptr->print(4,0);

     }
     if(buf[0]==0x64&&buf[1]==0x10)
     {	
	        Ptr->print(5,0);

     }
     if(buf[0]==0x64&&buf[1]==0x20)
     {	
	        Ptr->print(6,0);

     }
     if(buf[0]==0x66&&buf[1]==0x00)
     {	
	        Ptr->print(7,0);

     }
     if(buf[0]==0x66&&buf[1]==0x29)
     {	
	        Ptr->print(8,0);

     }
     if(buf[0]==0x65&&buf[1]==0x00)
     {	
	        Ptr->print(9,0);

     }
     if(buf[0]==0x65&&buf[1]==0x40)
     {			
		int sum = (int)(buf[2]);
	        Ptr->print(10,sum);

     }
     if(buf[0]==0x68&&buf[1]==0x00)
     {	
	        Ptr->print(11,0);

     }
     if(buf[0]==0x68&&buf[1]==0x7F)
     {	
	        Ptr->print(12,0);

     }
     if(buf[0]==0x70&&buf[1]==0x00)
     {	
	        Ptr->print(13,0);

     }
     if(buf[0]==0x70&&buf[1]==0x20)
     {	
	        Ptr->print(14,0);

     }
     if(buf[0]==0x70&&buf[1]==0x22)
     {	
	       Ptr->print(15,0);

     }
     if(buf[0]==0x69&&buf[1]==0x00)
     {	
	        Ptr->print(16,0);

     }
     if(buf[0]==0x69&&buf[1]==0x7F)
     {	
	        Ptr->print(17,0);

     }
     if(buf[0]==0x71&&buf[1]==0x00)
     {	
	        Ptr->print(18,0);

     }
     if(buf[0]==0x71&&buf[1]==0x01)
     {	
	        Ptr->print(19,0);

     }
     if(buf[0]==0x67&&buf[1]==0x00)
     {	
	        Ptr->print(20,0);

     }
     }
}


void SuperTerminal::print(int p, int q)
{

    switch(p)
	{
	case 0:
		cout<<"飞达连接成功"<<endl;
		//m_pList->addItem(QString::fromLocal8Bit("飞达操作没有完成，请等待") + tr("\r\n")
		break;
	case 1:
		cout<<"飞达操作没有完成，请等待"<<endl;
		break;
	case 2:
		cout<<"EEPROM写入错误"<<endl;
		break;
	case 3:
		cout<<"记录成功"<<endl;
		break;
	case 4:
		cout<<"复位成功"<<endl;
		break;
	case 5:
		cout<<"电机运行故障"<<endl;
		break;
	case 6:
		cout<<"目前数据为空"<<endl;
		break;
	case 7:
		cout<<"无故障"<<endl;
		break;
	case 8:
		cout<<"当前模式不可用"<<endl;
		break;	
	case 9:
		cout<<"检测完毕，无故障"<<endl;
		break;
	case 10:
		cout<<"无法矫正齿位，数目为："<<q<<endl;
		break;
	case 11:
		cout<<"记录矫正数据成功"<<endl;
		break;	
	case 12:
		cout<<"记录矫正数据失败"<<endl;
		break;
	case 13:
		cout<<"记录矫正数据写入EEPROM成功"<<endl;
		break;
	case 14:
		cout<<"记录矫正数据写入EEPROM错误"<<endl;
		break;
	case 15:
		cout<<"记录矫正数据读写EEPROM错误"<<endl;
		break;
	case 16:
		cout<<"记录矫正数据成功"<<endl;
		break; 
	case 17:
		cout<<"记录矫正数据失败"<<endl;
		break; 
	case 18:
		cout<<"清除数据成功"<<endl;
		break; 
	case 19:
		cout<<"清除数据失败"<<endl;
		break;
	case 20:
		cout<<"移动成功"<<endl;
		break;
	default:
		break;
	}
}
 void SuperTerminal::read_from_serial()
 {
     char v[4];

 }


 void SuperTerminal::call_handle()
 {
  
 }

