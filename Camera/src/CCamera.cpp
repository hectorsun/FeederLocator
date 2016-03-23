#include <Camera/CCamera.h>
#include <iostream>
using std::cout;
using std::endl;

#include <GxIAPI.h>
#include <Opencv2/opencv.hpp>
#include <memory>

class CCameraImpl : public CCamera{
public:
  CCameraImpl(){}
  ~CCameraImpl(){}

  ///////////////////////////////////
  virtual int init();
  virtual int snap();

  ////////////////////////////////////
  virtual int getWidth();
  virtual int getHeight() ;
  virtual unsigned char* getData();


private:
  GX_STATUS __OpenDevice();
  
  GX_STATUS __SetPixelFormat8bit();
  GX_STATUS __InitDevice();
  GX_STATUS __GetDeviceInitParam();
  GX_STATUS OpenDevice();
  GX_STATUS CloseDevice();

  GX_STATUS __StartSnap();

  

  int64_t    m_nPayLoadSize;
  GX_DEV_HANDLE m_hDevice;
  GX_FRAME_DATA m_stFrameData;
  BYTE* m_pImgBuffer;

private:
  int64_t m_imgWidth;
  int64_t m_imgHeight;
  unsigned char*  m_imgData;
  int m_imgSize;
};



int 
CCameraImpl::getWidth(){
  return (int)m_imgWidth;}
int 
CCameraImpl::getHeight() {
  return (int)m_imgHeight;}
unsigned char* 
CCameraImpl::getData() {
  return m_imgData;
}


int
CCameraImpl::init()
{
  std::cout<<"CCamera::init()"<<std::endl;
  memset(&m_stFrameData, 0, sizeof(GX_FRAME_DATA));

  if (GX_STATUS_SUCCESS != GXInitLib()){
    cout<<"failed to init lib"<<endl;
    return 1;
  }
  if (GX_STATUS_SUCCESS != OpenDevice()){
    cout<<"failed to openDevice"<<endl;
    return 2;
  }

  if (GX_STATUS_SUCCESS != __StartSnap()){
    return 3;
  }

  m_imgSize = (int)( 3*m_imgWidth * m_imgHeight);
  m_imgData = new unsigned char[m_imgSize];
  return 0;
}


int
CCameraImpl::snap()
{
  GX_STATUS emStatus  = GX_STATUS_SUCCESS;
  double dElapsedtime = 0;
  //GX_FRAME_DATA  m_stFrameData;
  UINT	m_nEditTimeOut=50000;
  //PyObject *out = NULL;


  //每次发送触发命令之前清空采集输出队列
  //防止库内部缓存帧，造成本次GXGetImage得到的图像是上次发送触发得到的图
  if ( GX_STATUS_SUCCESS != (emStatus = GXFlushQueue(m_hDevice))){
    cout <<"failed to flush queue:"<<emStatus<<endl;
    return 4;
  }

  //发送软触发命令
  if ( GX_STATUS_SUCCESS != (emStatus = GXSendCommand(m_hDevice,GX_COMMAND_TRIGGER_SOFTWARE))){
    cout << "failed to send command: "<< emStatus << endl;
    return 5;
  }

  cout << "get image" << endl;

  //获取图像
  if ( GX_STATUS_SUCCESS != (emStatus = GXGetImage(m_hDevice, &m_stFrameData, m_nEditTimeOut))){
    cout << "failed to get image : " << emStatus <<endl;
    return 6;
  }

  // 转换格式
  cv::Mat imgBayer = cv::Mat((int)m_imgHeight, (int)m_imgWidth,
			     CV_8UC1, m_stFrameData.pImgBuf);
  cout<<"imgBayer"<<endl;

  cv::Mat imgRGB = cv::Mat((int)m_imgHeight, (int)m_imgWidth, 
			   CV_8UC3, m_imgData);;
  cv::cvtColor(imgBayer, imgRGB, cv::COLOR_BayerGR2RGB);
  
  //mcpy(m_imgData, imgRGB.data, m_imgSize);


  cout << "succed in getting image:" << m_stFrameData.nTimestamp<<endl;
  return 0;
}



GX_STATUS
CCameraImpl::__OpenDevice()
{
  GX_STATUS      emStatus    = GX_STATUS_SUCCESS;	
  GX_OPEN_PARAM  stOpenParam;


  // 初始化设备打开参数,默认打开序号为1的设备
  stOpenParam.accessMode = GX_ACCESS_EXCLUSIVE;
  stOpenParam.openMode   = GX_OPEN_INDEX;
  stOpenParam.pszContent = "1";

  // 打开枚举列表中的第一台设备
  emStatus = GXOpenDevice(&stOpenParam, &m_hDevice);
	

  return emStatus;

}
GX_STATUS 
CCameraImpl::__SetPixelFormat8bit()
{
  GX_STATUS emStatus    = GX_STATUS_SUCCESS;
  int64_t   nPixelSize  = 0;
  uint32_t  nEnmuEntry  = 0;
  size_t    nBufferSize = 0;
  BOOL      bIs8bit     = TRUE;

  GX_ENUM_DESCRIPTION  *pEnumDescription = NULL;
  GX_ENUM_DESCRIPTION  *pEnumTemp        = NULL;

  // 获取像素点大小
  emStatus = GXGetEnum(m_hDevice, GX_ENUM_PIXEL_SIZE, &nPixelSize);
  //VERIFY_STATUS_RET(emStatus);

  // 判断为8bit时直接返回,否则设置为8bit
  if (nPixelSize == GX_PIXEL_SIZE_BPP8){
    return GX_STATUS_SUCCESS;
  } else{
    // 获取设备支持的像素格式枚举数
    emStatus = GXGetEnumEntryNums(m_hDevice, GX_ENUM_PIXEL_FORMAT, &nEnmuEntry);
    //    VERIFY_STATUS_RET(emStatus);

    // 为获取设备支持的像素格式枚举值准备资源
    nBufferSize      = nEnmuEntry * sizeof(GX_ENUM_DESCRIPTION);
    pEnumDescription = new GX_ENUM_DESCRIPTION[nEnmuEntry];

    // 获取支持的枚举值
    emStatus         = GXGetEnumDescription(m_hDevice, GX_ENUM_PIXEL_FORMAT, pEnumDescription, &nBufferSize);
    if (emStatus != GX_STATUS_SUCCESS){
      if (pEnumDescription != NULL){
	delete []pEnumDescription;
	pEnumDescription = NULL;
      }

      return emStatus;
    }

    // 遍历设备支持的像素格式,设置像素格式为8bit,
    // 如设备支持的像素格式为Mono10和Mono8则设置其为Mono8
    for (uint32_t i = 0; i<nEnmuEntry; i++)	{
      if ((pEnumDescription[i].nValue & GX_PIXEL_8BIT) == GX_PIXEL_8BIT){
	emStatus = GXSetEnum(m_hDevice, GX_ENUM_PIXEL_FORMAT, pEnumDescription[i].nValue);
	break;
      }
    }	

      // 释放资源
    if(pEnumDescription != NULL)	{
      delete []pEnumDescription;
      pEnumDescription = NULL;
    }
  }
   
  return emStatus;
}

GX_STATUS 
CCameraImpl::__InitDevice()
{
  GX_STATUS emStatus = GX_STATUS_SUCCESS;

  //设置采集模式连续采集
  emStatus = GXSetEnum(m_hDevice,GX_ENUM_ACQUISITION_MODE, GX_ACQ_MODE_CONTINUOUS);
  //VERIFY_STATUS_RET(emStatus);
	
	//设置触发模式为开
  emStatus = GXSetEnum(m_hDevice,GX_ENUM_TRIGGER_MODE, GX_TRIGGER_MODE_ON);

	// 已知当前相机支持哪个8位图像数据格式可以直接设置
	// 例如设备支持数据格式GX_PIXEL_FORMAT_BAYER_GR8,则可按照以下代码实现
	// emStatus = GXSetEnum(m_hDevice, GX_ENUM_PIXEL_FORMAT, GX_PIXEL_FORMAT_BAYER_GR8);
	// VERIFY_STATUS_RET(emStatus);

	// 不清楚当前相机的数据格式时，可以调用SetPixelFormat8bit函数将图像数据格式设置为8Bit
  emStatus = __SetPixelFormat8bit(); 

 
	//选择触发源为软触发
  emStatus = GXSetEnum(m_hDevice,GX_ENUM_TRIGGER_SOURCE, GX_TRIGGER_SOURCE_SOFTWARE);
  
  return emStatus;
}

GX_STATUS 
CCameraImpl::__GetDeviceInitParam()
{
  GX_STATUS emStatus       = GX_STATUS_ERROR;
  bool      bIsImplemented = false;

  // 查询当前相机是否支持GX_ENUM_PIXEL_COLOR_FILTER
  //emStatus = GXIsImplemented(m_hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &bIsImplemented);
  //VERIFY_STATUS_RET(emStatus);
  //m_bIsColorFilter = bIsImplemented;

  // 支持表示输出彩色图像
  //if(bIsImplemented)
  //{
  //	emStatus = GXGetEnum(m_hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &m_nPixelColorFilter);
  //	VERIFY_STATUS_RET(emStatus);
  //}

  // 获取宽度
  emStatus = GXGetInt(m_hDevice, GX_INT_WIDTH, &m_imgWidth);
  //VERIFY_STATUS_RET(emStatus);

  // 获取高度
  emStatus = GXGetInt(m_hDevice, GX_INT_HEIGHT, &m_imgHeight);
  //VERIFY_STATUS_RET(emStatus);
  
  // 获取图像大小
  emStatus = GXGetInt(m_hDevice,GX_INT_PAYLOAD_SIZE,&m_nPayLoadSize);


  cout << "width="<<m_imgWidth<<";height="<<m_imgHeight<<";size="<<m_nPayLoadSize<<endl;

  return emStatus;
}



GX_STATUS
CCameraImpl::OpenDevice()
{
  cout <<"open device"<<endl;
  
  GX_STATUS emStatus = GX_STATUS_SUCCESS;
  bool      bRet     = true;
  uint32_t  nDevNum  = 0;

  // 枚举设备
  if (GX_STATUS_SUCCESS != (emStatus = GXUpdateDeviceList(&nDevNum, 1000))){
    cout << "failed to get camera num"<<endl;
    return NULL;
  }
  cout <<"Camera num:"<< nDevNum <<endl;

  // 判断当前连接设备个数
  if (nDevNum <= 0){
    cout <<"no camera found"<<endl;
    return NULL;
  } 


  //打开相机
  if ( GX_STATUS_SUCCESS != (emStatus = __OpenDevice())){
    cout << "failed to open device" <<endl;
    return NULL;
  }


  //设置设备的默认参数，采集模式:连续采集,触发开关:开,触发源:软触发,数据格式:8-bit
  if ( GX_STATUS_SUCCESS != (emStatus = __InitDevice())){

    cout << "failed to Init Device" <<endl;
    return NULL;
  }

  //获取设备的宽高等信息
  if ( GX_STATUS_SUCCESS != ( emStatus = __GetDeviceInitParam())){
    cout << "failed to init param" <<endl;
    return NULL;
  }

  // 分配内存
  m_stFrameData.pImgBuf     = new BYTE[(size_t)m_nPayLoadSize];
  m_pImgBuffer = new BYTE[(size_t)m_nPayLoadSize*3];

  return emStatus;
}

GX_STATUS
CCameraImpl::CloseDevice()
{
  cout <<"close device"<<endl;

  GX_STATUS emStatus = GX_STATUS_ERROR;

  // 释放资源
  //UnPrepareForShowImg();
	
  // 关闭设备
  emStatus = GXCloseDevice(m_hDevice);

  return emStatus;
}

GX_STATUS
CCameraImpl::__StartSnap(){
  GX_STATUS emStatus = GX_STATUS_SUCCESS;
  
  // 使用GxGetImage获取图像,只需要发送开采命令
  // 发送开采命令
  emStatus = GXSendCommand(m_hDevice,GX_COMMAND_ACQUISITION_START);
  //GX_VERIFY(emStatus);
  if (GX_STATUS_SUCCESS != emStatus){
    cout << "failed" << endl;
  }else{
    cout << "success" << endl;
    // 更新开采标识
  }
  return emStatus;
}


//////////////////////////////////////////////////////////////////////
 /////////////////
int 
CCamera::init(){
  m_pImpl = new CCameraImpl;
  return m_pImpl->init();
}
