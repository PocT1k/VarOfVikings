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
    cout << "  к" << number << ": ";
    for (const auto& unit : units) {
        switch (unit->type) {
        case 'l':
            cout << "Лёгкий" << " "; break;
        case 'm':
            cout << "Средний" << " "; break;
        case 'h':
            cout << "Тяжёлый" << " "; break;
        case 'a':
            cout << "Лучник" << " "; break;
        case 'p':
            cout << "Хиллер" << " "; break;
        case 'c':
            cout << "Копимаг" << " "; break;
        default:
            break;
        }
    }
    cout << "(" << len /*units.size()*/ << ")" << endl;
}

void Team::move(Team& enemies) {
    if (len == 0 || enemies.len == 0) { return; } //Проверка на наличие воинов в команде

    int fullDamage = 0;
    int fullHealth = 0;
    bool copy = false;
    int index = 0;

    for (auto unit : units) { //Первый фигарит первого
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
            for (int i = index - unit->lenUse; i < 1 + index + unit->lenUse; i++) { //Проверяем воинов рядом и ищем лёгкого
                if (i == index || i < 0 || i > len - 1) { continue; } //Проверка на выход массива
                if (!copy && units[i]->type == 'l') { //Если нашли Лёгкого воина рядом и раньше не находили
                    copy = unit->chanceUse * 10000 > rand() % 10000 ? true : false; //Прокаем шанс на копирование
                }
            }
            if (copy) { //Копируем и вставляем в случае удачи
                auto position = units.begin() + index;
                units.insert(position + (rand() % 2 ? 1 : 0), make_shared<LowUnit>()); //Вставка перед или после мага
                len++;
                index++;
            }
            copy = false;
        }
    }
    index = 0;

    //Удаление бойца
    if (!enemies.units[0]->getHealth()) {
        enemies.units.erase(enemies.units.begin());
        enemies.len--;
    }
}
