#ifndef __UCOM_H__
#define __UCOM_H__


#ifdef __cplusplus
extern "C" {
#endif

/*
 * 原型： int OpenComDevice(void);
 * 功能： 串口初始化。
 * 参数： 无。
 * 返回： 0 成功，小于0失败。
 */
int OpenComDevice(void);


/*
 * 原型： int ComSendData(int id, void *data, int len);
 * 功能： 串口发送数据。
 * 参数： IN id: 串口标号，如果有n 个串口，那么id 取值为0~n-1
 * IN data: 要发送的数据。
 * IN len: 数据长度
 * 返回： 0 成功，小于0失败。
 */
int ComSendData(int id, void *data, int len);


/*
 * 原型： int ComReceiveData(int id, void *buf, int len);
 * 功能： 串口接收数据。
 * 参数： IN id: 串口标号
 * OUT buf: 缓冲区。
 * OUT len: 数据长度
 * 返回： 0 成功，小于0失败。
 */
int ComReceiveData(int id, void *buf, int rlen);



#ifdef __cplusplus
}
#endif
#endif
