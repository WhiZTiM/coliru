#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int file_select(const struct dirent *entry)
{
    struct stat st; 
    stat(entry->d_name, &st);
    return (st.st_mode & S_IFREG);       // This doesn't work
//    return (st.st_mode & S_IFDIR);  // This lists everything
}
int num_sort(const struct dirent **e1, const struct dirent **e2) {
    char* pch = strtok ((char*)(*e1)->d_name,".");
    char* pch2 = strtok ((char*)(*e2)->d_name,".");
    const char *a = (*e1)->d_name;
    const char *b = (*e2)->d_name;
    return atoi(b) > atoi(a);
}

int main(void)
{
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, file_select, num_sort);
    if (n < 0) {
        perror("scandir");
} else {
    while (n--) {
        printf("File:%s\n", namelist[n]->d_name);
        free(namelist[n]);
    }
    free(namelist);
}
}
