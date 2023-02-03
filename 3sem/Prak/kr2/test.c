    #include <stdlib.h>
    #include <inttypes.h>
    #include <sys/sem.h>
    #include <sys/shm.h>
    #include <sys/ipc.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <sys/wait.h>
    #include <unistd.h>
    #include <fcntl.h>

    enum
    {
    SIZE = 100000,
    BASE = 10
    };

    int
    main(int argc, char *argv[])
    {
    int fd = open(argv[1], O_RDONLY);
    unsigned long long input, num, array[SIZE] = {0}, cnt = 0;
    unsigned long long bound = strtoull(argv[2], NULL, BASE);

    while (read(fd, &input, sizeof(input)) == sizeof(input))
    {
    if (input >= bound) {
    array[cnt] = input;
    cnt++;
    }
    }
    close(fd);
    fd = open(argv[1], O_WRONLY|O_TRUNC);
    for (int i = 0; i < cnt; ++i) {
    num = array[i];
    printf("%llu\n", num);
    write(fd, &num, sizeof(num));
    }
    close(fd);

    return 0;
    }

