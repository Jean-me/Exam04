#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int ft_popen(const char *file, char *const argv[], char type);

int main(void)
{
    char buffer[4096];
    int fd;
    int bytes;

    printf("=== テスト1: 'r'モード - lsの出力を読む ===\n");
    char *argv_ls[] = {"ls", "-l", NULL};
    fd = ft_popen("ls", argv_ls, 'r');

    if (fd != -1) // read
    {
        bytes = read(fd, buffer, sizeof(buffer) - 1); // fdから読んでる
        buffer[bytes] = '\0';
        printf("%s\n", buffer);
        close(fd);
        wait(NULL);
    }

    printf("\n=== テスト2: 'r'モード - echoの出力を読む ===\n");
    char *argv_echo[] = {"echo", "Hello from echo!", NULL};
    fd = ft_popen("echo", argv_echo, 'r');

    if (fd != -1)
    {
        bytes = read(fd, buffer, sizeof(buffer) - 1);
        buffer[bytes] = '\0';
        printf("受け取った: %s", buffer);
        close(fd);
        wait(NULL);
    }

    printf("\n=== テスト3: 'r'モード - dateの出力を読む ===\n");
    char *argv_date[] = {"date", NULL};
    fd = ft_popen("date", argv_date, 'r');

    if (fd != -1)
    {
        bytes = read(fd, buffer, sizeof(buffer) - 1);
        buffer[bytes] = '\0';
        printf("現在時刻: %s", buffer);
        close(fd);
        wait(NULL);
    }

    printf("\n=== テスト4: 'w'モード - catに書き込む ===\n");
    char *argv_cat[] = {"cat", NULL};
    fd = ft_popen("cat", argv_cat, 'w');

    if (fd != -1)
    {
        char *msg = "Hello from parent!\nThis is line 2\n";
        write(fd, msg, strlen(msg));
        close(fd);
        wait(NULL);
    }

    printf("\n=== 完了 ===\n");
    return 0;
}
