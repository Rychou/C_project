#ifndef USER_H_INCLUDED
#define USER_H_INCLUDED
#include "../struct/struct.h"


#endif // USER_H_INCLUDED

void User();//输出用户界面
void Reserve();//输出预约界面
void cancelReservation();//输出取消预约界面
int isLeft();//查询某种房型房间余量，输出用户可预定房号
void getRNum();//在isLeft（）打印出可预定房号后 获取用户指令
void getGNum();//获取预定某房间的人数
void inputMsg(Date date,int i);//输入入住客户的信息，可以多个客户
void readRoom(); //读取房间文件
void readGuest();//读取User.txt
void writeGuest();//追加写入客户信息
void changeRStatusTo_0();//修改房间状态为0
void changeRStatusTo_1();//改变房间状态为1
void deleteGuest(Guest gst2[],int length);//用户取消预定删除特定用户信息
int judgeDate();//判断日期是否满足7天内的要求
int judgeLast(Date dt,int d,int i);//判断时间有无空余
int judgeOrder(int k);//判断房间可不可以预约

