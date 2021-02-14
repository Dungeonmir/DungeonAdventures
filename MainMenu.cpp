#include <iostream>
#include <cstdlib> // дл€ exit()

using namespace std;

// ¬ывести меню пользователю и вернуть номер варианта
int prompt_menu_item()
{
    // ¬ыбранный вариант меню
    int variant;
    cout << "1.Play\n" << endl;
    cout << "2.Settings\n" << endl;
    cout << "3.Load Game\n" << endl;
    cout << "4.Exit\n" << endl;
    cout << ">>> ";
    cin >> variant;
    return variant;
}

int main2(int argc, char* argv[])
{
    int variant = prompt_menu_item();

    switch (variant) {
    case 1:
        cout << "GAME" << endl;
        break;
    case 2:
        cout << "SETTINGS" << endl;
        break;
    case 3:
        cout << "SETTINGS" << endl;
        break;
    case 4:
        cout << "EXIT" << endl;
        break;
    }
    return 0;
}

