const int a = 1;
const int b = 1;
const int c = 1;

void functiona(char (&array)[a][b][c]){}
void functionb(char (&array)[a][b][c]){}

//this is not working
int main(){
  char array[a][b][c];

  functiona(array);
  functionb(array);
}