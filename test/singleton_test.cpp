#include "../include/singleton.hpp"
#include <string>
#include <iostream>/*std cout cin*/
using namespace pirates_speed;

class Person
{
    public:
        Person(std::string name, int age);
        void Print();

    private:
        std::string m_name;
        int m_age;
};

Person::Person(std::string name, int age)
    : m_name(name), m_age(age)
{

}

void Person::Print()
{
    std::cout << "Name: " << m_name << " Age: " << m_age << std::endl;
}

int main()
{
    Person p1 = Singleton<Person,std::string,int>::GetInstance("yarden",22);
    p1.Print();
    Person p2 = Singleton<Person,std::string, int>::GetInstance("georgi",33);
    p2.Print();

    

    return 0;
}