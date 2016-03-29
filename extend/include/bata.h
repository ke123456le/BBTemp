#ifndef BATA_H
#define BATA_H

#pragma once
#include <string.h>
#define BATA_API //__declspec(dllexport)

#define  BYTE unsigned char

#define  IN
#define  OUT
#define  INOUT


#define		SFE_FEATURE_ADAPT				1
#define		SFE_OK							0
#define		SFE_FAILED						-1
#define		SFE_NOT_INITIALIZED				-2
#define		SFE_INVALID_ARGUMENT			-3
#define		SFE_OUT_OF_MEMORY				-5
#define		SFE_FILEIO_ERROR				-6
#define		SFE_LOCK_ERROR					-7
#define     SFE_NO_FACE                     -8
#define		SFE_DEV_ERR						-11
#define		SFE_NO_UKEY						-100
struct MYFILE
{
    unsigned char*	buf;
    int				size;
    int				pos;
};
typedef struct _rect1{
    int							left;
    int							top;
    int							right;
    int							bottom;
} RECT1, *PRECT1;
typedef struct _point{
    int							x;
    int							y;
}Point, *PPoint;

typedef struct _sf_detail_face{
    RECT1						FLoc;
    int							foundFace;
    Point						leftEye;
    Point						rightEye;
}SF_DETAIL_FACE, *PSF_DETAIL_FACE;

typedef struct _sf_feature{
    //	unsigned int				bData[POINT_NUM * SF_HEAP_SIZE];
    // 2012-06-30 Li Won Ho	// for shifted match.
    // 1st-center, 2nd-left, 3rd-right
    unsigned int				bData[5184];//[POINT_NUM * SF_HEAP_SIZE * 3];

#if TESTENGINE_PHASE
    int							PhaseCong[2304];//[POINT_NUM * DIRECTION_NUM];
#endif

#if TESTENGINE_PCA
    /*unsigned*/ int				pcaData[250];//[ PCA_TEMPLATE_DIM ];
#endif

    signed char 						Yaw			;
    signed char						WithGlass	;
    /*char*/ unsigned char				Brightness	;
    unsigned char						EyeDistance ;
    unsigned char                       Quality;
} SF_FEATURE, *PSF_FEATURE;		// 20740 byte

typedef struct _sf_feature_One{
    unsigned int				bData[1728];//[POINT_NUM * SF_HEAP_SIZE];

#if TESTENGINE_PHASE
    int							PhaseCong[2304];//[POINT_NUM * DIRECTION_NUM];
#endif

#if TESTENGINE_PCA
    /*unsigned*/ int				pcaData[250];[ PCA_TEMPLATE_DIM ];
#endif

    signed char 						Yaw			;
    signed char						WithGlass	;
    /*char*/ unsigned char				Brightness	;
    unsigned char						EyeDistance ;
    unsigned char                       Quality;
} SF_FEATURE_ONE, *PSF_FEATURE_ONE;		// 6916 byte
typedef struct	_sf_feature_set_one{
    int							count;
    SF_FEATURE_ONE				feature[5];//[ MAX_ENROLL_NUM ];
    bool						bDuplicate;

    _sf_feature_set_one()
    {
        count = 0;
        bDuplicate = false;
        memset( feature , 0 , /*MAX_ENROLL_NUM*/5 * sizeof(SF_FEATURE_ONE) );
    }

}	MY_SF_FEATURE_SET_ONE , * MY_PSF_FEATURE_SET_ONE;
//初始化,系统一开始时调用
//MYFILE *fp 读入的初始化文件
//unsigned char* pFaceDevID,只需声明变量，无需分配空间，函数内会分配空间
//unsigned char* pFaceDevSN,只需声明变量，无需分配空间，函数内会分配空间
//返回值：成功--0
//        失败--（-1）
BATA_API int BataInfraredFace_Init(IN MYFILE *fp, OUT unsigned char* pFaceDevID, OUT unsigned char* pFaceDevSN );
//系统关闭时调用
//返回值：0
BATA_API int BataInfraredFace_Finalize( );

//识别时提取的特征
//unsigned char* pimg 图像数据区域指针
//int nHeight 图像高度
//int nWidth  图像宽度
//SF_FEATURE&	feature提取的待识别特征
//返回值 0-成功
BATA_API int BataInfratedFace_GetFeature(IN unsigned char* pimg,IN int nheight,IN int nwidth,OUT SF_FEATURE&	feature,OUT SF_DETAIL_FACE *face);
//提取单个注册时的特征
//unsigned char* pimg 图像数据区域指针
//int nHeight 图像高度
//int nWidth  图像宽度
//PSF_FEATURE_ONE pfeature提取的待识别特征
//返回值 0-成功
//       -8--没有检测到人脸
BATA_API int BataInfraredFace_GetMulFeature_Single(IN unsigned char* pimg,IN  int nHeight, IN int nWidth,OUT PSF_FEATURE_ONE pfeature,OUT SF_DETAIL_FACE *face);
//由5个单个特征注册成一个特征
//PSF_FEATURE_ONE pfeature0,PSF_FEATURE_ONE pfeature1,PSF_FEATURE_ONE pfeature2,PSF_FEATURE_ONE pfeature3,PSF_FEATURE_ONE pfeature4 5个待注册的特征
//（特征个数可以为1-5，不能小于1或大于5）；
//MY_SF_FEATURE_SET_ONE* pFeature注册后的特征
//返回值 0-成功
BATA_API int BataInfraredFace_Enroll(IN PSF_FEATURE_ONE pfeature0,IN PSF_FEATURE_ONE pfeature1,IN PSF_FEATURE_ONE pfeature2,IN PSF_FEATURE_ONE pfeature3,IN PSF_FEATURE_ONE pfeature4,
    OUT MY_SF_FEATURE_SET_ONE* pFeature);
//识别
//SF_FEATURE* feature 待识别特征
//MY_SF_FEATURE_SET_ONE *ft_set 注册特征
//bool badapt  更新标志，强烈建议该值置为true，即执行更新操作。执行更新后的注册特征将会发生变化需要再次保存，替换原来保存的注册特征
//int *int_sim 比对分数，分数取值范围0-999；阈值暂定560，对于560则判断为同一人，低于则判断为不是同一个人。
//返回值 0-成功
//1---注册特征更新
BATA_API int BataInfraredFace_MatchM(IN SF_FEATURE* feature,INOUT MY_SF_FEATURE_SET_ONE *ft_set , IN bool badapt, OUT int *int_sim);




//----------------------------------------IRIS------------------------------------------------------

#define		IRIS_FREQUENCY_NUM		(7)

struct Iris_MYFILE
{
    unsigned char*	buf;
    int				size;
    int				pos;
};
typedef struct _i_point{
    int							x;
    int							y;
    int							r;
}Eye_Feature, *PEye_Feature;

typedef struct _i_Feature{
    BYTE				PointW[600];
    BYTE				rawWei[600];
    BYTE				EnGC1[600*(IRIS_FREQUENCY_NUM - 1) *4];
}I_FEATURE, *PI_FEATURE;

typedef struct _i_qFeature{
    I_FEATURE					iFeature;
    unsigned char               iQuality;
}I_QFEATURE, *PI_QFEATURE;
//比对特征模板
typedef struct _m_i_Feature{
    I_FEATURE				rfeature;
    int*      				MergeRawData;//[67200];
    unsigned char           quality;

}M_I_FEATURE, *PMI_FEATURE;


typedef struct _i_Feature_en{
    BYTE				PointW[300];
    BYTE				rawWei[300];
    BYTE				EnGC1[300*(IRIS_FREQUENCY_NUM - 1) *4];
}I_FEATURE_EN, *PI_FEATURE_EN;

typedef struct _i_qFeature_en{
    I_FEATURE_EN           iFeature;
    unsigned char                 iQuality;
}I_QFEATURE_EN, *PI_QFEATURE_EN;
//注册特征模板
#define		IRIS_OK							0
#define		IRIS_FAILED						-1
#define		IRIS_NOT_INITIALIZED			-2
#define		IRIS_INVALID_ARGUMENT			-3
#define		IRIS_OUT_OF_MEMORY				-5
#define		IRIS_FILEIO_ERROR				-6
#define		IRIS_LOCK_ERROR					-7
#define		IRIS_EYE_ERROR					-8
#define		IRIS_DEV_ERR					-11
#define     IRIS_NO_UKEY                    -100
//初始化函数，系统启动时加载
BATA_API int		BataIris_init( Iris_MYFILE *fp );

//int		BataIris_Finalize( );

//特征比对
//I_QFEATURE_EN  feature1 注册特征
//I_QFEATURE feature2需要比对的特征
//int *sim 比对得分
//返回值  0--成功
BATA_API int BataIris_Match(IN I_QFEATURE_EN feature1, IN I_QFEATURE feature2, OUT int *sim);


//特征比对2: 用于注册时比对是否重复注册
//I_QFEATURE_EN  feature1 注册特征
//IN M_I_FEATURE feature2 要识别的待注册特征
//int *sim 比对得分
//返回值  0--成功
BATA_API int BataIris_Match_x(IN I_QFEATURE_EN feature1, IN M_I_FEATURE feature2, OUT int *sim );


//由三个特征得到一个注册特征
//M_I_FEATURE Feature0,M_I_FEATURE Feature1,M_I_FEATURE Feature2同一只眼睛的待注册特征
//I_QFEATURE_EN	*MFeature得到的注册特征
//返回值  0---成功
BATA_API int BataIris_Enroll(M_I_FEATURE Feature0,M_I_FEATURE Feature1,M_I_FEATURE Feature2,I_QFEATURE_EN	*MFeature);



//提取待注册特征--强制要求必须图像中有两只眼睛
//IN unsigned char* img, IN int nHeight, IN int nWidth待识别图像及其高、宽
//PEye_Feature FaceEyes 人脸中的眼睛位置
//PEye_Feature IrisInfo  虹膜图像中的眼睛位置
//M_I_FEATURE &FeatureLeft 提取到的左眼特征
//M_I_FEATURE &FeatureRight提取到的右眼特征
//bool IsPc   1--PC，0-ARM
//返回值  0---成功
BATA_API int BataIris_GetFeature_E_F(IN unsigned char* img, IN int nHeight, IN int nWidth,IN PEye_Feature FaceEyes,OUT PEye_Feature IrisInfo,
    OUT M_I_FEATURE *FeatureLeft,OUT M_I_FEATURE *FeatureRight,bool IsPc);
//提取待识别特征
//IN unsigned char* img, IN int nHeight, IN int nWidth待识别图像及其高、宽
//PEye_Feature FaceEyes 人脸中的眼睛位置
//int&	EyeNum 成功找到的眼睛数目
//PEye_Feature IrisInfo  虹膜图像中的眼睛位置
//I_QFEATURE &FeatureLeft 提取到的左眼特征
//I_QFEATURE &FeatureRight提取到的右眼特征
//bool IsPc   1--PC，0-ARM
BATA_API int BataIris_GetFeature_R_F(IN unsigned char* img, IN int nHeight, IN int nWidth ,IN PEye_Feature FaceEyes, OUT int *IrisNum, OUT PEye_Feature IrisInfo,
    I_QFEATURE *FeatureLeft,OUT I_QFEATURE *FeatureRight,bool IsPc);

//分数融合
//int fq 人脸质量分数
//int fs 人脸比对得分
//int ilq 左眼质量分数
//int ils 左眼比对分数
//int irq 右眼质量分数
//int irs 右眼比对分数
//int *sim 综合比对得分//目前阈值： 低安全等级500， 中安全等级510，高安全等级520
//返回值  0--成功
BATA_API int BataFIM(IN int fq, IN int  fs, IN int liq, IN int  lis,IN int riq, IN int  ris, OUT int *sim);


#endif // BATA_H

