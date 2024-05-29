#include "Funcs.h"


//money
extern int startMoney;
int standartMoney = startMoney;
//strateg
unsigned int typeStrateg = 0;
string arrStrategNames[COUNT_OF_STRATEG] = { "������ ������ �������", "������ �� ������ �� �������", "������ �� ������ ��������" };
//stream
unsigned int logStreamNumber = 0;
string arrLogStreamNames[COUNT_OF_STREAM] = { "����", "�������", "������" };
ofstream fout("logs.txt");
ostream* arrLogStreams[COUNT_OF_STREAM] = { &fout, &cout, nullptr };
ostream* logStream = arrLogStreams[logStreamNumber];


void printCommands() {
    cout << "������� �������������� �������:" << endl;
    cout << "1 ��������� ���������" << endl;
    cout << "2 �������� ��������� ������" << endl;
    cout << "3 �������� ��� ��������� ����" << endl;
    cout << "4 �������� �������� ������ �����������" << endl;
    //cout << "0 ������ ����������" << endl;
    cout << "ESC ����� �� ���������" << endl;
}

void menuStop() {
    cout << endl << "��� ����������� ������ ������� ENTER" << endl;
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
    cout << "2 ��������� ���������� �������" << endl;
    cout << endl;
    cout << "������� ��������: " << startMoney << " (����������� ��������: " << standartMoney << ")" << endl;
    cout << "������� ����� ������: " << endl;

    string str;
    getline(cin, str);
    string bufferNewMoney = "";

    for (char c : str) {
        if (isdigit(c)) {
            bufferNewMoney += c;
        }
    }

    if (bufferNewMoney == "") {
        cout << "��������� ������ �� ������ - ��� ���� � ������, ������ �������� " << startMoney << endl;
    }
    else if (stoi(bufferNewMoney) < minPriceUnit) {
        cout << "��������� ������ �� ������ - �������� " << stoi(bufferNewMoney) << " ������ ���� �������������� ����� (" << minPriceUnit << "), ������ �������� " << startMoney << endl;
    }
    else {
        startMoney = stoi(bufferNewMoney);
        cout << "��������� ������ ������ � ���������� " << startMoney << endl;
    }
}

void editStrateg() {
    menuClear();
    cout << "3 ��������� ���� ��������� ����" << endl;
    cout << endl;
    cout << "������� ��������� �" << typeStrateg + 1 << " (" << arrStrategNames[typeStrateg] << ")" << endl;
    cout << endl;
    cout << "�������� ����� ��������� (������� �������������� �������):" << endl;
    for (int i = 0; i < COUNT_OF_STRATEG; i++) { cout << i + 1 << " " << arrStrategNames[i] << endl; } //������ ��� �������

    char key;
    bool run = 1;
    while (run) {
    start:
        key = _getch();

        switch (key) {
        case kESC:
            run = 0;
            cout << endl;
            cout << "��������� ���� ��������� ���� ��������" << endl;
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
    cout << "������ ��� ��������� �" << typeStrateg + 1 << " (" << arrStrategNames[typeStrateg] << ")" << endl;
end:
    return;
}

void editStream() {
    menuClear();
    cout << "4 �������� �������� ������ �����������" << endl;
    cout << endl;
    cout << "������ ����������� ������������� � " << arrLogStreamNames[logStreamNumber] << endl;
    cout << endl;
    cout << "�������� ����� ����� ����������� (������� �������������� �������):" << endl;
    for (int i = 0; i < COUNT_OF_STREAM; i++) { cout << i + 1 << " � " << arrLogStreamNames[i] << endl; } //������ ��� �������

    char key;
    bool run = 1;
    while (run) {
    start:
        key = _getch();

        switch (key) {
        case kESC:
            run = 0;
            cout << endl;
            cout << "��������� ��������� ������ ����������� ��������" << endl;
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
    cout << "������� ����������� � " << arrLogStreamNames[logStreamNumber] << endl;
end:
    return;
}

void outInfo() { //TONOTDO
    void;
    switch (rand()) {
    case 1367:
        cout << "\7���\n�������, �������" << endl;
        break;
    default:
        cout << "\t " << endl;
        break;
    }
    return;
}

void runSimulation() {
    cout << "�������� ������..." << endl;
    Team team1(1);
    Team team2(2);

    menuClear();
    cout << "������� ����� ������� ���:" << endl;
    team1.print();
    team2.print();
    menuStop();

    unsigned int motion = 0; //����� ����
    while (team1.lenTeam != 0 && team2.lenTeam != 0) { //���� ���
        ////���
        //team1.move0(team2);
        //team2.move0(team1);

        ////����������
        //cout << ++motion << " ���: " << endl;
        //team1.print();
        //team2.print();

        ////�������� ������
        //team1.deleteDead();
        //team2.deleteDead();

        /*������ ����� ��������� ����� ���� ����� ������, ����� - ����� ����� ���� ����� �������*/

        cout << ++motion << " ���: " << endl;

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
        cout << endl << endl << "��� ������ ��������� ����� ���� �����" << endl;
        cout << endl << "��� ��������, ��������� �����" << endl;

        if (logStream != nullptr && logStream != &cout) { (*logStream) << "��� ��������, ��������� �����" << endl; }
    }
    else {
        Team* team = (team2.lenTeam == 0 ? &team1 : &team2);
        cout << endl << endl << "���������� � ���������� �������:" << endl;
        team->print();
        cout << endl << "��� ��������, �������� ������� " << team->numberTeam << endl;

        if (logStream != nullptr && logStream != &cout) { (*logStream) << "��� ��������, �������� ������� " << team->numberTeam << endl; }
    }
    if (logStream != nullptr && logStream != &cout) { (*logStream) << endl; }
}
