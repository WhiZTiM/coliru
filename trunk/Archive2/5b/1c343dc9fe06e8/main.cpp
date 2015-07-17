



void arp_controller(RemoteIP remote_ip, yield_context& yield)
{
    RemoteMAC remote_mac = stack.perform_arp(remote_ip, yield);
    yield(remote_mac);
}


void rpc_perform_arp(std::string s, yield_context& yield)
{
    RemoteIPv4 remote_ip  = RemoteIPv4::FromString(s);        
    RemoteMAC  remote_mac = arp_controller(remote_ip, yield);
    yield(remote_mac.toString());
}