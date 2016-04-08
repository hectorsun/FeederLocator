#include "misc/CSuperTerminal.h"


#include "../../GUI/src/CMainWindow.h"

extern CMainWindow *mainWindowPtr;
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
		mainWindowPtr->print(0,0);
		feederFlag = 1;		
     }
     }
     else{
     if(buf[0]==0x63&&buf[1]==0x7F)
     {	
		mainWindowPtr->print(1,0);

     }
     if(buf[0]==0x63&&buf[1]==0x20)
     {	
		mainWindowPtr->print(2,0);

     }
     if(buf[0]==0x63&&buf[1]==0x00)
     {	
		mainWindowPtr->print(3,0);

     }
     if(buf[0]==0x64&&buf[1]==0x00)
     {	
		mainWindowPtr->print(4,0);

     }
     if(buf[0]==0x64&&buf[1]==0x10)
     {	
		mainWindowPtr->print(5,0);

     }
     if(buf[0]==0x64&&buf[1]==0x20)
     {	
		mainWindowPtr->print(6,0);

     }
     if(buf[0]==0x66&&buf[1]==0x00)
     {	
		mainWindowPtr->print(7,0);

     }
     if(buf[0]==0x66&&buf[1]==0x29)
     {	
		mainWindowPtr->print(8,0);

     }
     if(buf[0]==0x65&&buf[1]==0x00)
     {	
		mainWindowPtr->print(9,0);

     }
     if(buf[0]==0x65&&buf[1]==0x40)
     {			
		int sum = (int)(buf[2]);
		mainWindowPtr->print(10,sum);

     }
     if(buf[0]==0x68&&buf[1]==0x00)
     {	
		mainWindowPtr->print(11,0);

     }
     if(buf[0]==0x68&&buf[1]==0x7F)
     {	
		mainWindowPtr->print(12,0);

     }
     if(buf[0]==0x70&&buf[1]==0x00)
     {	
		mainWindowPtr->print(13,0);

     }
     if(buf[0]==0x70&&buf[1]==0x20)
     {	
		mainWindowPtr->print(14,0);

     }
     if(buf[0]==0x70&&buf[1]==0x22)
     {	
		mainWindowPtr->print(15,0);

     }
     if(buf[0]==0x69&&buf[1]==0x00)
     {	
		mainWindowPtr->print(16,0);

     }
     if(buf[0]==0x69&&buf[1]==0x7F)
     {	
		mainWindowPtr->print(17,0);

     }
     if(buf[0]==0x71&&buf[1]==0x00)
     {	
		mainWindowPtr->print(18,0);

     }
     if(buf[0]==0x71&&buf[1]==0x01)
     {	
		mainWindowPtr->print(19,0);

     }
     if(buf[0]==0x67&&buf[1]==0x00)
     {	
		mainWindowPtr->print(20,0);

     }
     }
 }


 void SuperTerminal::read_from_serial()
 {
     char v[4];

 }


 void SuperTerminal::call_handle()
 {
  
 }

