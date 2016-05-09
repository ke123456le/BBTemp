#ifndef DECODE_H
#define DECODE_H

#include <setjmp.h>
#include "extend/include/jpeglib.h"
#include "../errorcode.h"

class DeCode
{
public:
    DeCode();

    virtual int mJpgDeCode(unsigned char *jpegPtr, int jpegSize,
                           unsigned char *yuvPtr)=0;
};



//--------------------
struct jpeg_error_manager
{
    struct jpeg_error_mgr pub;    /* "public" fields */
    jmp_buf setjmp_buffer;        /* for return to caller */
};

class SoftDeCode : public DeCode
{
public:
    SoftDeCode();

    int mJpgDeCode (unsigned char *jpegPtr, int jpegSize, unsigned char *yuvPtr);


private:
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_manager jerr;
};

#endif // DECODE_H
