# Практична робота №8

## Звіт по завданням

## Завдання 1

Чи може виклик count = write(fd, buffer, nbytes); повернути в змінній count значення, відмінне від nbytes? Якщо так, то чому? Наведіть робочий приклад програми, яка демонструє вашу відповідь.

### Реалізація

Програма демонструє частковий запис у pipe: через обмежений буфер і неблокуючий режим write() повертає 65536 замість 10000000.

```shell
admin@FreeBSD:~/ASPZ/practice8 $ gcc -Wall 1.c -o 1
admin@FreeBSD:~/ASPZ/practice8 $ ./1
Partial write occurred! Requested: 10000000, Written: 65536
admin@FreeBSD:~/ASPZ/practice8 $
```

## Завдання 2

Є файл, дескриптор якого — fd. Файл містить таку послідовність байтів: 4, 5, 2, 2, 3, 3, 7, 9, 1, 5. У програмі виконується наступна послідовність системних викликів:

lseek(fd, 3, SEEK_SET);

read(fd, &buffer, 4);

де виклик lseek переміщує покажчик на третій байт файлу. Що буде містити буфер після завершення виклику read? Наведіть робочий приклад програми, яка демонструє вашу відповідь.

### Реалізація

Початковий вміст файлу:
[4, 5, 2, 2, 3, 3, 7, 9, 1, 5]
(індексація з 0)

lseek(fd, 3, SEEK_SET) переміщує покажчик на 3-й байт (значення 2).

read(fd, buffer, 4) читає 4 байти, починаючи з поточної позиції:

3-й байт: 2

4-й байт: 3

5-й байт: 3

6-й байт: 7

Отже, buffer = {2, 3, 3, 7}.

```shell
admin@FreeBSD:~/ASPZ/practice8 $ gcc -Wall 2.c -o 2
admin@FreeBSD:~/ASPZ/practice8 $ ./2
Buffer: 2 3 3 7 
admin@FreeBSD:~/ASPZ/practice8 $
```

## Завдання 3

Бібліотечна функція qsort призначена для сортування даних будь-якого типу. Для її роботи необхідно підготувати функцію порівняння, яка викликається з qsort кожного разу, коли потрібно порівняти два значення.

Оскільки значення можуть мати будь-який тип, у функцію порівняння передаються два вказівники типу void* на елементи, що порівнюються.

Напишіть програму, яка досліджує, які вхідні дані є найгіршими для алгоритму швидкого сортування. Спробуйте знайти кілька масивів даних, які змушують qsort працювати якнайповільніше. Автоматизуйте процес експериментування так, щоб підбір і аналіз вхідних даних виконувалися самостійно.

Придумайте і реалізуйте набір тестів для перевірки правильності функції qsort.

### Реалізація

Аналіз результатів:

Reverse sorted (зворотно відсортовані дані): ~0.1-0.12 секунди

All equal (всі елементи однакові): ~0.04 секунди

Already sorted (відсортовані дані): ~0.08-0.1 секунди

Random data (випадкові дані): ~1.26-1.29 секунди

```shell
admin@FreeBSD:~/ASPZ/practice8 $ gcc -Wall 3.c -o 3
admin@FreeBSD:~/ASPZ/practice8 $ ./3
Reverse sorted       | Time: 0.11719  sec | PASS
Reverse sorted       | Time: 0.10156  sec | PASS
Reverse sorted       | Time: 0.10938  sec | PASS
All equal            | Time: 0.03906  sec | PASS
All equal            | Time: 0.03906  sec | PASS
All equal            | Time: 0.03906  sec | PASS
Already sorted       | Time: 0.10156  sec | PASS
Already sorted       | Time: 0.09375  sec | PASS
Already sorted       | Time: 0.07812  sec | PASS
Random data          | Time: 1.26562  sec | PASS
Random data          | Time: 1.28906  sec | PASS
Random data          | Time: 1.27344  sec | PASS
admin@FreeBSD:~/ASPZ/practice8 $
```

## Завдання 4

Виконайте наступну програму на мові програмування С:
```c
int main() {
  int pid;
  pid = fork();
  printf("%d\n", pid);
}
```
Завершіть цю програму. Припускаючи, що виклик fork() був успішним, яким може бути результат виконання цієї програми?

### Реалізація

Програма виведе два числа:

Спочатку батьківський процес виведе PID дочірнього процесу (3677).

Потім дочірній процес виведе 0.

```shell
admin@FreeBSD:~/ASPZ/practice8 $ gcc -Wall 4.c -o 4
admin@FreeBSD:~/ASPZ/practice8 $ ./4
3677
0
admin@FreeBSD:~/ASPZ/practice8 $
```

## Завдання по варіанту 19

Дослідіть, як працює write() у ситуації нестачі дискового простору, і зафіксуйте поведінку змінної errno.

### Опис рішення

Поведінка write():

Спочатку записує дані, доки є вільне місце.

Коли місце закінчується, повертає -1.

Значення errno:

ENOSPC (28) - "No space left on device" (немає вільного місця).

### Запуск програми

```shell
admin@FreeBSD:~/ASPZ/practice8 $ gcc -Wall 19.c -o 19
admin@FreeBSD:~/ASPZ/practice8 $ ./19

/: write failed, filesystem is full
write: No space left on device
errno: 28 (No space left on device)
admin@FreeBSD:~/ASPZ/practice8 $
```