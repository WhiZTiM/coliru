#include <iostream>
#include <string>
#include <cstdint>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef in_addr ipv4_t;
typedef in6_addr ipv6_t;

ipv4_t hintToIpv4(const uint32_t i)
{
    ipv4_t result = { htonl(i) };
	return result;
}

ipv4_t nintToIpv4(const uint32_t i)
{
	ipv4_t result = { i };
	return result;
}

std::string ipv4ToStr(const ipv4_t ipv4)
{
    char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &ipv4, str, INET_ADDRSTRLEN);
	return str;
}

std::string ipv4ToStr(const uint32_t i)
{
	return ipv4ToStr(hintToIpv4(i));
}

ipv4_t strToIpv4(const std::string& host)
{
	ipv4_t result;
	if (inet_pton(AF_INET, host.c_str(), &result) != 1)
		return ipv4_t();

	return result;
}

std::string ipv6ToStr(const ipv6_t ipv6)
{
	char dst[INET6_ADDRSTRLEN];
	inet_ntop(AF_INET6, &ipv6, dst, INET6_ADDRSTRLEN); 
	return dst;
}

ipv6_t strToIpv6(const std::string& host)
{
	ipv6_t result;
	if (inet_pton(AF_INET6, host.c_str(), &result) != 1)
		return ipv6_t();
	
	return result;
}

std::string toString(const uint32_t IN[4])
{
    std::string OUT;
    
    if (IN[0] != 0 && IN[1] == 0 && IN[2] == 0 && IN[3] == 0) {
		OUT = ipv4ToStr(IN[0]);
	}
	else {
		ipv6_t ip6;
		
		for (size_t i = 0, j = 0; i < 4; i++) {
			ip6.s6_addr[j++] = (IN[i]>>24) & 0xFF;
			ip6.s6_addr[j++] = (IN[i]>>16) & 0xFF;
			ip6.s6_addr[j++] = (IN[i]>>8)  & 0xFF;
			ip6.s6_addr[j++] = (IN[i])     & 0xFF;
		}
		
		OUT = ipv6ToStr(ip6);
	}
    
    return OUT;
}

void fromString(const std::string& IN, uint32_t OUT[4])
{
    OUT[0] = strToIpv4(IN).s_addr;
	if (OUT[0] == 0) {
		ipv6_t ip6 = strToIpv6(IN);
		for (size_t i = 0; i < 4; i++) {
			OUT[i]  = (ip6.s6_addr[i*4]     << 24);
			OUT[i] += (ip6.s6_addr[i*4 + 1] << 16);
			OUT[i] += (ip6.s6_addr[i*4 + 2] << 8);
			OUT[i] += (ip6.s6_addr[i*4 + 3]);
		}
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
