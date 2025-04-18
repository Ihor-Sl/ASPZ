# Практична робота №6

## Звіт по завданню

## Завдання по варіанту 19

Test Case #9: Use-after-return. Спробуйте запустити ASan з опцією detect_stack_use_after_return=1.

## Опис рішення

Запущено ASan з опцією detect_stack_use_after_return=1.

ASan видає помилку:

```
ERROR: AddressSanitizer: stack-use-after-return on address ...
```

Та показує її трасування

```
READ of size 26 at 0x000801644020 thread T0
...
    #3 0x2ed65c in main /home/admin/ASPZ/practice6/mem_issues.c:16:5
...
Address 0x000801644020 is located in stack of thread T0 at offset 32 in frame
    #0 0x2ed67f in uar /home/admin/ASPZ/practice6/mem_issues.c:4
```

AddressSanitizer з опцією detect_stack_use_after_return=1 успішно виявив помилку — спробу доступу до памʼяті, яка більше не є дійсною, бо була частиною стеку функції, що вже завершилася.

## Запуск програми

```shell
admin@FreeBSD:~/ASPZ/practice6 $ gmake mem_issues_dbg_asan
clang -g -ggdb -gdwarf-4 -O0 -Wall -Wextra -DDEBUG -fsanitize=address -c mem_issues.c -o mem_issues_dbg_asan.o
mem_issues.c:10:12: warning: address of stack memory associated with local variable 'name' returned [-Wreturn-stack-address]
   10 |     return name;
      |            ^~~~
1 warning generated.
clang -g -ggdb -gdwarf-4 -O0 -Wall -Wextra -DDEBUG -fsanitize=address -o mem_issues_dbg_asan mem_issues_dbg_asan.o
admin@FreeBSD:~/ASPZ/practice6 $ ASAN_OPTIONS=detect_stack_use_after_return=1 ./mem_issues_dbg_asan
=================================================================
==3265==ERROR: AddressSanitizer: stack-use-after-return on address 0x000801644020 at pc 0x00000026bf4e bp 0x7fffffffe320 sp 0x7fffffffdab0
READ of size 26 at 0x000801644020 thread T0
    #0 0x26bf4d in printf_common(void*, char const*, __va_list_tag*) /usr/src/contrib/llvm-project/compiler-rt/lib/sanitizer_common/sanitizer_common_interceptors_format.inc:563:9
    #1 0x26d07c in vprintf /usr/src/contrib/llvm-project/compiler-rt/lib/sanitizer_common/sanitizer_common_interceptors.inc:1644:1
    #2 0x26d07c in printf /usr/src/contrib/llvm-project/compiler-rt/lib/sanitizer_common/sanitizer_common_interceptors.inc:1702:1
    #3 0x2ed65c in main /home/admin/ASPZ/practice6/mem_issues.c:16:5
    #4 0x800456c39 in __libc_start1 /usr/src/lib/libc/csu/libc_start1.c:157:7
    #5 0x249cbf in _start /usr/src/lib/csu/amd64/crt1_s.S:83

Address 0x000801644020 is located in stack of thread T0 at offset 32 in frame
    #0 0x2ed67f in uar /home/admin/ASPZ/practice6/mem_issues.c:4

  This frame has 1 object(s):
    [32, 64) 'name' (line 5) <== Memory access at offset 32 is inside this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism, swapcontext or vfork
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-use-after-return /home/admin/ASPZ/practice6/mem_issues.c:16:5 in main
Shadow bytes around the buggy address:
  0x000801643d80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x000801643e00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x000801643e80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x000801643f00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x000801643f80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x000801644000: f5 f5 f5 f5[f5]f5 f5 f5 f5 f5 f5 f5 f5 f5 f5 f5
  0x000801644080: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x000801644100: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x000801644180: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x000801644200: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x000801644280: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==3265==ABORTING
admin@FreeBSD:~/ASPZ/practice6 $
```