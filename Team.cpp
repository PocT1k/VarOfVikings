#include "Team.h"


//��� ����������� ���� ���
LowUnit lu;
MediumUnit mu;
HigtUnit hu;
ArcherUnit au;
HillerUnit pu;
MagicUnit cu;
IBaseUnit* unitsArr[6] = { &lu, &mu, &hu, &au, &pu, &cu };
int prices[6] = { lu.price, mu.price, hu.price, au.price, pu.price, cu.price };
int minPrice = *std::min_element(prices, prices + 6); //���������� ����������� ����


Team::Team(int number) {
    this->number = number;
    money = startMoney;

    //���������� �����
    while (money >= minPrice) {
        shared_ptr<IBaseUnit> tempUnit = randomUnit();
        if (tempUnit != nullptr) {
            units.push_back(tempUnit);
            len++;
        }
    }
}

shared_ptr<IBaseUnit> Team::randomUnit() {
    int i = rand() % 6;

    switch (i) {
    case 0:
        if (money < prices[0]) { return nullptr; }
        else { money -= prices[0]; return make_shared<LowUnit>(); }
        break;
    case 1:
        if (money < prices[1]) { return nullptr; }
        else { money -= prices[1]; return make_shared<MediumUnit>(); }
        break;
    case 2:
        if (money < prices[2]) { return nullptr; }
        else { money -= prices[2]; return make_shared<HigtUnit>(); }
        break;
    case 3:
        if (money < prices[3]) { return nullptr; }
        else { money -= prices[3]; return make_shared<ArcherUnit>(); }
        break;
    case 4:
        if (money < prices[4]) { return nullptr; }
        else { money -= prices[4]; return make_shared<HillerUnit>(); }
        break;
    case 5:
        if (money < prices[5]) { return nullptr; }
        else { money -= prices[5]; return make_shared<MagicUnit>(); }
        break;
    default:
        return nullptr;
        break;
    }
    return nullptr;
}

void Team::print() {
    cout << "  �" << number << ": ";
    for (const auto& unit : units) {
        switch (unit->type) {
        case 'l':
            cout << "˸����" << " "; break;
        case 'm':
            cout << "�������" << " "; break;
        case 'h':
            cout << "������" << " "; break;
        case 'a':
            cout << "������" << " "; break;
        case 'p':
            cout << "������" << " "; break;
        case 'c':
            cout << "�������" << " "; break;
        default:
            break;
        }
    }
    cout << "(" << len /*units.size()*/ << ")" << endl;
}

void Team::move(Team& enemies) {
    if (len == 0 || enemies.len == 0) { return; } //�������� �� ������� ������ � �������

    int fullDamage = 0;
    int fullHealth = 0;
    bool copy = false;
    int index = 0;

    for (auto unit : units) { //������ ������� �������
        if (unit->lenDamage >= index) { //���������� ������ ���� ��������� ����������
            fullDamage += unit->damage;
        }

        if (unit->type == 'p') { //������������� ����� �������
            if (unit->lenUse >= index) {
                unit->chanceUse * 100 > rand() % 100 ? fullHealth += unit->medication : false; //���� ����
            }
        }
        index++;
    }
    index = 0;

    enemies.units[0]->takeDamage(fullDamage); //���������� ������
    units[0]->takeHealth(fullHealth); //���������� ����
    fullDamage = 0;
    fullHealth = 0;

    for (index = 0; index < len; index++) { //����� ����
        auto unit = units[index];
        if (unit->type == 'c') {
            for (int i = index - unit->lenUse; i < 1 + index + unit->lenUse; i++) { //��������� ������ ����� � ���� ������
                if (i == index || i < 0 || i > len - 1) { continue; } //�������� �� ����� �������
                if (!copy && units[i]->type == 'l') { //���� ����� ˸����� ����� ����� � ������ �� ��������
                    copy = unit->chanceUse * 10000 > rand() % 10000 ? true : false; //������� ���� �� �����������
                }
            }
            if (copy) { //�������� � ��������� � ������ �����
                auto position = units.begin() + index;
                units.insert(position + (rand() % 2 ? 1 : 0), make_shared<LowUnit>()); //������� ����� ��� ����� ����
                len++;
                index++;
            }
            copy = false;
        }
    }
    index = 0;

    //�������� �����
    if (!enemies.units[0]->getHealth()) {
        enemies.units.erase(enemies.units.begin());
        enemies.len--;
    }
}
