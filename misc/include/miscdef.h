#ifndef MISC_DEF_H
#define MISC_DEF_H

#if defined WIN32 && defined MISCAPI_EXPORTS
#define MISC_EXPORTS __declspec(dllexport)
#else
#define MISC_EXPORTS 
#endif

#endif //MISC_DEF_H
