#ifndef __HW_JPEG_H__
#define __HW_JPEG_H__


#ifdef __cplusplus
extern "C" {
#endif


int JpegCodeInit();

int JpegCodeRelease();

int JpegCodeDecode(char *buf, int size, char **oBuf, int *oWidth, int *oHeight);


#ifdef __cplusplus
}
#endif

#endif