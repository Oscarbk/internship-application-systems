// Headers needed
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip_icmp.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>

// Define the Packet Constants

// ping packet size
#define PING_PKT_S 64
// Automatic port number
#define PORT_NO 0
#define PING_SLEEP_RATE 1000000 x
// Timeout delay will be 1 second
#define RECV_TIMEOUT 1
// Set a ping loop so we can handle interrupts later
int pingLoop = 1;

// Create ping packet structure
struct ping_pkt
{
	struct icmphdr hdr;
	char msg[PING_PKT_S - sizeof(struct icmphdr)];
};

// TODO: is param necessary?
// Breaks ping loop on interrupt
void intHandler(int dummy);
// Get IP address from host name
char *dns_lookup(char *addr_host, struct sockaddr_in *addr_con);

void send_ping(int ping_sockfd, struct sockaddr_in *ping_addr, 
				char *ping_dom, char *ping_ip, char *rev_host);

int main(int argc, char** argv)
{
	// Check param
	if ((argc != 2))
	{
		// TODO: Check to make sure argument is a valid IP address
		printf("Usage: ./host [hostname / IP Address]\n");
		return 1;
	}

	// Begin requests at a rate of 1 per second
	while(1)
	{

	}

	return 0;
}

void intHandler(int dummy)
{
	pingloop = 0;
}

char* dns_lookup(char *addr_host, struct sockaddr_in *addr_con) 
{
	printf("\nResolving DNS. . .\n");
	struct hostent *host_entity;
	char *ip = (char*) malloc(NI_MAXHOST * sizeof(char));
	int i;

	// Check that the hostname can be resolved
	if ((host_entity = gethostbyname()) == NULL)
		return NULL;
	// Else we can fill up the address structure
	strcpy(ip, inet_ntoa(*s(truct in_addr *)host_entity->h_addr));
	(*addr_con).sin_family = host_entity->h_addrtype;
	(*addr_con).sin_port = htons (PORT_NO);
	(*addr_con).sin_addr.s_addr = *(long*)host_entity->h_addr;
	return ip;
}

void send_ping(int ping_sockfd, struct sockaddr_in *ping_addr, 
				char *ping_dom, char *ping_ip, char *rev_host)
{
	int ttl_val = 64, msg_count = 0, i, addr_len, flag = 1, msg_received_count = 0;
	struct ping_pkt pckt;
	struct sockaddr_in r_addr;
	struct timespec time_start, time_end, tfs, tfe;
	long double rtt_msec = 0, total_msec = 0;
	struct timeval tv_out;
	tv_out.tv_sec = RECV_TIMEOUT;
	tv_out.tv_usec = 0;

	clock_gettime(CLOCK_MONOTONIC, &tfs);

	//TODO: Check if -ttl flag was set
	// If it was, set socket to TTL
	if (setsockopt(ping_sockfd, SOL_IP, IP_TTL, &ttl_val, sizeof(ttl_val)) != 0)
	{
		printf("\nSetting socket options to TTL failed\n");
		return;
	}
	else
		printf("\nSocket set to TTL\n");

	// Set timeout TODO: error?
	setsockopt(ping_sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_out, sizeof(tv_out));

	while(pingloop)
	{
		// Determine whether packet was sent or not
		flag = 1;
	}

}