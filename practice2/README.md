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

