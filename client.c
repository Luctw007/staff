/************************************************************
#      FileName : server.c
#      Author   : Luctw_朱银飞
#      Email    : 15290605912@163.com
#      Created  : 2019年06月10日 星期一 20时13分21秒
 ************************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>


#include "common.h"

void show_userinfo(MSG *msg){
	printf("===========================================================================\n");
	printf("%s\n",msg->recvmsg);
	return;
}

void do_admin_query(int sockfd,MSG *msg){
	printf("----------------------%s---------------------%d\n",__func__,__LINE__);
	int n;
	msg->msgtype = ADMIN_QUERY;

	while(1){
		bzero(&msg->info,sizeof(staffer_info_t));
		if(msg->usertype == ADMIN){
		printf("********************************************************************\n");
		printf("**************  1：按人名查找   2：查找所有   3：退出 **************\n");
		printf("********************************************************************\n");
		printf("请输入数字：");
		scanf("%d",&n);
		getchar();
		
		switch(n){
			case 1:
				msg->flags = 1;
				break;
			case 2:
				msg->flags = 0;
				break;
			case 3:
				return;
			}
		}

		if(msg->flags == 1){
			printf("请输入要查找的用户名：");
			scanf("%s",msg->info.name);
			getchar();

			send(sockfd,msg,sizeof(MSG),0);
			recv(sockfd,msg,sizeof(MSG),0);
			printf("工号\t用户类型\t姓名\t密码\t年龄\t电话\t地址\t职位\t入职年月\t等级\t工资\n");
			show_userinfo(msg);
		}else{
			send(sockfd,msg,sizeof(MSG),0);
			printf("工号\t用户类型\t姓名\t密码\t年龄\t电话\t地址\t职位\t入职年月\t等级\t工资\n");
			while(1){
				recv(sockfd,msg,sizeof(MSG),0);
				if(strncmp(msg->recvmsg,"over*",5) == 0)
					break;
				show_userinfo(msg);
			}	
		}
	}
	printf("查找结束\n");
}

void do_admin_modification(int sockfd,MSG *msg){
	printf("----------------------%s---------------------%d\n",__func__,__LINE__);
}

void do_admin_adduser(int sockfd,MSG *msg){
	printf("----------------------%s---------------------%d\n",__func__,__LINE__);
}

void do_admin_deluser(int sockfd,MSG *msg){
	printf("----------------------%s---------------------%d\n",__func__,__LINE__);
}

void do_history(int sockfd,MSG *msg){
	printf("----------------------%s---------------------%d\n",__func__,__LINE__);
}

void do_admin_menu(int sockfd,MSG *msg){
	printf("----------------------%s---------------------%d\n",__func__,__LINE__);

	int n;
	while(1){
		printf("********************************************************************\n");
		printf("*  1：查询   2：修改   3：添加用户   4：删除用户   5：查询历史记录 *\n");
		printf("*  6：退出                                                         *\n");
		printf("********************************************************************\n");
		printf("请输入数字：");
		scanf("%d",&n);
		getchar();

		switch(n){
		case 1:
			do_admin_query(sockfd,msg);
			break;
		case 2:
			do_admin_modification(sockfd,msg);
			break;
		case 3:
			do_admin_adduser(sockfd,msg);
			break;
		case 4:
			do_admin_deluser(sockfd,msg);
			break;
		case 5:
			do_history(sockfd,msg);
			break;
		case 6:
			msg->msgtype = QUIT;
			send(sockfd,msg,sizeof(MSG),0);
			close(sockfd);
			exit(0);
		default:
			printf("输入错误，请重新输入\n");
			break;

		}
	}
}

void do_user_query(int sockfd,MSG *msg){
	printf("----------------------%s---------------------%d\n",__func__,__LINE__);
}

void do_user_modification(int sockfd,MSG *msg){
	printf("----------------------%s---------------------%d\n",__func__,__LINE__);
}

void do_user_memu(int sockfd,MSG *msg){
	printf("----------------------%s---------------------%d\n",__func__,__LINE__);
	int n;
	while(1){
		printf("********************************************************************\n");
		printf("******************  1：查询   2：修改   3：退出 ********************\n");
		printf("********************************************************************\n");
		printf("请输入数字：");
		scanf("%d",&n);
		getchar();

		switch(n){
		case 1:
			do_user_query(sockfd,msg);
			break;
		case 2:
			do_user_modification(sockfd,msg);
			break;
		case 3:
			msg->msgtype = QUIT;
			send(sockfd,msg,sizeof(MSG),0);
			close(sockfd);
			exit(0);
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
	}
}

int login(int sockfd,MSG *msg){
	printf("----------------------%s---------------------%d\n",__func__,__LINE__);

	bzero(msg->username,NAMELEN);
	printf("请输入用户名：");
	scanf("%s",msg->username);
	getchar();

	bzero(msg->passwd,DATALEN);
	printf("请输入密码：");
	scanf("%s",msg->passwd);
	getchar();


	send(sockfd,msg,sizeof(MSG),0);
	recv(sockfd,msg,sizeof(MSG),0);
	printf("msg->recvmsg:%s\n",msg->recvmsg);

	if(strncmp(msg->recvmsg,"OK",2) == 0){
		if(msg->usertype == ADMIN){
			printf("管理员登录\n");
			do_admin_menu(sockfd,msg);
		}else if(msg->msgtype == USER){
			printf("用户登录\n");
			do_user_memu(sockfd,msg);
		}
	}else{
		printf("登录失败,%s\n",msg->recvmsg);
	}
	return 0;
}

int do_login(int sockfd){
	printf("----------------------%s---------------------%d\n",__func__,__LINE__);
	int n;
	MSG msg;

	while(1){
		printf("********************************************************************\n");
		printf("*********  1：管理员模式   2：普通用户模式   3：退出 ***************\n");
		printf("********************************************************************\n");
		printf("请输入数字：");
		scanf("%d",&n);
		getchar();

		switch(n){
		case 1:
			msg.msgtype = ADMIN_LOGIN;
			msg.usertype = ADMIN;
			break;
		case 2:
			msg.msgtype = USER_LOGIN;
			msg.usertype = USER;
			break;
		case 3:
			msg.msgtype = QUIT;
			if(send(sockfd,&msg,sizeof(MSG),0) < 0){
				perror("do_login send");
				return -1;
			}
			close(sockfd);
			exit(0);
		default:
			printf("输入错误，请重新输入\n");
			break;
		}
		login(sockfd,&msg);
	}

}


int main(int argc, const char *argv[])
{
	int sockfd;
	int acceptfd;
	ssize_t recvbytes,sendbytes;
	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;

	if(argc != 3){
		printf("input:%s serverip port.\n",argv[0]);
		return -1;
	}

	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		perror("fail to socked.\n");
		return -1;
	}
	printf("sock is ok.\n");

	bzero(&serveraddr, sizeof(serveraddr));
	bzero(&clientaddr, sizeof(clientaddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));

	if(connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0){
		perror("fail to connect.\n");
		return -1;
	}
	do_login(sockfd);

	close(sockfd);

	return 0;
}

