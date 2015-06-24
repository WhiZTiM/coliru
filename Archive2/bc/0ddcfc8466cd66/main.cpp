void func(char *) {
    
}

int main() {
    char arr[8];
    char (*arp)[8] = &arr;
    func(arp);
}
