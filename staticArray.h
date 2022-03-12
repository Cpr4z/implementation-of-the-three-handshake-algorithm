#pragma once
#include "common.h"
//Самопальный вектор
template <class T>
class StaticArray {
public:
    StaticArray(int size = 0)//констурктор, который инициализирует самопальный вектор
    {
        count = size;
        if (size > 0) {
            for (int i = 0; i < size; i++)
                array[i] = T();
        }
    }
    void add(T newval) //добавление в вектор нового элемента
    {
        if (count < SIZE) {
            array[count++] = newval;
        }
    }
    void del(int index)//удаление элемента из вектора
    {
        if (index < 0 || index >= count)//если index меньше нуля, либо больше или равен количеству элементов в векторе
            return;
        count--;
        for (int i = index; i < count; i++) //сдвигаем все эелменты вектора на 1 влево
        {
            array[i] = array[i + 1];
        }
    }
    T& operator [](int index) //перегрузка оператора []
    {
        if (index < 0 || index >= count)
            throw 0;
        return array[index];
    }

    int find(const T& val)//метод нахождения элемента и возвращении его индекса
    {
        for (int i = 0; i < count; i++)
            if (array[i] == val)
                return i;
        return -1;
    }

    int size()//метод вывода размера вектора
    {
        return count;
    }

private:
    T array[SIZE];
    int count;
};
