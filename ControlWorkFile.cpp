#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <iomanip>

using namespace std;

const int MAX_STUDENTS = 100;

struct Student
{
    char name[30];
    int group;
    double grade;
};


int ReadStudents(const char* filename, Student students[]) {
    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Ошибка открытия файла.\n";
    }

    int counter = 0;
    while (file.good() && counter < MAX_STUDENTS)
    {
        char line[100];
        file.getline(line, 100);

        if (strlen(line) == 0) continue;
        char* token = strtok(line, ";");

        if (token == nullptr) continue;
        strncpy(students[counter].name, token, 29);
        students[counter].name[29] = '\0';

        token = strtok(nullptr, ";");
        if (token == nullptr) continue;
        students[counter].group = atoi(token);

        token = strtok(nullptr, ";");
        if (token == nullptr) continue;
        students[counter].grade = atof(token);

        counter++;
    }

    file.close();
    return counter;
}


void WriteStudents(const char* filename, Student students[], int counter)
{
    ofstream file(filename);
    if (!file.is_open())
    {
        cout << "Не удалось открыть файл для записи.\n";
    
    }
    else
    {
        for (int i = 0; i < counter; ++i)
        {
        file << students[i].name << ";" << students[i].group << ";" << students[i].grade << "\n";
        }

        file.close();
    }

}


void SortByName(Student students[], int counter) {
    for (int i = 0; i < counter - 1; ++i) {
        for (int j = 0; j < counter - i - 1; ++j) {
            if (strcmp(students[j].name, students[j + 1].name) > 0) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}


void SortGroupAndName(Student students[], int counter) {
    for (int i = 0; i < counter - 1; ++i) {
        for (int j = 0; j < counter - i - 1; ++j) {
            if (students[j].group > students[j + 1].group ||
               (students[j].group == students[j + 1].group &&
                strcmp(students[j].name, students[j + 1].name) > 0)) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}


void FindStudent(Student students[], int counter, const char* surname) {
    bool found = false;
    for (int i = 0; i < counter; ++i)
    {
        if (strncmp(students[i].name, surname, strlen(surname)) == 0)
        {
            cout << "Найден: " << students[i].name << ", группа: " << students[i].group << ", балл: " << students[i].grade << "\n";
            found = true;
        }
    }
    if (found == false)
    {
        cout << "Студент с фамилией '" << surname << "' не найден.\n";
    }
}



void MenuProgramm(Student students[], int counter, const char* filename)
{
    int choice;
    char input[30];

    do {
        cout << "\n--- Меню ---\n"
             << "1. Отсортировать по фамилиям и сохранить в файл\n"
             << "2. Найти студента по фамилии\n"
             << "3. Отсортировать по группам и фамилиям (на экран)\n"
             << "0. Выход\n"
             << "Выбор: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                SortByName(students, counter);
                WriteStudents(filename, students, counter);
                cout << "Данные отсортированы и сохранены.\n";
                break;
            case 2:
                cout << "Введите фамилию: ";
                cin.getline(input, 30);
                FindStudent(students, counter, input);
                break;
            case 3:
                SortGroupAndName(students, counter);
                for (int i = 0; i < counter; ++i) {
                    cout << students[i].name << "\t" << students[i].group << "\t" << students[i].grade << "\n";
                }
                break;
            case 0:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор.\n";
        }

    } while (choice != 0);
}

int main()
{
    Student students[MAX_STUDENTS];
    const char* filename = "datafilestudents.txt";
    int counter = ReadStudents(filename, students);

    if (counter <= 0)
    {
        cout << "Нет данных для обработки.\n";
    }

    MenuProgramm(students, counter, filename);
    return 0;
}
