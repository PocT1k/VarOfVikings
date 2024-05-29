#include "Funcs.h"


//money
extern int startMoney;
int standartMoney = startMoney;
//strateg
unsigned int typeStrateg = 0;
string arrStrategNames[COUNT_OF_STRATEG] = { "Первый хуярит первого", "Стенка на стенку по порядку", "Стенка на стенку рандомно" };
//stream
unsigned int logStreamNumber = 0;
string arrLogStreamNames[COUNT_OF_STREAM] = { "файл", "консоль", "никуда" };
ofstream fout("logs.txt");
ostream* arrLogStreams[COUNT_OF_STREAM] = { &fout, &cout, nullptr };
ostream* logStream = arrLogStreams[logStreamNumber];


void printCommands() {
    cout << "Нажмите соотвествующую клавишу:" << endl;
    cout << "1 Запустить симуляцию" << endl;
    cout << "2 Изменить стартовый бюджет" << endl;
    cout << "3 Изменить тип стратегии игры" << endl;
    cout << "4 Изменить выходной прокси логирования" << endl;
    //cout << "0 Печать параметров" << endl;
    cout << "ESC выход из программы" << endl;
}

void menuStop() {
    cout << endl << "Для продолжения работы нажмите ENTER" << endl;
    char key;
    while (true) {
        key = _getch();
        switch (key) {
        case kENTER:
            return;
        default:
            break;
        }
    }
}

void menuClear() {
    system("CLS");
}

void editMoney() {
    menuClear();
    cout << "2 Изменение стартового бюджета" << endl;
    cout << endl;
    cout << "Текущее значение: " << startMoney << " (стандартное значение: " << standartMoney << ")" << endl;
    cout << "Введите новый бюджет: " << endl;

    string str;
    getline(cin, str);
    string bufferNewMoney = "";

    for (char c : str) {
        if (isdigit(c)) {
            bufferNewMoney += c;
        }
    }

    if (bufferNewMoney == "") {
        cout << "Стартовый бюджет не изменён - нет цифр в строке, старое значение " << startMoney << endl;
    }
    else if (stoi(bufferNewMoney) < minPriceUnit) {
        cout << "Стартовый бюджет не изменён - значение " << stoi(bufferNewMoney) << " меньше цены наидешёвейшего бойца (" << minPriceUnit << "), старое значение " << startMoney << endl;
    }
    else {
        startMoney = stoi(bufferNewMoney);
        cout << "Стартовый бюджет изменён и состовляет " << startMoney << endl;
    }
}

void editStrateg() {
    menuClear();
    cout << "3 Изменение типа стратегии игры" << endl;
    cout << endl;
    cout << "Текущее стратегия №" << typeStrateg + 1 << " (" << arrStrategNames[typeStrateg] << ")" << endl;
    cout << endl;
    cout << "Выберите новую стратегию (нажмите соотвествующую клавишу):" << endl;
    for (int i = 0; i < COUNT_OF_STRATEG; i++) { cout << i + 1 << " " << arrStrategNames[i] << endl; } //Печать для вфыбора

    char key;
    bool run = 1;
    while (run) {
    start:
        key = _getch();

        switch (key) {
        case kESC:
            run = 0;
            cout << endl;
            cout << "Изменение типа стратегии игры отменено" << endl;
            goto end;
            break;
        case k1:
            run = 0;
            typeStrateg = 0;
            break;
        case k2:
            run = 0;
            typeStrateg = 1;
            break;
        case k3:
            run = 0;
            typeStrateg = 2;
            break;
        default:
            goto start;
            break;
        } //switch

    } //while
    cout << endl;
    cout << "Выбран тип стратегии №" << typeStrateg + 1 << " (" << arrStrategNames[typeStrateg] << ")" << endl;
end:
    return;
}

void editStream() {
    menuClear();
    cout << "4 Изменить выходной прокси логирования" << endl;
    cout << endl;
    cout << "Сейчас логирование производиться в " << arrLogStreamNames[logStreamNumber] << endl;
    cout << endl;
    cout << "Выберите новое место логирования (нажмите соотвествующую клавишу):" << endl;
    for (int i = 0; i < COUNT_OF_STREAM; i++) { cout << i + 1 << " В " << arrLogStreamNames[i] << endl; } //Печать для вфыбора

    char key;
    bool run = 1;
    while (run) {
    start:
        key = _getch();

        switch (key) {
        case kESC:
            run = 0;
            cout << endl;
            cout << "Изменение выходного прокси логирования отменено" << endl;
            goto end;
            break;
        case k1:
            run = 0;
            logStreamNumber = 0;
            break;
        case k2:
            run = 0;
            logStreamNumber = 1;
            break;
        case k3:
            run = 0;
            logStreamNumber = 2;
            break;
        default:
            goto start;
            break;
        } //switch
    } //while

    logStream = arrLogStreams[logStreamNumber];
    cout << endl;
    cout << "Выбрано логирования в " << arrLogStreamNames[logStreamNumber] << endl;
end:
    return;
}

void outInfo() { //TONOTDO
    void;
    switch (rand()) {
    case 1367:
        cout << "\7ООО\nПовезло, повезло" << endl;
        break;
    default:
        cout << "\t " << endl;
        break;
    }
    return;
}

void runSimulation() {
    cout << "Создание команд..." << endl;
    Team team1(1);
    Team team2(2);

    menuClear();
    cout << "Комманы перед началом боя:" << endl;
    team1.print();
    team2.print();
    menuStop();

    unsigned int motion = 0; //Номер хода
    while (team1.lenTeam != 0 && team2.lenTeam != 0) { //Цикл боя
        ////Ход
        //team1.move0(team2);
        //team2.move0(team1);

        ////Результаты
        //cout << ++motion << " ход: " << endl;
        //team1.print();
        //team2.print();

        ////Удаление мёртвых
        //team1.deleteDead();
        //team2.deleteDead();

        /*Сверху бойцы удаляются после хода обоих команд, снизу - сразу после хода одной команды*/

        cout << ++motion << " ход: " << endl;

        team1.move0(team2);
        team2.print();
        team2.deleteDead();
        timeSleep();

        team2.move0(team1);
        team1.print();
        team1.deleteDead();
        timeSleep();
    }
    team1.deleteDead();
    team2.deleteDead();

    if (team1.lenTeam == 0 && team2.lenTeam == 0) {
        cout << endl << endl << "Обе команы полностью убили друг друга" << endl;
        cout << endl << "Бой завершён, результат ничья" << endl;

        if (logStream != nullptr && logStream != &cout) { (*logStream) << "Бой завершён, результат ничья" << endl; }
    }
    else {
        Team* team = (team2.lenTeam == 0 ? &team1 : &team2);
        cout << endl << endl << "Оставшиеся в победившей команде:" << endl;
        team->print();
        cout << endl << "Бой завершён, победила команда " << team->numberTeam << endl;

        if (logStream != nullptr && logStream != &cout) { (*logStream) << "Бой завершён, победила команда " << team->numberTeam << endl; }
    }
    if (logStream != nullptr && logStream != &cout) { (*logStream) << endl; }
}
