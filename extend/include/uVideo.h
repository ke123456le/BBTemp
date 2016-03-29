#ifndef __U_VIDEO_H__
#define __U_VIDEO_H__

#ifdef __cplusplus
extern "C" {
#endif

#define _MAX_NAME					64							//


typedef enum {
    YUYV_FMT = 0,
    MJPG_FMT = 1
}VIDEO_FMT;

typedef enum{
    V_FACE_VIDEO, //可见光人脸
    I_FACE_VIDEO, //近红外人脸
    I_IRIS_VIDEO  //近红外虹膜
}VIDEO_TYPE;


typedef struct{
        void    *start;
        size_t  length;
}DataBufs;

typedef struct{
    int devHandle;				//设备句柄
    unsigned int videoWidth;	//图像宽
    unsigned int videoHeight;	//图像高
    VIDEO_FMT videoFmt;			//帧格式
    VIDEO_TYPE videoType;		//摄像头类型
    int isSetExposure;		//是否设置曝光
    DataBufs *buffers;			//数据缓冲区
    unsigned int n_buffers;
    char videoName[_MAX_NAME];		//名称；如USB2.0 UVC HQ WebCam
    char devPath[_MAX_NAME];	//设备节点路径，如/dev/video3
}VideoDevice;

typedef struct{
    VideoDevice Dev;
    int idProduct;
    int idVendor;
}uVideoDevice;



int OpenCamera(VideoDevice *mDev);
int OpenUvcCamera(uVideoDevice *uDev);

int StartVideoStream(VideoDevice *mDev);
int StopVideoStream(VideoDevice *mDev);

int setVideoExposure(VideoDevice *vDev, int nexposure);
int getVideoExposure(VideoDevice *vDev, int *nexposure);

int resetVideoBuf(VideoDevice *vDev);
int initExposure(VideoDevice *vDev, int mExpVal);
int checkAndUpdateExposure(VideoDevice *vDev, unsigned char * buf, int nsize, int *nexposure);

int updateVideoFmt(VideoDevice *vDev);

//int getVideoMirror(VideoDevice *vDev, int *value);

int GetImage(VideoDevice *mDev, char *buf);
int CloseCamera(VideoDevice *mDev);



#ifdef __cplusplus
}
#endif



#endif
