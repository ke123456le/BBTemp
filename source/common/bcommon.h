#ifndef BCOMMON_H
#define BCOMMON_H


class BCommon
{
public:
    BCommon();
    static int ImageResize_f(unsigned char *src, int o_height, int o_width,
                           unsigned char *dst, int n_height, int n_width);
    static int ImageResize(unsigned char *src, int o_height, int o_width,
                           unsigned char *dst, int n_height, int n_width);
    static void Bata_ImResize(unsigned char *src, int srcRows, int srcCols,
                              unsigned char *dst, int dstRows, int dstCols);
    static void doYuvToRgb(unsigned char *rgbPtr, unsigned char *yuvPtr,
                           int iWidth, int iHight);
};

#endif // BCOMMON_H
