# Matrix Multiplication
Автор: Линёв Роман
Курс: Параллельное программирование 

Лабораторная работа: перемножение двух квадратных матриц на C++.

## Возможности
- чтение двух квадратных матриц из файлов;
- последовательное умножение матриц;
- измерение времени выполнения;
- сохранение результата в файл;
- автоматическая проверка результата через Python + NumPy.

## Структура

```text
MatrixMultiplication/
├── CMakeLists.txt
├── README.md
└── lab1/
    ├── cpp/
    │   ├── main.cpp
    │   ├── matrix.cpp
    │   └── matrix.h
    ├── data/
    │   ├── matrix_a.txt
    │   ├── matrix_b.txt
    │   └── result.txt
    └── python/
        └── verify.py
```

## Формат входных файлов

Первая строка содержит размер `N`, далее идут `N*N` элементов матрицы.

Пример:

```text
3
1 2 3
4 5 6
7 8 9
```

## Сборка

```bash
cmake -S . -B build
cmake --build build
```

## Запуск

Из корня проекта:

```bash
./build/matrix_multiplication lab1/data/matrix_a.txt lab1/data/matrix_b.txt lab1/data/result.txt
```

Windows:

```powershell
.\build\Debug\matrix_multiplication.exe lab1\data\matrix_a.txt lab1\data\matrix_b.txt lab1\data\result.txt
```

## Проверка

Установить NumPy:

```bash
pip install numpy
```

Запустить:

```bash
python lab1/python/verify.py
```

Скрипт независимо вычисляет `A @ B` и сравнивает его с результатом программы на C++.

## Измеряемые характеристики

Программа выводит:
- размер матрицы;
- количество элементов;
- количество операций умножения и сложения;
- время выполнения.
