#include "time.h"
#include <stdio.h>
#include <windows.h>
#include  <assert.h>
#include <stdlib.h>
#include "../struct/struct.h"

int front(){
    system("cls");
    printf("=======================================\n");
    printf("1.XXXXXX\n");
    printf("2.��ѯ���з�����Ϣ\n");
    printf("=======================================\n");
    int i;
    printf("��ѡ��::");
    scanf("%d",&i);
    while(i!=1&&i!=2)
    {
        printf("�������������:");
        scanf("%d",&i);
    }
    switch(i){
        case 1 : Reserve();break;
        case 2 : SreachRoomMsg();break;
    }
    return 0;
}

int SreachRoomMsg(){
     system("cls");
     FILE *r = fopen("f:\\c\\C_project-wangjintao\\data\\User.txt","r");
     assert(r!=NULL);
     char g[100];
     int i;
     int count=0;
     while(fgets(g,100,r)!=NULL){
        printf("%s\n",g);
     }
     fclose(r);
     return 0;
}

