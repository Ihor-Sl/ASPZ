# Практична робота №7

## Звіт по завданням

## Завдання 1

Використайте popen(), щоб передати вивід команди rwho (команда UNIX) до more (команда UNIX) у програмі на C.

```shell
admin@FreeBSD:~/ASPZ/practice7 $ gcc -Wall 1.c -o 1
admin@FreeBSD:~/ASPZ/practice7 $ ./1
admin            ttyv8        Feb 14 09:51 (:0)
admin@FreeBSD:~/ASPZ/practice7 $
```

## Завдання 2

Напишіть програму мовою C, яка імітує команду ls -l в UNIX — виводить список усіх файлів у поточному каталозі та перелічує права доступу тощо.

```shell
admin@FreeBSD:~/ASPZ/practice7 $ ./2
drwxr-xr-x 2 admin admin   512 May 08 00:56 .
drwxr-xr-x 10 admin admin   512 May 08 00:14 ..
-rw-r--r-- 1 admin admin  1071 May 08 00:14 19.c
-rw-r--r-- 1 admin admin  1764 May 08 00:52 README.md
-rw-r--r-- 1 admin admin 62418 May 08 00:14 out.txt
-rw-r--r-- 1 admin admin   331 May 08 00:19 1.c
-rwxr-xr-x 1 admin admin  8920 May 08 00:55 1
-rw-r--r-- 1 admin admin  1312 May 08 00:22 2.c
-rwxr-xr-x 1 admin admin 10000 May 08 00:56 2
-rw-r--r-- 1 admin admin   493 May 08 00:25 3.c
-rwxr-xr-x 1 admin admin  9064 May 08 00:25 3
-rw-r--r-- 1 admin admin   616 May 08 00:32 4.c
-rw-r--r-- 1 admin admin   285 May 08 00:42 9.c
-rw-r--r-- 1 admin admin   699 May 08 00:33 5.c
-rwxr-xr-x 1 admin admin  9344 May 08 00:34 5
-rw-r--r-- 1 admin admin   768 May 08 00:35 6.c
-rwxr-xr-x 1 admin admin  9616 May 08 00:37 6
-rw-r--r-- 1 admin admin   703 May 08 00:38 7.c
-rw-r--r-- 1 admin admin   522 May 08 00:39 8.c
-rwxr-xr-x 1 admin admin  9104 May 08 00:40 8
-rwxr-xr-x 1 admin admin  8472 May 08 00:42 9
-rw-r--r-- 1 admin admin   844 May 08 00:51 10.c
-rwxr-xr-x 1 admin admin  9584 May 08 00:52 10
admin@FreeBSD:~/ASPZ/practice7 $
```

## Завдання 3

Напишіть програму, яка друкує рядки з файлу, що містять слово, передане як аргумент програми (проста версія утиліти grep в UNIX).

```shell
admin@FreeBSD:~/ASPZ/practice7 $ gcc -Wall 3.c -o 3
admin@FreeBSD:~/ASPZ/practice7 $ ./3
Usage: ./3 <word> <filename>
admin@FreeBSD:~/ASPZ/practice7 $ ./3 main 2.c
int main() {
admin@FreeBSD:~/ASPZ/practice7 $
```

## Завдання 4

Напишіть програму, яка виводить список файлів, заданих у вигляді аргументів, з зупинкою кожні 20 рядків, доки не буде натиснута клавіша (спрощена версія утиліти more в UNIX).

```shell
admin@FreeBSD:~/ASPZ/practice7 $ gcc -Wall 4.c -o 4
admin@FreeBSD:~/ASPZ/practice7 $ ./4 3.c
#include <stdio.h>
#include <string.h>

#define LINE_LEN 1024

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[2], "r");
    if (!fp) {
        perror("fopen failed");
        return 1;
    }

    char line[LINE_LEN];
    while (fgets(line, LINE_LEN, fp)) {
        if (strstr(line, argv[1])) {
--More--
            printf("%s", line);
        }
    }

    fclose(fp);
    return 0;
}
admin@FreeBSD:~/ASPZ/practice7 $
```

## Завдання 5

Напишіть програму, яка перелічує всі файли в поточному каталозі та всі файли в підкаталогах.

```shell
admin@FreeBSD:~/ASPZ/practice7 $ gcc -Wall 5.c -o 5
admin@FreeBSD:~/ASPZ/practice7 $ cd ..
admin@FreeBSD:~/ASPZ $ ./practice7/5
./.git
./.git/description
./.git/hooks
./.git/hooks/applypatch-msg.sample
./.git/hooks/commit-msg.sample
./.git/hooks/fsmonitor-watchman.sample
./.git/hooks/post-update.sample
./.git/hooks/pre-applypatch.sample
./.git/hooks/pre-commit.sample
./.git/hooks/pre-merge-commit.sample
./.git/hooks/pre-push.sample
./.git/hooks/pre-rebase.sample
./.git/hooks/pre-receive.sample
./.git/hooks/prepare-commit-msg.sample
./.git/hooks/push-to-checkout.sample
./.git/hooks/sendemail-validate.sample
./.git/hooks/update.sample
./.git/info
./.git/info/exclude
./.git/objects
./.git/objects/pack
./.git/objects/pack/pack-f4f3514a3a52d24bfc00ecbbf253ba5c51fea648.pack
./.git/objects/pack/pack-f4f3514a3a52d24bfc00ecbbf253ba5c51fea648.rev
./.git/objects/pack/pack-f4f3514a3a52d24bfc00ecbbf253ba5c51fea648.idx
./.git/objects/pack/pack-3170aa88246f87fd940c82b453bcb552657aecac.pack
./.git/objects/pack/pack-3170aa88246f87fd940c82b453bcb552657aecac.rev
./.git/objects/pack/pack-3170aa88246f87fd940c82b453bcb552657aecac.idx
./.git/objects/info
./.git/objects/e6
./.git/objects/e6/27baf23fd59b0318fa8835074a9635d16b302a
./.git/objects/e7
./.git/objects/e7/af73d7dba3216885018c269aa12f8ae1c52d30
./.git/objects/cf
./.git/objects/cf/a40d297822e690112247b6573b6bf31d878c1d
./.git/objects/2f
./.git/objects/2f/0b0c59b9b9324a73a7e1b9aed328d16b0b0def
./.git/objects/d7
./.git/objects/d7/44d2a66a6fb39c22b0119f0df31d97744b74a1
./.git/objects/df
./.git/objects/df/96aa2ef15464c994a7b1bd1921817d6711a76d
./.git/objects/fb
./.git/objects/fb/90df6878f0dccf2d035725fa1921ab2aef71f9
./.git/objects/dc
./.git/objects/dc/2b14c962dfd99013b97aaa37d2b2f8f219fd20
./.git/objects/bf
./.git/objects/bf/7e0115a5889bcff983f9fab00560bc5f56a70d
./.git/objects/c5
./.git/objects/c5/b92b6955270939248e4881abbd6ace8ee78c65
./.git/objects/c5/f12247dc3a44953ccc74f5bfdf14e14e4cfed5
./.git/objects/6d
./.git/objects/6d/93159e1fe48447df78bb592a88420720e38440
./.git/objects/0b
./.git/objects/0b/23a956e57ed3bac0cafd3c2f7ea339c5cec1c1
./.git/objects/32
./.git/objects/32/75d3e310b457278067698daac1ee3381d4ee32
./.git/objects/73
./.git/objects/73/124b624f094c664165dc8445144f39cea30bc4
./.git/objects/f8
./.git/objects/f8/1c1a994f1355aac610fe7c881ea25c347d6651
./.git/objects/3b
./.git/objects/3b/5bd8db0c00b33a9c4e4e846516a4599cd1bf97
./.git/objects/3b/e8533bc133cc6d8042fa6b90f6e0aa32ecbcbf
./.git/objects/26
./.git/objects/26/e55ebfe871cc7f10f207a237820389c752ba61
./.git/objects/33
./.git/objects/33/7fdcb78e686571dafe8f2aa81e5ec708d77e29
./.git/objects/83
./.git/objects/83/21e25d3174e06bfbcc553517e13c5250e25772
./.git/objects/fa
./.git/objects/fa/4582585da75cd88d76c2b3c252862391a913da
./.git/objects/b7
./.git/objects/b7/153a02132b9f66ca9953a30ac50130adc72b6e
./.git/objects/14
./.git/objects/14/8548f74971efb9780d4495d2f1d67de5d98e07
./.git/objects/97
./.git/objects/97/2d2dfc42b82e56102c0c4e2aee7512fbe9bf79
./.git/objects/dd
./.git/objects/dd/b70f1b0225299792546b2defbafedc35a6117e
./.git/objects/1d
./.git/objects/1d/a586f4356192c1b198c549ee56b8f3f23110f0
./.git/objects/f6
./.git/objects/f6/133c047e5f964743422a022d1d67315a5dbd0f
./.git/objects/3e
./.git/objects/3e/7aba3fc5c1212b19161368dffa7045cd41864c
./.git/objects/f2
./.git/objects/f2/0d1cb1b37e0a69059a88fc1757dc3c501b4389
./.git/objects/7c
./.git/objects/7c/e913295835c403d6d0550b84d8f143dd7f2ee1
./.git/objects/5e
./.git/objects/5e/e2d96e8a3f4d90893c9fb38d637fcd6840ae18
./.git/objects/93
./.git/objects/93/a9ac54bc2f0c9b177cb95f45f0edb9a2aaebf1
./.git/objects/7e
./.git/objects/7e/592122ec18f39ad9ca5351fc9fd0592aaae463
./.git/objects/7e/d5175c6bb829546b4fc9539c6cbbffa4a921b2
./.git/objects/6f
./.git/objects/6f/e5917d810a1e8918b453ff5ee5f9a40d056f1b
./.git/objects/d6
./.git/objects/d6/a8d7fc81e526d9da09e4bdfeef224d1bc0498d
./.git/objects/c7
./.git/objects/c7/9d5cf47f647258730108d559ed0ed140829338
./.git/objects/9d
./.git/objects/9d/4ae22f7ae39102663df255727299b132e9514f
./.git/objects/0c
./.git/objects/0c/d098b6caa9674b8e7eaf552f027bc97bb5cc7d
./.git/objects/8c
./.git/objects/8c/7895b5c6fa22c22705087481f05fc80ff15db7
./.git/objects/40
./.git/objects/40/bf6e5ef348f936655eaed2d93bf7dd04117d40
./.git/config
./.git/HEAD
./.git/refs
./.git/refs/heads
./.git/refs/heads/main
./.git/refs/tags
./.git/refs/remotes
./.git/refs/remotes/origin
./.git/refs/remotes/origin/HEAD
./.git/refs/remotes/origin/main
./.git/logs
./.git/logs/refs
./.git/logs/refs/remotes
./.git/logs/refs/remotes/origin
./.git/logs/refs/remotes/origin/HEAD
./.git/logs/refs/remotes/origin/main
./.git/logs/refs/heads
./.git/logs/refs/heads/main
./.git/logs/HEAD
./.git/FETCH_HEAD
./.git/index
./.git/packed-refs
./.git/COMMIT_EDITMSG
./.git/ORIG_HEAD
./practice1
./practice1/README.md
./practice1/char_freq.c
./practice1/execution.png
./practice2
./practice2/1.c
./practice2/2_1.c
./practice2/2_2.c
./practice2/2_3.c
./practice2/2_4.c
./practice2/README.md
./practice2/3_1
./practice2/3_1.c
./practice2/3_2.c
./practice2/3_2
./practice2/4.c
./practice2/4
./practice2/variant_19
./practice2/variant_19.c
./.gitignore
./practice3
./practice3/README.md
./practice3/task1
./practice3/task1/Dockerfile
./practice3/task2
./practice3/task2/Dockerfile
./practice3/task3
./practice3/task3/Dockerfile
./practice3/task3/dice_roll.c
./practice3/task4
./practice3/task4/Dockerfile
./practice3/task4/numbers_generator.c
./practice3/task5
./practice3/task5/Dockerfile
./practice3/task5/file_copy.c
./practice3/task5/input.txt
./practice3/task6
./practice3/task6/Dockerfile
./practice3/task6/stack_example.c
./practice3/variant19
./practice3/variant19/Dockerfile
./practice3/variant19/server_load.c
./practice4
./practice4/1.c
./practice4/19.c
./practice4/2.c
./practice4/3.c
./practice4/4_1.c
./practice4/4_2.c
./practice4/5.c
./practice4/6.c
./practice4/7_1.c
./practice4/7_2.c
./practice4/README.md
./practice5
./practice5/19.c
./practice5/README.md
./practice6
./practice6/README.md
./practice6/makefile
./practice6/mem_issues.c
./practice6/mem_issues_dbg_asan.o
./practice7
./practice7/19.c
./practice7/README.md
./practice7/out.txt
./practice7/1.c
./practice7/1
./practice7/2.c
./practice7/2
./practice7/3.c
./practice7/3
./practice7/4.c
./practice7/9.c
./practice7/5.c
./practice7/5
./practice7/6.c
./practice7/6
./practice7/7.c
./practice7/8.c
./practice7/8
./practice7/9
./practice7/10.c
./practice7/10
./practice7/4
admin@FreeBSD:~/ASPZ $
```
## Завдання 6

Напишіть програму, яка перелічує лише підкаталоги у алфавітному порядку.

```shell
admin@FreeBSD:~/ASPZ/practice7 $ gcc -Wall 6.c -o 6
admin@FreeBSD:~/ASPZ/practice7 $ cd ..
admin@FreeBSD:~/ASPZ $ ./practice7/6
.git
practice1
practice2
practice3
practice4
practice5
practice6
practice7
admin@FreeBSD:~/ASPZ $
```

## Завдання 7

Напишіть програму, яка показує користувачу всі його/її вихідні програми на C, а потім в інтерактивному режимі запитує, чи потрібно надати іншим дозвіл на читання (read permission); у разі ствердної відповіді — такий дозвіл повинен бути наданий.

```shell
admin@FreeBSD:~/ASPZ/practice7 $ gcc -Wall 7.c -o 7.out
admin@FreeBSD:~/ASPZ/practice7 $ ./7.out
Allow read permission for others on 7.out? (y/n): y
admin@FreeBSD:~/ASPZ/practice7 $
```

## Завдання 8

Напишіть програму, яка надає користувачу можливість видалити будь-який або всі файли у поточному робочому каталозі. Має з’являтися ім’я файлу з запитом, чи слід його видалити.

```shell
admin@FreeBSD:~/ASPZ/practice7 $ gcc -Wall 8.c -o 8
admin@FreeBSD:~/ASPZ/practice7 $ ./8
Delete 19.c? (y/n): n
Delete README.md? (y/n): n
Delete out.txt? (y/n): n
Delete 1.c? (y/n): n
Delete 1? (y/n): y
Delete 2.c? (y/n): n
Delete 2? (y/n): y
Delete 3.c? (y/n): n
Delete 3? (y/n): n
Delete 4.c? (y/n): n
Delete 9.c? (y/n): n
Delete 5.c? (y/n): n
Delete 5? (y/n): n
Delete 6.c? (y/n): n
Delete 6? (y/n): y
Delete 7.c? (y/n): n
Delete 8.c? (y/n): n
Delete 8? (y/n): n
Delete 9? (y/n): n
Delete 10.c? (y/n): n
Delete 10? (y/n): n
Delete 4? (y/n): n
Delete 7? (y/n): n
Delete 7.out? (y/n): n
admin@FreeBSD:~/ASPZ/practice7 $
```

## Завдання 9

Напишіть програму на C, яка вимірює час виконання фрагмента коду в мілісекундах.

```shell
admin@FreeBSD:~/ASPZ/practice7 $ gcc -Wall 9.c -o 9
admin@FreeBSD:~/ASPZ/practice7 $ ./9
Elapsed time: 46.88 ms
admin@FreeBSD:~/ASPZ/practice7 $
```

## Завдання 10
Напишіть програму мовою C для створення послідовності випадкових чисел з плаваючою комою у діапазонах:

 (a) від 0.0 до 1.0
 
 (b) від 0.0 до n, де n — будь-яке 
 дійсне число з плаваючою точкою.
 Початкове значення генератора випадкових чисел має бути встановлене так, щоб гарантувати унікальну послідовність.

```shell
admin@FreeBSD:~/ASPZ/practice7 $ gcc -Wall 10.c -o 10
admin@FreeBSD:~/ASPZ/practice7 $ ./10
Випадкові числа в діапазоні [0.0; 1.0]:
0.347547
0.676168
0.516638
0.418935
0.426977

Введіть значення n для генерації чисел в [0.0; n]: 7
Випадкові числа в діапазоні [0.0; 7.00]:
0.691524
1.252261
2.152356
5.014871
6.453279
admin@FreeBSD:~/ASPZ/practice7 $
```

## Завдання по варіанту 19

Зробіть скрипт, який виявляє неочевидні залежності між файлами і процесами, що їх використовують.

## Опис рішення

Программа призначена для виявлення зв’язків між процесами та файлами, які вони використовують, що дозволяє встановити неочевидні залежності в системі. Він отримує інформацію про всі активні процеси та для кожного з них збирає дані про відкриті файли, виводячи на екран PID процесу та шлях до файлу. Таким чином можна виявити, які файли використовуються одночасно кількома процесами, що може свідчити про спільні ресурси, конфігураційні залежності або потенційні конфлікти, які не є очевидними при звичайному аналізі.

Використовується `libprocstat`, щоб виявити зв’язки між процесами та файлами які використовуються ними.

## Запуск програми

Вивід програми записано у файл: [out.txt](out.txt)

```shell
root@FreeBSD:/home/admin/ASPZ/practice7 # gcc -Wall 19.c -o 19 -lprocstat
root@FreeBSD:/home/admin/ASPZ/practice7 # ./19 > out.txt
root@FreeBSD:/home/admin/ASPZ/practice7 #
```