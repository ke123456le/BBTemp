#ifndef ERRORCODE
#define ERRORCODE


typedef int BT_RET;

#define __BT_SUCC                                       0   //Success
#define __BT_FAIL                                       -1   //fail
#define __BT_PARA_INVILD                                -2

#define __BT_DATA_INVILD                                -3

#define __BT_NOT_FOUND_USER                             -10

#define __BT_INIT_FAIL                                  -100
#define __BT_INIT_FEATURE_FAIL                          -101
#define __BT_INIT_USER_FAIL                             -102
#define __BT_INIT_DB_FAIL                               -103



#define __BT_UPDATA_DATA_FAIL                           -200
#define __BT_NOT_FOUND_FEATURE_LIB                      -201
#define __BT_FEATURE_RMPTY                              -202
#define __BT_USERS_EMPTY                                -203
#define __BT_NOT_FOUNT_USERS_LIB                        -204
#define __BT_NOT_FOUND_PARA_LIB                         -205
#define __BT_NOT_FOUND_ALGORITHM_DATA                   -206

#define __BT_CAMERA_OPEN_FAIL                           -300


#define CHECK_ERROR_RETURN(code)    do{if (code)return code;}while(0);

#endif // ERRORCODE

