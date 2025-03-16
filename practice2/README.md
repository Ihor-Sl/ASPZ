# Завдання 1

## Визначення моменту, коли time_t закінчиться.

Для 32 бітної архітектури: Tue Jan 19 05:14:07 2038

Для 64 бітної архітектури: 9223372036854775807, ctime не може перевести

## Вивід консолі

```shell
admin@FreeBSD:~/ASPZ/practice2 $ gcc -m32 1.c -o 1
admin@FreeBSD:~/ASPZ/practice2 $ ./1
Maximum time: 2147483647
ctime max: Tue Jan 19 05:14:07 2038

ctime max+1: Fri Dec 13 22:47:56 1901

admin@FreeBSD:~/ASPZ/practice2 $ size 1
   text    data     bss     dec     hex filename
   1160     280       8    1448     5a8 1
admin@FreeBSD:~/ASPZ/practice2 $ gcc 1.c -o 1
admin@FreeBSD:~/ASPZ/practice2 $ ./1
Maximum time: 9223372036854775807
ctime max: (null)
ctime max+1: (null)
admin@FreeBSD:~/ASPZ/practice2 $ size 1
   text    data     bss     dec     hex filename
   1298     560      16    1874     752 1
admin@FreeBSD:~/ASPZ/practice2 $
```

# Завдання 2

## Результати аналізу розмірів виконуваних файлів та сегментів

У цій роботі було проаналізовано, як різні зміни у коді та параметри компіляції впливають на розмір виконуваного файлу та розподіл пам'яті між сегментами.

## Вивід консолі

```shell
admin@FreeBSD:~/ASPZ/practice2 $ gcc 2_1.c -o 2_1
admin@FreeBSD:~/ASPZ/practice2 $ ls -l 2_1
-rwxr-xr-x  1 admin admin 8200 Mar 15 22:59 2_1
admin@FreeBSD:~/ASPZ/practice2 $ size 2_1
   text    data     bss     dec     hex filename
   1079     552      16    1647     66f 2_1
admin@FreeBSD:~/ASPZ/practice2 $ gcc 2_2.c -o 2_2
admin@FreeBSD:~/ASPZ/practice2 $ ls -l 2_2
-rwxr-xr-x  1 admin admin 8232 Mar 15 23:00 2_2
admin@FreeBSD:~/ASPZ/practice2 $ size 2_2
   text    data     bss     dec     hex filename
   1079     552    4032    5663    161f 2_2
admin@FreeBSD:~/ASPZ/practice2 $ gcc 2_3.c -o 2_3
admin@FreeBSD:~/ASPZ/practice2 $ ls -l 2_3
-rwxr-xr-x  1 admin admin 12272 Mar 15 23:00 2_3
admin@FreeBSD:~/ASPZ/practice2 $ size 2_3
   text    data     bss     dec     hex filename
   1079    4568      16    5663    161f 2_3
admin@FreeBSD:~/ASPZ/practice2 $ gcc 2_4.c -o 2_4
admin@FreeBSD:~/ASPZ/practice2 $ ls -l 2_4
-rwxr-xr-x  1 admin admin 8328 Mar 15 23:01 2_4
admin@FreeBSD:~/ASPZ/practice2 $ size 2_4
   text    data     bss     dec     hex filename
   1175     552      16    1743     6cf 2_4
admin@FreeBSD:~/ASPZ/practice2 $ gcc 2_4.c -g -o 2_4
admin@FreeBSD:~/ASPZ/practice2 $ ls -l 2_4
-rwxr-xr-x  1 admin admin 9128 Mar 15 23:01 2_4
admin@FreeBSD:~/ASPZ/practice2 $ size 2_4
   text    data     bss     dec     hex filename
   1175     552      16    1743     6cf 2_4
admin@FreeBSD:~/ASPZ/practice2 $ gcc 2_4.c -O3 -o 2_4
admin@FreeBSD:~/ASPZ/practice2 $ ls -l 2_4
-rwxr-xr-x  1 admin admin 8264 Mar 15 23:02 2_4
admin@FreeBSD:~/ASPZ/practice2 $ size 2_4
   text    data     bss     dec     hex filename
   1118     552      16    1686     696 2_4
admin@FreeBSD:~/ASPZ/practice2 $
```

## Таблиця результатів

| Файл | Розмір (байти) | text | data | bss | dec | hex |
|------|----------------|------|------|-----|-----|-----|
| 2_1  | 8200           | 1079 | 552  | 16  | 1647| 66f |
| 2_2  | 8232           | 1079 | 552  | 4032| 5663| 161f|
| 2_3  | 12272          | 1079 | 4568 | 16  | 5663| 161f|
| 2_4  | 8328           | 1175 | 552  | 16  | 1743| 6cf |
| 2_4 (з -g) | 9128    | 1175 | 552  | 16  | 1743| 6cf |
| 2_4 (з -O3)| 8264    | 1118 | 552  | 16  | 1686| 696 |

## Пояснення

### 1 програма

Це базова програма без додаткових даних, тому розмір text відповідає коду програми, а data і bss містять мінімальні дані.

### 2 програма

Масив із 1000 int додав 4000 байт до сегмента bss, оскільки він не ініціалізований. Сегмент text залишився незмінним, оскільки код програми не змінювався.

### 3 програма

Ініціалізація масиву перемістила його з сегмента bss у сегмент data. Це призвело до збільшення розміру файлу, оскільки ініціалізовані дані зберігаються у виконуваному файлі.

### 4 програма

Локальні масиви у функціях не впливають на розмір сегментів data або bss, оскільки вони виділяються під час виконання програми (у стеку). Однак розмір сегмента text збільшився через додавання коду для роботи з цими масивами.

### Налагодження

Збільшення розміру файлу відбулося через додавання налагоджувальної інформації.

### Оптимізація

Оптимізація зменшила розмір сегмента text, оскільки компілятор оптимізував код.

# Завдання 3

## Дослідження адрес стеку, кучі та сегментів

## Вивід консолі

```shell
admin@FreeBSD:~/ASPZ/practice2 $ gcc 3_1.c -o 3_1
admin@FreeBSD:~/ASPZ/practice2 $ ./3_1
The stack top is near 0x820dd64fc
admin@FreeBSD:~/ASPZ/practice2 $ gcc 3_2.c -o 3_2
admin@FreeBSD:~/ASPZ/practice2 $ ./3_2
Stack top is near: 0x8212d6af4
Heap var 1 (malloc) is near: 0x2d1b0ba09000
Heap var 2 (malloc) is near: 0x2d1b0ba091c0
Data segment (global_var) is near: 0x401b60
Data segment (static_var) is near: 0x401b64
Text segment (main function) is near: 0x40065d
Recursion depth: 1, stack top near 0x8212d5b40
Recursion depth: 2, stack top near 0x8212d4b80
Recursion depth: 3, stack top near 0x8212d3bc0
Recursion depth: 4, stack top near 0x8212d2c00
Recursion depth: 5, stack top near 0x8212d1c40
admin@FreeBSD:~/ASPZ/practice2 $
```

Купа росте вгору

Стек росте вниз

# Завдання 4

## Вивід програми

```shell
admin@FreeBSD:~/ASPZ/practice2 $ gcc 4.c -o 4
admin@FreeBSD:~/ASPZ/practice2 $ ./4
In function                 main; &localvar = 0x82132d77c
In function                  foo; &localvar = 0x82132d74c
In function                  bar; &localvar = 0x82132d72c
In function    bar_is_now_closed; &localvar = 0x82132d70c

 Now blocking on pause()...
```

## Вивід gdb

```shell
admin@FreeBSD:~/ASPZ/practice2 $ pgrep 4
1955
admin@FreeBSD:~/ASPZ/practice2 $ gdb --quiet -p 1955
Attaching to process 1955
Reading symbols from /home/admin/ASPZ/practice2/4...
Reading symbols from /lib/libc.so.7...
Reading symbols from /usr/lib/debug//lib/libc.so.7.debug...
Reading symbols from /libexec/ld-elf.so.1...
Reading symbols from /usr/lib/debug//libexec/ld-elf.so.1.debug...
_sigsuspend () at _sigsuspend.S:4

warning: 4      _sigsuspend.S: No such file or directory
(gdb) bt
#0  _sigsuspend () at _sigsuspend.S:4
#1  0x0000000824403c35 in __pause () at /usr/src/lib/libc/gen/pause.c:51
#2  0x000000000040068b in bar_is_now_closed ()
#3  0x00000000004006bd in bar ()
#4  0x00000000004006ef in foo ()
#5  0x0000000000400728 in main ()
(gdb) q
A debugging session is active.

        Inferior 1 [process 1955] will be detached.

Quit anyway? (y or n) y
Detaching from program: /home/admin/ASPZ/practice2/4, process 1955
[Inferior 1 (process 1955) detached]
admin@FreeBSD:~/ASPZ/practice2 $
```

# Завдання 5

Ні, не можна. Лічильник команд (IP) потрібен для збереження адреси наступної інструкції, яку потрібно виконати. Хоча стек використовується для збереження контексту при виклику процедур, без лічильника команд неможливо точно визначити, яку інструкцію виконувати наступною, оскільки стек зберігає лише адресу повернення, а не послідовність команд.

# Завдання по варіанту 19

Написано програму для перевірки залежностей ELF-файлів.

## Вивід програми

```shell
admin@FreeBSD:~/ASPZ/practice2 $ gcc variant_19.c -o variant_19
admin@FreeBSD:~/ASPZ/practice2 $ ./variant_19 /bin/ls

Dynamic section at offset 0x7840 contains 27 entries:
  Tag        Type                         Name/Value
 0x0000000000000001 (NEEDED)             Shared library: [libutil.so.9]
 0x0000000000000001 (NEEDED)             Shared library: [libtinfow.so.9]
 0x0000000000000001 (NEEDED)             Shared library: [libc.so.7]
 0x000000006ffffffb (FLAGS_1)            Flags: PIE
 0x0000000000000015 (DEBUG)              0x0
 0x0000000000000007 (RELA)               0x1330
 0x0000000000000008 (RELASZ)             384 (bytes)
 0x0000000000000009 (RELAENT)            24 (bytes)
 0x000000006ffffff9 (RELACOUNT)          5
 0x0000000000000017 (JMPREL)             0x14b0
 0x0000000000000002 (PLTRELSZ)           1824 (bytes)
 0x0000000000000003 (PLTGOT)             0xaa98
 0x0000000000000014 (PLTREL)             RELA
 0x0000000000000006 (SYMTAB)             0x308
 0x000000000000000b (SYMENT)             24 (bytes)
 0x0000000000000005 (STRTAB)             0xf94
 0x000000000000000a (STRSZ)              922 (bytes)
 0x000000006ffffef5 (GNU_HASH)           0xc90
 0x0000000000000004 (HASH)               0xcbc
 0x0000000000000019 (INIT_ARRAY)         0x97f8
 0x000000000000001b (INIT_ARRAYSZ)       8 (bytes)
 0x000000000000000c (INIT)               0x82dc
 0x000000000000000d (FINI)               0x82e8
 0x000000006ffffff0 (VERSYM)             0xb78
 0x000000006ffffffe (VERNEED)            0xc2c
 0x000000006fffffff (VERNEEDNUM)         1
 0x0000000000000000 (NULL)               0x0
admin@FreeBSD:~/ASPZ/practice2 $
```
