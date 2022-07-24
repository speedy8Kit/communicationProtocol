#ifndef __CREATORSCOMPONENTS_H__
#define __CREATORSCOMPONENTS_H__

#include "Contents.h"
#include "StructsForMessage.h"

class CreatorContents
{
public:
    static ACBaseContent *createContent(ETypeMsg msg_type, const char* buf, unsigned int size = 0);
};

#endif // __CREATORSCOMPONENTS_H__