#ifndef ERRORCODE
#define ERRORCODE


typedef int BT_RET;

#define __BT_SUCC                                       0       //Success
#define __BT_FAIL                                       -1      //fail
#define __BT_PARA_INVILD                                -2      //参数错误

#define __BT_DATA_INVILD                                -3      //数据错误
#define __BT_ALLOC_BUF_FAIL                             -4      //开辟空间失败

#define __BT_NOT_FOUND_USER                             -10     //未发现用户


#define __BT_INIT_FAIL                                  -100    //初始化失败
#define __BT_INIT_FEATURE_FAIL                          -101    //初始化特征库失败
#define __BT_INIT_USER_FAIL                             -102    //初始化用户库失败
#define __BT_INIT_DB_FAIL                               -103    //初始化数据库失败



#define __BT_UPDATA_DATA_FAIL                           -200    //更新用户失败
#define __BT_NOT_FOUND_FEATURE_LIB                      -201    //未发现特征库
#define __BT_FEATURE_RMPTY                              -202    //特征库空
#define __BT_USERS_EMPTY                                -203    //用户库空
#define __BT_NOT_FOUNT_USERS_LIB                        -204    //未发现用户库
#define __BT_NOT_FOUND_PARA_LIB                         -205    //未发现参数库
#define __BT_NOT_FOUND_ALGORITHM_DATA                   -206    //未发现算法库

#define __BT_NOT_FOUND_IDENT_PARA                       -207    //

#define __BT_CAMERA_OPEN_FAIL                           -300    //摄像头设备打开失败
#define __BT_CAMERA_STREAM_FAIL                         -301    //摄像头数据口打开失败
#define __BT_CAMERA_CAPTURE_FAIL                        -302    //摄像头采集失败

#define __BT_CAMERA_CTRL_NOT_SUPPORT                    -320    //不支持的摄像头控制操作
#define __BT_CAMERA_CTRL_EXPOSURE_FAIL                  -321    //摄像头曝光控制失败
#define __BT_CAMERA_INFO_FAIL                           -322

#define __BT_CAMERA_BUSY                                -330    //摄像头忙

#define __BT_DECODE_FAIL                                -350    //解码失败

#define __BT_IDENT_SERVICE_BUSY                         -360    //
#define __BT_IDENT_INIT_FAIL                            -361    //


/*检查返回码,非__BT_SUCC 直接返回该码*/
#define CHECK_ERROR_RETURN(code)    do{if (code)return code;}while(0);

#endif // ERRORCODE

