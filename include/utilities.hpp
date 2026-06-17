#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <string>

// ===== Hằng số chung =====
const double VAT_RATE_DEFAULT = 0.10;
const int    MAX_STOCK        = 10000;
const int    MAX_INVOICES     = 100;
const int    MAX_DETAILS      = 500;
const int    MAX_TOP          = 10;

// ===== Struct thống kê sản phẩm bán chạy =====
struct ProductSales {
    std::string productID;
    std::string productName;
    int    totalQuantity;
    double totalRevenue;
};

// Forward declaration (tránh include vòng)
class Invoice;

// ===== Đọc file =====
int loadInvoicesFromFile(const std::string& invoiceFile,
                          const std::string& detailFile,
                          Invoice invoices[],
                          int maxInvoices);

// ===== Thống kê doanh thu =====
int revenueByDay(Invoice invoices[], int invoiceCount,
                  std::string dates[], double revenues[], int maxDays);

int revenueByMonth(Invoice invoices[], int invoiceCount,
                    std::string months[], double revenues[], int maxMonths);

// ===== Top 10 sản phẩm bán chạy =====
int top10BestSellingProducts(Invoice invoices[], int invoiceCount,
                               ProductSales result[], int maxTop);

// ===== Hiển thị =====
void displayRevenueReport(std::string keys[], double revenues[],
                           int count, const std::string& title);

void displayTopProducts(ProductSales topProducts[], int count);

#endif