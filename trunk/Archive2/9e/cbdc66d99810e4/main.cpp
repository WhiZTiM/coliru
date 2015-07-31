#include <stdio.h>
#include <assert.h>

int main()
{
    char v1 = 'x', v2 = 'x'; // variables not assigned to by scanf maintain their initial value
    
    int result = scanf("--%c--%c--", &v1, &v2);
    printf("scanf return value is %d. v1 has value '%c'. v2 has value '%c'.\n", result, v1, v2); 
}
