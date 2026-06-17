#ifndef DATAMANAGER_HPP
#define DATAMANAGER_HPP

#include <vector>
#include <string>
#include "product.hpp"
#include "customer.hpp"
#include "invoice.hpp"
#include "utilities.hpp"

/*
 * Module quản lý dữ liệu
 * Chịu trách nhiệm đọc/ghi dữ liệu giữa chương trình và 4 file .txt
 * Các danh sách được khai báo extern để menu.cpp có thể truy cập
 */

// ===== Danh sách dữ liệu dùng chung toàn chương trình =====
extern std::vector<Product>  productList;
extern std::vector<Customer> customerList;
extern Invoice invoiceList[MAX_INVOICES];
extern int     invoiceCount;

// ===== Hàm tổng (gọi khi khởi động / khi lưu) =====

// Tải toàn bộ dữ liệu từ 4 file .txt vào bộ nhớ khi khởi động chương trình
void loadData();

// Lưu toàn bộ dữ liệu từ bộ nhớ xuống 4 file .txt
void saveData();

// ===== Hàm đọc riêng từng file =====

// Đọc dữ liệu sản phẩm từ data/products.txt
// Định dạng: productID|name|unitPrice|stock|vatRate
void loadProducts();

// Đọc dữ liệu khách hàng từ data/customers.txt
// Định dạng: customerID|fullName|phone|address
void loadCustomers();

// ===== Hàm ghi riêng từng file =====

// Ghi dữ liệu sản phẩm xuống data/products.txt
void saveProducts();

// Ghi dữ liệu khách hàng xuống data/customers.txt
void saveCustomers();

// Ghi dữ liệu hóa đơn và chi tiết hóa đơn xuống invoices.txt, invoicedetails.txt
void saveInvoices();

#endif