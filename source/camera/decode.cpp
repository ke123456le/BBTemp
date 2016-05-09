#include <stdio.h>
#include <stdlib.h>
#include "decode.h"


#include <QDebug>

typedef void (*pFunc)(j_common_ptr cinfo);



DeCode::DeCode()
{

}



//===soft decode
SoftDeCode::SoftDeCode()
{

}


static void test_error(j_common_ptr cinfo)
{
    qDebug()<<__func__<<"Error:";
    struct jpeg_error_manager * JpgErr = (struct jpeg_error_manager *) cinfo->err;
    qDebug()<<__func__<<" Found Error";
    longjmp(JpgErr->setjmp_buffer, 1);
}

static void JpgDeCodeErrPro(j_common_ptr cinfo)
{
    qDebug()<<__func__<<"Error:";
    struct jpeg_error_manager * JpgErr = (struct jpeg_error_manager *) cinfo->err;
    qDebug()<<__func__<<" Found Error";
    longjmp(JpgErr->setjmp_buffer, 1);
}

int SoftDeCode::mJpgDeCode (unsigned char *jpegPtr, int jpegSize, unsigned char *yuvPtr)
{
 #if 1
     //struct jpeg_decompress_struct cinfo;
     //struct jpeg_error_manager jerr;
     JSAMPARRAY buffer;            /* Output row buffer */
     int row_stride;

     unsigned char *outPtr = yuvPtr;

     FILE *infile = (FILE *)fmemopen(jpegPtr, jpegSize, "r");
     if (!infile){
         qDebug()<<__func__<<"File Fail";
         return __BT_DECODE_FAIL;
     }
 #if 0
     unsigned char *tmpBuf = (unsigned char *)malloc(jpegSize*2);
     fread(tmpBuf, jpegSize, 1, infile);
     FILE *outFile = fopen("./123pp.jpg", "wb");
     if (!outFile){
         free(tmpBuf);
         qDebug()<<__func__<<"";
         return __BT_DECODE_FAIL;
     }

     fwrite(tmpBuf, jpegSize, 1, outFile);
     fclose(outFile);
 #endif

     //qDebug()<<__func__<<" jpeg_std_error";
     cinfo.err = jpeg_std_error(&jerr.pub);
     //jerr.pub.error_exit = (pFunc*)(this->jpgDeCodeErrPro);
     jerr.pub.error_exit = test_error;

     if(setjmp(jerr.setjmp_buffer)){
         jpeg_destroy_decompress(&cinfo);
         fclose(infile);

         return __BT_DECODE_FAIL;
     }

     /* Now we can initialize the JPEG decompression object. */
     jpeg_create_decompress(&cinfo);
     /* specify data source (eg, a file) */
     jpeg_stdio_src(&cinfo, infile);
     /* read file parameters with jpeg_read_header() */
     (void) jpeg_read_header(&cinfo, TRUE);

     //cinfo.out_color_space = JCS_YCbCr;
     cinfo.out_color_space = JCS_GRAYSCALE;

     //cinfo.raw_data_out = TRUE;
     //cinfo.do_fancy_upsampling = FALSE;

     (void) jpeg_start_decompress(&cinfo);
     row_stride = cinfo.output_width * cinfo.output_components;

     //qDebug()<<__func__<<cinfo.output_scanline;
     //qDebug()<<__func__<<cinfo.output_height;
     int image_size = row_stride * cinfo.output_height;

     buffer = (*cinfo.mem->alloc_sarray) ((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);
     //qDebug()<<__func__<<" jpeg_read_scanlines";
     for(unsigned int i = 0; i < cinfo.output_height; i++){
         int num_rows = jpeg_read_scanlines(&cinfo, buffer, 1);
         if (num_rows == 0) {
             break;
         }
         if (outPtr){
             //memcpy(outPtr, buffer, row_stride);
             //outPtr += row_stride;
             for(int j = 0; j < row_stride; j += 1)
             {
                 //r = (int)buffer[0][i];
                 //g = (int)buffer[0][i + 1];
                 //b = (int)buffer[0][i + 2];

                 *outPtr++ = (int)buffer[0][j];
                 //*outPtr++ = (int)buffer[0][j + 1];
                 //*outPtr++ = (int)buffer[0][j + 2];
             }
         }else{
             break;
         }
         //qDebug()<<__func__<<" i="<<i<<"row_stride"<<row_stride<<"out_color_space"<<cinfo.out_color_space;
     }

     (void) jpeg_finish_decompress(&cinfo);

     /* Release JPEG decompression object */
     jpeg_destroy_decompress(&cinfo);

     fclose(infile);

     return image_size;
 #endif
}





