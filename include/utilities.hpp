#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>
#include <vector>
#include <map>
#include "invoice.hpp"

// ===== Hằng số chung của dự án =====
const double VAT_RATE_DEFAULT = 0.10; // VAT mặc định 10%
const int MAX_STOCK = 10000;          // Tồn kho tối đa cho phép

// Cấu trúc lưu thông tin thống kê 1 sản phẩm bán chạy
struct ProductSales {
    std::string productID;
    std::string productName;
    int totalQuantity;   // Tổng số lượng đã bán
    double totalRevenue; // Tổng tiền (lineTotal) thu được từ sản phẩm này
};

// ===== Đọc dữ liệu hóa đơn từ file (format pipe |) =====
// invoices.txt      : invoiceID|customerID|purchaseDate|discountRate
// invoicedetails.txt: invoiceID|productID|productName|unitPrice|quantity|discountRate|vatRate
std::vector<Invoice> loadInvoicesFromFile(const std::string& invoiceFile,
                                           const std::string& detailFile);

// ===== Thống kê doanh thu theo ngày =====
// Trả về map: "YYYY-MM-DD" -> tổng finalTotal trong ngày đó
std::map<std::string, double> revenueByDay(const std::vector<Invoice>& invoices);

// ===== Thống kê doanh thu theo tháng =====
// Trả về map: "YYYY-MM" -> tổng finalTotal trong tháng đó
std::map<std::string, double> revenueByMonth(const std::vector<Invoice>& invoices);

// ===== Top 10 sản phẩm bán chạy (theo số lượng) =====
std::vector<ProductSales> top10BestSellingProducts(const std::vector<Invoice>& invoices);

// ===== Hiển thị kết quả thống kê =====
void displayRevenueReport(const std::map<std::string, double>& revenueMap,
                           const std::string& title);
void displayTopProducts(const std::vector<ProductSales>& topProducts);

#endif