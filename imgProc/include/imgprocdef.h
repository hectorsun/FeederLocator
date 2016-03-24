#ifndef IMG_PROC_DEF_H
#define IMG_PROC_DEF_H

#if defined WIN32 && defined IMGPROCAPI_EXPORTS
#define IMGPROC_EXPORTS __declspec(dllexport)
#else
#define IMGPROC_EXPORTS 
#endif

#endif //CAMERA_DEF_H
