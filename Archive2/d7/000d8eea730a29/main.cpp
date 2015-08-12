struct link {
    link* next;
};
link* first;
void h(link*& p) { // p is a reference to pointer
    p->next = first;
    first = p;
    p = 0;
}
void k() {
    link* q = new link;
    h(q);
}

int main()
{
int x = 10;
int* p = &x;
int*& rpx = p;
rpx = 0;
}