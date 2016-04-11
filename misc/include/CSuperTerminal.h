#ifndef CSUPERTERMINA_H
#define CSUPERTERMINA_H
#include <boost/asio.hpp>
 #include <boost/bind.hpp>
 #include <iostream>
#include "boost/thread/thread.hpp"
#include "miscdef.h"

 using namespace std;
 using namespace boost::asio;

 typedef string anytype;


 class MISC_EXPORTS SuperTerminal
 {
 public:
     //SuperTerminal(const anytype &port_name);
     SuperTerminal();//debug
     ~SuperTerminal();

 private:
     bool init_port(const anytype port, const unsigned int char_size);
     //bool SuperTerminal::init_port(const unsigned int char_size);

 public:

     void write_to_serial( const char* data,const int num);
     void read_from_serial();
     void handle_read(char buf[], boost::system::error_code ec,std::size_t bytes_transferred);
     void call_handle();
     void print(int p,int q);
 private:
     io_service m_ios;
     serial_port *pSerialPort;
     anytype m_port;
     boost::system::error_code m_ec;
     boost::asio::io_service::work work;
     boost::thread tt;

 };
#endif

