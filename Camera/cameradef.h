#ifndef CAMERA_DEF_H
#define CAMERA_DEF_H

#if defined WIN32 && defined CAMAPI_EXPORTS
#define CAM_EXPORTS __declspec(dllexport)
#else
#define CAM_EXPORTS 
#endif

#endif //CAMERA_DEF_H
