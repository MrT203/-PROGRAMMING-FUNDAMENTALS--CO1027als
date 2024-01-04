#ifndef awakened_h
#define awakened_h

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;


// khai báo h?ng s? hàng và c?t
const int ROWS = 10;
const int COLS = 10;


bool isValidDateTime(int DD, int MM, int hh, int mm) {
    // Check the validity of month
    if (MM < 1 || MM > 12) {
        return false;
    }
    
    // Check the validity of day
    int daysInMonth[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // Number of days in each month (leap year)
    int days = daysInMonth[MM - 1]; // Get the number of days in the corresponding month
    if (DD < 1 || DD > days) {
        return false;
    }
    
    // Check the validity of hour
    if (hh < 0 || hh > 23) {
        return false;
    }
    
    // Check the validity of minute
    if (mm < 0 || mm > 59) {
        return false;
    }
    
    return true;
}

int invalidTime(const string& schedule) {
    // Complete this function to gain point
    ifstream inputFile(schedule);
    int n;
    string tmp;
    for (int i = 0; i < 4; i++) inputFile >> tmp;
    for (int i = 0; i < 3; i++){
        if (!isdigit(tmp[i])){
            
            return -1;
        }
    }
    n = stoi(tmp);
    if (n <= 0 && n > 999) return -1;
    // xu li tau
    int count = 0;
    string line;
    while (getline(inputFile, line)) {
        size_t commaPos = line.find(",");
        size_t dashPos = line.find("-");

        if (commaPos == string::npos || dashPos == string::npos) {
            continue;
        }

        string shipName = line.substr(0, commaPos);
        string arrivalTime = line.substr(commaPos + 2, dashPos - commaPos - 3);
        string departureTime = line.substr(dashPos + 2);
        
        // Replace '?' with '1' in arrivalTime and departureTime
        for (int i = 0; i < arrivalTime.length(); i++)
        {
            if (arrivalTime[i] == '?')
            {
                if (i == 0){
                   if (arrivalTime[1] == '0'){
                        arrivalTime[0] = '1';
                    }
                    else if (arrivalTime[1] == '?'){
                        arrivalTime[0] = '0';
                        arrivalTime[1] = '1';
                    }
                    else {
                        arrivalTime[0] = '0';
                    }
                }
                if (i == 1){
                    if (arrivalTime[0] == '0'){
                        arrivalTime[1] = '1';
                    }
                    else {
                        arrivalTime[1] = '0';
                    }
                }
                    
                if (i == 3){
                    if (arrivalTime[4] == '0'){
                        arrivalTime[3] = '1';
                    }
                    else if (arrivalTime[4] == '?'){
                        arrivalTime[3] = '0';
                        arrivalTime[4] = '1';
                    }
                    else if (arrivalTime[4] == '2'){
                        arrivalTime[3] = '1';
                    }
                    else {
                        arrivalTime[3] = '0';
                    }
                }
                if (i == 4){
                    if (arrivalTime[3] == '0'){
                        arrivalTime[4] = '1';
                    }
                    else {
                        arrivalTime[i] = '0';
                    }
                }
                    
                if (i > 5)
                    arrivalTime[i] = '1';
            }

            if (departureTime[i] == '?')
            {
                if (i == 0){
                   if (departureTime[1] == '0'){
                        departureTime[0] = '1';
                    }
                    else if (departureTime[1] == '?'){
                        departureTime[0] = '0';
                        departureTime[1] = '1';
                    }
                    else {
                        departureTime[0] = '0';
                    }
                }
                    
                 if (i == 1){
                    if (departureTime[0] == '0'){
                        departureTime[1] = '1';
                    }
                    else {
                        departureTime[1] = '0';
                    }
                }
                if (i == 3){
                    if (departureTime[4] == '0'){
                        departureTime[3] = '1';
                    }
                    else if (departureTime[4] == '?'){
                        departureTime[3] = '0';
                        departureTime[4] = '1';
                    }
                    else if (departureTime[4] == '2'){
                        departureTime[3] = '1';
                    }
                    else {
                        departureTime[3] = '0';
                    }
                }
               if (i == 4){
                    if (departureTime[3] == '0'){
                        departureTime[4] = '1';
                    }
                    else {
                        departureTime[i] = '0';
                    }
                }
                if (i > 5)
                    departureTime[i] = '1';
            }
        }
        
        // cout << arrivalTime  <<  " - " << departureTime << endl;
        
        // Extract DD, MM, hh, mm from arrivalTime
        string DDa = arrivalTime.substr(0, 2);
        string MMa = arrivalTime.substr(3, 2);
        string hha = arrivalTime.substr(6, 2);
        string mma = arrivalTime.substr(9, 2);
        string DDd = departureTime.substr(0, 2);
        string MMd = departureTime.substr(3, 2);
        string hhd = departureTime.substr(6, 2);
        string mmd = departureTime.substr(9, 2);
            
        bool check = isValidDateTime(stoi(DDa), stoi(MMa), stoi(hha), stoi(mma)) 
                && isValidDateTime(stoi(DDd), stoi(MMd), stoi(hhd), stoi(mmd));
        if (check){
            // cout << shipName << ' ' << arrivalTime << " - " << departureTime << endl;
            count++;
        } 
        // else {
        //     cout << "False : " << endl;
        //   cout << shipName << ' ' << arrivalTime << " - " << departureTime << endl;

        // }

    }
   
    if (count > 0) return count;
    return -1;
}


int calculateTimeDifference(int DD, int MM, int hh, int mm)
{
    if (MM < 1 || MM > 12 || DD < 1 || DD > 31 || hh < 0 || hh > 23 || mm < 0 || mm > 59)
    {
        // Th?i di?m không h?p l?
        return -1;
    }

    // S? ngày trong m?i tháng trong nam 1864
    int daysInMonth[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Chuy?n d?i thông tin ngày, tháng, gi? và phút thành s? phút
    int referenceTime = 0; // Th?i gian tham chi?u là 00:00 ngày 1/1/1864
    int targetTime = 0;

    for (int i = 1; i < MM; i++)
    {
        targetTime += daysInMonth[i - 1] * 24 * 60;
    }

    targetTime += ((DD)*24*60 + hh*60 + mm);
    
    // Tính kho?ng th?i gian (theo phút)
    int timeDifference = targetTime - referenceTime;

    return timeDifference;
}

int rightTime(int DDa, int MMa, int hha, int mma, int DDd, int MMd, int hhd, int mmd)
{

    // Ki?m tra tính h?p l? c?a ngày tháng
    if (!isValidDateTime(DDa, MMa, hha, mma))
    {
        return -1;
    }
    if (!isValidDateTime(DDd, MMd, hhd, mmd))
    {
        return -1;
    }
    // cout << " Ðu?c  phép  tính" << endl;
    // Ki?m tra tính h?p l? c?a thông tin th?i gian d?n và r?i b?n
    if (MMa > MMd)
        return -1;
    if (MMa == MMd && DDa > DDd)
        return -1;
    if (MMa == MMd && DDa == DDd && hha > hhd)
        return -1;
    if (MMa == MMd && DDa == DDd && hha == hhd && mma > mmd)
        return -1;
        
    // cout << DDd << ' ' << MMd << ' ' << hhd << ' ' << mmd << endl;
    // Tính th?i gian luu trú t?i b?n
    // cout  << calculateTimeDifference(DDd, MMd, hhd, mmd) <<  ' '  << calculateTimeDifference(DDa, MMa, hha, mma) << endl;
    int duration = calculateTimeDifference(DDd, MMd, hhd, mmd) - calculateTimeDifference(DDa, MMa, hha, mma);
    
    // Tr? v? th?i gian luu trú
    return duration;
}

string longestDuration(const string &schedule)
{
    // Complete this function to gain point
    // return "";
    ifstream inputFile(schedule);
    int n;
    string tmp;
    for (int i = 0; i < 4; i++)
        inputFile >> tmp;
    for (int i = 0; i < 3; i++)
    {
        if (!isdigit(tmp[i]))
        {
            return "";
        }
    }
    n = stoi(tmp);
    if (n <= 0 && n > 999)
        return "";
    string line;
    string res = "";
    int timeMax = 0;
    while (getline(inputFile, line))
    {
        size_t commaPos = line.find(",");
        size_t dashPos = line.find("-");

        if (commaPos == string::npos || dashPos == string::npos)
        {
            continue;
        }

        string shipName = line.substr(0, commaPos);
        string arrivalTime = line.substr(commaPos + 2, dashPos - commaPos - 3);
        string departureTime = line.substr(dashPos + 2);
        
        
        size_t questionPos = line.find("?");
        if (questionPos == string::npos)
        {
            // cout <<arrivalTime << ' ' << departureTime << endl;
            int DDa = stoi(arrivalTime.substr(0, 2));
            int MMa = stoi(arrivalTime.substr(3, 2));
            int hha = stoi(arrivalTime.substr(6, 2));
            int mma = stoi(arrivalTime.substr(9, 2));
            int DDd = stoi(departureTime.substr(0, 2));
            int MMd = stoi(departureTime.substr(3, 2));
            int hhd = stoi(departureTime.substr(6, 2));
            int mmd = stoi(departureTime.substr(9, 2));

            // cout << DDa << ' ' << MMa << ' ' << hha << ' ' << mma <<  endl;
            // cout << DDd << ' ' << MMd << ' ' << hhd << ' ' << mmd <<  endl;

            int currentTime = rightTime(DDa, MMa, hha, mma, DDd, MMd, hhd, mmd);
            if (currentTime > 0 && currentTime >= timeMax)
            {
                res = shipName;
                timeMax = currentTime;
            }
        }
        // N?u trong ngày tháng gi? phút ch?a d?u ?
        else
        {
            // cout << shipName <<  ' ' << arrivalTime << " - " << departureTime  << endl; 
            while (arrivalTime.find('/') != string::npos)
            {
                int pos = arrivalTime.find('/');
                arrivalTime[pos] = ':';
            }
            while (departureTime.find('/') != string::npos)
            {
                int pos = departureTime.find('/');
                departureTime[pos] = ':';
            }

            //  cout << arrivalTime << " @ _ @ " << departureTime << endl;

            // xu li ngay thang den arrivalTime
            {
                // xu li gio phut den
                for (int i = 5; i < arrivalTime.length(); i++)
                {
                    if (arrivalTime[i] == '?')
                    {
                        arrivalTime[i] = '0';
                    }
                }
                
                // x? lí ngày d?n
                // n?u ngày c? d?nh xx
                if (arrivalTime[0] != '?' && arrivalTime[1] != '?'){
                    // tháng khong c? d?nh 
                    if (arrivalTime[3] == '?' && arrivalTime[4] == '?'){
                        arrivalTime[3] = '0';
                        arrivalTime[4] = '1';
                    }
                    else if (arrivalTime[3] == '?' && arrivalTime[4] != '?'){
                        if (arrivalTime[4] == '0'){
                            arrivalTime[3] = '1';
                        }
                        else if (arrivalTime[4] == '1'){
                            arrivalTime[3] = '0';
                        }
                        else if (arrivalTime[4] == '2'){
                            // thang 12 or thang 2
                            // n?u ngày nho hon = 29 -> thang 2
                            if (stoi(arrivalTime.substr(0,2)) <= 29){
                                arrivalTime[3] = '0';
                            }
                            else {
                                arrivalTime[3] = '1';
                            }
                        }
                        // n?u ?x x >= 3 -> ? = 0
                        else {
                            arrivalTime[3] =  '0';
                        }
                        
                    }
                    else if (arrivalTime[3] != '?' && arrivalTime[4] == '?'){
                        if (arrivalTime[3] == '0'){
                            arrivalTime[4] = '1';
                        }
                        // 1? -> 10 11 12 -> chon 10
                        else if (arrivalTime[3] == '1'){
                            arrivalTime[4] = '0';
                        }
                        // 2? -> l?i cho = 0;
                        else {
                            arrivalTime[4] =  '0';
                        }
                    }
                    // xx
                    else {
                        // n?u ngày tháng c? d?nh k làm gì;
                    }
                }
                // ?x:
                else if (arrivalTime[0] == '?' && arrivalTime[1] != '?'){
                    if (arrivalTime[1] == '0'){
                        arrivalTime[0] = '1';
                    }
                    else {
                        arrivalTime[0] = '0';
                    }
                }
                // x?
                else if (arrivalTime[0] != '?' && arrivalTime[1] == '?'){
                    //0? -> 01
                    if  (arrivalTime[0]  == '0'){
                        arrivalTime[1] = '1';
                    }
                    // 1? -> 10
                    else {
                        arrivalTime[1] = '0';
                    }
                }
                // ngày ??
                else {
                    arrivalTime[0] = '0';
                    arrivalTime[1] = '1';
                }
                
                // x? lí tháng d?n
                // n?u tháng c? d?nh & ngày dã du?c xuwrr lí -> b? qua
                if (arrivalTime[3] == '?' && arrivalTime[4] == '?'){
                    arrivalTime[3] = '0';
                    arrivalTime[4] = '1';
                }
                //  x?
                else if (arrivalTime[3] != '?' && arrivalTime[4] == '?'){
                    if (arrivalTime[3] == '0'){
                        arrivalTime[4] = '1';
                    }
                    else if (arrivalTime[3] = '1'){
                        arrivalTime[4] = '0';
                    }
                    else {
                        // TH l?i
                        arrivalTime[4]  = '0';
                    }
                }
                else if (arrivalTime[3] == '?' && arrivalTime[4] != '?'){
                    if (arrivalTime[4] == '0'){
                        arrivalTime[3] = '1';
                    }
                    else {
                        arrivalTime[3] = '0';
                    }
                }
                // tháng c? d?nh dã du?c x? lí
                else {
                    
                }
                // n?u ngày không c? dinh: ch?a d?u ?
                // if (arrivalTime[0] == '?')
                // {
                //     if (arrivalTime[1] == '?')
                //     {
                //         arrivalTime[0] = '0';
                //         arrivalTime[1] = '1';
                //     }
                //     else if (arrivalTime[1] == '0')
                //     {
                //         arrivalTime[0] = '1';
                //     }
                //     else
                //     {
                //         arrivalTime[0] = '0';
                //     }
                // }
                // else
                // {
                //     if (arrivalTime[0] == '0' && arrivalTime[1] == '?')
                //     {
                //         arrivalTime[1] = '1';
                //     }
                //     else if (arrivalTime[0] != '0' && arrivalTime[1] == '?')
                //     {
                //         arrivalTime[1] = '0';
                //     }
                // }

                // // xu li thang den
                // if (arrivalTime[3] == '?')
                // {
                //     if (arrivalTime[4] == '?')
                //     {
                //         arrivalTime[3] = '0';
                //         arrivalTime[4] = '1';
                //     }
                //     else if (arrivalTime[4] == '0')
                //     {
                //         arrivalTime[3] = '1';
                //     }
                //     else
                //     {
                //         arrivalTime[3] = '0';
                //     }
                // }
                // else
                // {
                //     if (arrivalTime[4] == '?')
                //     {
                //         if (arrivalTime[3] == '0')
                //         {
                //             arrivalTime[4] = '1';
                //         }
                //         else
                //         {
                //             arrivalTime[4] = '0';
                //         }
                //     }
                // }

                // debug ngay den
                //  cout << arrivalTime <<  " @-@ "  << endl;
            }
            
            {
                // xu li ngay thang di departure max
                // xu li thang di ?
                if (departureTime[3] == '?')
                {
                    if (departureTime[4] == '?')
                    {
                        departureTime[3] = '1';
                        departureTime[4] = '2';
                    }
                    else if (departureTime[4] == '0' ||  departureTime[4] == '2')
                    {
                        departureTime[3] = '1';
                    }
                    else if (departureTime[4] == '1')
                    {
                        if (departureTime[0] == '?' && departureTime[1] == '?'){
                            departureTime[0] = '3';
                            departureTime[1] = '0';
                            departureTime[3] = '1';
                        }
                        else if (departureTime[0] != '?' && departureTime[1] == '?'){
                            if (departureTime[0] == '0' || departureTime[0] == '1' || departureTime[0] == '2'){
                                departureTime[1] = '9';
                                departureTime[3] = '1';
                            }
                            else {
                                departureTime[1] = '0';
                                departureTime[3] = '1';
                            }
                        }
                        else if (departureTime[0] == '?' && departureTime[1] != '?'){
                            if (departureTime[1] == '0'){
                                departureTime[0] = '3';
                                departureTime[3]  = '1';
                            }
                            else {
                                departureTime[0] = '2';
                                departureTime[3] = '1';
                            }
                        }
                        // ngày c? d?nh
                        else {
                            if (stoi(departureTime.substr(0, 2)) <= 30){
                                departureTime[3] = '1';
                            }
                            else {
                                departureTime[3] = '0';
                            }
                        }
                        
                    }
                    else
                    {
                        departureTime[3] = '0';
                    }
                }
                // n?u departureTime[3] != ? - ?x
                else
                {
                    if (departureTime[4] == '?')
                    {
                        if (departureTime[3] == '0')
                        {
                            departureTime[4] = '9';
                        }
                        else
                        {
                            departureTime[4] = '2';
                        }
                    }
                }

                string month = departureTime.substr(3, 2);

                // xu li ngay di
                // n?u hàng ch?c khác ? và hàng don v? = ? : ex 0?
                if (departureTime[1] == '?' && departureTime[0] != '?')
                {
                    // n?u ngày t? 0-29
                    if (departureTime[0] == '0' || departureTime[0] == '1' || departureTime[0] == '2')
                    {
                        departureTime[1] = '9';
                    }
                    // n?u hàng ch?c l?n hon 2
                    else
                    {
                        if (month == "04" || month == "06" || month == "09" || month == "11")
                        {
                            departureTime[1] = '0';
                        }
                        else
                        {
                            departureTime[1] = '1';
                        }
                    }
                }
                else if (departureTime[1] != '?' && departureTime[0] == '?')
                {
                    // cout << "thuoc truong hop nay " << endl;
                    if (departureTime[1] == '0')
                    {
                        if (month == "02")
                        {
                            departureTime[0] = '2';
                        }
                        else
                        {
                            departureTime[0]  = '3';
                        }
                    }
                    else if (departureTime[1] == '1')
                    {
                        if (month == "02" || month == "04" || month == "06" || month == "09" || month == "11")
                        {
                            departureTime[0] = '2';
                        }
                        else
                        {
                            departureTime[0] = '3';
                        }
                    }
                    else
                    {
                        departureTime[0] = '2';
                    }
                }
                else if (departureTime[0] == '?' && departureTime[1] == '?')
                {
                    if (month == "02")
                    {
                        departureTime[0] = '2';
                        departureTime[1] = '9';
                    }
                    else if (month == "04" || month == "06" || month == "09" || month == "11")
                    {
                        departureTime[0] = '3';
                        departureTime[1] = '0';
                    }
                    else
                    {
                        departureTime[0] = '3';
                        departureTime[1] = '1';
                    }
                }
                // xu li gio
                if (departureTime[6] == '?')
                {
                    if (departureTime[7] == '?')
                    {
                        departureTime[6] = '2';
                        departureTime[7] = '3';
                    }
                    else if (departureTime[7] == '0' || departureTime[7] == '1' ||
                             departureTime[7] == '2' || departureTime[7] == '3')
                    {
                        departureTime[6] = '2';
                    }
                    else
                    {
                        departureTime[6] = '1';
                    }
                }
                else
                {
                    if (departureTime[7] == '?')
                    {
                        if (departureTime[6] == '0' || departureTime[6] == '1')
                        {
                            departureTime[7] = '9';
                        }
                        else
                        {
                            departureTime[7] = '3';
                        }
                    }
                }

                // xu li phut
                if (departureTime[9] == '?')
                {
                    departureTime[9] = '5';
                }

                if (departureTime[10] == '?')
                {
                    departureTime[10] = '9';
                }
                // debug ngay den

                //  cout << departureTime << endl;

                // cout << shipName << ' ' << arrivalTime << " - " << departureTime << endl;
                // cout << endl;
                // Tinh thoi gian
                int DDa = stoi(arrivalTime.substr(0, 2));
                int MMa = stoi(arrivalTime.substr(3, 2));
                int hha = stoi(arrivalTime.substr(6, 2));
                int mma = stoi(arrivalTime.substr(9, 2));
                int DDd = stoi(departureTime.substr(0, 2));
                int MMd = stoi(departureTime.substr(3, 2));
                int hhd = stoi(departureTime.substr(6, 2));
                int mmd = stoi(departureTime.substr(9, 2));


                int currentTime = rightTime(DDa, MMa, hha, mma, DDd, MMd, hhd, mmd);
                
                // cout << shipName << ": " << arrivalTime << " - " << departureTime << endl;
                // cout << DDa << ' ' << MMa << ' ' << hha << ' ' << mma <<  endl;
                // cout << DDd << ' ' << MMd << ' ' << hhd << ' ' << mmd <<  endl;
                
                // cout << currentTime << endl;
                if (currentTime > 0 && currentTime >= timeMax)
                {
                    res = shipName;
                    timeMax = currentTime;
                }
            }
        }
    }

    return res;
    return "";
}


// xoay map 180 d?
// Hàm d? xoay b?n d? 180 d?
void rotateMap180(char mp[ROWS][COLS]) {
    char tempMap[ROWS][COLS];

    // Sao chép b?n d? ban d?u sang b?n d? t?m th?i
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            tempMap[i][j] = mp[i][j];
        }
    }

    // Xoay b?n d? 180 d?
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            mp[i][j] = tempMap[ROWS - 1 - i][COLS - 1 - j];
        }
    }
}

void rotateDMap180(int dem[ROWS][COLS]) {
    int tempMap[ROWS][COLS];

    // Sao chép b?n d? ban d?u sang b?n d? t?m th?i
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            tempMap[i][j] = dem[i][j];
        }
    }

    // Xoay b?n d? 180 d?
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            dem[i][j] = tempMap[ROWS - 1 - i][COLS - 1 - j];
        }
    }
}
void saveSpecialPos(char mp[ROWS][COLS], int posx[], int posy[]){
    // Ð?c map và luu v? trí các kí t? d?c bi?t 
     // gan cac gia tri dac biet = -1
    for (int i = 0; i < COLS; i++){
            posx[i] = -1;
            posy[i] = -1;
    }
    int cntT = 0;
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            switch (mp[i][j]) {
            case 'S': {
                posx[0] = i; posy[0] = j;
                break;
            }
            case 'A': {
                posx[1] = i; posy[1] = j;
                break;
            }
            case 'R': {
                posx[2] = i; posy[2] = j;
                break;
            }
            case 'T': {
                cntT++;
                if (cntT == 1) {
                    posx[3] = i; posy[3] = j;
                } else {
                    posx[4] = i; posy[4] = j;
                }
                break;
            }
            case 'H': {
                posx[5] = i; posy[5] = j;
                break;
            }
            case 'P': {
                posx[6] = i; posy[6] = j;
                break;
            }
            case 'C': {
                posx[7] = i; posy[7] = j;
                break;
            }
            case 'L': {
                posx[8] = i; posy[8] = j;
                break;
            }
            case 'M': {
                posx[9] = i; posy[9] = j;
                break;
            }
            default: {
                // N?u không ph?i các ký t? trên, ti?p t?c vòng l?p
                continue;
            }
            }
        }
    }
}

bool investigateTemple(const string& map, const string& moveStyle,
    int stamina, int& outTime, string& outPath) {
    
    outTime = 0;
    // Complete this function to gain point
    int pointH = stamina/3;
    int thelucgoc = stamina;
    

    // 
    string move = moveStyle;
    ifstream inputMap(map);
    
    char mp[ROWS][COLS];
    // m?ng d?m s? l?n di qua m?t ô
    int demD[ROWS][COLS];
    // kh?i t?o m?ng d?m = 0;
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            demD[i][j] = 0;
        }
    }
    
    // m?ng luu b?n d? ban d?u và b?n d? khi m?t 1/3 stamina
    char originalMap[ROWS][COLS], pointHMap[ROWS][COLS];
    // m?ng luu các v? trí d?c bi?t
    int posx[10]; // 0-S, 1-A, 2-R, 3:4-T, 5-H, 6-P, 7-C, 8-L, 9-M
    int posy[10];
    // ki?m tra v? trí tí T1 và T2
    int posT = 3;
    int cntT = 0;
    
    // gan cac gia tri dac biet = -1
    for (int i = 0; i < COLS; i++){
            posx[i] = -1;
            posy[i] = -1;
    }
    // Ð?c map và luu v? trí các kí t? d?c bi?t 
    for (int i = 0; i < ROWS; i++){
        for (int j = 0; j < COLS; j++){
            inputMap >> mp[i][j];
            originalMap[i][j] =  mp[i][j];
            
            switch (mp[i][j]) {
            case 'S': {
                posx[0] = i; posy[0] = j;
                break;
            }
            case 'A': {
                posx[1] = i; posy[1] = j;
                break;
            }
            case 'R': {
                posx[2] = i; posy[2] = j;
                break;
            }
            case 'T': {
                cntT++;
                if (cntT == 1) {
                    posx[3] = i; posy[3] = j;
                } else {
                    posx[4] = i; posy[4] = j;
                }
                break;
            }
            case 'H': {
                posx[5] = i; posy[5] = j;
                break;
            }
            case 'P': {
                posx[6] = i; posy[6] = j;
                break;
            }
            case 'C': {
                posx[7] = i; posy[7] = j;
                break;
            }
            case 'L': {
                posx[8] = i; posy[8] = j;
                break;
            }
            case 'M': {
                posx[9] = i; posy[9] = j;
                break;
            }
            default: {
                // N?u không ph?i các ký t? trên, ti?p t?c vòng l?p
                continue;
            }
            }
        }
    }
    
    // ki?m tra các kí t? d?c bi?t
    for (int i = 0; i < COLS; i++){
        if (posx[i] < 0 || posx[i] >= ROWS){
            posx[i] = -1;
            posy[i] = -1;
        }
    }
    
    // x? lí map
    int size = moveStyle.length();
    int r = 0;
    int preI = posx[0], preJ = posy[0];
    int i = posx[0], j = posy[0];
    
    // Bi?n ki?m tra cho P dã d? 2 bu?c di chuy?n chua
    int countStep = 0;
    int checkP = 0;
    
    // bi?n t?m luu v? trí khi h?t 1/3 th? l?c
    int tempX1_3 = 0, tempY1_3 = 0;
    
    // m?ng d?m l?i  lúc 1/3 th? l?c
    int dem1_3[ROWS][COLS] = {0};
   
    // x? lí t?ng bu?c di chuy?n
    while(stamina > 0){
        
        // các công vi?c c?n làm t?i th?i di?m 1/3 stamina b? m?t
        if (thelucgoc-stamina  == pointH + 1){
            // luu l?i v? trí lúc h?t 1/3
            tempX1_3 = i; tempY1_3 = j;
            // cout << stamina << endl;  
            // cout << "Vi tri 1/3 " <<   i   <<  ' ' << j << endl;
            // luu l?i b?n d? lúc tiêu th? h?t 1/3 stamina  
            for (int i = 0; i < ROWS; i++){
                for (int j = 0; j < COLS; j++){
                    pointHMap[i][j] = mp[i][j];
                }
            }
            
            // luu l?i m?ng d?m lúc 1/3 th? l?c
            for (int i = 0; i < ROWS; i++){
                for (int j = 0; j < COLS; j++){
                    dem1_3[i][j] = demD[i][j];
                }
            }
        }
        
        
        //  th?c hi?n l?p l?i chu?i di chuy?n
        if (r >= size) r = 0;
        // kí t? c?a bu?c di chuy?n L - R  - U - D
        char step = move[r++];
        //move L , R , D, U
        if (step == 'U'){
            i--;
            if (i < 0){
                i = 9;
            }
        }
        else if (step == 'L'){
            j--;
            if (j < 0){
                j = 9;
            }
        }
        else if (step == 'R'){
            j++;
            if (j > 9){
                j = 0;
            }
        }
        else {
            i++;
            if (i > 9){
                i = 0;
            }
        }
        
        // Ki?m tra n?u chua du?c bình thu?c thì -1 m?i bu?c
        if (!checkP){
            stamina--;
        }
        else {
            countStep++;
            if (countStep == 2){
                stamina--;
                countStep = 0;
            }
        }
        // cout << thelucgoc-stamina <<  endl;
        // th?c hi?n các bu?c di chuy?n
        char c = mp[i][j];
        
        // tang th?i gian di chuy?n
        outTime++;
        
        // Debug:
        // cout << step <<  " :" <<  '[' << i << ", " << j << "] = " << c << endl; 
        // tang m?ng d?m
        demD[i][j]++;
        // cout << demD[i][j] << endl;
        
        if (demD[i][j] > 3){
            
            if(c != 'X'){
                outPath += (to_string(i) + ',' + to_string(j) + ';');
            }
            if (outPath[outPath.length() - 1] == ';'){
                outPath.pop_back();
            }
            return false;
        }
        
        // check
        switch(c){
            
            case 'S':{
                outPath += (to_string(i) + ',' + to_string(j) + ';');
                break;
            }
            case '0':
            {
                outPath += (to_string(i) + ',' + to_string(j) + ';');
                break;
            }
            // g?p bàn th?, k?t thúc 
            case 'A': 
            {
                outPath += (to_string(i) + ',' + to_string(j));
                if (outPath[outPath.length() - 1] == ';'){
                    outPath.pop_back();
                }
                return true;
                break;
            }
            // g?p v?t c?n, không th? di chuy?n vào nhung v?n tr? stamina
            case 'X': 
            {    
                i = preI; j = preJ;
                break;
            }
            // guong, d?o ngu?c chu?i di chuy?n
            case 'R': 
            {
                outPath += (to_string(i) + ',' + to_string(j) + ';');
                
                for (int i = 0; i < size/2; i++){
                    swap(move[i], move[size-1-i]);
                }
                break;
            }
            // c?a bí m?t, di chuy?n d?n c?a bí m?t còn l?i
            case 'T': 
            {
                outPath += (to_string(i) + ',' + to_string(j) + ';');
                // ki?m tra dang ? c?a d?u hay c?a sau
                // n?u c?a d?u d?ch d?n c?a sau
                if (i == posx[posT] && j == posy[posT]){
                    i = posx[posT + 1]; j = posy[posT + 1];   
                }
                // n?u c?a sau d?ch chuy?n d?n c?a d?u
                else {
                    i = posx[posT]; j = posy[posT];
                }
                break;
            }
            // g?p máy th?i gian, tr? v? th?i di?m 1/3 th? l?c, xóa các di?m dã di qua trong quá kh?
            case 'H': 
            {
                // ki?m tra xem dã tiêu th? du?c 1/3 th? l?c ban d?u chua
                if (thelucgoc-stamina >= pointH){ // dã tiêu th? hon 1/3 th? l?c
                    
                    // tr? v? map lúc 1/3  stamina b? tiêu th?
                    for (int i = 0;  i < ROWS; i++){
                        for (int j = 0; j < COLS; j++){
                            mp[i][j] = pointHMap[i][j];
                        }
                    }
                    
                    // c?p nh?p l?i m?ng d?m
                    for (int i = 0; i < ROWS; i++){
                        for (int j = 0; j < COLS; j++){
                            demD[i][j] = dem1_3[i][j];
                        }
                    }
                    
                    // gán l?i các giá tr? d?c bi?t
                    saveSpecialPos(mp, posx, posy);
                    // tr? i,j v? v? trí tiêu th? 1/3 th? l?c
                    // i = posx[0]; j = posy[0];
                    i = tempX1_3; j = tempY1_3;
                    // c?p nh?p l?i outpath t?i di?m 1/3 th? l?c
                      outPath += (to_string(i) + ',' + to_string(j) + ';');
                }
                else { // chua tiêu th? d? 1/3 th? l?c
                    
                    // tr? v? b?n d? ban d?u
                    for (int i = 0; i < 10; i++){
                        for (int j = 0; j < 10; j++){
                            mp[i][j] = originalMap[i][j];
                        }
                    }

                    // reset m?ng d?m v? 0
                    for (int i = 0; i < 10; i++){
                        for (int j = 0; j < 10; j++){
                            demD[i][j] = 0;
                        }
                    }
                    // gán l?i các giá tr? d?c bi?t
                    saveSpecialPos(mp, posx, posy);
                    // tr? i,j v? v? trí S ban d?u
                    i = posx[0]; j = posy[0];
                    // cap nhap l?i outpath là di?m d?u tiên
                    outPath += (to_string(i) + ',' + to_string(j) + ';');
                }
                break;
            }
            // g?p bình thu?c, 2 bu?c m?i gi?m 1 th? l?c
            case 'P': 
            {   
                outPath += (to_string(i) + ',' + to_string(j) + ';');
                checkP = 1;
                break;
            }    
            // kí hi?u bí ?n, xoay b?n d? 180 d?
            // luu b?n d? tru?c khi xoay, t?o b?n d? m?i luu b?n d? xoay
            case 'C': 
            {    
                outPath += (to_string(i) + ',' + to_string(j) + ';');
                // xoay b?n d?, thay d?i v? trí trên b?n d? và c?p nh?p l?i
                // m?ng các v? trí d?c bi?t
                
                rotateMap180(mp);
                rotateDMap180(demD);
                // thay d?i v? trí giá tr? d?c bi?t
                
                saveSpecialPos(mp, posx, posy);
                // gán l?i v? trí m?i c?a R
                // i = posx[7]; j = posy[7];
                // cout  <<  i << " " << j << " " << endl;
                // luu l?i bi?n thay d?i b?n d? hay chua
                // checkRotate = thelucgoc-stamina;
                // for  (int i = 0; i < 10; i++){
                //     for  (int j = 0; j < 10; j++){
                //         cout << mp[i][j] << ' '; 
                //     }
                //     cout << endl;
                // }
                // cout << endl;
                // for  (int i = 0; i < 10; i++){
                //     for  (int j = 0; j < 10; j++){
                //         cout << demD[i][j] << ' '; 
                //     }
                //     cout << endl;
                // }
                break;
                
            }    
            // g?p ánh sáng, ki?m tra các ô chung d?nh xem có A thì d?ng return true;
            case 'L': 
            {
                outPath += (to_string(i) + ',' + to_string(j) + ';');
                int dx[8] = {-1, -1, -1, 0 , 0, 1, 1, 1};
                int dy[8] = {-1 , 0, 1, -1 , 1, -1, 0, 1};
                for (int k = 0; k < 7; k++){
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if (mp[x][y] == 'A'){
                        if (outPath[outPath.length() - 1] == ';'){
                            outPath.pop_back();
                        }
                        return true;
                    }
                }
                break;
            }
            // g?p quái v?t, return false
            case 'M': 
            {
                outPath += (to_string(i) + ',' + to_string(j));
                return false;
                break;
            }
            default:
                break;
                
        }
        // end switch;
        // ki?m tra n?u không ph?i X thì luu v? trí tru?c dó l?i
        if (c != 'X'){
            preI = i; preJ = j;
        }
        // if (demD[i][j] >= 3){
            
        //     if (outPath[outPath.length() - 1] == ';'){
        //         outPath.pop_back();
        //     }
        //     return false;
        // }
    }
     
    
    
    if (outPath[outPath.length() - 1] == ';'){
        outPath.pop_back();
    }
    return false;
}


int solveCrate(int* arr, int size, int k) {
    // Complete this function to gain point
    if (size < 1 || size > 50) return -1;
    if (k < 1 || k > size) return -1;
	long long sum[size][size];
	for (int i = 0; i < size; i++){
	    for (int j = 0; j < size;  j++){
	        sum[i][j] = 0;
	    }
	}
	for (int i = 0; i < size; i++) {
	    sum[0][i] = arr[i];

	}
	for (int i = 1; i < size; i++){
		for (int j = 0; j < size - i; j++) {
			sum[i][j] = (sum[i-1][j] + sum[i-1][j+1]);
		}
	}
	
	long long res = 0;
	for (int i = 0; i < size+1-k; i++) {
	    res += sum[k-1][i];
	   // cout << sum[k-1][i]  << endl;
	}
	
    res  %= 1000;
	return res;
    return -1;
}

////////////////////////////////////////////////
///END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* awakened_h */
