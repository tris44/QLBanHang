#include "../include/menu.hpp"
#include "../include/datamanager.hpp"
#include <iostream>
#include <windows.h>
using namespace std;

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    // Thông tin sinh viên thực hiện
    cout << "Nhóm 10: \n";
    cout << "Nguyễn Quang Huy - 202418920\n";
    cout << "Nguyễn Minh Trí - 202419000\n";
    cout << "Hoàng Nguyên Vũ - 202419020\n\n";
    cout << "Chương Trình Quản lý Bán Hàng\n";
    cout << "========================================\n\n";

    // Tải dữ liệu từ 4 file .txt vào bộ nhớ
    loadData();

    // Hiển thị menu chính, chương trình chạy tới khi người dùng chọn Thoát
    mainMenu();

    return 0;
}