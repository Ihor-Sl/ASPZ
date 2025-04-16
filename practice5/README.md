# Практична робота №5

## Звіт по завданню

## Завдання по варіанту 19

Реалізуйте сценарій, де пам’ять не звільняється лише в разі виклику програми певним користувачем або групою.

## Опис рішення

Написано програму що демонструє приклад умовного витоку памʼяті в залежності від користувача та групи.

Використані бібліотеки:

 - `<unistd.h>` — для отримання UID користувача (getuid).

 - `<pwd.h>` — для отримання структури passwd, яка містить інформацію про користувача (getpwuid).

 - `<grp.h>` — для роботи з групами (getgrgid, getgroups).

## Запуск програми

```shell
admin@FreeBSD:~/ASPZ/practice5 $ gcc 19.c -o 19
admin@FreeBSD:~/ASPZ/practice5 $ ./19
Running as user: admin (UID: 1001)
admin
admin@FreeBSD:~/ASPZ/practice5 $ gcc 19.c -o 19
admin@FreeBSD:~/ASPZ/practice5 $ groups
admin wheel video
admin@FreeBSD:~/ASPZ/practice5 $ ./19 
Usage: ./19 <target_user> <target_group>
admin@FreeBSD:~/ASPZ/practice5 $ ./19 admin somegroup
Running as user: admin (UID: 1001)
Memory NOT freed for user admin or group somegroup
admin@FreeBSD:~/ASPZ/practice5 $ ./19 someuser wheel
Running as user: admin (UID: 1001)
Memory NOT freed for user someuser or group wheel
admin@FreeBSD:~/ASPZ/practice5 $ ./19 someuser somegroup
Running as user: admin (UID: 1001)
Memory freed (user/group do not match)
admin@FreeBSD:~/ASPZ/practice5 $
```