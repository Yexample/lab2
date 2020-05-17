#include <iostream>
#include <cmath>
#include <windows.h>
#include <iomanip>
#include <cctype>
#include <random>
#include <cstdlib>
#include <algorithm>

#define DOT '.'
#define MINUS '-'

using namespace std;

float checkinput (string call);
int checkint (string call);

int main() {

    SetConsoleOutputCP(CP_UTF8);

    int n;
    float a, b, Yi, U, amin, amax, bmin, bmax, da, db;

    bool aClear = false;
    bool bClear = false;
    bool daClear = false;
    bool dbClear = false;

    string call = "Введите amin = ";
    do {
        amin = checkinput(call); // Ввод и проверка исходных значений
        call = "\nВведите amax = ";
        amax = checkinput(call);
        if (amin <= amax)
            aClear = true;
    } while (aClear == false );
    do {
        call = "\nВведите bmin = ";
        bmin = checkinput(call);
        call = "\nВведите bmax = ";
        bmax = checkinput(call);
        if (bmin <= bmax)
            bClear = true;
    } while (bClear == false );
    do {
        call = "\nВведите da = ";
        da = checkinput(call);
        if ((da <= amax - amin) || (amax - amin == 0))
            daClear = true;
    } while (daClear == false);
    do {
        call = "\nВведите db = ";
        db = checkinput(call);
        if ((db <= bmax - bmin) || (bmax - bmin == 0))
            dbClear = true;
    } while (dbClear == false);
    call = "\nВведите n = ";
    n = checkint (call);

    string header[5] = {"a", "b", "i", "Yi", "U"}; // Шапка таблицы

    for (int i = 0; i < 5; i++)
        cout << setw(15) << header[i];


    vector <float> output;
    vector <float> function;

    for (a = amin; a <= amax; a += da) {
        for (b = bmin; b <= bmax; b += db) {
            for (int i = 1; i <= n; i++) {
                output.push_back(a);
                output.push_back(b);
                output.push_back(i);
                Yi = a > b ? ((i + 1.0) * pow((2 * a + b * i), 3.0/2.0) / (pow((b - a), 2.0) + a * i + pow(i, 2.0))) :
                     ((i - 1.0) * pow((2 * b + a * i), 3.0/2.0) / (pow((b - a), 2.0) + a * i + pow(i, 2.0)));
                output.push_back(Yi);
            }
        }
    }

    float yi;
    float A;

    for (int i = 0; i < output.size(); i += 4) {
        yi = output[i + 3];
        A = output[i];
        U = pow((pow(yi, 2.0) + pow(A, 2.0)), 1.0/2.0);
        function.push_back(U);
    }

    float resultU = *min_element(function.begin(), function.end()); // Функция U, которую требуется вычислить в задании'

    int k = 0; // номер элемента верктора output
    int counta = 0;
    int countb = 0;
    int counti = 0;

    cout << endl;

    for (a = amin; a <= amax; a += da) {
        for (b = bmin; b <= bmax; b += db) {
            for (int i = 1; i <= n; i++) {
                cout << fixed
                     << setprecision(3)
                     << "\n"
                     << setw(18)
                     << output[k]
                     << fixed
                     << setprecision(3)
                     << setw(15)
                     << output[k+1]
                     << fixed
                     << setprecision(3)
                     << setw(13)
                     << output[k+2];
                if (isnan(output[k+3])) {
                    cout << fixed
                         << setprecision(3)
                         << setw(15)
                         << "*";
                }
                else {
                    cout << fixed
                         << setprecision(3)
                         << setw(17)
                         << output[k + 3];
                }
                if (isnan(resultU)) {
                    cout << fixed
                         << setprecision(3)
                         << setw(14)
                         << "*"
                         << "\t";
                }
                else {
                    cout << fixed
                         << setprecision(3)
                         << setw(15)
                         << resultU
                         << "\t";
                }
                if (a <= amax)
                    counta ++;
                if (b <= bmax)
                    countb ++;
                if (i <= n)
                    counti ++;
                k += 4;
            }
        }
    }

    cout << endl;

    output.clear();
    function.clear();

    char rerun;
    cout << "Would you like to run the program again? (Y/N) "; // Запрос на повторный запуск
    cin >> rerun;

    if (rerun == 'y' or rerun == 'Y')
    {
        main();
    }
    else
        system("pause");
}

///////// FUNCTIONS

float checkinput (string call) {
    string input;
    int count = 0; // счетчик цифр
    int count_dot = 0;
    int count_minus = 0;
    bool flag = true;
    bool flag_dot = false;
    bool flag_minus = false;
    bool correct = false;

    do {
        cout << call;
        cin >> input;
        for (int i = 0; i < (int) input.length(); i++) {
            if (input[i] == DOT) {
                count_dot++;
                flag_dot = true;
            }
            if (input[i] == MINUS) {
                flag_minus = true;
                count_minus++;
            }
            if (((!isdigit(input[i])) && (!flag_dot) && (!flag_minus)) || (count_dot >= 2) || (count_minus >= 2)) {
                cout << "Введено не число, попробуйте еще раз" << endl;
                cin.ignore(10000, '\n');
                flag = true;
                break;
            } else
                count++;
        }
        if ((((count == (int) input.length()) && (atof(input.c_str()) > -9223372036854775808.0) &&
              (atoi(input.c_str()) < 9223372036854775807.0))) || (count_minus == 1) &&
                                                                 (((int(count + 1) == (int) input.length()) &&
                                                                   (atof(input.c_str()) > -9223372036854775808.0) &&
                                                                   (atoi(input.c_str()) < 9223372036854775807.0)))) {
            correct = true;
        } else if (flag) {
            correct = false;
        }
    } while (correct == false);

    float floatInput = stof(input);

    return floatInput;

}

int checkint (string call) {

    string str;
    bool flag = true;
    int count = 0;
    bool flag_dot = false;
    bool correct = false;

    do {
        cout << call;
        cin >> str;
        for (int i = 0; i < (int) str.length(); i++) {
            if (str[i] == DOT) {
                flag_dot = true;
            }
            if (((!isdigit(str[i])) || (flag_dot))) {
                cout << "Ошибка, введите целое число" << endl;
                cin.ignore(10000, '\n');
                flag = true;
                break;
            }
            else
                count++;
        }
        if ((((count == (int) str.length()) && (atoi(str.c_str()) > 0.0)))) {
            correct = true;
        }
        else if (flag) {
            correct = false;
        }
    } while (correct == false);

    int integerInput = stoi(str);
    return integerInput;
}
