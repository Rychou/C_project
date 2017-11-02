# 旅店管理系统任务分配 #

## 程序流程 ##
1. 主界面
>1.1 客户
```
User();//客户界面输出
Reserve();//预定房间
cancelReservation();//取消预定
isLeft(int i);//客户选择房型后进行查询的函数
getRNum();//在isLeft（）打印出可预定房号后 获取用户指令
getGNum();//获取预定某房间的人数
inputMsg();//输入入住客户的信息，可以多个客户
readRoom(); //读取房间文件
readGuest(Guest array[]);//读取User.txt
writeGuest();//追加写入客户信息
changeRStatusTo_0();//修改房间状态为0(空房)
changeRStatusTo_1();//改变房间状态为1(已入住/已预约)
deleteGuest(Guest gst2[],int length);//用户取消预定删除特定用户信息
judgeDate();//判断入住日期是否满足要求
```
1.2 前台
```
getPassword();//主界面选择前台后，进行密码登陆，不需要账号！
indexFront();
//如果密码输入正确,打印前台操作界面.
//如果错误，打印
//1.重新输入
//2.返回主界面
changeRoomStatus();//修改房间状态
checkOut();//退房
inputMsg();//录入客户信息
search();//查询客房信息,打印出两种查询方式
searchUserMsg();//1.查询已入住客户信息
searchRoomMsg();//2.查询所有客房信息`
```

# 第四周任务分配 #

1.大家自学文档操作以及结构体相关的知识<br>
2.熟悉基本的github协作流程,如建立自己的分支等<br>
3.具体任务分配暂时没有，大家回到宿舍多进行交流，林圣钊多往626跑。<br>
