# Wargaming test task

## Задание 1

<details>
  <summary>Условие задания</summary>

На языке Python или С/С++, написать алгоритм (функцию) определения четности целого числа, который будет аналогичен нижеприведенному по функциональности, но отличен по своей сути.

Объяснить плюсы и минусы обеих реализаций.

Python example:
```python
def isEven(value):
   return value % 2 == 0
```
C/C++ example:
```cpp
bool isEven(int value)
{
   return value % 2 == 0;
}
```

</details>

```cpp
bool isEven(int value) { return (value & 1) == 0; }
```
В двоичной системе счисления у четных чисел младший бит всегда равен 0, у нечетных - 1. Имея в виду данный факт и использовав побитовый оператор И, получим следующее:
(6)0110 & (1)0001 = 0000 - результатом данного выражения для четных чисел всегда будет 0, для нечетных 1 - (7)0111 & (1)0001 = 0001.
Отличие по скорости выполения будут заметны на компиляторах Clang и MSVC с выключенной оптимизацей, на GCC оба метода работают одинаково.


## Задание 2

<details>
  <summary>Условие задания</summary>

На языках Python(2.7) и/или С++, написать минимум по 2 класса реализовывающих циклический буфер FIFO.

Объяснить плюсы и минусы каждой реализации.

</details>

Циклический буфер: 
- через индексы - [ссылка](https://github.com/SPQR1608/wg_test_task/blob/main/circular_buffer_thread_safe.h);
- помощью связных списков - [ссылка](https://github.com/SPQR1608/wg_test_task/blob/main/circular_buffer_list.h);

В реализации циклического буфера через индексы можно выделить следующие плюсы - это поддержка многопоточности 
и отсутствие Race condition, т.к. потоки сихнронизированы, запись и чтение выполняется в правильном порядке.
Минусом является отсутствие возможности увеличение размера буфера в режиме выполнения программы. 

Реализация с помощью связных списков не поддерживает многопоточность, занимает больше места в памяти из-за указателя на следующий элемент в списке,
но при этом не требует операции для инкремента индексов (head_->next выполнится быстрее, чем (head_ + 1) % max_size_)

Также стоит отметить то, что в обеих реализациях, при достижении конца буфера, данные продолжают записываться, переписывая данные из начала буфера.
Это является как плюсом, так и минусом. Непрерывная запись может переписать те данные, которые еще не прочитаны, в итоге они потеряются.


## Задание 3

<details>
  <summary>Условие задания</summary>

На языке Python или С/С++, написать функцию, которая быстрее всего (по процессорным тикам) отсортирует данный ей массив чисел.

Массив может быть любого размера со случайным порядком чисел (в том числе и отсортированным).

Объяснить почему вы считаете, что функция соответствует заданным критериям.

</details>

Код - [ссылка](https://github.com/SPQR1608/wg_test_task/blob/main/sort.h);

Была выбрана и реализована сортировка улучшенная `Quicksort` (Выбор медианы из трёх элементов). `Heapsort` и обычная `Quicksort` добавлены для сравнения. 
У обычной `Quicksort` в худших случаях время работы может быть О(n^2), в отличии от `Heapsort` или Merge sort, где сложность для любых случаев O(n*log n),
но в обычных условиях тесты показывают, что даже обычная `Quicksort` быстрее. Улучшенный метод `Quicksort` снижает вероятность возникновения худшего случая 
и работает быстрее.
Например, в данной реализации время сортировки массива из 1 000 000 перемешанных элементов типа int
у улучшенной `Quicksort` заняло `0.206` секунды, обычная `Quicksort` - `0.220` секунды, а у `Heapsort` - `0.352` секунды.


## Результат выполнения

<details>
  <summary>Log</summary>
  
      === CPP Circular buffer check ===
    Size: 0, Capacity: 10
    Put 1, val: 1
    Popped: 1
    Empty: 1
    Adding 9 values
    Full: 0
    Adding 10 values
    Full: 1
    Reading back values: 0 1 2 3 4 5 6 7 8 9
    Adding 15 values
    Full: 1
    Reading back values: 5 6 7 8 9 10 11 12 13 14
    Empty: 1
    Full: 0

     === CPP Circular buffer thread check ===
    1
    5
    0
    7
    9
    11

     === CPP Circular buffer list check ===
    Size: 0, Capacity: 15
    Put 1, val: 1
    Popped: 1
    Empty: 1
    Adding 14 values
    Full: 0
    Adding 15 values
    Full: 1
    Reading back values: 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
    Adding 20 values
    Full: 0
    Reading back values: 14 15 16 17 18 19 5 6 7 8 9 10 11 12 13 14 15 16 17 18
    Empty: 1
    Full: 0
    -------------------------------------------------
    ---------- quick sort ---------------------------
    -------------------------------------------------
    0 seconds
    221 miliseconds
    221105 microseconds
    221105700 nanoseconds

    -------------------------------------------------
    ---------- quick sort median ---------------------------
    -------------------------------------------------
    0 seconds
    219 miliseconds
    219095 microseconds
    219095900 nanoseconds

    -------------------------------------------------
    ---------- heap sort ---------------------------
    -------------------------------------------------
    0 seconds
    399 miliseconds
    399897 microseconds
    399897800 nanoseconds
</details>
