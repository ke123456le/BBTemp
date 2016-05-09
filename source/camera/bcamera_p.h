#ifndef BCAMERA_P
#define BCAMERA_P

#include <QVideoFrame>

#include "bcamerawidget.h"

#if 0
class BCameraWidgetPrivate
{
    //Q_DECLARE_PUBLIC(BCameraWidget)
public:
    QVideoFrame m_frame;
    QImage m_image;
};
#endif

/* YUV向RGB转换类 */
class CYuvToRgb
{
    int m_RV[256], m_GU[256], m_GV[256], m_BU[256];	// 预转换表
    unsigned char _C_P[2048], *m_CP;							// 8BCLIP表

    unsigned char *m_pRgb; int m_nWd, m_nHi;					// 图及宽高

private: /*--------------------------------------------*/

    /* 生成YUV2RGB所使用的参数表(倍乘2的16次幂) */
    void GenYuvRgbTbl(int *nVal/*[256]*/, double dCof)
    {
        const int nAdd = 128;
        for(int i=0; i<256; i++)
        {
            nVal[i] = (int)((i - nAdd) * dCof * 0x10000);
        }
    }

    /* 生成[-227, 479]内规整到[0, 255]查表 */
    unsigned char *Gen8bitClipTbl(unsigned char *pTbl/*[2048]*/)
    {
        const int nOfs = 1024;
        for(int i=0; i<2048; i++) /* 由RGB中最大范围来确定 */
        {
            int k = i - nOfs;
            pTbl[i] = (unsigned char)((k < 0) ? 0 : ((k > 255) ? 255 : k));
        }
        return (pTbl + nOfs);
    }

    /* 确保整数在[0, 255]之间(8-Bit字节)，输出R-G-B计算 */
    #define CALC_RGB(vRgb, tY, tU, tV) \
    { \
        *(vRgb)++ = m_CP[tY + (m_RV[tV]>>16)]; \
        *(vRgb)++ = m_CP[tY - (m_GU[tU]>>16) - (m_GV[tV]>>16)]; \
        *(vRgb)++ = m_CP[tY + (m_BU[tU]>>16)]; \
    }

public: /*---------------------------------------------*/

    /*
    R = Y + (V - 128) * 1.4022
    G = Y - (U - 128) * 0.3456 - (V - 128) * 0.7145
    B = Y + (U - 128) * 1.7710
    */
    CYuvToRgb() /* 实为YCbCr->RGB转换 */
    {
        GenYuvRgbTbl(m_RV, 1.4022); // R-V表
        GenYuvRgbTbl(m_GU, 0.3456); // G-U表
        GenYuvRgbTbl(m_GV, 0.7145); // G-V表
        GenYuvRgbTbl(m_BU, 1.7710); // B-U表
        m_CP = Gen8bitClipTbl(_C_P); // [0,255]表
        m_pRgb = NULL;
    }

    ~CYuvToRgb()
    {
        if(m_pRgb) {delete[] m_pRgb; m_pRgb = NULL;}
    }

public: /*---------------------------------------------*/

    /* 将YUV的分别3个独立平面，转换为R-G-B格式(内部自动释放) */
    unsigned char *Do422Flat(const unsigned char *pY, const unsigned char *pU, const unsigned char *pV,
                int iWd, int iHi)
    {
        if(m_pRgb) delete[] m_pRgb; // 释放已有的
        int nIsz = iWd * iHi;

        m_pRgb = new unsigned char[nIsz * 3]; // 分配RGB图像
        if(!m_pRgb) return (NULL);

        m_nWd = iWd; m_nHi = iHi; // 记下宽和高
        unsigned char *pDst = m_pRgb;

        for(int k=0; k<nIsz; k++) // 逐点YUV->RGB
        {
            CALC_RGB(pDst, *pY, *pU, *pV);
            pY++;
            //if(k & 1) {pU++; pV++;}
            if(k & 1) {pU+=2; pV+=2;}
        }
        return (m_pRgb); // 返回RGB图像区首指针，外部不必释放
    }

    /* 将YUV的分别3个独立平面，转换为R-G-B格式(内部自动释放) */
    int DoYUV( unsigned char *pRGB, unsigned char *pYuv,
                int iWd, int iHi)
    {
        //m_nWd = iWd; m_nHi = iHi; // 记下宽和高
        unsigned char *pDst = pRGB;

        unsigned char *pY = pYuv;
        unsigned char *pU = pYuv + 1;
        unsigned char *pV = pYuv + 3;
        int nIsz = iWd * iHi;

        for(int k=0; k<nIsz; k++) // 逐点YUV->RGB
        {
            CALC_RGB(pDst, *pY, *pU, *pV);
            pY+=2;
            //if(k & 1) {pU++; pV++;}
            if(k & 1) {pU+=4; pV+=4;}
        }
        //return (m_pRgb); // 返回RGB图像区首指针，外部不必释放
        return 0;
    }
#if 0
    /* 保存到指定的图像文件(依扩展名确定保存格式) */
    BOOL SaveToFile(LPCTSTR chFile)
    {
        return (SaveImgFile(chFile, m_pRgb, m_nWd, m_nHi, 0, 0, -1, 0));
    }
#endif
};


#endif // BCAMERA_P

