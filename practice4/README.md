# Практична робота №3

# Звіт по завданням

# Завдання 1

Скільки пам’яті може виділити malloc(3) за один виклик? Максимальне значення, яке можна передати в malloc(3), — це SIZE_MAX, оскільки параметр malloc() має тип size_t. У 64-бітній системі size_t займає 8 байтів, отже, SIZE_MAX = 2^64 - 1. Але фізично система не може виділити 16 ексабайт через:
- Обмеження віртуальної пам’яті процесу.
- Обмеження ядра та керування пам’яттю.
- Реальні апаратні обмеження.

```shell
admin@FreeBSD:~/ASPZ/practice4 $ gcc 1.c -o 1
admin@FreeBSD:~/ASPZ/practice4 $ ./1
Attempting to allocate 18446744073709551615 bytes of memory...
malloc failed: cannot allocate 18446744073709551615 bytes
admin@FreeBSD:~/ASPZ/practice4 $ gcc 1.c -m32 -o 1
admin@FreeBSD:~/ASPZ/practice4 $ ./1
Attempting to allocate 4294967295 bytes of memory...
malloc failed: cannot allocate 4294967295 bytes
admin@FreeBSD:~/ASPZ/practice4 $
```

# Завдання 2

Що станеться, якщо передати malloc(3) від’ємний аргумент? Оскільки malloc(3) приймає size_t, передати йому від’ємне значення напряму неможливо, але якщо використовується int, можлива ситуація з переповненням.

При від'ємному значенні із-за переповненя буде максимальне значення size_t

```shell
admin@FreeBSD:~/ASPZ/practice4 $ gcc 2.c -o 2
admin@FreeBSD:~/ASPZ/practice4 $ ./2
malloc failed: cannot allocate 18446744072982171648 bytes
admin@FreeBSD:~/ASPZ/practice4 $ gcc 2.c -m32 -o 2
admin@FreeBSD:~/ASPZ/practice4 $ ./2
malloc failed: cannot allocate 3567587328 bytes
admin@FreeBSD:~/ASPZ/practice4 $
```

# Завдання 3

Що станеться, якщо використати malloc(0)?

Повертається не NULL вказівник

Дослідженно роботу програми через ltrace

```shell
admin@FreeBSD:~/ASPZ/practice4 $ gcc 3.c -o 3
admin@FreeBSD:~/ASPZ/practice4 $ ./3
malloc(0) returned a non-NULL pointer
admin@FreeBSD:~/ASPZ/practice4 $ ltrace ./3
Couldn't determine base address of [vdso]
Couldn't load ELF object [vdso]: No such file or directory
__libc_start1(1, 0x820ffc310, 0x820ffc320, 0xf7e258aacc0, 0x400602 <unfinished ...>
malloc(0)                                                           = 0x25d6d8008008
puts("malloc(0) returned a non-NULL po"...malloc(0) returned a non-NULL pointer
)                         = 10
free(0x25d6d8008008)                                                = <void>
+++ exited (status 0) +++
admin@FreeBSD:~/ASPZ/practice4 $
```

# Завдання 4

Проблема цього коду полягає в тому, що після виклику free(ptr) вказівник ptr стає недійсним, і наступна ітерація циклу спробує використати цей вказівник, що може призвезти до невизначеної поведінки.

Правильним варіантом буде звільнити пам'ять після циклу або ptr = NULL; на кінці ітерації

```shell
admin@FreeBSD:~/ASPZ/practice4 $ gcc 4_2.c -o 4_2
admin@FreeBSD:~/ASPZ/practice4 $ ./4_2
Data: 11111111
Data: 22222222
Data: 33333333
Data: 44444444
Data: 55555555
admin@FreeBSD:~/ASPZ/practice4 $ ltrace ./4_2
Couldn't determine base address of [vdso]
Couldn't load ELF object [vdso]: No such file or directory
__libc_start1(1, 0x8211f3900, 0x8211f3910, 0x20f15eb33cc0, 0x400662 <unfinished ...>
malloc(8)                                                           = 0x3d0d69c08008
printf("Data: ")                                                    = 6
printf("%d", 1)                                                     = 1
printf("%d", 1)                                                     = 1
printf("%d", 1)                                                     = 1
printf("%d", 1)                                                     = 1
printf("%d", 1)                                                     = 1
printf("%d", 1)                                                     = 1
printf("%d", 1)                                                     = 1
printf("%d", 1)                                                     = 1
putchar(10, 0x8211f2dff, 49, 0xc4659adfa372773f, 0x822380618Data: 11111111
)       = 10
printf("Data: ")                                                    = 6
printf("%d", 2)                                                     = 1
printf("%d", 2)                                                     = 1
printf("%d", 2)                                                     = 1
printf("%d", 2)                                                     = 1
printf("%d", 2)                                                     = 1
printf("%d", 2)                                                     = 1
printf("%d", 2)                                                     = 1
printf("%d", 2)                                                     = 1
putchar(10, 0x8211f2dff, 50, 0xc4659adfa372773f, 0x822380618Data: 22222222
)       = 10
printf("Data: ")                                                    = 6
printf("%d", 3)                                                     = 1
printf("%d", 3)                                                     = 1
printf("%d", 3)                                                     = 1
printf("%d", 3)                                                     = 1
printf("%d", 3)                                                     = 1
printf("%d", 3)                                                     = 1
printf("%d", 3)                                                     = 1
printf("%d", 3)                                                     = 1
putchar(10, 0x8211f2dff, 51, 0xc4659adfa372773f, 0x822380618Data: 33333333
)       = 10
printf("Data: ")                                                    = 6
printf("%d", 4)                                                     = 1
printf("%d", 4)                                                     = 1
printf("%d", 4)                                                     = 1
printf("%d", 4)                                                     = 1
printf("%d", 4)                                                     = 1
printf("%d", 4)                                                     = 1
printf("%d", 4)                                                     = 1
printf("%d", 4)                                                     = 1
putchar(10, 0x8211f2dff, 52, 0xc4659adfa372773f, 0x822380618Data: 44444444
)       = 10
printf("Data: ")                                                    = 6
printf("%d", 5)                                                     = 1
printf("%d", 5)                                                     = 1
printf("%d", 5)                                                     = 1
printf("%d", 5)                                                     = 1
printf("%d", 5)                                                     = 1
printf("%d", 5)                                                     = 1
printf("%d", 5)                                                     = 1
printf("%d", 5)                                                     = 1
putchar(10, 0x8211f2dff, 53, 0xc4659adfa372773f, 0x822380618Data: 55555555
)       = 10
free(0x3d0d69c08008)                                                = <void>
+++ exited (status 0) +++
admin@FreeBSD:~/ASPZ/practice4 $
```

# Завдання 5

Що станеться, якщо realloc(3) не зможе виділити пам’ять?

realloc(3) повертає NULL, залишаючи старий вказівник незмінним.

```shell
admin@FreeBSD:~/ASPZ/practice4 $ gcc 5.c -o 5
admin@FreeBSD:~/ASPZ/practice4 $ ./5
Memory reallocation failed
admin@FreeBSD:~/ASPZ/practice4 $
```

# Завдання 6

Що станеться, якщо realloc(3) викликати з NULL або size == 0?

realloc(NULL, size) еквівалентно malloc(size).

realloc(ptr, 0) працює.

```shell
admin@FreeBSD:~/ASPZ/practice4 $ gcc 6.c -o 6
admin@FreeBSD:~/ASPZ/practice4 $ ./6
realloc(NULL, 1024) = 0x1933cb809000
realloc(ptr, 0) = 0x1933cb808008
admin@FreeBSD:~/ASPZ/practice4 $
```

# Завдання 7

Переписано код, використовуючи reallocarray(3)

Досліджено за допомогою ltrace

```shell
admin@FreeBSD:~/ASPZ/practice4 $ gcc 7_1.c -o 7_1
admin@FreeBSD:~/ASPZ/practice4 $ ./7_1
Memory allocated for 1000 elements
Memory reallocated to 500 elements
admin@FreeBSD:~/ASPZ/practice4 $ ltrace ./7_1
Couldn't determine base address of [vdso]
Couldn't load ELF object [vdso]: No such file or directory
__libc_start1(1, 0x820773448, 0x820773458, 0x210a663fccc0, 0x400662 <unfinished ...>
calloc(1000, 4)                                                     = 0x8475c009000
printf("Memory allocated for %zu element"..., 1000Memory allocated for 1000 elements
)                 = 35
realloc(0x8475c009000, 2000)                                        = 0x8475c013000
printf("Memory reallocated to %zu elemen"..., 500Memory reallocated to 500 elements
)                  = 35
free(0x8475c013000)                                                 = <void>
+++ exited (status 0) +++
admin@FreeBSD:~/ASPZ/practice4 $ gcc 7_2.c -o 7_2
admin@FreeBSD:~/ASPZ/practice4 $ ./7_2
Memory allocated for 1000 elements
Memory reallocated to 500 elements
admin@FreeBSD:~/ASPZ/practice4 $ ltrace ./7_2
Couldn't determine base address of [vdso]
Couldn't load ELF object [vdso]: No such file or directory
__libc_start1(1, 0x820653208, 0x820653218, 0x320bbd6bdcc0, 0x4006c2 <unfinished ...>
calloc(1000, 4)                                                     = 0x3732a2609000
printf("Memory allocated for %zu element"..., 1000Memory allocated for 1000 elements
)                 = 35
reallocarray(0x3732a2609000, 500, 4, 500, 0x8230f6618)              = 0x3732a2613000
printf("Memory reallocated to %zu elemen"..., 500Memory reallocated to 500 elements
)                  = 35
free(0x3732a2613000)                                                = <void>
+++ exited (status 0) +++
admin@FreeBSD:~/ASPZ/practice4 $
```

# Завдання по варіанту 19

Написано код, що примусово викликає out-of-memory killer у Linux.

```shell
admin@FreeBSD:~/ASPZ/practice4 $ gcc 19.c -o 19
admin@FreeBSD:~/ASPZ/practice4 $ ./19
Allocated: 1024 MB
Allocated: 2048 MB
Allocated: 3072 MB
Allocated: 4096 MB
Allocated: 5120 MB
Allocated: 6144 MB
Killed
admin@FreeBSD:~/ASPZ/practice4 $
```