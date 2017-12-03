#include <stdio.h>
#include <sys/types.h> 	// socket, bind, accept, open
#include <sys/socket.h> // socket, bind, listen, accept
#include <unistd.h>		// read, write
#include <sys/stat.h> 	// open
#include <fcntl.h>		// open
#include <errno.h>

#include <string.h>

#define PORT	5500
#define MAXBUF	1024

int main() {
	int server_sockfd;
	int client_sockfd;
	int des_fd;	// file num
	struct sockaddr_in serveraddr, clientaddr;
	int client_len, read_len, file_read_len;	// length
	char buf[MAXBUF];
	
	
	int check_bind;
	

	client_len = sizeof(clientaddr);

	/* socket() */
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_sockfd == -1) {
		perror("socket error : ");
		exit(0);
	}

	/* bind() */
	bzero(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family		= AF_INET;
	serveraddr.sin_addr.s_addr	= htonl(INADDR_ANY);
	serveraddr.sin_port			= htons(PORT);

	if(bind(server_sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) > 0) {
		perror("bind error : ");
		exit(0);
	}

	/* listen */
	if(listen(server_sockfd, 5) != 0) {
		perror("listen error : ");
	}

	while(1) {
		char file_name[MAXBUF]; // local val
		memset(buf, 0x00, MAXBUF);
		
		/* accept() */
		client_sockfd = accept(server_sockfd, (struct sockaddr *)&clientaddr, &client_len);
		printf("New Client Connect : %s\n", inet_ntoa(clientaddr.sin_addr));

		/* file name */
		read_len = read(client_sockfd, buf, MAXBUF);
		if(read_len > 0) {
			strcpy(file_name, buf);
			printf("%s > %s\n", inet_ntoa(clientaddr.sin_addr), file_name);
		} else {
			close(client_sockfd);
			break;
		}

		/* create file */
FILE_OPEN:
		des_fd = open(file_name, O_WRONLY | O_CREAT | O_EXCL, 0700);
		if(!des_fd) {
			perror("file open error : ");
			break;
		}
		if(errno == EEXIST) {
			close(des_fd);
			size_t len = strlen(file_name);
			file_name[len++] = '_';
			file_name[len++] = 'n';
			file_name[len] = '\0';
			goto FILE_OPEN;
		}
		
		/* file save */
		while(1) {
			memset(buf, 0x00, MAXBUF);
			file_read_len = read(client_sockfd, buf, MAXBUF);
			write(des_fd, buf, file_read_len);

			if(file_read_len == EOF | file_read_len == 0) {
				printf("finish file\n");
				break;
			}


		}


		close(client_sockfd);
		close(des_fd);
	}
	close(server_sockfd);
	return 0;
}
