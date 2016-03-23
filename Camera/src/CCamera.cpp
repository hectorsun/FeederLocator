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


  //ÿ�η��ʹ�������֮ǰ��ղɼ��������
  //��ֹ���ڲ�����֡����ɱ���GXGetImage�õ���ͼ�����ϴη��ʹ����õ���ͼ
  if ( GX_STATUS_SUCCESS != (emStatus = GXFlushQueue(m_hDevice))){
    cout <<"failed to flush queue:"<<emStatus<<endl;
    return 4;
  }

  //������������
  if ( GX_STATUS_SUCCESS != (emStatus = GXSendCommand(m_hDevice,GX_COMMAND_TRIGGER_SOFTWARE))){
    cout << "failed to send command: "<< emStatus << endl;
    return 5;
  }

  cout << "get image" << endl;

  //��ȡͼ��
  if ( GX_STATUS_SUCCESS != (emStatus = GXGetImage(m_hDevice, &m_stFrameData, m_nEditTimeOut))){
    cout << "failed to get image : " << emStatus <<endl;
    return 6;
  }

  // ת����ʽ
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


  // ��ʼ���豸�򿪲���,Ĭ�ϴ����Ϊ1���豸
  stOpenParam.accessMode = GX_ACCESS_EXCLUSIVE;
  stOpenParam.openMode   = GX_OPEN_INDEX;
  stOpenParam.pszContent = "1";

  // ��ö���б��еĵ�һ̨�豸
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

  // ��ȡ���ص��С
  emStatus = GXGetEnum(m_hDevice, GX_ENUM_PIXEL_SIZE, &nPixelSize);
  //VERIFY_STATUS_RET(emStatus);

  // �ж�Ϊ8bitʱֱ�ӷ���,��������Ϊ8bit
  if (nPixelSize == GX_PIXEL_SIZE_BPP8){
    return GX_STATUS_SUCCESS;
  } else{
    // ��ȡ�豸֧�ֵ����ظ�ʽö����
    emStatus = GXGetEnumEntryNums(m_hDevice, GX_ENUM_PIXEL_FORMAT, &nEnmuEntry);
    //    VERIFY_STATUS_RET(emStatus);

    // Ϊ��ȡ�豸֧�ֵ����ظ�ʽö��ֵ׼����Դ
    nBufferSize      = nEnmuEntry * sizeof(GX_ENUM_DESCRIPTION);
    pEnumDescription = new GX_ENUM_DESCRIPTION[nEnmuEntry];

    // ��ȡ֧�ֵ�ö��ֵ
    emStatus         = GXGetEnumDescription(m_hDevice, GX_ENUM_PIXEL_FORMAT, pEnumDescription, &nBufferSize);
    if (emStatus != GX_STATUS_SUCCESS){
      if (pEnumDescription != NULL){
	delete []pEnumDescription;
	pEnumDescription = NULL;
      }

      return emStatus;
    }

    // �����豸֧�ֵ����ظ�ʽ,�������ظ�ʽΪ8bit,
    // ���豸֧�ֵ����ظ�ʽΪMono10��Mono8��������ΪMono8
    for (uint32_t i = 0; i<nEnmuEntry; i++)	{
      if ((pEnumDescription[i].nValue & GX_PIXEL_8BIT) == GX_PIXEL_8BIT){
	emStatus = GXSetEnum(m_hDevice, GX_ENUM_PIXEL_FORMAT, pEnumDescription[i].nValue);
	break;
      }
    }	

      // �ͷ���Դ
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

  //���òɼ�ģʽ�����ɼ�
  emStatus = GXSetEnum(m_hDevice,GX_ENUM_ACQUISITION_MODE, GX_ACQ_MODE_CONTINUOUS);
  //VERIFY_STATUS_RET(emStatus);
	
	//���ô���ģʽΪ��
  emStatus = GXSetEnum(m_hDevice,GX_ENUM_TRIGGER_MODE, GX_TRIGGER_MODE_ON);

	// ��֪��ǰ���֧���ĸ�8λͼ�����ݸ�ʽ����ֱ������
	// �����豸֧�����ݸ�ʽGX_PIXEL_FORMAT_BAYER_GR8,��ɰ������´���ʵ��
	// emStatus = GXSetEnum(m_hDevice, GX_ENUM_PIXEL_FORMAT, GX_PIXEL_FORMAT_BAYER_GR8);
	// VERIFY_STATUS_RET(emStatus);

	// �������ǰ��������ݸ�ʽʱ�����Ե���SetPixelFormat8bit������ͼ�����ݸ�ʽ����Ϊ8Bit
  emStatus = __SetPixelFormat8bit(); 

 
	//ѡ�񴥷�ԴΪ����
  emStatus = GXSetEnum(m_hDevice,GX_ENUM_TRIGGER_SOURCE, GX_TRIGGER_SOURCE_SOFTWARE);
  
  return emStatus;
}

GX_STATUS 
CCameraImpl::__GetDeviceInitParam()
{
  GX_STATUS emStatus       = GX_STATUS_ERROR;
  bool      bIsImplemented = false;

  // ��ѯ��ǰ����Ƿ�֧��GX_ENUM_PIXEL_COLOR_FILTER
  //emStatus = GXIsImplemented(m_hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &bIsImplemented);
  //VERIFY_STATUS_RET(emStatus);
  //m_bIsColorFilter = bIsImplemented;

  // ֧�ֱ�ʾ�����ɫͼ��
  //if(bIsImplemented)
  //{
  //	emStatus = GXGetEnum(m_hDevice, GX_ENUM_PIXEL_COLOR_FILTER, &m_nPixelColorFilter);
  //	VERIFY_STATUS_RET(emStatus);
  //}

  // ��ȡ���
  emStatus = GXGetInt(m_hDevice, GX_INT_WIDTH, &m_imgWidth);
  //VERIFY_STATUS_RET(emStatus);

  // ��ȡ�߶�
  emStatus = GXGetInt(m_hDevice, GX_INT_HEIGHT, &m_imgHeight);
  //VERIFY_STATUS_RET(emStatus);
  
  // ��ȡͼ���С
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

  // ö���豸
  if (GX_STATUS_SUCCESS != (emStatus = GXUpdateDeviceList(&nDevNum, 1000))){
    cout << "failed to get camera num"<<endl;
    return NULL;
  }
  cout <<"Camera num:"<< nDevNum <<endl;

  // �жϵ�ǰ�����豸����
  if (nDevNum <= 0){
    cout <<"no camera found"<<endl;
    return NULL;
  } 


  //�����
  if ( GX_STATUS_SUCCESS != (emStatus = __OpenDevice())){
    cout << "failed to open device" <<endl;
    return NULL;
  }


  //�����豸��Ĭ�ϲ������ɼ�ģʽ:�����ɼ�,��������:��,����Դ:����,���ݸ�ʽ:8-bit
  if ( GX_STATUS_SUCCESS != (emStatus = __InitDevice())){

    cout << "failed to Init Device" <<endl;
    return NULL;
  }

  //��ȡ�豸�Ŀ�ߵ���Ϣ
  if ( GX_STATUS_SUCCESS != ( emStatus = __GetDeviceInitParam())){
    cout << "failed to init param" <<endl;
    return NULL;
  }

  // �����ڴ�
  m_stFrameData.pImgBuf     = new BYTE[(size_t)m_nPayLoadSize];
  m_pImgBuffer = new BYTE[(size_t)m_nPayLoadSize*3];

  return emStatus;
}

GX_STATUS
CCameraImpl::CloseDevice()
{
  cout <<"close device"<<endl;

  GX_STATUS emStatus = GX_STATUS_ERROR;

  // �ͷ���Դ
  //UnPrepareForShowImg();
	
  // �ر��豸
  emStatus = GXCloseDevice(m_hDevice);

  return emStatus;
}

GX_STATUS
CCameraImpl::__StartSnap(){
  GX_STATUS emStatus = GX_STATUS_SUCCESS;
  
  // ʹ��GxGetImage��ȡͼ��,ֻ��Ҫ���Ϳ�������
  // ���Ϳ�������
  emStatus = GXSendCommand(m_hDevice,GX_COMMAND_ACQUISITION_START);
  //GX_VERIFY(emStatus);
  if (GX_STATUS_SUCCESS != emStatus){
    cout << "failed" << endl;
  }else{
    cout << "success" << endl;
    // ���¿��ɱ�ʶ
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
