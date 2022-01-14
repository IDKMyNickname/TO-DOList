
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

int checkNotifycation() {
    ifstream notifyList("notifycations.d");
    if (notifyList.fail()) {
        return 1;
    }
    else {
        return 2;
    }

    notifyList.close();
}

void showNotifys() {

    //setlocale(LC_ALL, "Russian");
    string notifys;

    ifstream notifyList("notifycations.d");
    
    while (getline(notifyList, notifys)) { 
        notifys = notifys + "\n";
        cout << notifys << endl;
    }

    notifyList.close();

}

string getTime() {
    //time
    auto start = std::chrono::system_clock::now();
    // Some computation here
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    string timeStr = std::ctime(&end_time);
    //strReturn
    return timeStr;
}

string getDate() {
    //Date
    const time_t tm = time(nullptr);

    char buf[64];
    strftime(buf, std::size(buf), "%d.%m.%Y", localtime(&tm));
    //cout << buf << std::endl;
    return buf;

}

void timeOperation() {
    char ch;
    int code;
    bool ruProgramm = true;
    while (true)
    {
        //ch = _getch();
        //code = static_cast<int>(ch);
       // if (ch == 27 | ch = ) // если клавиша esc
       //     cout << ch;
       //     ruProgramm = false;//Выход из прогр

        vector<string> times; //Создать массив

        //Положить в массив время, в которое

        string notifys;

        ifstream notifyList("notifycations.d");

        while (getline(notifyList, notifys)) {
            times.push_back(notifys); //Добавить дату и время напоминания
        }
        notifyList.close();
        string gdNow = getDate();
        
        string timeNow = getTime();
        
        gdNow = gdNow.substr(0, 5);
        string timeN = timeNow.substr(timeNow.length() - 14, 15);
        
        string hasTwo = timeN.substr(0, 5);
        cout << hasTwo << endl; //19:14
        cout << gdNow << endl; // 14.01
        
        string dtTimeNow = gdNow + " " + hasTwo; //Строка с временем и датой для сравнения

        //cout << dtTimeNow << " - Сгенерированое время сейчас" << endl; //Строка с временем и датой для сравнения
        
        for (int i = 0; i <= size(times)-1; i++) {
            cout << size(times) << " - mass" << endl;
            string nowTimesAndVr = times[i];
            nowTimesAndVr = nowTimesAndVr.substr(nowTimesAndVr.length() - 11, nowTimesAndVr.length());
            cout << nowTimesAndVr << " - timeDateRasp" << endl;
            cout << dtTimeNow << " - dateTimeNow" << endl;
            if (dtTimeNow == nowTimesAndVr) {
                cout << "URA TUTA MUSIC BYDET!!" << endl;
                exit(0);
            }
            Sleep(2000);
        }

        cout << "end" << endl;
    }

    
}

void deleteNotifi() {
    string notifys;
    int strr = 1;
    ifstream notifyList("notifycations.d");

    while (getline(notifyList, notifys)) {
        cout << strr << " - " << notifys << endl;
    }

    int numberSToDelete;
    cin >> numberSToDelete;

    notifyList.close();

}

void createNotify(string nameNotify, string date, string time) {
    ofstream notificatioList("notifycations.d", ios::app);

    notificatioList << nameNotify + " " + date + " " + time << endl;

    notificatioList.close();
}


void playMusic() {
    //Тут музыка
}

int main()
{
    system("title TO-DOᅠList");
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    //setlocale(LC_ALL, "Russian");
    setlocale(LC_ALL, "Russian_Russia.1251");
    //timeOperation();
    cout << "Добро пожаловать в программу вновь!" << endl;
    cout << "Следующие напоминание: \n\n";
    showNotifys();
        
    
     
    bool runProgram = true;
    while (runProgram) {

        cout << "Следующие напоминание: \n\n";
        //showNotifys();
        //timeOperation();

        cout << "\nВыберите один из предложенных вариантов: \n";
        cout << "1 - Добавить напоминание" << endl;
        cout << "2 - Удалить напомиание" << endl;
        int command;
        cin >> command;
        
        if (command == 1) {
            cout << "Enter name of Notification: ";
            string nN;
            cin >> nN;
            cout << "Enter date of notification(DD/MM): ";
            string dt;
            cin >> dt;
            cout << "Enter time of notification: ";
            string timeN;
            cin >> timeN;
            //cout << "Введите за сколько вам напомнить про это напоминание?(Если не надо введите 0, воодить в часах): ";
            //int nnnm;
            //cin >> nnnm;

            createNotify(nN, dt, timeN);
        }
        else if (command == 2) {
            deleteNotifi();
        }
        else if (command == 3) {
            timeOperation();
        }
    }




    //HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
    //SetConsoleTextAttribute(hOUTPUT, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    //cout << "GREEN TEXT\n";
    //SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_INTENSITY);
    //cout << "RED TEXT\n";
    //SetConsoleTextAttribute(hOUTPUT, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    //cout << "sad";
    //return 0;
}
