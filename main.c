#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "./User/User.h"
#include "./Front/Front.h"
#include "./struct/struct.h"
#include "./User/time.h"

Date now;//当前时间

int main()
{
    void index();
    int i=0;
    index();
    while((i=getch())!= 0x1B){
        now = getDt();
        readRoom();
        readGuest();
        switch(i)
        {
            case 50: getPassword();
                     index();
                     continue;
            case 49: User();
                     pause();
                     index();
                     continue;
            default:continue;
        }
    }
    return 0;
}

void index()
{
    system("cls");
    printf("\n--------------旅店管理系统--------------\n");
    printf("               按ESC退出\n");
    printf("\n");
    printf(" @@@@@@@@@@@@@@@@@首页@@@@@@@@@@@@@@@@@\n");
    printf("@                                      @\n");
    printf("@        1.客户                        @\n");
    printf("@        2.前台                        @\n");
    printf("@                                      @\n");
    printf(" @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
    printf("请输入指令：");
}

void pause()//实现暂停
{
    printf("按ESC返回首页..");
    while(1){
        if(getch()== 0x1B)
            break;
    }
}

