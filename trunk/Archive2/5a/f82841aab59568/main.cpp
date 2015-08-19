enum class ConnectionState : int
{
    Connecting,
    Reconnecting = 2,
    Disconnecting,
    LocalConnection,
    NoNetwork = 2,
    WifiNetwork,
    Last
};

int main() {}