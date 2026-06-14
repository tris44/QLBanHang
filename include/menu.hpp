#ifndef MENU_HPP
#define MENU_HPP

#include <iostream>

/*
 * Module quản lý giao diện menu
 * Cung cấp các hàm hiển thị và điều hướng menu chính và menu con
 */

// Hiển thị menu chính và xử lý lựa chọn của người dùng
void mainMenu();

// Menu quản lý sản phẩm: thêm, sửa, xóa, tìm kiếm, hiển thị
void productMenu();

// Menu quản lý khách hàng: thêm, sửa, xóa, tìm kiếm, hiển thị
void customerMenu();

// Menu quản lý hóa đơn: lập hóa đơn, cập nhật, xóa, hiển thị
void invoiceMenu();

// Menu thống kê: doanh thu theo ngày/tháng, top 10 sản phẩm bán chạy
void statisticsMenu();

#endif