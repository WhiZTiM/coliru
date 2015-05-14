
struct Test {};

static Test (&ms_channel)[2] = *(Test(*)[2])(0x0);

int main()
{
}