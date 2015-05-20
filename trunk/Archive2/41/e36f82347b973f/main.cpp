extern int r[2];
int main() {
    int i = 10;
    extern int r[1 + ((&i +1) - &i)];// ok (but redudant)
}

