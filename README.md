# **Электронная таблица**

Проект консольной электронной таблицы, в котором частично реализован функционал Excel.

## **Возможности**

Проект позволяет производить вычисления и запись данных по принципу электронных таблиц с управлением из консоли.
Реализованы следующие возможности:
- Поддержка текстового и числового типов данных
- Все арифметические операции
- Оповещение о распространненых ошибках (деление на 0, некорректная операция и т.д.)
- Ссылки на другие ячейки
- Вывод результатов в консоль или запись в файл

## **Использование**

1. Использовать необходимые инструкции в `main.cpp`
```cpp
// создание экземпляра класса
auto sheet = CreateSheet();
// заполнение ячеек значениями
sheet->SetCell("A1"_pos, "2");
sheet->SetCell("B1"_pos, "2");
sheet->SetCell("С1"_pos, "=A1+B1");
sheet->SetCell("A2"_pos, "hello");
// вывод значений и формул как текстовый тип данных
std::ostringstream texts;
sheet->PrintTexts(texts);
std::cout << texts.str() << std::endl;
// вывод результатов рассчитанных формул и других значений
std::ostringstream values;
sheet->PrintValues(values);
std::cout << values.str() << std::endl;
// удалить значение из выбранной ячейки
sheet->ClearCell("B2"_pos);
```
2. Собрать проект с использовавнием CMake и выбранного компилятора
3. Запустить исполняемый файл (spreadsheet.exe)

## **Зависимости**

1. [С++17](https://en.cppreference.com/w/cpp/17)
2. [GCC(MinGW-w64)](https://www.mingw-w64.org/) 11+ version requires
3. [CMake](https://cmake.org) 3.8 version requires
4. [Java JDK](https://www.oracle.com/java/technologies/downloads/)
5. [ANTLR4](https://www.antlr.org/)
