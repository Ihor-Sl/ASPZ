# Практична робота №10-11

## Звіт по завданням

## Завдання 1

Створити просту оболонку, яка запускає команди користувача.

### Реалізація

```shell
admin@FreeBSD:~/ASPZ/practice10-11 $ gcc -Wall 1.c -o 1
admin@FreeBSD:~/ASPZ/practice10-11 $ ./1
dumbsh> ls
1               1.c             19.c            2.c             3.c             README.md
dumbsh> whoami
admin
dumbsh> exit
admin@FreeBSD:~/ASPZ/practice10-11 $
```

## Завдання 2

API wait — деталі

### Реалізація

```shell
admin@FreeBSD:~/ASPZ/practice10-11 $ ./2
Child process, PID: 3718
Child exited with code 42
admin@FreeBSD:~/ASPZ/practice10-11 $
```

## Завдання 3

Приклад створення кількох дітей:


### Реалізація

```shell
admin@FreeBSD:~/ASPZ/practice10-11 $ gcc -Wall 3.c -o 3
admin@FreeBSD:~/ASPZ/practice10-11 $ ./3
Child 0
Child 1
Child 2
admin@FreeBSD:~/ASPZ/practice10-11 $
```

## Завдання за варіантом 19

Створіть цикл, у якому викликається fork(), поки це можливо. Визначте, скільки процесів вдалося створити до помилки.

### Реалізація

```shell
admin@FreeBSD:~/ASPZ/practice10-11 $ gcc -Wall 19.c -o 19
admin@FreeBSD:~/ASPZ/practice10-11 $ ./19
Кількість успішно створених процесів: 12120
admin@FreeBSD:~/ASPZ/practice10-11 $
```