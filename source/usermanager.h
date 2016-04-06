#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QString>

class UserInfo
{
    QString             userId;         //用户ID
    QString             userName;       //用户姓名
    QString             orgCode;        //所属部门
    unsigned int        userRole;       //用户角色
    QString             userPasswd;     //用户密码
    QString             userCardCode;   //卡片号码
    QString             userRegTime;    //注册时间
    QString             userModTime;    //最近修改时间
    QString             userPhoneId;    //用户照片(UUID)
};

class UserContdition
{
    QString             userName;
    QString             orgCode;
    QString             userCardCode;
    QString             userTimeBegin;
    QString             userTimeEnd;
};

class UserManager
{
public:
    UserManager();

    int init();

    int getUsers();
    int removeUser();
    int removeOneUser(QString _userId);

};

#endif // USERMANAGER_H
