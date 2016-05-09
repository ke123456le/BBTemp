#include "bcommon.h"
#include "../errorcode.h"

#define  BYTE unsigned char



BCommon::BCommon()
{
     //yuvToRgb = new CYuvToRgb();
}


int BCommon::ImageResize_f(unsigned char *src, int o_height, int o_width,
                                      unsigned char *dst, int n_height, int n_width)
{
    static int o_lastWidth = 0;
    static int o_lastHeight = 0;

    static int n_lastWidth = 0;
    static int n_lastHeight = 0;

    static int m_index[1024*500] = {0};

    if (o_height<480 || o_width<640 || n_height>480 || n_width>640){
        return __BT_PARA_INVILD;
    }

    int o_len = o_width*o_height;

    if (o_lastWidth!=o_width || o_lastHeight!=o_height ||
            n_lastWidth!=n_width || n_lastHeight!=n_height)
    {
        o_lastWidth = o_width;
        o_lastHeight = o_height;
        n_lastWidth = n_width;
        n_lastHeight = n_height;

        //double scaled_w = (double)n_width/(double)o_width;
        //double scaled_h = (double)n_height/(double)o_height;

        double scaled_w = (double)o_width/(double)n_width;
        double scaled_h = (double)o_height/(double)n_height;

        for (int h=0; h<n_height; h++){
            int pos_h = ((int)(h*1*scaled_h+0.5));
            int off_o = pos_h*o_width;
            //int off_n = (h<<9)+(h<<6)+(h<<6)/*h*640*/;
            int off_n = h*n_width;
            //for (int w=0; w<640; w++){
            for (int w=0; w<n_width; w++){
                int pos_w = ((int)(w*1*scaled_w+0.5));
                int pos = off_o+pos_w;
                m_index[off_n + w] = pos;
            }
        }
    }


#if 0
    for (int h=0; h<n_height; h++){
        int pos_h = ((int)(h*1/scaled_h+0.5));
        int off_o = pos_h*o_width;
        int off_n = h*n_width;
        for (int w=0; w<n_width; w++){
            int pos_w = ((int)(w*1/scaled_w+0.5));
            int pos = off_o+pos_w;
            if (pos<o_len){
                dst[off_n + w] = src[pos];
            }else{
                dst[off_n + w] = 255;
            }
        }
    }
#endif

    for (int _h=0; _h<n_height; _h++){
        int off_n = _h*n_width;
        for (int _w=0; _w<n_width; _w++){
            int pos = (_h<<9)+(_h<<6)+(_h<<6) + _w;
            if (m_index[pos] < o_len)
                dst[off_n + _w] = src[m_index[pos]];
            else
                dst[off_n + _w] = 255;
        }
    }

    return __BT_SUCC;
}

int BCommon::ImageResize(unsigned char *src, int o_height, int o_width,
                                      unsigned char *dst, int n_height, int n_width)
{
    static int o_lastWidth = 0;
    static int o_lastHeight = 0;

    static int n_lastWidth = 0;
    static int n_lastHeight = 0;

    static int m_index[800*480] = {0};
#if 0
    if (o_height<480 || o_width<640 || n_height>480 || n_width>640){
        return __BT_PARA_INVILD;
    }
#endif

    if (n_height>480 || n_width>800)
        return __BT_DATA_INVILD;

    int o_len = o_width*o_height;

    if (o_lastWidth!=o_width || o_lastHeight!=o_height ||
            n_lastWidth!=n_width || n_lastHeight!=n_height)
    {
        o_lastWidth = o_width;
        o_lastHeight = o_height;
        n_lastWidth = n_width;
        n_lastHeight = n_height;

        //double scaled_w = (double)n_width/(double)o_width;
        //double scaled_h = (double)n_height/(double)o_height;

        double scaled_w = (double)o_width/(double)n_width;
        double scaled_h = (double)o_height/(double)n_height;

        for (int h=0; h<n_height; h++){
            int pos_h = ((int)(h*1*scaled_h+0.5));
            int off_o = pos_h*o_width;
            //int off_n = (h<<9)+(h<<6)+(h<<6)/*h*640*/;
            int off_n = h*1024;
            //for (int w=0; w<640; w++){
            for (int w=0; w<n_width; w++){
                int pos_w = ((int)(w*1*scaled_w+0.5));
                int pos = off_o+pos_w;
                m_index[off_n + w] = pos;
            }
        }
    }


#if 0
    for (int h=0; h<n_height; h++){
        int pos_h = ((int)(h*1/scaled_h+0.5));
        int off_o = pos_h*o_width;
        int off_n = h*n_width;
        for (int w=0; w<n_width; w++){
            int pos_w = ((int)(w*1/scaled_w+0.5));
            int pos = off_o+pos_w;
            if (pos<o_len){
                dst[off_n + w] = src[pos];
            }else{
                dst[off_n + w] = 255;
            }
        }
    }
#endif

    for (int _h=0; _h<n_height; _h++){
        int off_n = _h*n_width;
        for (int _w=0; _w<n_width; _w++){
            //int pos = (_h<<9)+(_h<<6)+(_h<<6) + _w;
            int pos = _h*1024 + _w;
            if (m_index[pos] < o_len)
                dst[off_n + _w] = src[m_index[pos]];
            else
                dst[off_n + _w] = 255;
        }
    }

    return __BT_SUCC;
}


void BCommon::Bata_ImResize(unsigned char *src, int srcRows, int srcCols,
                                      unsigned char *dst, int dstRows, int dstCols)
{
    int			i, j ;
    int			w_ScaleX;
    int	    	w_ScaleY;
    BYTE		*dst_ptr;
    int			*w_pIndRow = 0, *w_pIndCol = 0;
    int			*w_pWgtRow = 0, *w_pWgtCol = 0;

    int  Iris_gImg1[640*480];
    int  Iris_gImg2[640*480];
    //static int  Iris_gImg1[640*480];
    //static int  Iris_gImg2[640*480];
    int			*w_pIndX = Iris_gImg1;
    int			*w_pWgt = Iris_gImg2;

    //static int o_Rows = 0;
    //static int o_Cols = 0;
    //static int n_Rows = 0;
    //static int n_Cols = 0;

    //if (o_Rows!=srcRows || o_Cols!=srcCols || n_Rows!=dstRows || n_Cols!=dstCols)
    {
        //o_Rows = srcRows;
        //o_Cols = srcCols;
        //n_Rows = dstRows;
        //n_Cols = dstCols;

        //.========== Build Index =====================

        w_ScaleX = 1024 * (srcCols - 1) / (dstCols - 1);
        w_ScaleY = 1024 * (srcRows - 1) / (dstRows - 1);

        w_pIndX += 2 * dstRows;
        w_pWgt += 2 * dstRows;
        for( i = 0 ; i < dstCols ; i ++ ){
            int w_Temp = w_ScaleX * i;
            int w_Ind1 = w_Temp >> 10;
            int w_Temp1 = w_Temp - ( w_Ind1 << 10 );
            if ( w_Ind1 >= srcCols - 1 ){
                w_pIndX[i * 2] = srcCols-1;
                w_pIndX[i * 2 + 1] = srcCols-1;
                w_pWgt[i * 2] = 1024;
                w_pWgt[i * 2 + 1] = 0;
            }else{
                w_pIndX[i * 2] = w_Ind1;
                w_Ind1 ++;
                w_pIndX[i * 2 + 1] = w_Ind1;
                w_pWgt[i * 2] = 1024 - w_Temp1;
                w_pWgt[i * 2 + 1] = w_Temp1;
            }
        }
        w_pIndX -= 2 * dstRows;
        w_pWgt -= 2 * dstRows;

        for( i = 0; i < dstRows; i ++ ){
            int w_Temp = w_ScaleY * i;
            int w_Ind1 = w_Temp >> 10;
            int w_Temp1 = w_Temp - ( w_Ind1 << 10 );
            if ( w_Ind1 >= srcRows-1 ){
                w_pIndX[i * 2] = srcRows-1;
                w_pIndX[i * 2 + 1] = srcRows-1;
                w_pWgt[i * 2] = 1024;
                w_pWgt[i * 2 + 1] = 0;
            }else{
                w_pIndX[i * 2] = w_Ind1;
                w_Ind1 ++;
                w_pIndX[i * 2 + 1] = w_Ind1;
                w_pWgt[i * 2] = 1024 - w_Temp1;
                w_pWgt[i * 2 + 1] = w_Temp1;
            }
        }
        //..========== Build Index =====================
    }


    //.========== Interpolation =====================
    w_pIndRow = w_pIndX;
    w_pWgtRow = w_pWgt;

    dst_ptr = dst;
    for( i = 0; i < dstRows; i ++ ){
        w_pIndCol = w_pIndX + 2 * dstRows;
        w_pWgtCol = w_pWgt + 2 * dstRows;

        BYTE * t1 = src + w_pIndRow[0] * srcCols;
        BYTE * t2 = src + w_pIndRow[1] * srcCols;

        int w1 = w_pWgtRow[0];
        int w2 = w_pWgtRow[1];
        for( j = 0; j < dstCols; j ++ ){
            int w_Temp =  t1[ w_pIndCol[0] ] * w1 * w_pWgtCol[0] +
                t1[ w_pIndCol[1] ] * w1 * w_pWgtCol[1] +
                t2[ w_pIndCol[1] ] * w2 * w_pWgtCol[1] +
                t2[ w_pIndCol[0] ] * w2 * w_pWgtCol[0];

            *dst_ptr++ = (BYTE)( (w_Temp + ( 1 << 19 ) ) >> 20);

            w_pIndCol += 2;
            w_pWgtCol += 2;
        }
        w_pIndRow += 2;
        w_pWgtRow += 2;
    }

    //..========== Interpolation =====================
    w_pIndCol = w_pIndRow = 0;
    w_pWgtRow = w_pWgtCol = 0;

}//..ImResize


