extern struct {
   short len;
   char s[32700];
   } foo;
 
int main() 
{
    foo.len = 0;
}