#define PWDLEN 20
void getpwd(char *pwd, int pwdlen);
int comparePwd(char *pwd);
void front_index();

void getPassword()
{
    system("cls");
    char pwd[20];
    int count = 3;
    printf("�������¼���룺\n");
    getpwd(pwd, PWDLEN);
    while(comparePwd(pwd) != 1 && count > 0)
    {
        printf("������������룺\n");
        getpwd(pwd, PWDLEN);
        -- count;
    }
    if(comparePwd(pwd) == 1)
    {
        front_index();
    }
}

void front_index()
{
    printf("@@@@@@@@@@@@@@@��½�ɹ�!@@@@@@@@@@@@@@@@@@\n");
}

int comparePwd(char *pwd)
{
    int i = 0;
    char passWd[6] ={'1','2','3','4','5','6'};
    for(;i < 6; i++)
    {
        if(*(pwd+i) != passWd[i])
            return -1;
    }
    return 1;
}

/**
* ��ȡ�û����������
* @param  pwd     char*  ����������ڴ���׵�ַ
* @param  pwdlen  int    �������󳤶�
**/
void getpwd(char *pwd, int pwdlen){
    char ch = 0;
    int i = 0;
    while(i<pwdlen){
        ch = getch();
        if(ch == '\r'){  //�س���������
            printf("\n");
            break;
        }

        if(ch=='\b' && i>0){  //����ɾ����
            i--;
            printf("\b \b");
        }else if(isprint(ch)){  //����ɴ�ӡ�ַ�
            pwd[i] = ch;
            printf("*");
            i++;
        }
    }
    pwd[i] = '\0';
}
