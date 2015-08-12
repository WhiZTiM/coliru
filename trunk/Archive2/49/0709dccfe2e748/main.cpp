#include <iostream>
#include <string>
#include <cstdint>
#include <boost/array.hpp>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef uint32_t ipv4_t;
typedef boost::array<unsigned char, 16> ipv6_t;

std::string ipv4ToStr(const ipv4_t ipv4, bool big_endian = false)
{
    struct sockaddr_in sa;
	char str[INET_ADDRSTRLEN];

	sa.sin_addr.s_addr = big_endian ? ipv4 : htonl(ipv4);
	inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);

	return str;
}

ipv4_t strToIpv4(const std::string& host)
{
    in_addr result;
	if (inet_pton(AF_INET, host.c_str(), &result) != 1)
		return 0;

	return static_cast<ipv4_t>(ntohl(result.s_addr));
}

ipv6_t strToIpv6(const std::string& host)
{
	ipv6_t addr;
	if (inet_pton(AF_INET6, host.c_str(), &addr[0]) != 1)
		return ipv6_t();
	return addr;
}

std::string ipv6ToStr(const ipv6_t ipv6)
{
	char dst[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET6, &ipv6[0], dst, INET6_ADDRSTRLEN); 
	return dst;
}

std::string toString(const uint32_t IN[4])
{
    std::string OUT;
    
    if(IN[0] != 0 && IN[1] == 0 && IN[2] == 0 && IN[3] == 0) {
		// Address is of ipv4 type
		OUT = ipv4ToStr(IN[0]);
	}
	else {
		ipv6_t ip6;
		size_t i=0, j=0;
		for(; i<4; i++) {
			ip6[j++]   = (IN[i]>>24) & 0xFF;
			ip6[j++]   = (IN[i]>>16) & 0xFF;
			ip6[j++]   = (IN[i]>>8)  & 0xFF;
			ip6[j++]   = (IN[i])     & 0xFF;
		}
		OUT = ipv6ToStr(ip6);
	}
    
    return OUT;
}

void fromString(const std::string& IN, uint32_t OUT[4])
{
	OUT[0] = strToIpv4(IN);
	if(OUT[0] == 0) {
		// ipv6 address
		ipv6_t ip6 = strToIpv6(IN);
		for(int i=0; i<4; i++)
			OUT[i] = (ip6[i*4] << 24) + (ip6[i*4+1] << 16) + (ip6[i*4+2] << 8) + ip6[i*4+3];
	}
	else {
		OUT[1] = 0;
		OUT[2] = 0;
		OUT[3] = 0;
	}
}

int main()
{
    const uint32_t IN[4]  = {0xC0A80001, 0, 0, 0};
    const std::string STR = toString(IN);
    
    uint32_t OUT[4];
    fromString(STR, OUT);
    
    std::cout << std::hex << std::showbase << IN[0] << ',' << IN[1] << ',' << IN[2] << ',' << IN[3] << '\n';
    std::cout << STR << '\n';
    std::cout << std::hex << std::showbase << OUT[0] << ',' << OUT[1] << ',' << OUT[2] << ',' << OUT[3] << '\n';
}
