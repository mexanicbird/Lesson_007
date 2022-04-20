#include <iostream>
#include <ostream>
#include <memory>

using namespace std;


/* task 001 */
class Date {
protected:
    uint16_t day;
    uint16_t month;
    uint16_t year;
public:
    void setDay (uint16_t day) {
        this->day = day;
    }
    void setMonth (uint16_t month) {
        this->month = month;
    }
    void setYear (uint16_t year) {
        this->year = year;
    }
    uint16_t getDay() const {
        return day;
    }
    uint16_t getMonth() const {
        return month;
    }
    uint16_t getYear() const {
        return year;
    }
    Date( uint16_t _day, uint16_t _month, uint16_t _year) : day(_day), month(_month), year(_year) {
    }
    ~Date() = default;

    friend ostream &operator<<(ostream &stream, const Date &date) {
        return stream  << "<--" << date.getDay() << '.' << date.getMonth()
                   << '.' << date.getYear() << "-->" << endl;
    }
};


/* task 002 */
std::shared_ptr<Date> maxDate(const std::shared_ptr<Date>& date1, const std::shared_ptr<Date>& date2)
{
    if (date1.get()->getYear() > date2.get()->getYear())
        {return std::shared_ptr<Date>(date1);}
    else if(date1.get()->getYear() < date2.get()->getYear())
    {return std::shared_ptr<Date>(date2);}
    else if(date1.get()->getMonth() > date2.get()->getMonth())
        {return std::shared_ptr<Date>(date1);}
    else if(date1.get()->getMonth() < date2.get()->getMonth())
        {return std::shared_ptr<Date>(date2);}
    else if(date1.get()->getDay() > date2.get()->getDay())
        {return std::shared_ptr<Date>(date1);}
    else
        {return std::shared_ptr<Date>(date2);}
}

void swapDate(std::shared_ptr<Date>& date1, std::shared_ptr<Date>& date2)
{
    auto temp = move(date1);
    date1 = move(date2);
    date2 = move(temp);
}


int main() {
    /* execution time control */
    double start_time =  clock();
    std::cout << "Lesson 007" << std::endl;
    std::cout << "Task 1" << std::endl;
    time_t now = time(0);

    tm *ltm = localtime(&now);
    const Date d1(ltm->tm_mday,1 + ltm->tm_mon,1900 + ltm->tm_year);
    std::cout << d1;
    std::cout << "\n";

    auto today = make_unique<Date>(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
    unique_ptr<Date> date;

    cout << "Data: " << endl;
    cout << "Day: " << today.get()->getDay() << endl;
    cout << "Month : " << today.get()->getMonth() << endl;
    cout << "Year: " << today.get()->getYear() << endl << endl;
    cout << *today << endl;

    cout << "Today: " << (static_cast<bool>(today) ? "NOT null\n" : "null\n");
    cout << "Date: " << (static_cast<bool>(date) ? "NOT null\n" : "null\n");
    cout << "Swap" << endl;

    date = move(today);
    cout << "Today: " << (static_cast<bool>(today) ? "NOT null\n" : "null\n");
    cout << "Date: " << (static_cast<bool>(date) ? "NOT null\n" : "null\n");
    std::cout << "\n";


    std::cout << "Task 2" << std::endl;
    auto date1 = make_shared<Date>(24,2,2022);
    auto date2 = make_shared<Date>(9,5,2022);
    cout << "Date1: " << *date1;
    cout << "Date2: " << *date2 << endl;
    auto dateMax = maxDate(date1, date2);
    cout << "Late date: " << *dateMax << endl;
    cout << "Date1: " << *date1;
    cout << "Date2: " << *date2 << endl;
    std::cout << "\n";
    cout << "Swapping dates: " << endl;
    swapDate(date1, date2);
    cout << "Date1: " << *date1;
    cout << "Date2: " << *date2 << endl;
    cout << "Late date: " << *dateMax << endl;

    /* execution time control */
    double end_time = clock();
    double search_time = (end_time - start_time)/1000;
    std::cout << "Program execution time = " << search_time << " sec"<< std::endl;
    return 0;
}

/*
1. Создайте класс Date с полями день, месяц, год и методами доступа к этим полям.
 Перегрузите оператор вывода для данного класса. Создайте два "умных" указателя today и date.
 Первому присвойте значение сегодняшней даты. Для него вызовите по отдельности методы доступа
 к полям класса Date, а также выведите на экран данные всего объекта с помощью перегруженного
 оператора вывода. Затем переместите ресурс, которым владеет указатель today в указатель date.
 Проверьте, являются ли нулевыми указатели today и date и выведите соответствующую информацию
 об этом в консоль.

2. По условию предыдущей задачи создайте два умных указателя date1 и date2.
• Создайте функцию, которая принимает в качестве параметра два умных указателя типа Date и
 сравнивает их между собой (сравнение происходит по датам). Функция должна вернуть более позднюю дату.
• Создайте функцию, которая обменивает ресурсами (датами) два умных указателя, переданных в
 функцию в качестве параметров.
Примечание: обратите внимание, что первая функция не должна уничтожать объекты, переданные ей в
 качестве параметров.
 */