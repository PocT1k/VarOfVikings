#include "Team.h"

extern float medLenShild;
extern float medHealthShield;

//Хендл консоли
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

LowUnit lu;
MediumUnit mu;
HigtUnit hu;
ArcherUnit au;
HillerUnit pu;
MagicUnit cu;
IBaseUnit* unitsArr[COUNT_OF_UNITS] = { &lu, &mu, &hu, &au, &pu, &cu };

//Минимальная цена
int prices[COUNT_OF_UNITS] = { lu.price, mu.price, hu.price, au.price, pu.price, cu.price };
int minPriceUnit = *std::min_element(prices, prices + COUNT_OF_UNITS); //Минимальная цена


void playDeadSound();

void playDeadSound() {
    cout << "\a";
}


Team::Team(int number) {
    this->numberTeam = number;
    moneyTeam = startMoney;

    //Заполнение войск
    while (moneyTeam >= minPriceUnit) {
        shared_ptr<IBaseUnit> tempUnit = generateUnit();
        if (tempUnit == nullptr) {
            continue;
        }
        units.push_back(tempUnit);
        lenTeam++;
    }

    //Выдача щита
    generateShield();
}

shared_ptr<IBaseUnit> Team::generateUnit() {
    int i = rand() % COUNT_OF_UNITS;

    switch (i) {
    case 0:
        if (moneyTeam < prices[0]) { return nullptr; }
        else { moneyTeam -= prices[0]; return make_shared<LowUnit>(); }
        break;
    case 1:
        if (moneyTeam < prices[1]) { return nullptr; }
        else { moneyTeam -= prices[1]; return make_shared<MediumUnit>(); }
        break;
    case 2:
        if (moneyTeam < prices[2]) { return nullptr; }
        else { moneyTeam -= prices[2]; return make_shared<HigtUnit>(); }
        break;
    case 3:
        if (moneyTeam < prices[3]) { return nullptr; }
        else { moneyTeam -= prices[3]; return make_shared<ArcherUnit>(); }
        break;
    case 4:
        if (moneyTeam < prices[4]) { return nullptr; }
        else { moneyTeam -= prices[4]; return make_shared<HillerUnit>(); }
        break;
    case 5:
        if (moneyTeam < prices[5]) { return nullptr; }
        else { moneyTeam -= prices[5]; return make_shared<MagicUnit>(); }
        break;
    default:
        return nullptr;
        break;
    }
    return nullptr;
}

void Team::generateShield() {
    //Средняя цена
    int sum = 0;
    for (int i = 0; i < COUNT_OF_UNITS; i++) { sum += prices[i]; }
    int medPriceUnit = sum / COUNT_OF_UNITS; //Средняя цена

    //Среднее здоровье
    int healths[COUNT_OF_UNITS] = { lu.getHealth(), mu.getHealth(), hu.getHealth(), au.getHealth(), pu.getHealth(), cu.getHealth() };
    for (int i = 0; i < COUNT_OF_UNITS; i++) { sum += healths[i]; }
    int medHealthUnit = sum / COUNT_OF_UNITS; //Среднее здоровье

    int medCountUnits = (startMoney + medPriceUnit / 2) / medPriceUnit; //Среднее количество воинов в команде
    int medHealthUnits = medCountUnits * medHealthUnit; //Среднее число здоровья на команду

    lenShield = medCountUnits * medLenShild;
    healthShield = medHealthUnits * medHealthShield;
    ptrShield = rand() % lenTeam;
    if (ptrShield + lenShield > lenTeam) { //Сдвигаем щит, если он вышел в бок
        ptrShield = lenTeam - lenShield;
    }
}

int Team::getUnitNumber(shared_ptr<IBaseUnit> unit) {
    auto it = find(units.begin(), units.end(), unit);
    if (it != units.end()) {
        return distance(units.begin(), it);
    }
    else {
        return -1; //Воин не найден
    }
}

bool Team::isUnderShield(shared_ptr<IBaseUnit> unit) {
    int numberUnit = getUnitNumber(unit);
        if (numberUnit >= ptrShield && numberUnit < ptrShield + lenShield) {
            return true;
        }
    return false;
}

void Team::print() {
    cout << "  к" << numberTeam << ": ";

    //Определение цвета
    int health, color, count = 0;
    for (const auto& unit : units) {
        health = unit->getHealth();
        color = (health == 0 ? 4 : (health == unit->getMAX_HP() ? 2 : 6)); //Окрашиваем в зависимости от уровня здоровья
        if (isUnderShield(unit)) { color += 16; } //Если под щитом, то дополнительно красим
        SetConsoleTextAttribute(hConsole, color);
        cout << unit->getName() << " ";
        if (health != 0) { count++; }
    }

    SetConsoleTextAttribute(hConsole, 7);
    cout << "(" << count << ")" << endl;
}

void Team::deleteDead() {
    int i = 0;
    for (auto it = units.begin(); it != units.end();) { //Перебираем итераторы в списке
        if (!(*it)->getHealth()) { // 0 => воин умер, иначе любое ненулевое значение => воин жив
            playDeadSound();
            it = units.erase(it);
            lenTeam--;
            if (i < ptrShield) { //Передвижение щита
                ptrShield--;
            }
            else if (i == ptrShield && lenShield > 0) { //Уменьшение щита
                lenShield--;
            }
        }
        else {
            it++;
            i++;
        }
    }
}

void Team::move0(Team& enemies) {
    if (lenTeam == 0 || enemies.lenTeam == 0) { return; } //Проверка на наличие воинов в команде

    int fullDamage = 0;
    int fullHealth = 0;
    bool copy = false; //нужно чтобы копирование срабатывало максимум 1 раз за ход
    int index = 0;

    for (auto unit : units) { //Вся комманда пытается ударить первого
        if (unit->lenDamage >= index) { //Применение дамага если позволяет расстояние
            fullDamage += unit->damage;
        }

        if (unit->type == 'p') { //Дополнительно ходят хиллеры
            if (unit->lenUse >= index) {
                unit->chanceUse * 100 > rand() % 100 ? fullHealth += unit->medication : false; //Шанс хила
            }
        }
        index++;
    }
    index = 0;

    enemies.units[0]->takeDamage(fullDamage); //Применение дамага
    units[0]->takeHealth(fullHealth); //Применение хила
    fullDamage = 0;
    fullHealth = 0;

    for (index = 0; index < lenTeam; index++) { //Ходят маги
        auto unit = units[index];
        if (unit->type == 'c') {
            for (int i = index - unit->lenUse; i < 1 + index + unit->lenUse; i++) { //Проверяем воинов рядом в зоне действия и ищем лёгкого
                if (i == index || i < 0 || i > lenTeam - 1) { continue; } //Проверка на выход массива
                if (!copy && units[i]->type == 'l') { //Если нашли Лёгкого воина рядом и раньше не находили
                    copy = unit->chanceUse * 10000 > rand() % 10000 ? true : false; //Прокаем шанс на копирование
                }
            }
            if (copy) { //Копируем и вставляем в случае удачи
                auto position = units.begin() + index;
                units.insert(position + rand() % 2, make_shared<LowUnit>()); //Вставка перед или после позиции мага
                lenTeam++;
                index++;
            }
            copy = false;
        }
    }
    index = 0;
}
