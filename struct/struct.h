#ifndef STRUCT_H_INCLUDED
#define STRUCT_H_INCLUDED


typedef struct {
    int num;//房间号
    int rank;//房间类型
    int price;//房间价格
    int roomStatus;//房间状态：0为空，预约和入住为1
}Room;

typedef struct{
    int year;
    int month;
    int day;
}Date;

/*typedef struct {
    int num;//房间号
    char ID[18];//身份证
    Date time;//入住时间
    int day;//入住天数
    int status;//1为已入住；2为预约
}RG;
*/
typedef struct {
    char ID[20];//身份证
    char name[30];//名字
    int phone;//电话
    int num;//入住房号
    //int status;//1为已入住；2为预约
    Date time;//入住时间
    int day;//入住天数
}Guest;

#endif // STRUCT_H_INCLUDED
