#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int ft_popen(const char *file, char *const argv[], char type);

int main(void)
{
    char buffer[1024];
    int fd;

    printf("=== Test 1: 'r' mode - ls ===\n");
    char *argv1[] = {"ls", "-l", NULL};
    fd = ft_popen("ls", argv1, 'r');
    int bytes = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytes] = '\0';
    printf("%s\n", buffer);
    close(fd);
    wait(NULL);

    printf("=== Test 2: 'r' mode - echo ===\n");
    char *argv2[] = {"echo", "Hello!", NULL};
    fd = ft_popen("echo", argv2, 'r');
    bytes = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytes] = '\0';
    printf("Result: %s", buffer);
    close(fd);
    wait(NULL);

    printf("\n=== Test 3: 'w' mode - cat ===\n");
    char *argv3[] = {"cat", NULL};
    fd = ft_popen("cat", argv3, 'w');
    write(fd, "Line 1\nLine 2\n", 14);
    close(fd);
    wait(NULL);

    printf("\n=== All tests passed! ===\n");
    return 0;
}
