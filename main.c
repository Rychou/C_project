#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "./User/User.h"
#include "./Front/Front.h"
#include "./struct/struct.h"
#include "./User/time.h"

Date now;

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
                     pause();
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
    printf("\n--------------�õ����ϵͳ--------------\n");
    printf("               ��ESC�˳�\n");
    printf("========================================\n");
    printf("1.�ͻ�\n\n");
    printf("2.ǰ̨\n");
    printf("========================================\n");
    printf("��ѡ��");
}

void pause()//ʵ����ͣ
{
    printf("��ESC������ҳ..");
    while(1){
        if(getch()== 0x1B)
            break;
    }
}

