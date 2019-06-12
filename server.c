/************************************************************
#      FileName : server.c
#      Author   : Luctw_朱银飞
#      Email    : 15290605912@163.com
#      Created  : 2019年06月10日 星期一 20时13分21秒
************************************************************/


#include "common.h"

sqlite3 *db;

int login(int acceptfd,MSG *msg){
	printf("------------------%s--------------------%d\n",__func__,__LINE__);
	char sql[DATALEN] = {0};
	char *errmsg;
	char **result;
	int nrow,ncolumn;

	msg->info.usertype = msg->usertype;
	strcpy(msg->info.name,msg->username);
	strcpy(msg->info.passwd,msg->passwd);

	printf("usertype:%#x----username:%s----passwd:%s\n",msg->info.usertype,msg->info.name,msg->info.passwd);
	sprintf(sql,"select * from usrinfo where usertype=%d and name='%s' and passwd='%s';",msg->info.usertype,msg->info.name,msg->info.passwd);
	if(sqlite3_get_table(db,sql,&result,&nrow,&ncolumn,&errmsg) != SQLITE_OK){
		printf("---***---%s\n",errmsg);
	}else{
		if(nrow == 0){
			strcpy(msg->recvmsg,"name or passwd failed.\n");
			send(acceptfd,msg,sizeof(MSG),0);
		}else{
			strcpy(msg->recvmsg,"OK");
			send(acceptfd,msg,sizeof(MSG),0);
		}
	}
}

int user_modify(int acceptfd,MSG *msg){
	printf("------------------%s--------------------%d\n",__func__,__LINE__);
}

int user_query(int acceptfd,MSG *msg){
	printf("------------------%s--------------------%d\n",__func__,__LINE__);
	int i = 0,j = 0;
	char sql[DATALEN] = {0};
	char **resultp;
	int nrow,ncolumn;
	char *errmsg;

	sprintf(sql,"select * from usrinfo where name = '%s';",msg->username);
	if(sqlite3_get_table(db,sql,&resultp,&nrow,&ncolumn,&errmsg) != SQLITE_OK){
		printf("%s\n",errmsg);
	}else{
		printf("searching...\n");
		for(i=0;i<ncolumn;i++){
			printf("%-8s",resultp[i]);
		}
		puts("");
		puts("===================================================================");

		int index = ncolumn;
		for(i = 0;i < nrow;i++){
			printf("%s    %s     %s     %s     %s     %s     %s     %s     %s     %s     %s.\n",resultp[index+ncolumn-11],resultp[index+ncolumn-10],\
					resultp[index+ncolumn-9],resultp[index+ncolumn-8],resultp[index+ncolumn-7],resultp[index+ncolumn-6],resultp[index+ncolumn-5],\
							resultp[index+ncolumn-4],resultp[index+ncolumn-3],resultp[index+ncolumn-2],resultp[index+ncolumn-1]);

			sprintf(msg->recvmsg,"%s,    %s,    %s,    %s,    %s,    %s,    %s,    %s,    %s,    %s,    %s;",resultp[index+ncolumn-11],resultp[index+ncolumn-10],\
					resultp[index+ncolumn-9],resultp[index+ncolumn-8],resultp[index+ncolumn-7],resultp[index+ncolumn-6],resultp[index+ncolumn-5],\
					resultp[index+ncolumn-4],resultp[index+ncolumn-3],resultp[index+ncolumn-2],resultp[index+ncolumn-1]);
			send(acceptfd,msg,sizeof(MSG),0);
			usleep(1000);
			puts("===================================================================");
			index += ncolumn;
		}
		sqlite3_free_table(resultp);
		printf("sqlite3_get_table ok\n");
	}


}

int admin_modify(int acceptfd,MSG *msg){
	printf("------------------%s--------------------%d\n",__func__,__LINE__);
}

int admin_adduser(int acceptfd,MSG *msg){
	printf("------------------%s--------------------%d\n",__func__,__LINE__);
}

int admin_deluser(int acceptfd,MSG *msg){
	printf("------------------%s--------------------%d\n",__func__,__LINE__);
}

int admin_query(int acceptfd,MSG *msg){
	printf("------------------%s--------------------%d\n",__func__,__LINE__);
	int i = 0,j = 0;
	char sql[DATALEN] = {0};
	char **resultp;
	int nrow,ncolumn;
	char *errmsg;

	sprintf(sql,"select * from usrinfo where name = '%s';",msg->username);
	if(sqlite3_get_table(db,sql,&resultp,&nrow,&ncolumn,&errmsg) != SQLITE_OK){
		printf("%s\n",errmsg);
	}else{
		printf("searching...\n");
		for(i=0;i<ncolumn;i++){
			printf("%-8s",resultp[i]);
		}
		puts("");
		puts("===================================================================");

		int index = ncolumn;
		for(i = 0;i < nrow;i++){
			printf("%s    %s     %s     %s     %s     %s     %s     %s     %s     %s     %s.\n",resultp[index+ncolumn-11],resultp[index+ncolumn-10],\
					resultp[index+ncolumn-9],resultp[index+ncolumn-8],resultp[index+ncolumn-7],resultp[index+ncolumn-6],resultp[index+ncolumn-5],\
							resultp[index+ncolumn-4],resultp[index+ncolumn-3],resultp[index+ncolumn-2],resultp[index+ncolumn-1]);

			sprintf(msg->recvmsg,"%s,    %s,    %s,    %s,    %s,    %s,    %s,    %s,    %s,    %s,    %s;",resultp[index+ncolumn-11],resultp[index+ncolumn-10],\
					resultp[index+ncolumn-9],resultp[index+ncolumn-8],resultp[index+ncolumn-7],resultp[index+ncolumn-6],resultp[index+ncolumn-5],\
					resultp[index+ncolumn-4],resultp[index+ncolumn-3],resultp[index+ncolumn-2],resultp[index+ncolumn-1]);
			send(acceptfd,msg,sizeof(MSG),0);
			usleep(1000);
			puts("===================================================================");
			index += ncolumn;
		}
		sqlite3_free_table(resultp);
		printf("sqlite3_get_table ok\n");
	}

("------------------%s--------------------%d\n",__func__,__LINE__);

}

int admin_history(int acceptfd,MSG *msg){
	printf("------------------%s--------------------%d\n",__func__,__LINE__);
}

int client_quit(int acceptfd,MSG *msg){
	printf("------------------%s--------------------%d\n",__func__,__LINE__);
}

int client(int acceptfd,MSG *msg){
	printf("------------------%s--------------------%d\n",__func__,__LINE__);
	switch(msg->msgtype)
	{
	case USER_LOGIN:
	case ADMIN_LOGIN:
		login(acceptfd,msg);
		break;
	case USER_MODIFY:
		user_modify(acceptfd,msg);
		break;
	case USER_QUERY:
		user_query(acceptfd,msg);
		break;

	case ADMIN_MODIFY:
		admin_modify(acceptfd,msg);
		break;
	case ADMIN_ADDUSER:
		admin_adduser(acceptfd,msg);
		break;
	case ADMIN_DELUSER:
		admin_deluser(acceptfd,msg);
		break;
	case ADMIN_QUERY:
		admin_query(acceptfd,msg);
		break;
	case ADMIN_HISTORY:
		admin_history(acceptfd,msg);
		break;
	case QUIT:
		client_quit(acceptfd,msg);
		break;
	default:
		break;

	}
}

int main(int argc,const char *argv[])
{
	int sockfd;
	int acceptfd;

	struct sockaddr_in serveraddr;
	struct sockaddr_in clientaddr;

	socklen_t serverlen = sizeof(serveraddr);
	socklen_t clientlen = sizeof(clientaddr);

	MSG msg;

	char *errmsg;

	if(argc != 3){
		printf("input:%s serverip port.\n",argv[0]);
	return -1;
	}

	//打开数据库
	if(sqlite3_open(DATABASE,&db) != SQLITE_OK){
		printf("%s\n",sqlite3_errmsg(db));
		return -1;
	}else{
		printf("open DATABASE success.\n");
	}


	if(sqlite3_exec(db,"create table usrinfo(staffno integer,usertype integer,name text,passwd text,age integer,phone text,addr text,work text,date text,level integer,salary REAL);",NULL,NULL,&errmsg)!= SQLITE_OK){
		printf("%s.\n",errmsg);
	}else{
		printf("Creationate usrinfo table success.\n");
	}

	if(sqlite3_exec(db,"create table historyinfo(time text,name text,words text);",NULL,NULL,&errmsg)!= SQLITE_OK){
		printf("%s.\n",errmsg);
	}else{ 
		printf("create historyinfo table success.\n");
	}


	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0){
		perror("fail to sockfd.\n");
		return -1;
	}

	bzero(&serveraddr, sizeof(serveraddr));
	bzero(&clientaddr, sizeof(clientaddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	serveraddr.sin_port = htons(atoi(argv[2]));

	if(bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr)) < 0){
		perror("fail to bind.\n");
	return -1;
	}

	//将套接字设为监听模式
	if(listen(sockfd,5) < 0){
		printf("fail to listen.\n");
	return -1;
	}

	//处理僵尸进程
	signal(SIGCHLD,SIG_IGN);

	//定义一张表
	fd_set readfds,tempfds;
	//清空表
	FD_ZERO(&readfds);
	FD_ZERO(&tempfds);
	//添加要监听的事件
	FD_SET(sockfd,&readfds);
	int nfds = sockfd;
	int retval;
	int i = 0;
	ssize_t recvbytes;

	while(1){
		tempfds = readfds;
		retval = select(nfds + 1,&tempfds,NULL,NULL,NULL);

		for(i = 0;i < nfds+1;i++){
			if(FD_ISSET(i,&tempfds)){
				if(i == sockfd){
					if((acceptfd = accept(sockfd,(struct sockaddr *)&clientaddr,&clientlen)) < 0){
						printf("fail to acceptfd.\n");
						return -1;
					}
					printf("ip:%s\n",inet_ntoa(clientaddr.sin_addr));
					FD_SET(acceptfd,&readfds);
					nfds = nfds > acceptfd ? nfds : acceptfd;
				}else{
					recvbytes = recv(i,&msg,sizeof(msg),0);
					printf("msg.type:%#x\n",msg.msgtype);
					if(recvbytes == -1){
						printf("fail to recv.\n");
						continue;
					}else if(recvbytes == 0){
						printf("peer shutdown.\n");
						close(i);
						FD_CLR(i,&readfds);
					}else{
						client(i,&msg);
					}
				}
			}
		}
	}
	close(sockfd);

	return 0;
}


