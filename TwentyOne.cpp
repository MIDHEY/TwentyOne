#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iso646.h>
#include <thread>
#include <chrono>

int menuOption() {
    char menuOption[1000];
    std::cout << "==========================\n     1. Начать игру\n     2. Выход\n";
    int menuReturn;
    std::cout << "Выберите пункт: ";
    std::cin >> menuOption;
    std::cout << "==========================\n";
    if (strlen(menuOption) == 1 and (menuOption[0] == '1' or menuOption[0] == '2')) {
        menuReturn = atoi(menuOption);
    }
    else {
        menuReturn = 404;
    }
    return menuReturn;
}
int gameMenu(int menu) {
    menu = menuOption();
    while (menu == 404)
    {
        std::cout << "Вы ввели не верный пункт в меню. Введите верный пункт.\n";
        system("pause");
        system("cls");
        menu = menuOption();
    }
    return menu;
}
int getRandomNumber()
{
    int number = 6 + rand() % 4;
    return number;
}
int getCard() {
    int number = getRandomNumber();
    int procentOfCard = rand() % 100;
    int card = 0;
    int points = 0;
    bool selOfPoints = false;
    if (procentOfCard > 0 and procentOfCard <= 7) {
        card = 1;
    }
    else if (procentOfCard > 7 and procentOfCard <= 20) {
        card = 2;
    }
    else if (procentOfCard > 20 and procentOfCard <= 40) {
        card = 3;
    }
    else if (procentOfCard > 40 and procentOfCard <= 60) {
        card = 4;
    }
    else {
        card = 5;
    }
    switch (card)
    {
    case 1:
        std::cout << "Вам выпал Туз, выберите количество очков (1 или 11):";
        int chace;
        while (selOfPoints == 0) {
            std::cin >> chace;
            if (chace == 1) {
                points = 1;
                selOfPoints = 1;
            }
            else if (chace == 11) {
                points = 11;
                selOfPoints = 1;
            }
            else {
                std::cout << "Выберите верное количество очков";
            }
        }
        break;
    case 2:
        std::cout << "Вам выпал Король (4 очка)\n";
        points = 4;
        break;
    case 3:
        std::cout << "Вам выпала Дама (3 очка)\n";
        points = 3;
        break;
    case 4:
        std::cout << "Вам выпал Валет (2 очка)\n";
        points = 2;
        break;
    case 5:
        std::cout << "Вам выпала карта в " << number << " очка(ов)\n";
        points = number;
        break;
    default:
        break;
    }
    return points;
}
bool checkFail(int points) {
    return (points > 21);
}
int playerChoiceCheck() {
    bool playerChoiceCheck = false;
    char playerChoiceChar[1000];
    int playerChoice = 0;
    while (playerChoiceCheck == false) {
        std::cin >> playerChoiceChar;
        playerChoice = atoi(playerChoiceChar);
        bool playerChoiceCheck = (playerChoice == 2 or playerChoice == 1) ? true : false;
        if (!playerChoiceCheck)
        {
            std::cout << "Введите верный пункт меню: ";
        }
        else {
            return playerChoice;
        }
    }
    return playerChoice;
}
int playerChoice(bool fail, int points, int &count) {
    if (!fail) {
        std::cout << "\n**************************\nХотите добавить карты?\n1. Вытянуть еще одну карту\n2. Оставить данную колоду\n";
        std::cout << "Ваш выбор: ";
        int playerChoice = playerChoiceCheck();
        if (playerChoice == 1)
        {
            std::cout << std::endl;
            points = getCard();
            count--;
            return points;
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}
int getEnemyCard(int actuallyPoints) {
    int number = getRandomNumber();
    int procentOfCard = rand() % 100;
    int card = 0;
    int points = 0;
    bool selOfPoints = false;
    if (procentOfCard > 0 and procentOfCard <= 7) {
        card = 1;
    }
    else if (procentOfCard > 7 and procentOfCard <= 20) {
        card = 2;
    }
    else if (procentOfCard > 20 and procentOfCard <= 40) {
        card = 3;
    }
    else if (procentOfCard > 40 and procentOfCard <= 60) {
        card = 4;
    }
    else {
        card = 5;
    }
    switch (card)
    {
    case 1:
        int chace;
        if (actuallyPoints + 11 <= 21)
        {
            points = 11;
        }
        else {
            points = 1;
        }
        break;
    case 2:
        points = 4;
        break;
    case 3:
        points = 3;
        break;
    case 4:
        points = 2;
        break;
    case 5:
        points = number;
        break;
    default:
        break;
    }
    return points;

}
int enemyChoice(bool fail,int points, int &count) {
    if (!fail) {
        int possiblePoints = getEnemyCard(points);
        if (points >=17 and points < 21)
        {
            int random = rand() % 10;
            if (random <=3)
            {
                count--;
                return possiblePoints;
            }
            else {
                return 0;
            }
        }
        else if (points < 17){
            count--;
            return possiblePoints;
        }
    }
    else {
        return 0;
    }
}
bool checkOver(int *points, int countOfRounds, bool *fails) {
    //Проверка на проигрыш соперников
    int countOfFails = 0;
    int numberOfTrue = 0;
    for (int i = 0; i < 3; i++)
    {
        if (fails[i]==1) countOfFails++;
    }
    if (countOfFails == 2)
    {
        int numberOfTrue = 0;
        for (int i = 0; i < 3; i++)
        {
            if (fails[i] != 1) numberOfTrue = i;
        }
        switch (fails[numberOfTrue])
        {
        case 0:
            std::cout << "\n\nВы побеждаете набрав " << points[0] << " очка(ов)\nЭнди проигрывает набрав " << points[1] << " очка(ов)\nДжон проигрывает набрав " << points[2] << " очка(ов)\n";
            break;
        case 1:
            std::cout << "\n\nВы проигрываете набрав " << points[0] << " очка(ов)\nЭнди побеждает набрав " << points[1] << " очка(ов)\nДжон проигрывает набрав " << points[2] << " очка(ов)\n";
            break;
        case 2:
            std::cout << "\n\nВы проигрываете набрав " << points[0] << " очка(ов)\nЭнди проигрывает набрав " << points[1] << " очка(ов)\nДжон побеждает набрав " << points[2] << " очка(ов)\n";
            break;
        default:
            break;
        }
        return false;
    }
    //Проверка на победу
    int countOfRes = 0;
    int numberOfRes = 5;
    for (int i = 0; i < 3; i++)
    {
        if (points[i]==21)
        {
            countOfRes++;
            numberOfRes = i;
        }
    }
    if (countOfRes == 1)
    {
        switch (numberOfRes)
        {
        case 0:
            std::cout << "\n\nВы побеждаете набрав 21 очко\nЭнди проигрывает набрав " << points[1] << " очка(ов)\nДжон проигрывает набрав" << points[2] << " очка(ов)";
            break;
        case 1:
            std::cout << "\n\nВы проигрываете набрав " << points[0] << " очка(ов)\nЭнди побеждает набрав 21 очко\nДжон проигрывает набрав " << points[2] << " очка(ов)\n";
            break;
        case 2:
            std::cout << "\n\nВы проигрываете набрав " << points[0] << " очка(ов)\nЭнди проигрывает набрав " << points[1] << " очка(ов)\nДжон побеждает набрав 21 очко\n";
            break;
        default:
            break;
        }
        return false;
    }
    //Проверка на раунды
    if (countOfRounds < 0)
    {
        int max = points[0];
        int numOfMax = 0;
        int countOfMax = 0;
        for (int i = 0; i < 3; i++)
        {
            if (points[0] > max)
            {
                numOfMax = i;
                max = points[i];
            }
        }
        for (int i = 0; i < 3; i++)
        {
            if (points[i] == max)
            {
                countOfMax++;
            }
        }
        if (countOfMax==1)
        {
            switch (numOfMax)
            {
            case 0:
                std::cout << "\n\nВы побеждаете набрав " << points[0] << " очка(ов)\nЭнди проигрывает набрав " << points[1] << " очка(ов)\nДжон проигрывает набрав " << points[2] << " очка(ов)\n";
                break;
            case 1:
                std::cout << "\n\nВы проигрываете набрав " << points[0] << " очка(ов)\nЭнди побеждает набрав " << points[1] << " очка(ов)\nДжон проигрывает набрав " << points[2] << " очка(ов)\n";
                break;
            case 2:
                std::cout << "\n\nВы проигрываете набрав " << points[0] << " очка(ов)\nЭнди проигрывает набрав " << points[1] << " очка(ов)\nДжон побеждает набрав " << points[2] << " очка(ов)\n";
                break;
            default:
                break;
            }
        }
        else {
            std::cout << "\n\nПобедила дружба!\n";
        }
        return false;
    } 
    return true;
}
void printPoints(bool pFail, int pPoints, bool aFail, int aPoints, bool jFail, int jPoints, bool progress, int count, int countOfRounds) {
    if ((pFail != 1 or aFail != 1 or jFail != 1) and progress == true) {
        if (pFail == 1)
        {
            std::cout << "Вы проиграли набрав " << pPoints << " очка(ов)\n";
        }
        else {
            std::cout << "У вас " << pPoints << " очка(ов)\n";
        }
        if (aFail == 1) {
            std::cout << "Энди проиграл набрав " << aPoints << " очка(ов)\n";
        }
        else {
            std::cout << "У Энди " << aPoints << " очка(ов)\n";
        }
        if (jFail == 1) {
            std::cout << "Джон проиграл набрав " << jPoints << " очка(ов)\n";
        }
        else {
            std::cout << "У Джона " << jPoints << " очка(ов)\n\n";
        }
        std::cout << "На столе осталось " << count << " карт(а)\nОсталось " << countOfRounds << " раунд(а)\n";
    }
}


int main()
{
    setlocale(LC_ALL, "ru");
    srand(time(NULL));
    int option = 0;
    do
    {
        option = gameMenu(option);
        if (option == 2)
        {
            std::cout << "Прощайте!";
            continue;
        }
        bool gameProgress = 1;
        int points[3] = { 0,0,0 };
        bool fails[3] = { 0,0,0 };
        int countOfCards = 36;
        int countOfRounds = 2 + rand() % 10;
        std::cout << "В игре будет сыграно " << countOfRounds << " раунда(ов)\n";
        std::cout << "Игра началась, вы тяните первую карту\n";
        points[0] = getCard();
        for (int i = 1; i < 3; i++)
        {
            points[i] = getEnemyCard(points[i]);
        }
        std::cout << "У Энди " << points[1] << " очка(ов). Джон вытянул карту и теперь у него " << points[2] << " очка(ов)\n";
        countOfRounds--;
        while (gameProgress)
        {
            points[0] += playerChoice(fails[0], points[0], countOfCards);
            fails[0] = checkFail(points[0]);
            for (int i = 1; i < 3; i++)
            {
                points[i] += enemyChoice(fails[i], points[i], countOfCards);
                fails[i] = checkFail(points[i]);
            }
            printPoints(fails[0], points[0], fails[1], points[1], fails[2], points[2], gameProgress, countOfCards, countOfRounds);
            countOfRounds--;
            gameProgress = checkOver(points, countOfRounds, fails);
        }
        system("pause");
        system("cls");
    } while (option != 2);
    return 0;
}