#define PWDLEN 20
//前台输入密码
void getpwd(char *pwd, int pwdlen);//得到密码
int comparePwd(char *pwd);//验证密码
void getPassword();//密码输入界面

//前台功能
void front();//前台功能函数
void front_index();//打印前台功能页面

//入住
void checkIn();//入住功能函数
int checkReserve();//预约变入住功能
void changeGStatusTo_1(int i);//更改客人的status，由预约到入住
void writeAllGuest();//重新写入全部客户信息
int front_isLeft(int i);//查询某种房型房间余量，输出可选择房号
int front_judgeOrder(int k);//判断房间可不可以入住——调用了 User.h 的judgeLast()函数

//退房
void checkOut();//退房功能函数
int count_money(int day,int num);//计算钱数

//查询
void search_index();//打印查询功能界面
void search();//查询功能函数
void searchAllRoom();//查询所有房间
void searchOneRoom();//查询一个房间具体信息


