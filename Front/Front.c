#define PWDLEN 20
void getpwd(char *pwd, int pwdlen);
int comparePwd(char *pwd);
void front_index();

void getPassword()
{
    system("cls");
    char pwd[20];
    int count = 3;
    printf("请输入登录密码：\n");
    getpwd(pwd, PWDLEN);
    while(comparePwd(pwd) != 1 && count > 0)
    {
        printf("密码错误，请输入：\n");
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
    printf("@@@@@@@@@@@@@@@登陆成功!@@@@@@@@@@@@@@@@@@\n");
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
* 获取用户输入的密码
* @param  pwd     char*  保存密码的内存的首地址
* @param  pwdlen  int    密码的最大长度
**/
void getpwd(char *pwd, int pwdlen){
    char ch = 0;
    int i = 0;
    while(i<pwdlen){
        ch = getch();
        if(ch == '\r'){  //回车结束输入
            printf("\n");
            break;
        }

        if(ch=='\b' && i>0){  //按下删除键
            i--;
            printf("\b \b");
        }else if(isprint(ch)){  //输入可打印字符
            pwd[i] = ch;
            printf("*");
            i++;
        }
    }
    pwd[i] = '\0';
}
