#ifndef DECODE_H
#define DECODE_H


class DeCode
{
public:
    DeCode();

    virtual int mJpgDeCode(unsigned char *jpegPtr, int jpegSize,
                           unsigned char *yuvPtr)=0;
};

#endif // DECODE_H
