00 LOAD 99 ; (Ввод А)
01 JUMP 12 ; (Ввод В)
02 HALT 00 ; (Загрузка А в аккумулятор)
03 STORE 96 ; (Отнять В)
04 HALT 00 ; (Переход на 07, если отрицательное)
05 WRITE 00 ; (Вывод А)
06 HALT 00 ; (Останов)
07 WRITE 10 ; (Вывод В)
08 HALT 00 ; (Останов)
09 = +0000 ; (Переменная А)
10 = +9999 ; (Переменная В)