# Завдання 1

Використання --privileged ulimit

Запуск без --privileged

```shell
$ ulimit -n
1048576
$ ulimit -aS | grep "open files"
open files                          (-n) 1048576
$ ulimit -aH | grep "open files"
open files                          (-n) 1048576
$ ulimit -n 3000
$ ulimit -aS | grep "open files"
open files                          (-n) 3000
$ ulimit -aH | grep "open files"
open files                          (-n) 3000
$ ulimit -n 3001
/bin/bash: line 1: ulimit: open files: cannot modify limit: Operation not permitted
$ ulimit -n 2000
$ ulimit -n
2000
$ ulimit -aS | grep "open files"
open files                          (-n) 2000
$ ulimit -aH | grep "open files"
open files                          (-n) 2000
$ ulimit -n 3000
/bin/bash: line 1: ulimit: open files: cannot modify limit: Operation not permitted
```

Запуск з --privileged

```shell
$ ulimit -n
1048576
$ ulimit -aS | grep "open files"
open files                          (-n) 1048576
$ ulimit -aH | grep "open files"
open files                          (-n) 1048576
$ ulimit -n 3000
$ ulimit -aS | grep "open files"
open files                          (-n) 3000
$ ulimit -aH | grep "open files"
open files                          (-n) 3000
$ ulimit -n 3001
$ ulimit -n 2000
$ ulimit -n
2000
$ ulimit -aS | grep "open files"
open files                          (-n) 2000
$ ulimit -aH | grep "open files"
open files                          (-n) 2000
$ ulimit -n 3000
```

# Завдання 2

Проексперементовано утиліту perf

```shell
$ perf --version
perf version 6.1.129
$ perf stat echo Hello World
Hello World!

 Performance counter stats for 'echo Hello World!':

              0.41 msec task-clock:u                     #    0.447 CPUs utilized
                 0      context-switches:u               #    0.000 /sec
                 0      cpu-migrations:u                 #    0.000 /sec
                53      page-faults:u                    #  129.743 K/sec
            480590      cycles:u                         #    1.176 GHz
             59949      stalled-cycles-frontend:u        #   12.47% frontend cycles idle   
             38599      stalled-cycles-backend:u         #    8.03% backend cycles idle    
            113567      instructions:u                   #    0.24  insn per cycle
                                                  #    0.53  stalled cycles per insn
             23891      branches:u                       #   58.485 M/sec
              2596      branch-misses:u                  #   10.87% of all branches

       0.000913754 seconds time elapsed

       0.000199000 seconds user
       0.000000000 seconds sys


```

# Завдання 3

Написано програму, що імітує лотерею

Задано ліміт за допомогою prlimit --fsize=16:16 ./dice_roll

Обреблено коректно досягнення ліміту

```shell
$ prlimit --fsize=16:16 ./dice_roll
Current file size limit: soft = 16, hard = 16
File size limit reached. Stopping write operation.
Contents of dice_rolls.txt:
1
1
6
4
1
2
2
2
```

# Завдання 4

Написано програму для генерації випадкових чисел

Встановлено ліміт та обробленно сиуації перевищення

```shell
$ prlimit --cpu=1:2 ./numbers_generator
Numbers to 49: 8 41 48 35 9 37 14
Numbers to 36: 10 14 23 13 12 26
```

Додамо навантаження у вигляді бескінечного циклу перед printf("Numbers to 36: ")

Відпрацює обробка помилки

```shell
$ prlimit --cpu=1:2 ./numbers_generator
Numbers to 49: 30 40 19 7 27 13 41
CPU limit usage reached
```

# Завдання 5

Написано програму для копіювання одного іменованого файлу в інший

Встановлено ліміт програмно (setrlimit) та обробленно ситуації перевищення лі

```shell
$ ./file_copy input.txt outpux.txt
Reached file size limit
Contents of outpux.txt:
1
2
```

# Завдання 6

Написано програму, що демонструє використання обмеження (max stack segment size)

```shell
$ prlimit --stack=100000:100000 ./stack_example
Stack size limit: 100000 bytes
Recursion depth: 1
Recursion depth: 2
Recursion depth: 3
Recursion depth: 4
Recursion depth: 5
Recursion depth: 6
Recursion depth: 7
Recursion depth: 8
Recursion depth: 9
```

# Завдання по варіанту 19

Створено імітацію серверного навантаження і протестовано обмеження за допомогою ulimit -u

```shell
$ ulimit -u 80
$ ./server_load
Child process ID: 7
fork failed: Resource temporarily unavailable
fork failed: Resource temporarily unavailable
fork failed: Resource temporarily unavailable
Child process ID: 9
Child process ID: 8
fork failed: Resource temporarily unavailable
fork failed: Resource temporarily unavailable
fork failed: Resource temporarily unavailable
fork failed: Resource temporarily unavailable
```