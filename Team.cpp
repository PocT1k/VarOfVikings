#include "Team.h"


//Для определения всех цен
LowUnit lu;
MediumUnit mu;
HigtUnit hu;
ArcherUnit au;
HillerUnit pu;
MagicUnit cu;
IBaseUnit* unitsArr[6] = { &lu, &mu, &hu, &au, &pu, &cu };
int prices[6] = { lu.price, mu.price, hu.price, au.price, pu.price, cu.price };
int minPrice = *std::min_element(prices, prices + 6); //Нахождение минимальной цены


Team::Team(int number) {
    this->number = number;
    money = startMoney;

    //Заполнение войск
    while (money >= minPrice) {
        shared_ptr<IBaseUnit> tempUnit = randomUnit();
        if (tempUnit == nullptr) {
            continue;
        }
        units.push_back(tempUnit);
        len++;
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

bool isUnderShield() {
    return false;
}

void Team::print() {
    cout << "  к" << number << ": ";
    for (const auto& unit : units) {
        cout << unit->getName() << " ";
    }
    cout << "(" << len /*units.size()*/ << ")" << endl;
}

void Team::move0(Team& enemies) {
    if (len == 0 || enemies.len == 0) { return; } //Проверка на наличие воинов в команде

    int fullDamage = 0;
    int fullHealth = 0;
    bool copy = false;
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

    for (index = 0; index < len; index++) { //Ходят маги
        auto unit = units[index];
        if (unit->type == 'c') {
            for (int i = index - unit->lenUse; i < 1 + index + unit->lenUse; i++) { //Проверяем воинов рядом в зоне действия и ищем лёгкого
                if (i == index || i < 0 || i > len - 1) { continue; } //Проверка на выход массива
                if (!copy && units[i]->type == 'l') { //Если нашли Лёгкого воина рядом и раньше не находили
                    copy = unit->chanceUse * 10000 > rand() % 10000 ? true : false; //Прокаем шанс на копирование
                }
            }
            if (copy) { //Копируем и вставляем в случае удачи
                auto position = units.begin() + index;
                units.insert(position + rand() % 2, make_shared<LowUnit>()); //Вставка перед или после позиции мага
                len++;
                index++;
            }
            copy = false;
        }
    }
    index = 0;

    //Удаление бойца
    if (!enemies.units[0]->getHealth()) { // 0 => воин умер, иначе любое ненулевое значение => воин жив
        enemies.units.erase(enemies.units.begin());
        enemies.len--;
    }
}
