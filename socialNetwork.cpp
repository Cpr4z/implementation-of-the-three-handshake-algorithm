#include "socialnetwork.h"
#include <memory>
#include <iostream>

SocialNetwork::Human::Human() : id(-1)//изначально присваиваем id -1
{
}

SocialNetwork::Human::Human(const Name _name, int _id) : id(_id) //инициализируем пользователя с помощбю имени и id
{
    strcpy_s(name, _name);
}
SocialNetwork::Human& SocialNetwork::Human::operator=(const Human& other) //оператор присваивания 
{
    strcpy_s(name, other.name);
    id = other.id;
    return *this;
}
SocialNetwork::Human::Human(const Human& other)//констуктор копиования 
{
    strcpy_s(name, other.name);
    id = other.id;
}

bool SocialNetwork::Human::operator==(const Human& other)//функция, которая  проверяет, является ли текущий человек,заданным
{
    return other.id == this->id;
}

SocialNetwork::SocialNetwork()//конструктор, который иницмализирует матрицу дружбы
{
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            friend_matrix[i][j] = 0;

    for (int i = 0; i < SIZE; i++) 
    {
        busyids.add(false);
    }
}
void SocialNetwork::addnewMan(const Name name)// добалвяем нового человека
{
    Human man = findManByName(name);
    if (man.id >= 0)//если данный пользователь уже есть, то выходим из функции 
        return;

    int i = 0;

    for (; i < SIZE; i++)
        if (!busyids[i])//если id не занято, то занимаем его, и добавляем нового пользователя
            break;
    busyids[i] = true;
    people.add(Human(name, i));//добавляем нового пользователя
}

SocialNetwork::Human SocialNetwork::findManByName(const Name name)//метод поиска пользователя по имени 
{
    for (int i = 0; i < people.size(); i++)
        if (!strcmp(name, people[i].name))//сравниваем каждый элемент занятых имен, с искомым именем
            return people[i];
    return Human();
}

void SocialNetwork::delMan(const Name name)//функция удаления пользоваателя
{
    Human man = findManByName(name);
    if (man.id < 0)//если id пользователя равно -1, то такого пользователя нет, и мы выходим из метода
        return;
    busyids[man.id] = false;//если имя уже занято
    int index = people.find(man);
    for (int i = 0; i < people.size(); i++)//зануляем все связи данного пользователя с другими пользователями 
    {
        friend_matrix[i][man.id] = 0;
        friend_matrix[man.id][i] = 0;
    }
    people.del(index);//удаляем пользователя
}

void SocialNetwork::addFriendship(const Name name_1, const Name name_2)//добавляем дружбу между пользователями
{
    Human m1 = findManByName(name_1);
    Human m2 = findManByName(name_2);

    if (m1.id < 0 || m2.id < 0)//если пользователи не найдены
        return;
    //если найдены, то устанавливаем дружбу между ними
    friend_matrix[m1.id][m2.id] = 1;
    friend_matrix[m2.id][m1.id] = 1;
}

void SocialNetwork::showThreeHandshakes()//метод, который находит пользователей, знакомых через 3 рукопожатия
{
    int wavesLevels[SIZE];//инициализиум массив, в котором храним инфу по поводу знакомства пользователей
    for (int i = 0; i < SIZE; i++) {
        wavesLevels[i] = -1;
    }
    wavesLevels[0] = 0;

    StaticArray<int> queue;//создаем вектор очереди
    queue.add(0);//добавляем в очередь нулевой элемент вектора

    while (queue.size())//пока не конец вектора
    {
        int currentManIndex = queue[0];//берем элемент из очереди
        queue.del(0);//удаляем элемент из очереди

        for (int i = 0; i < people.size(); i++)
            if (are_friends(people[currentManIndex], people[i]) &&  wavesLevels[i] == -1)//проверяем то, являются ли люди друзьями
            {
                wavesLevels[i] = wavesLevels[currentManIndex] + 1;
                queue.add(i);
            }
    }

    for (int i = 0; i < people.size(); i++) {
        for (int j = i + 1; j < people.size(); j++) {
            if (abs(wavesLevels[i] - wavesLevels[j]) <= 3) {
                std::cout << people[i].name << " " << people[j].name << std::endl;
            }
        }
    }
}


bool SocialNetwork::are_friends(const Human& m1, const Human& m2)//проверяем есть ли дружба между пользователями
{
    return friend_matrix[m1.id][m2.id] == 1;
}

bool SocialNetwork::man_exists_with_id(int man_id)//проверяем существует ли данный человек уже
{
    for (int i = 0; i < people.size(); i++)
        if (people[i].id == man_id)
            return true;
    return false;
}
