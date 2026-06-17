#include "../include/menu.hpp"
#include "../include/datamanager.hpp"
#include <iostream>
using namespace std;

int main() {
    // Thông tin sinh viên thực hiện
    cout << "Nguyễn Quang Huy - 202418920\n";
    cout << "Nguyễn Minh Trí - 202419000\n";
    cout << "Hoàng Nguyên Vũ - 202419020\n";
    cout << "Chuong trinh Quan ly Ban hang\n";
    cout << "========================================\n\n";

    // Tải dữ liệu từ 4 file .txt vào bộ nhớ
    loadData();

    // Hiển thị menu chính, chương trình chạy tới khi người dùng chọn Thoát
    mainMenu();

    return 0;
}