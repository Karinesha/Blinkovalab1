#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;
struct Pipe
{
    string name;
    double length;
    double diameter;
    bool isRepair;
};

struct Station
{
    string name;
    int countAll;
    int countWork;
    string effect;
};
// оператор ввода трубы
void operator >> (istream& in, Pipe& pipe) {
    do
    {
        // очищает флаг ошибки
        cin.clear();
        // переходит к следующей новой строке
        cin.ignore(10000, '\n');
        cout << "Type name: ";
        getline(cin, pipe.name);
    } while (pipe.name == "");
    do
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Type length: ";
        cin >> pipe.length;
    } while (cin.fail() || pipe.length < 0);
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type diameter: ";
        cin >> pipe.diameter;
    } while (cin.fail() || pipe.diameter < 0);
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type in repair (1=in repair, 0=not in repair): ";
        cin >> pipe.isRepair;
    } while (cin.fail());
}
// редактирование трубы
void EditPipe(Pipe& pipe)
{
    pipe.isRepair = !pipe.isRepair;//==1 ? 0 : 1;
};

// редактирование станции
void EditStation(Station& station)
{
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Number of workshops in operation: ";
        cin >> station.countWork;
    } while (cin.fail() || station.countWork<0 || station.countWork>station.countAll);
};

// вывод трубы в консоль
void operator << (ostream& out, const Pipe& p) {
    cout << "Pipe" << endl;
    cout << "Name: " << p.name
        << "\tLength: " << p.length
        << "\tDiameter: " << p.diameter
        << "\tIsRepair: " << p.isRepair << endl;
}

// чтение данных из файла о станции
Station LoadStation()
{
    ifstream fin;
    string st, s;
    Station station;
    string listData[4];
    int index = 0;
    int lengthStation = 9;
    // окрываем файл
    fin.open("data.txt");
    // проверка на открытие файла
    if (fin.is_open())
    {
        while (getline(fin, st))
        { // пока не достигнут конец файла класть очередную строку в переменную (st)
            // ss - это объект stringstream, который ссылается на строку st.
            stringstream ss(st);
            if (st.find("station") != string::npos)
            {
                while (getline(ss, s, ';'))
                {
                    if (index == 0)
                    {
                        // c_str () возвращает указатель на символьный массив, который содержит строку объекта стринг (string) в том виде, в котором она размещалась бы, во встроенном строковом типе
                        listData[index] = s.substr(lengthStation, strlen(s.c_str()));
                    }
                    else
                    {
                        listData[index] = s;
                    }
                    index += 1;
                }
                station.name = listData[0];
                // преобрзование строки в число
                station.countAll = stoi(listData[1]);
                station.countWork = stoi(listData[2]);
                station.effect = listData[3];
            }
        }
        fin.close();
    }

    return station;
};

// чтение данных из файла о трубе
Pipe LoadPipe()
{
    ifstream fin;
    string st, s;
    Pipe pipe;
    string a1[4];
    int index = 0;
    int lengthPipe = 6;
    // окрываем файл
    fin.open("data.txt");
    // проверка на открытие файла
    if (fin.is_open())
    {
        while (getline(fin, st))
        { // пока не достигнут конец файла класть очередную строку в переменную (st)
            // ss - это объект stringstream, который ссылается на строку st.
            stringstream ss(st);
            if (st.find("pipe") != string::npos)
            {
                while (getline(ss, s, ';'))
                {
                    if (index == 0)
                    {
                        // c_str () возвращает указатель на символьный массив, который содержит строку объекта стринг (string) в том виде, в котором она размещалась бы, во встроенном строковом типе
                        a1[index] = s.substr(lengthPipe, strlen(s.c_str()));
                    }
                    else
                    {
                        a1[index] = s;
                    }
                    index += 1;
                }
                pipe.name = a1[0];
                // преобрзование строки double в число
                pipe.length = atof(a1[1].c_str());
                pipe.diameter = atof(a1[2].c_str());
                pipe.isRepair = stoi(a1[3]);
            }
        }
        fin.close();
    }

    return pipe;
};

// оперотор ввода станции
void operator >> (istream& in, Station& station) {
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type name: ";
        getline(cin, station.name);
    } while (station.name == "");
    do
    {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cout << "Number of workshops: ";
        cin >> station.countAll;
    } while (cin.fail());
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Number of workshops in operation: ";
        cin >> station.countWork;
    } while (cin.fail());
    do
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type effectiveness: ";
        cin >> station.effect;
    } while (cin.fail());
}
//вывод в консоль станции
void operator << (ostream& out, const Station& s) {
    cout << "Station" << endl;
    cout << "Name: " << s.name
        << "\tCountAll: " << s.countAll
        << "\tCountWork: " << s.countWork
        << "\tEffectiveness: " << s.effect << endl;
}
void PrintStation(const Station& s)
{
    cout << "Station" << endl;
    cout << "Name: " << s.name
        << "\tCountAll: " << s.countAll
        << "\tCountWork: " << s.countWork
        << "\tEffectiveness: " << s.effect << endl;
};

// сохранение данных в файл
void SaveStation(const Station& s, ofstream& fout) {
    fout << "station:" << ' ' << s.name << ";" << to_string(s.countAll) << ";" << to_string(s.countWork) << ";" << s.effect << endl;
};
void SavePipe(const Pipe p, ofstream& fout) {
    fout << "pipe:" << ' ' << p.name << ";" << to_string(p.length) << ";" << to_string(p.diameter) << ";" << to_string(p.isRepair) << endl;
}

void SaveStationPipe(const Station& s, const Pipe p, bool isStation, bool isPipe)
{
    // объект файлового потока вывода
    ofstream fout;
    // запись в файл
    fout.open("data.txt", ios::out);
    if (fout.is_open())
    {
        if (isStation)
        {
            SaveStation(s, fout);
        }
        if (isPipe)
        {
            SavePipe(p, fout);
        }
        fout.close();
    }
};

void PrintMenu()
{
    cout << "Add pipe: 1" << endl
        << "Add CS: 2" << endl
        << "View all objects: 3" << endl
        << "Edit pipe: 4" << endl
        << "Edit CS: 5" << endl
        << "Save: 6" << endl
        << "Download: 7" << endl
        << "Exit: 0" << endl;
};

int main()
{
    Station station;
    Pipe pipe;
    bool isStation = false;
    bool isPipe = false;
    while (1)
    {
        PrintMenu();
        int i = 0;
        do {
            if (cin.fail() || i > 7) {
                cin.clear();
                cin.ignore(10000, '\n');
            }
            cin >> i;//!!!!!!!!!!!!
        } while (cin.fail() || i > 7);
        switch (i)
        {
        case 1:
        {
            cin >> pipe;
            isPipe = true;
            break;
        }
        case 2:
        {
            cin >> station;
            isStation = true;
            break;
        }
        case 3:
        {
            if (isStation)
            {
                cout << station;
            }
            if (isPipe)
            {
                cout << pipe;
            }
            break;
        }
        case 4:
        {
            if (isPipe)
            {
                EditPipe(pipe);
                cout << pipe;
            }
            else
            {
                cout << "Трубы не существует" << endl;
            }
            break;
        }
        case 5:
        {
            if (isStation)
            {
                EditStation(station);
                PrintStation(station);
            }
            else
            {
                cout << "Станции не существует" << endl;
            }
            break;
        }
        case 6:
        {
            SaveStationPipe(station, pipe, isStation, isPipe);
            break;
        }
        case 7:
        {
            station = LoadStation();
            pipe = LoadPipe();
            if (station.countAll != 0) {
                isStation = true;
                PrintStation(station);
            };
            if (pipe.isRepair == 0 || pipe.isRepair == 1) {
                isPipe = true;
                cout << pipe;
            }
            break;
        }
        case 0:
        {
            return 0;
        }
        default:
        {
            cout << "Произошла ошибка" << endl;
        }
        }
    }
    return 0;
}

