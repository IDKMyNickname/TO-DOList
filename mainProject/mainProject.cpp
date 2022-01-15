
#pragma warning(disable:4996)
#include <windows.h>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <conio.h>
#include <chrono>
#include <ctime>
#include <clocale>
#include <string>
#include <algorithm>
#include <vector>


using namespace std;

HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);

//string getTime() {

//}

int aBug = 1;

void showNotifis() {

    //setlocale(LC_ALL, "Russian");
    string notifis;

    ifstream notifiList("notifications.txt");
    
    while (getline(notifiList, notifis)) { 
        notifis = notifis + "\n";//
        cout << notifis << endl;
    }
    //Пройтись по всем строкам и вывести все напоминания которые есть
    notifiList.close();

}

string getTime() {
    //Тут локально берём время с компьтера
    auto start = std::chrono::system_clock::now();
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    string timeStr = std::ctime(&end_time);
    return timeStr;
}

string getDate() {
    //Тут локально берём дату с компьютера
    const time_t tm = time(nullptr);

    char buf[64];
    strftime(buf, std::size(buf), "%d.%m.%Y", localtime(&tm));
    //cout << buf << std::endl;
    return buf;

}

void sendNotifi(string nameNotifiNow) {
    nameNotifiNow = nameNotifiNow.substr(0, nameNotifiNow.length() - 12); //Обрезать только до названия напоминания

    LPCSTR toSend = nameNotifiNow.c_str(); //Переформатировать строку в особый формат
    MessageBoxA(NULL, toSend, "TO-DO List", MB_OK); //Вывести сообщения на экран
}

void clearTxt(int strToDel) {
    ifstream file_in("notifications.txt");
    int schetNow = 0;
    string generateFile;
    string strNow;
    while (getline(file_in, strNow)) {
        schetNow++; //Прибавляем один к текущей строке чтобы знать какая сейчас строка
        if (schetNow != strToDel) {
            generateFile = generateFile + strNow + "\n"; //Добавить строку сейчас ко всем
        }
    }
    file_in.close();
    remove("notifications.txt"); //Удалим файл для его очитски >З
    ofstream out_of("notifications.txt");
    out_of << generateFile;
    out_of.close();
}



void timeOperation() {
    while (true)
    {
        vector<string> times; //Создать массив

        //Положить в массив время, в которое

        string notifis;

        ifstream notifiList("notifications.txt");

        while (getline(notifiList, notifis)) {
            times.push_back(notifis); //Добавить дату и время напоминания
        }
        notifiList.close();
        string gdNow = getDate();
        
        string timeNow = getTime();
        
        gdNow = gdNow.substr(0, 5);
        string timeN = timeNow.substr(timeNow.length() - 14, 15);
        
        string hasTwo = timeN.substr(0, 5);
        
        string dtTimeNow = gdNow + " " + hasTwo; //Строка с временем и датой для сравнения

        int a = 0;
        
        if (size(times) == 0) { //Если массив со временм пуст, завершаем т.к. проверять нечего
            break;
        }

        for (int i = 0; i <= size(times)-1; i++) {

            string nowTimesAndVr = times[i];
            string nameNotifiNow = nowTimesAndVr; //Дублируем переменную для отделения названия в случае надобности
            nowTimesAndVr = nowTimesAndVr.substr(nowTimesAndVr.length() - 11, nowTimesAndVr.length());

            if (dtTimeNow == nowTimesAndVr) { //Если строки совпали
                clearTxt(i+1);//Очищаем файл от сработовшего напоминания
                sendNotifi(nameNotifiNow); //Уведомляем пользователя о нём
                a = 1; //Ставим флажок что программа сработала
                break;
                
            }
        }
        if (a == 1) {
            break;
        }
        system("cls");//Очищаем консоль
    }
        

    
}


void deleteNotifi() {
    string notifis;
    int strr = 1;
    ifstream file_in("notifications.txt");

    cout << "Введите цифру вначале строки напоминнания, которого вы хотиту удалить\n" << endl;

    while (getline(file_in, notifis)) {
        cout << strr << " - " << notifis << endl;
        strr++;
    }

    int numberSToDelete;
    cout << "Какую строку вы хотите удалить(введите цифру): ";
    cin >> numberSToDelete;

    string fileGenerate = "";
    string notNow;
    int strNow = 0;
    while (getline(file_in, notNow)) {
        strNow++;
        if (numberSToDelete != strNow) { //Если строка не та, которая введена пользователем, добавляем его в список, чтобы занести
            fileGenerate = fileGenerate + notNow + "\n";
        }

    }

    file_in.close();
    clearTxt(numberSToDelete);
    
    system("cls");
}

void createNotifi(string nameNotifi, string date, string time) {
    ofstream notificatioList("notifications.txt", ios::app); //Открываем на дозапись

    notificatioList << nameNotifi + " " + date + " " + time << endl; //Записываем

    notificatioList.close();

    system("cls");
}


int main()
{
    system("title TO-DOᅠList");

    setlocale(LC_ALL, "Russian_Russia.1251");

    cout << "Добро пожаловать в программу вновь!" << endl;
    cout << "Следующие напоминание: \n\n";
    showNotifis();
        
    
     
    bool runProgram = true;
    while (runProgram) {


        cout << "\nВыберите один из предложенных вариантов: \n";
        cout << "1 - Добавить напоминание" << endl;
        cout << "2 - Удалить напомиание" << endl;
        cout << "3 - Активировать напоминание" << endl;
        int command;
        cin >> command;
        
        if (command == 1) {
            cout << "Введите имя напоминания: ";
            cin.ignore(7777, '\n');
            //string nN;
            char nN[100]; //Делаем так, т.к. cin с пробелом не работает
            cin.getline(nN, sizeof(nN));
            cout << "Введите дату напоминания(ДД/MM): ";
            string dt;
            cin >> dt;
            cout << "Введите время напоминания: ";
            string timeN;
            cin >> timeN;
            //cout << "Введите за сколько вам напомнить про это напоминание?(Если не надо введите 0, воодить в часах): ";
            //int nnnm;
            //cin >> nnnm;

            createNotifi(nN, dt, timeN); //создать напоминание
        }
        else if (command == 2) {
            deleteNotifi(); //Удалить напоминание
        }
        else if (command == 3) {
            timeOperation(); //Включить режим ожидания
        }
        else {
            cout << "Такой команды не бывает!" << endl;
        }
    }


}
