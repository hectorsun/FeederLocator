#include <CStepDlg.h>
#include <QSplitter>
#include <QMessageBox>
#include <QString>
//#include <CSuperTerminal.h>
#include <vector>
 #include <string>
  
 //#define BOOST_REGEX_NO_LIB
 //#define BOOST_DATE_TIME_SOURCE
 //#define BOOST_SYSTEM_NO_LIB
// #include <misc/CSuperTerminal.h>
/********************************/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

#define BAUDRATE B115200
//#define MODEMDEVICE "/dev/ttymxc0"
#define MODEMDEVICE "/dev/ttyUSB0"
#define STOP '@'

//SuperTerminal sps;
SuperTerminal sp;
CStepDlg::CStepDlg(CPaintWidget* pPaint, QListWidget* pList, QWidget* parent)
  : QDialog(parent),
    m_pPaint(pPaint),
    m_pList(pList)
{

    MoveValueSum = 0;
    CorrectNum = 0;
    GearNum = 0;
    fd =0;

    this->setWindowTitle(tr("step"));

    /*****************************/
    //QVBoxLayout *topLayout = new QVBoxLayout();//垂直布局
    //QVBoxLayout *testLayout = new QVBoxLayout();
 

    /**************************/


 
    QGridLayout *LeftLayout = new QGridLayout();
    QGridLayout *RightLayout = new QGridLayout();
    QHBoxLayout *mainLayout = new QHBoxLayout();
    mainLayout->addLayout(LeftLayout);
    mainLayout->addLayout(RightLayout);

    m_pButtonMove = new QPushButton(tr("移动"));
    connect(m_pButtonMove, SIGNAL(clicked()),
        this, SLOT(MoveButton()));//clicked信号后调用MoveButton（）槽函数
    LeftLayout->addWidget(m_pButtonMove,0,0);

    m_pLineMove = new QLineEdit(this);
    LeftLayout->addWidget(m_pLineMove,0,1);

    m_pButtonRecord = new QPushButton(tr("记录"));
    connect(m_pButtonRecord, SIGNAL(clicked()),
        this, SLOT(RecordButton()));
    LeftLayout->addWidget(m_pButtonRecord,1,0);

    m_pButtonErrnum = new QPushButton(tr("无法矫正齿位"));
    connect(m_pButtonErrnum, SIGNAL(clicked()),
        this, SLOT(ErrnumButton()));
    LeftLayout->addWidget(m_pButtonErrnum,1,1);

    m_pButtonZerocorrect = new QPushButton(tr("零位调整"));
    connect(m_pButtonZerocorrect, SIGNAL(clicked()),
        this, SLOT(ZerocorrectButton()));
    LeftLayout->addWidget(m_pButtonZerocorrect,2,0);

    m_pButtonSinglecorrect = new QPushButton(tr("单齿调整"));
    connect(m_pButtonSinglecorrect, SIGNAL(clicked()),
        this, SLOT(SinglecorrectButton()));
    LeftLayout->addWidget(m_pButtonSinglecorrect,2,1);

    m_pButtonDatareset = new QPushButton(tr("数据重置"));
    connect(m_pButtonDatareset, SIGNAL(clicked()),
        this, SLOT(DataresetButton()));
    LeftLayout->addWidget(m_pButtonDatareset,3,0);

    m_pComboDataReset = new QComboBox();
    m_pComboDataReset->addItem(tr(""));
    m_pComboDataReset->addItem(tr("清除全部数据"));
    m_pComboDataReset->addItem(tr("重置矫正数据"));
    m_pComboDataReset->addItem(tr("清除全齿数据"));
    m_pComboDataReset->addItem(tr("清除半齿数据"));
    LeftLayout->addWidget(m_pComboDataReset,3,1);

    m_pButtonForward = new QPushButton(tr("前进"));
    connect(m_pButtonForward, SIGNAL(clicked()),
        this, SLOT(ForwardButton()));
    RightLayout->addWidget(m_pButtonForward,0,0);

    m_pButtonBackward = new QPushButton(tr("后退"));
    connect(m_pButtonBackward, SIGNAL(clicked()),
        this, SLOT(BackwardButton()));
    RightLayout->addWidget(m_pButtonBackward,1,0);

    m_pButtonReset = new QPushButton(tr("复位"));
    connect(m_pButtonReset, SIGNAL(clicked()),
        this, SLOT(ResetButton()));
    RightLayout->addWidget(m_pButtonReset,2,0);

    m_pLabelPace = new QLabel(tr("步距"));
    RightLayout->addWidget(m_pLabelPace,3,0);

    m_pComboPace = new QComboBox();
    m_pComboPace->addItem(tr(""));
    m_pComboPace->addItem(tr("2mm"));
    m_pComboPace->addItem(tr("4mm"));
    m_pComboPace->addItem(tr("8mm"));
    m_pComboPace->addItem(tr("12mm"));
    RightLayout->addWidget(m_pComboPace,3,1);


    this->setLayout(mainLayout);
	
    /*************接收处理****************/
   /* SuperTerminal sp;
    sp.read_from_serial();
    sp.call_handle();
    getchar();*/
}


//click move button
void CStepDlg::MoveButton()
{
    QString strMove;
    strMove = m_pLineMove->text();//get the string of lineedit

    if(strMove == tr(""))
    {
        /*remind user to input number*/
        QMessageBox::warning(this,tr("Warning"),tr("Please input data before clicking the button"));
    }
    else
    {
        double numMove = strMove.toDouble();//change string to double

        int MoveInt = 0;
        char MoveCh;
        MoveInt = numMove*200;
        MoveCh = char(MoveInt);

        int RandNum;
        char RandCh;
        RandNum = rand()%128;
        RandCh = (char)RandNum;
        //char string[4],stringKey[4];
        char string[4],stringKey[4];
        if(numMove >= 0 && numMove <= 163.835)//input is +
        {	
	    string[0] = 0x37;
            string[1] = MoveCh/256;
            string[2] = 0x00;
            string[3] = MoveCh%256;
	    
            /*指令加密……*/
            stringKey[0] = string[0]^string[3];
            stringKey[1] = string[0]^string[1]^string[3];
            stringKey[2] = string[0]^string[2]^string[3];
            stringKey[3] = string[3];

            m_pList->addItem(tr("向前移动") + strMove + tr("微步（mm）\r\n"));/*show the message in mainwindow： 向前移动*/

            /*m_Comm.WriteToPort(stringKey,4)*/
    	   // SuperTerminal sp;
            sp.write_to_serial(stringKey,4);
	    sp.read_from_serial();
            sp.call_handle();
        }
        else if(numMove >= -163.84 && numMove < 0)//input is +
        {
            int MoveInt2 = -MoveInt;
            //char MoveCh2 = (char)MoveInt2;
            short MoveCh3 = (int)MoveInt2;
            string[0] = 0x37;
            string[1] = MoveCh3/256;
            string[2] = 0x01;
            string[3] = MoveCh3%256;
            /*指令加密……*/
            stringKey[0] = string[0]^string[3];
            stringKey[1] = string[0]^string[1]^string[3];
            stringKey[2] = string[0]^string[2]^string[3];
            stringKey[3] = string[3];

            m_pList->addItem(tr("反向移动") + strMove + tr("微步（mm）\r\n"));/*show the message in mainwindow： 反向移动*/

            /*m_Comm.WriteToPort(stringKey,4)*/
            sp.write_to_serial(stringKey,4);
        }

        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("Please input data in correct range"));
            MoveInt = 0;//unuseful data to 0
        }

        MoveValueSum = MoveValueSum + MoveInt;
    }
}

//Click record button
void CStepDlg::RecordButton()
{
    int RandNum;
    char RandCh;
    RandNum = rand()%128;
    RandCh = (char)RandNum;

    char string[4],stringKey[4];
    string[0] = 0x33;
    string[1] = RandCh;
    string[2] = RandCh;
    string[3] = RandCh;
    /*指令加密……*/
    stringKey[0] = string[0]^string[3];
    stringKey[1] = string[0]^string[1]^string[3];
    stringKey[2] = string[0]^string[2]^string[3];
    stringKey[3] = string[3];

    /*m_Comm.WriteToPort(stringKey,4)*/
    MoveValue = 0;
    sp.write_to_serial(stringKey,4);
}

//Click 无法矫正齿位 button
void CStepDlg::ErrnumButton()
{
    int RandNum;
    char RandCh;
    RandNum = rand()%128;
    RandCh = (char)RandNum;

    char string[4],stringKey[4];
    string[0] = 0x35;
    string[1] = RandCh;
    string[2] = RandCh;
    string[3] = RandCh;
    /*指令加密……*/
    stringKey[0] = string[0]^string[3];
    stringKey[1] = string[0]^string[1]^string[3];
    stringKey[2] = string[0]^string[2]^string[3];
    stringKey[3] = string[3];

    /*m_Comm.WriteToPort(stringKey,4)*/
    sp.write_to_serial(stringKey,4);
}
//Click Forward button
void CStepDlg::ForwardButton()
{
    QString strPace;
    strPace = m_pComboPace->currentText();

    int RandNum;
    char RandCh;
    RandNum = rand()%128;
    RandCh = (char)RandNum;
    char string[4],stringKey[4];

    if(strPace == tr(""))
    {
        QMessageBox::warning(this,tr("Warning"),tr("Please change pace"));
    }
    else if(strPace == tr("2mm"))
    {
        string[0] = 0x36;
        string[1] = 0x7F;//0x7F +
        string[2] = 0x00;//2mm
        string[3] = RandCh;
        /*指令加密……*/
        stringKey[0] = string[0]^string[3];
        stringKey[1] = string[0]^string[1]^string[3];
        stringKey[2] = string[0]^string[2]^string[3];
        stringKey[3] = string[3];

        m_pList->addItem(tr("前进：步距为") + strPace + tr("\r\n"));/*show the message in mainwindow*/

        /*m_Comm.WriteToPort(stringKey,4)*/
    	sp.write_to_serial(stringKey,4);
    }
    else if(strPace == tr("4mm"))
    {
        string[0] = 0x36;
        string[1] = 0x7F;//0x7F +
        string[2] = 0x01;//2mm
        string[3] = RandCh;
        /*指令加密……*/
        stringKey[0] = string[0]^string[3];
        stringKey[1] = string[0]^string[1]^string[3];
        stringKey[2] = string[0]^string[2]^string[3];
        stringKey[3] = string[3];

        m_pList->addItem(tr("前进：步距为") + strPace + tr("\r\n"));/*show the message in mainwindow*/

        /*m_Comm.WriteToPort(stringKey,4)*/
    	sp.write_to_serial(stringKey,4);
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("Current pace is not correct"));
    }


}

//Click Backward button
void CStepDlg::BackwardButton()
{
    QString strPace;
    strPace = m_pComboPace->currentText();

    int RandNum;
    char RandCh;
    RandNum = rand()%128;
    RandCh = (char)RandNum;
    char string[4],stringKey[4];

    if(strPace == tr(""))
    {
        QMessageBox::warning(this,tr("Warning"),tr("Please change pace"));
    }
    else if(strPace == tr("2mm"))
    {
        string[0] = 0x36;
        string[1] = 0x00;//0x00 -
        string[2] = 0x00;//2mm
        string[3] = RandCh;
        /*指令加密……*/
        stringKey[0] = string[0]^string[3];
        stringKey[1] = string[0]^string[1]^string[3];
        stringKey[2] = string[0]^string[2]^string[3];
        stringKey[3] = string[3];

        m_pList->addItem(tr("后退：步距为") + strPace + tr("\r\n"));/*show the message in mainwindow*/

        /*m_Comm.WriteToPort(stringKey,4)*/
    	sp.write_to_serial(stringKey,4);
    }
    else if(strPace == tr("4mm"))
    {
        string[0] = 0x36;
        string[1] = 0x00;//0x7F -
        string[2] = 0x01;//4mm
        string[3] = RandCh;
        /*指令加密……*/
        stringKey[0] = string[0]^string[3];
        stringKey[1] = string[0]^string[1]^string[3];
        stringKey[2] = string[0]^string[2]^string[3];
        stringKey[3] = string[3];

        m_pList->addItem(tr("后退：步距为") + strPace + tr("\r\n"));/*show the message in mainwindow*/

        /*m_Comm.WriteToPort(stringKey,4)*/
    	sp.write_to_serial(stringKey,4);
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("Current pace is not correct"));
    }


}
//Click 复位 button
void CStepDlg::ResetButton()
{
    QString strPace;
    strPace = m_pComboPace->currentText();

    int RandNum;
    char RandCh;
    RandNum = rand()%128;
    RandCh = (char)RandNum;
    char string[4],stringKey[4];

    if(strPace == tr(""))
    {
        QMessageBox::warning(this,tr("Warning"),tr("Please change pace"));
    }
    else if(strPace == tr("2mm"))
    {
        string[0] = 0x34;
        string[1] = 0x00;//0x00 -
        string[2] = RandCh;//2mm
        string[3] = RandCh;
        /*指令加密……*/
        stringKey[0] = string[0]^string[3];
        stringKey[1] = string[0]^string[1]^string[3];
        stringKey[2] = string[0]^string[2]^string[3];
        stringKey[3] = string[3];

        /*m_Comm.WriteToPort(stringKey,4)*/
    	sp.write_to_serial(stringKey,4);
    }
    else if(strPace == tr("4mm"))
    {
        string[0] = 0x34;
        string[1] = 0x01;//0x7F -
        string[2] = RandCh;//4mm
        string[3] = RandCh;
        /*指令加密……*/
        stringKey[0] = string[0]^string[3];
        stringKey[1] = string[0]^string[1]^string[3];
        stringKey[2] = string[0]^string[2]^string[3];
        stringKey[3] = string[3];

        /*m_Comm.WriteToPort(stringKey,4)*/
    	sp.write_to_serial(stringKey,4);
    }
    else
    {
        QMessageBox::warning(this,tr("Warning"),tr("Current pace is not correct"));
    }



    GearNum =0;
}
//Click 零位调整 button
void CStepDlg::ZerocorrectButton()
{
    double Movevalue;
    QString strMoveValue;

    QString strPace;
    strPace = m_pComboPace->currentText();
    /*if(strPace != tr("4mm"))
    {
        QMessageBox::warning(this,tr("Warning"),tr("请选择步距为4mm后再点击零位调整"));
    }*/
    //else
    //{
        if(MoveValueSum >= 0)//input is +
        {
            if(MoveValueSum < 200)
            {
                Movevalue = ((int)(MoveValueSum+200))/200.0-1;
            }
            else
            {
                Movevalue = ((int)MoveValueSum)/200.0;
            }

            strMoveValue = QString::number(Movevalue);
            m_pList->addItem(tr("总计向前移动") + strMoveValue + tr("微步（mm）\r\n"));/*show the message in mainwindow*/
        }
        else//input is -
        {
            if(MoveValueSum < 200)
            {
                Movevalue = ((int)(MoveValueSum+200))/200.0-1;
            }
            else
            {
                Movevalue = ((int)MoveValueSum)/200.0;
            }
            strMoveValue = QString::number(-Movevalue);
            m_pList->addItem(tr("总计反向移动") + strMoveValue + tr("微步（mm）\r\n"));/*show the message in mainwindow*/
        }

        int MoveInt1 = (int)MoveValueSum;

        int RandNum;
        char RandCh;
        RandNum = rand()%128;
        RandCh = (char)RandNum;

        char string[4],stringKey[4];
        if(MoveInt1 >= 0 && MoveInt1 <= 32767)
        {
            string[0] = 0x38;
            string[1] = MoveValueSum/256;
            string[2] = 0x00;
            string[3] = MoveValueSum%256;
            /*指令加密……*/
            stringKey[0] = string[0]^string[3];
            stringKey[1] = string[0]^string[1]^string[3];
            stringKey[2] = string[0]^string[2]^string[3];
            stringKey[3] = string[3];
            /*m_Comm.WriteToPort(stringKey,4)*/
            MoveValueSum = 0;
            sp.write_to_serial(stringKey,4);
        }
        else if(MoveInt1 < 0 && MoveInt1 >= -32768)
        {
            string[0] = 0x38;
            string[1] = MoveValueSum/256 - 1;
            string[2] = 0x01;
            string[3] = MoveValueSum%256;
            /*指令加密……*/
            stringKey[0] = string[0]^string[3];
            stringKey[1] = string[0]^string[1]^string[3];
            stringKey[2] = string[0]^string[2]^string[3];
            stringKey[3] = string[3];
            /*m_Comm.WriteToPort(stringKey,4)*/
            MoveValueSum = 0;
    	    sp.write_to_serial(stringKey,4);
        }
        else
        {
            QMessageBox::warning(this,tr("Warning"),tr("Distance has been out of range"));//有点问题！！！！
        }

        CorrectNum = CorrectNum + 1;

        QString strCorrectNum;
        strCorrectNum = QString::number(CorrectNum);
        m_pList->addItem(tr("(零位调整)已矫正齿数：") + strCorrectNum + tr("\r\n"));

        //QString strPace;
        //strPace = m_pComboPace->currentText();
        if(strPace == tr("4mm") && CorrectNum == 40)
        {
            switch(QMessageBox::question(this,"Question",tr("是否将矫正数据写入至EEPROM？"),QMessageBox::Yes |QMessageBox::No,QMessageBox::Yes))
            {
            case QMessageBox::Yes:
                CorrectNum = 0;
            case QMessageBox::No:
                CorrectNum = 0;
            default:
                break;
            }

        }
        MoveValueSum = 0;
    //}
}
//Click 单齿调整 button
void CStepDlg::SinglecorrectButton()
{
    QString strPace;
    strPace = m_pComboPace->currentText();

    int MoveInt2 = (int)MoveValueSum;

    int RandNum;
    char RandCh;
    RandNum = rand()%128;
    RandCh = (char)RandNum;
    char string[4],stringKey[4];


   if(strPace == ("2mm") || ("4mm"))
    {

        if(strPace == tr("2mm"))
        {

            if(MoveInt2 >= 0 && MoveInt2 <= 32767)
            {
                string[0] = 0x39;
                string[1] = GearNum + (0 << 7);
                string[2] = MoveValueSum/256;
                string[3] = MoveValueSum%256;
                /*指令加密……*/
                stringKey[0] = string[0]^string[3];
                stringKey[1] = string[0]^string[1]^string[3];
                stringKey[2] = string[0]^string[2]^string[3];
                stringKey[3] = string[3];

                /*m_Comm.WriteToPort(stringKey,4)*/
                sp.write_to_serial(stringKey,4);
                GearNum = GearNum + 1;
            }
            else if(MoveInt2 >= -32768 && MoveInt2 < 0)
            {
                string[0] = 0x39;
                string[1] = GearNum + (0 << 7);
                string[2] = MoveValueSum/256 - 1;
                string[3] = MoveValueSum%256;
                /*指令加密……*/
                stringKey[0] = string[0]^string[3];
                stringKey[1] = string[0]^string[1]^string[3];
                stringKey[2] = string[0]^string[2]^string[3];
                stringKey[3] = string[3];

                /*m_Comm.WriteToPort(stringKey,4)*/
    		sp.write_to_serial(stringKey,4);
                GearNum = GearNum + 1;
            }
            else
            {
                QMessageBox::warning(this,tr("Warning"),tr("Distance has been out of range"));//有点问题！！！！
            }
            if(strPace == tr("2mm") && GearNum == 80)
            {
                string[0] = 0x40;
                string[1] = 0x00;
                string[2] = RandCh;
                string[3] = RandCh;
                /*指令加密……*/
                stringKey[0] = string[0]^string[3];
                stringKey[1] = string[0]^string[1]^string[3];
                stringKey[2] = string[0]^string[2]^string[3];
                stringKey[3] = string[3];

                switch(QMessageBox::question(this,"Question",tr("80个齿已矫正结束，是否写入EEPROM？"),QMessageBox::Yes |QMessageBox::No,QMessageBox::Yes))
                {
                case QMessageBox::Yes:
                    /*m_Comm.WriteToPort(stringKey,4)*/
		    //SuperTerminal sp;
		    sp.write_to_serial(stringKey,4);
                    GearNum = 0;
                case QMessageBox::No:
                    GearNum = 0;
                default:
                    break;
                }
                MoveValueSum = 0;
            }

        }
        else
        {
            if(MoveInt2 >= 0 && MoveInt2 <= 32767)
            {
                string[0] = 0x39;
                string[1] = GearNum + (1 << 7);
                string[2] = MoveValueSum/256;
                string[3] = MoveValueSum%256;
                //*指令加密……*/
                stringKey[0] = string[0]^string[3];
                stringKey[1] = string[0]^string[1]^string[3];
                stringKey[2] = string[0]^string[2]^string[3];
                stringKey[3] = string[3];

                /*m_Comm.WriteToPort(stringKey,4)*/
    		sp.write_to_serial(stringKey,4);
                GearNum = GearNum + 1;
            }
            else if(MoveInt2 >= -32768 && MoveInt2 < 0)
            {
                string[0] = 0x39;
                string[1] = GearNum + (1 << 7);
                string[2] = MoveValueSum/256 - 1;
                string[3] = MoveValueSum%256;
                /*指令加密……*/
                stringKey[0] = string[0]^string[3];
                stringKey[1] = string[0]^string[1]^string[3];
                stringKey[2] = string[0]^string[2]^string[3];
                stringKey[3] = string[3];

                /*m_Comm.WriteToPort(stringKey,4)*/
    		sp.write_to_serial(stringKey,4);
                GearNum = GearNum + 1;
            }
            else
            {
                QMessageBox::warning(this,tr("Warning"),tr("Distance has been out of range"));//有点问题！！！！
            }

            if(strPace == tr("4mm") && GearNum == 40)
            {
                string[0] = 0x40;
                string[1] = 0x01;
                string[2] = RandCh;
                string[3] = RandCh;
                /*指令加密……*/
                stringKey[0] = string[0]^string[3];
                stringKey[1] = string[0]^string[1]^string[3];
                stringKey[2] = string[0]^string[2]^string[3];
                stringKey[3] = string[3];

                switch(QMessageBox::question(this,"Question",tr("40个齿已矫正结束，是否写入EEPROM？"),QMessageBox::Yes |QMessageBox::No,QMessageBox::Yes))
                {
                case QMessageBox::Yes:
                    /*m_Comm.WriteToPort(stringKey,4)*/
		    //SuperTerminal sp;
		    sp.write_to_serial(stringKey,4);
                    GearNum = 0;
                case QMessageBox::No:
                    GearNum = 0;
                default:
                    break;
                }
            }
            MoveValueSum = 0;
        }
    }
   else
   {
       QMessageBox::warning(this,tr("Warning"),tr("Please change pace 2mm/4mm"));
   }
}

//Click 数据重置 button
 void CStepDlg::DataresetButton()
 {
     QString strDatareset;
     strDatareset = m_pComboDataReset->currentText();

     int RandNum;
     char RandCh;
     RandNum = rand()%128;
     RandCh = (char)RandNum;
     char string[4],stringKey[4];

     if(strDatareset == tr(""))
     {
         QMessageBox::warning(this,tr("Warning"),tr("Please change Datareset"));
     }
     else
     {
         switch(QMessageBox::question(this,"Question",tr("是否确定清除数据？"),QMessageBox::Yes |QMessageBox::No,QMessageBox::Yes))
         {
         case QMessageBox::Yes:

            if(strDatareset == tr("清除全部数据"))
            {
                string[0] = 0x41;
                string[1] = 0x00;
                string[2] = RandCh;
                string[3] = RandCh;
                /*指令加密……*/
                stringKey[0] = string[0]^string[3];
                stringKey[1] = string[0]^string[1]^string[3];
                stringKey[2] = string[0]^string[2]^string[3];
                stringKey[3] = string[3];

                /*m_Comm.WriteToPort(stringKey,4)*/
    		sp.write_to_serial(stringKey,4);
                m_pList->addItem(tr("清除全部数据") + tr("\r\n"));
            }
            if(strDatareset == tr("重置矫正数据"))
            {
                string[0] = 0x41;
                string[1] = 0x01;
                string[2] = RandCh;
                string[3] = RandCh;
                /*指令加密……*/
                stringKey[0] = string[0]^string[3];
                stringKey[1] = string[0]^string[1]^string[3];
                stringKey[2] = string[0]^string[2]^string[3];
                stringKey[3] = string[3];

                /*m_Comm.WriteToPort(stringKey,4)*/
    		sp.write_to_serial(stringKey,4);
                m_pList->addItem(tr("重置矫正数据") + tr("\r\n"));
            }
            if(strDatareset == tr("清除全齿数据"))
            {
                string[0] = 0x41;
                string[1] = 0x02;
                string[2] = RandCh;
                string[3] = RandCh;
                /*指令加密……*/
                stringKey[0] = string[0]^string[3];
                stringKey[1] = string[0]^string[1]^string[3];
                stringKey[2] = string[0]^string[2]^string[3];
                stringKey[3] = string[3];

                /*m_Comm.WriteToPort(stringKey,4)*/
    		sp.write_to_serial(stringKey,4);
                m_pList->addItem(tr("清除全齿数据") + tr("\r\n"));
            }
            if(strDatareset == tr("清除半齿数据"))
            {
                string[0] = 0x41;
                string[1] = 0x03;
                string[2] = RandCh;
                string[3] = RandCh;
                /*指令加密……*/
                stringKey[0] = string[0]^string[3];
                stringKey[1] = string[0]^string[1]^string[3];
                stringKey[2] = string[0]^string[2]^string[3];
                stringKey[3] = string[3];

                /*m_Comm.WriteToPort(stringKey,4)*/
    		sp.write_to_serial(stringKey,4);
                m_pList->addItem(tr("清除半齿数据") + tr("\r\n"));
            }

        case QMessageBox::No:
             ;
        default:
            break;
        }
    }
}


