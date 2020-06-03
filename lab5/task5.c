#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

static void myls(const char *name_dir, int flag) {
    DIR *dir;
    struct dirent *entry; // entry - указатель на структуру dirent
    dir = opendir(name_dir);
    if (!dir) {
        perror("dir opening error!\n");
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type != DT_DIR) {       // если это не директория
            printf("%s", entry->d_name);
            if (flag) { // если есть -l
                char fileName[1024];
                snprintf(fileName, sizeof fileName, "%s%s", name_dir,
                         entry->d_name); // склеиваем путь
                struct stat file_stat; // структура для описани файла
                printf(" (Size: %li, Number link: %lu, Number block: %li, UID: %u, "
                       "GID: %u, Mode: %u)",
                       file_stat.st_size, file_stat.st_nlink, file_stat.st_blocks,
                       file_stat.st_uid, file_stat.st_gid, file_stat.st_mode);
            }
            printf("\n");
        }
    }
    closedir(dir);
}

static int task5() {
    myls("../lab1/", 1); //../    ../lab1/
    return 0;
}