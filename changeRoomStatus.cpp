#include <stdio.h>
#include <stdlib.h>

int changeRoomStatus(){
int pay;{
int room_standard , day;
Guest[i] = (struct Guest*)malloc(sizeof(struct Guest));
Guest(Guest[i]);
printf("����ѡ��Ԥ������ı�׼:\n");
printf("1.���˼�/��68Ԫ\n   2.˫�˼�/��168Ԫ\n   3.VIP/��268Ԫ\n");
scanf("%d", &room_rank);
printf("������ס������\n");
scanf("%d", &day);
set_day(Guest[i] , day);
switch(room_rank){
int n;

case 1: pay=day*68;
//set_pay(customer[i],pay);
printf("���շ���%dԪ��!\n",pay);
for(n=0 ; n<20 ; n++){
if(room[n].RoomStatus == 0){
printf("��ס�������Ϊ:%d\n",room[n].num);
room[n].RoomStatus = 2;
set_room_num(Guest[i],room[n].num ) ; break;
}
}
break;

case 2 : pay=day*168;
printf("���շ���%dԪ��!\n" , pay);
for(n=20 ; n<40 ; n++){
if(room[n].RoomStatus == 0){
printf("��ס�������Ϊ:%d\n",room[n].num);
room[n].RoomStatus=2;
set_room_number(Guest[i],room[n].number) ; break;
}
}
break;

case 3 :pay = day*268;
printf("���շ���%dԪ��!\n",pay);
for(n=40 ; n<60 ; n++){
if(room[n].RoomStatus == 0){
printf("��ס�������Ϊ:%d\n",room[n].num);
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
