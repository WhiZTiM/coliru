#include <stdio.h>
#include <string.h>
int main()
{
    unsigned char dAddr[256];
    unsigned char sMask[256];
    unsigned char nHop[256];
    memset(dAddr,0,sizeof(dAddr));
    memset(sMask,0,sizeof(sMask));
    memset(nHop,0,sizeof(nHop));
    unsigned int u4IpDAddr = 0x01020304;
    unsigned int u4IpSNetMask = 0xffff01ff;
    unsigned int u4NHopGt = 0x01020304;
    char *dip = (char *)&u4IpDAddr;
    char *smk = (char *)&u4IpSNetMask;
    char *nhp = (char *)&u4NHopGt;
    sprintf((char *) dAddr, "%u.%u.%u.%u", dip[3], dip[2], dip[1], dip[0]);  //if I used %d.%d.%d.%d its working fine
    sprintf((char *) sMask, "%u.%u.%u.%u", smk[3], smk[2], smk[1], smk[0]); //if I used %d.%d.%d.%d its working fine
    sprintf((char *) nHop, "%u.%u.%u.%u", nhp[3], nhp[2], nhp[1], nhp[0]); //if I used %d.%d.%d.%d its working fine
    printf("SAM: func %s line %d IpDAddr %s Mask %s NHop %s\n",__func__,__LINE__,dAddr,sMask,nHop);
}