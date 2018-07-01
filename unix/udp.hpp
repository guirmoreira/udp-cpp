#ifndef UDP_HPP
    #define UDP_HPP

#define EXPR_SIZE   2048
#define BUFLEN      2048
#define TRUE        1
#define FALSE       0
#define SERVERLEN   1024


class Server
{
private:
    char* 			ip;
    unsigned int 	port;


public:
    Server(char* ip, unsigned int port);

    void 			set_ip(char* ip);
    void 			set_port(unsigned int port);

    char* 			get_ip();
    unsigned int 	get_port();

    void 			connect();

};
















#endif  // UDP_HPP
