#include <stdio.h>
#include <stdlib.h>

int changeRoomStatus(){
int pay;{
int room_standard , day;
Guest[i] = (struct Guest*)malloc(sizeof(struct Guest));
Guest(Guest[i]);
printf("请您选择预定房间的标准:\n");
printf("1.单人间/天68元\n   2.双人间/天168元\n   3.VIP/天268元\n");
scanf("%d", &room_rank);
printf("请输入住宿天数\n");
scanf("%d", &day);
set_day(Guest[i] , day);
switch(room_rank){
int n;

case 1: pay=day*68;
//set_pay(customer[i],pay);
printf("请收房费%d元整!\n",pay);
for(n=0 ; n<20 ; n++){
if(room[n].RoomStatus == 0){
printf("入住房间号码为:%d\n",room[n].num);
room[n].RoomStatus = 2;
set_room_num(Guest[i],room[n].num ) ; break;
}
}
break;

case 2 : pay=day*168;
printf("请收房费%d元整!\n" , pay);
for(n=20 ; n<40 ; n++){
if(room[n].RoomStatus == 0){
printf("入住房间号码为:%d\n",room[n].num);
room[n].RoomStatus=2;
set_room_number(Guest[i],room[n].number) ; break;
}
}
break;

case 3 :pay = day*268;
printf("请收房费%d元整!\n",pay);
for(n=40 ; n<60 ; n++){
if(room[n].RoomStatus == 0){
printf("入住房间号码为:%d\n",room[n].num);
room[n].RoomStatus=2;
set_room_num(Guset[i],room[n].num) ; break;
}
}
break;
}
i++;
}
return 4;
}
