#include "../include/utilities.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

// Hàm phụ: tách chuỗi theo dấu '|'
static std::vector<std::string> splitLine(const std::string& line, char delimiter = '|') {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// ===== Đọc dữ liệu hóa đơn từ file =====
std::vector<Invoice> loadInvoicesFromFile(const std::string& invoiceFile,
                                           const std::string& detailFile) {
    std::vector<Invoice> invoices;
    std::map<std::string, int> indexByID; // invoiceID -> vị trí trong vector

    // ---- Đọc invoices.txt ----
    // Format: invoiceID|customerID|purchaseDate|discountRate
    std::ifstream finv(invoiceFile);
    if (!finv.is_open()) {
        std::cerr << "Khong mo duoc file: " << invoiceFile << std::endl;
        return invoices;
    }

    std::string line;
    while (std::getline(finv, line)) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = splitLine(line);
        if (tokens.size() < 4) continue;

        Invoice inv(tokens[0], tokens[1], tokens[2]);
        try {
            inv.setDiscountRate(std::stod(tokens[3]));
        } catch (...) {
            inv.setDiscountRate(0.0);
        }

        indexByID[inv.getInvoiceID()] = invoices.size();
        invoices.push_back(inv);
    }
    finv.close();

    // ---- Đọc invoicedetails.txt ----
    // Format: invoiceID|productID|productName|unitPrice|quantity|discountRate|vatRate
    std::ifstream fdet(detailFile);
    if (!fdet.is_open()) {
        std::cerr << "Khong mo duoc file: " << detailFile << std::endl;
        return invoices;
    }

    while (std::getline(fdet, line)) {
        if (line.empty()) continue;
        std::vector<std::string> tokens = splitLine(line);
        if (tokens.size() < 7) continue;

        const std::string& invoiceID = tokens[0];
        if (indexByID.find(invoiceID) == indexByID.end()) {
            continue; // Bỏ qua dòng nếu không tìm thấy hóa đơn tương ứng
        }

        std::string productID   = tokens[1];
        std::string productName = tokens[2];
        double unitPrice, discountRate, vatRate;
        int quantity;
        try {
            unitPrice    = std::stod(tokens[3]);
            quantity     = std::stoi(tokens[4]);
            discountRate = std::stod(tokens[5]);
            vatRate      = std::stod(tokens[6]);
        } catch (...) {
            continue; // Bỏ qua dòng lỗi dữ liệu
        }

        InvoiceDetail detail(productID, productName, unitPrice, quantity,
                              discountRate, vatRate);

        int idx = indexByID[invoiceID];
        invoices[idx].addProductDetail(detail);
    }
    fdet.close();

    // Tính tổng tiền cho từng hóa đơn sau khi đã nạp đầy đủ các dòng chi tiết
    for (auto& inv : invoices) {
        inv.calculateTotal();
    }

    return invoices;
}

// ===== Thống kê doanh thu theo ngày (YYYY-MM-DD) =====
std::map<std::string, double> revenueByDay(const std::vector<Invoice>& invoices) {
    std::map<std::string, double> result;
    for (const auto& inv : invoices) {
        result[inv.getPurchaseDate()] += inv.getFinalTotal();
    }
    return result;
}

// ===== Thống kê doanh thu theo tháng (YYYY-MM) =====
std::map<std::string, double> revenueByMonth(const std::vector<Invoice>& invoices) {
    std::map<std::string, double> result;
    for (const auto& inv : invoices) {
        std::string date = inv.getPurchaseDate(); // YYYY-MM-DD
        if (date.size() >= 7) {
            std::string month = date.substr(0, 7); // Lấy "YYYY-MM"
            result[month] += inv.getFinalTotal();
        }
    }
    return result;
}

// ===== Top 10 sản phẩm bán chạy theo số lượng =====
std::vector<ProductSales> top10BestSellingProducts(const std::vector<Invoice>& invoices) {
    std::map<std::string, ProductSales> salesMap; // productID -> thông tin tổng hợp

    for (const auto& inv : invoices) {
        for (const auto& detail : inv.getDetails()) {
            auto it = salesMap.find(detail.productID);
            if (it == salesMap.end()) {
                ProductSales ps;
                ps.productID    = detail.productID;
                ps.productName  = detail.productName;
                ps.totalQuantity = detail.quantity;
                ps.totalRevenue  = detail.lineTotal;
                salesMap[detail.productID] = ps;
            } else {
                it->second.totalQuantity += detail.quantity;
                it->second.totalRevenue  += detail.lineTotal;
            }
        }
    }

    // Chuyển sang vector để sắp xếp
    std::vector<ProductSales> result;
    for (const auto& pair : salesMap) {
        result.push_back(pair.second);
    }

    // Sắp xếp giảm dần theo tổng số lượng đã bán
    std::sort(result.begin(), result.end(),
              [](const ProductSales& a, const ProductSales& b) {
                  return a.totalQuantity > b.totalQuantity;
              });

    // Lấy tối đa 10 sản phẩm đầu tiên
    if (result.size() > 10) {
        result.resize(10);
    }

    return result;
}

// ===== Hiển thị báo cáo doanh thu =====
void displayRevenueReport(const std::map<std::string, double>& revenueMap,
                           const std::string& title) {
    std::cout << "===== " << title << " =====" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    double total = 0.0;
    for (const auto& pair : revenueMap) {
        std::cout << pair.first << " : " << pair.second << std::endl;
        total += pair.second;
    }
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TONG DOANH THU : " << total << std::endl;
    std::cout << "=============================================" << std::endl;
}

// ===== Hiển thị top sản phẩm bán chạy =====
void displayTopProducts(const std::vector<ProductSales>& topProducts) {
    std::cout << "===== TOP " << topProducts.size() << " SAN PHAM BAN CHAY =====" << std::endl;
    std::cout << std::left
              << std::setw(10) << "Ma SP"
              << std::setw(25) << "Ten SP"
              << std::setw(12) << "SL ban"
              << "Doanh thu" << std::endl;

    std::cout << std::fixed << std::setprecision(2);
    for (size_t i = 0; i < topProducts.size(); ++i) {
        const auto& p = topProducts[i];
        std::cout << std::left
                  << std::setw(10) << p.productID
                  << std::setw(25) << p.productName
                  << std::setw(12) << p.totalQuantity
                  << p.totalRevenue << std::endl;
    }
    std::cout << "=============================================" << std::endl;
}