#include "../include/utilities.hpp"
#include "../include/invoice.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

// ===== Hàm phụ: tách chuỗi theo dấu '|' =====
// Trả về số lượng token tách được, lưu vào mảng tokens[]
static int splitLine(const std::string& line, std::string tokens[], int maxTokens, char delim = '|') {
    int count = 0;
    std::string token;
    std::stringstream ss(line);
    while (std::getline(ss, token, delim) && count < maxTokens) {
        tokens[count++] = token;
    }
    return count;
}

// ===== Đọc dữ liệu từ file vào mảng hóa đơn =====
// invoices.txt      : invoiceID|customerID|purchaseDate|discountRate
// invoicedetails.txt: invoiceID|productID|productName|unitPrice|quantity|discountRate|vatRate
int loadInvoicesFromFile(const std::string& invoiceFile,
                          const std::string& detailFile,
                          Invoice invoices[],
                          int maxInvoices) {
    int invoiceCount = 0;

    // ---- Đọc invoices.txt ----
    std::ifstream finv(invoiceFile);
    if (!finv.is_open()) {
        std::cout << "Khong mo duoc file: " << invoiceFile << std::endl;
        return 0;
    }

    std::string line;
    std::string tokens[10];
    while (std::getline(finv, line) && invoiceCount < maxInvoices) {
        if (line.empty()) continue;
        int n = splitLine(line, tokens, 10);
        if (n < 4) continue;

        Invoice inv(tokens[0], tokens[1], tokens[2]);
        try {
            inv.setDiscountRate(std::stod(tokens[3]));
        } catch (...) {
            inv.setDiscountRate(0.0);
        }
        invoices[invoiceCount++] = inv;
    }
    finv.close();

    // ---- Đọc invoicedetails.txt ----
    std::ifstream fdet(detailFile);
    if (!fdet.is_open()) {
        std::cout << "Khong mo duoc file: " << detailFile << std::endl;
        return invoiceCount;
    }

    while (std::getline(fdet, line)) {
        if (line.empty()) continue;
        int n = splitLine(line, tokens, 10);
        if (n < 7) continue;

        std::string invoiceID = tokens[0];

        // Tìm hóa đơn tương ứng trong mảng (tìm tuyến tính, không dùng map)
        int idx = -1;
        for (int i = 0; i < invoiceCount; i++) {
            if (invoices[i].getInvoiceID() == invoiceID) {
                idx = i;
                break;
            }
        }
        if (idx == -1) continue;

        double unitPrice, discountRate, vatRate;
        int quantity;
        try {
            unitPrice    = std::stod(tokens[3]);
            quantity     = std::stoi(tokens[4]);
            discountRate = std::stod(tokens[5]);
            vatRate      = std::stod(tokens[6]);
        } catch (...) {
            continue;
        }

        InvoiceDetail detail(tokens[1], tokens[2], unitPrice, quantity,
                              discountRate, vatRate);
        invoices[idx].addProductDetail(detail);
    }
    fdet.close();

    // Tính tổng tiền cho từng hóa đơn
    for (int i = 0; i < invoiceCount; i++) {
        invoices[i].calculateTotal();
    }

    return invoiceCount;
}

// ===== Thống kê doanh thu theo ngày =====
// Lưu kết quả vào 2 mảng song song: dates[] và revenues[]
// Trả về số lượng ngày khác nhau
int revenueByDay(Invoice invoices[], int invoiceCount,
                  std::string dates[], double revenues[], int maxDays) {
    int dayCount = 0;

    for (int i = 0; i < invoiceCount; i++) {
        std::string date = invoices[i].getPurchaseDate();
        double total     = invoices[i].getFinalTotal();

        // Tìm ngày trong mảng (tìm tuyến tính)
        int found = -1;
        for (int j = 0; j < dayCount; j++) {
            if (dates[j] == date) { found = j; break; }
        }

        if (found != -1) {
            revenues[found] += total;
        } else if (dayCount < maxDays) {
            dates[dayCount]    = date;
            revenues[dayCount] = total;
            dayCount++;
        }
    }
    return dayCount;
}

// ===== Thống kê doanh thu theo tháng (YYYY-MM) =====
int revenueByMonth(Invoice invoices[], int invoiceCount,
                    std::string months[], double revenues[], int maxMonths) {
    int monthCount = 0;

    for (int i = 0; i < invoiceCount; i++) {
        std::string date = invoices[i].getPurchaseDate();
        if (date.size() < 7) continue;

        std::string month = date.substr(0, 7); // Lấy "YYYY-MM"
        double total      = invoices[i].getFinalTotal();

        int found = -1;
        for (int j = 0; j < monthCount; j++) {
            if (months[j] == month) { found = j; break; }
        }

        if (found != -1) {
            revenues[found] += total;
        } else if (monthCount < maxMonths) {
            months[monthCount]    = month;
            revenues[monthCount]  = total;
            monthCount++;
        }
    }
    return monthCount;
}

// ===== Top 10 sản phẩm bán chạy (tự viết selection sort) =====
int top10BestSellingProducts(Invoice invoices[], int invoiceCount,
                               ProductSales result[], int maxTop) {
    // Bước 1: Gộp tất cả sản phẩm vào mảng tạm
    ProductSales temp[MAX_DETAILS * 10]; // đủ lớn cho mọi dòng
    int tempCount = 0;

    for (int i = 0; i < invoiceCount; i++) {
        for (int j = 0; j < invoices[i].getDetailCount(); j++) {
            const InvoiceDetail& d = invoices[i].getDetail(j);

            // Tìm sản phẩm trong temp (tìm tuyến tính)
            int found = -1;
            for (int k = 0; k < tempCount; k++) {
                if (temp[k].productID == d.productID) { found = k; break; }
            }

            if (found != -1) {
                temp[found].totalQuantity += d.quantity;
                temp[found].totalRevenue  += d.lineTotal;
            } else {
                temp[tempCount].productID    = d.productID;
                temp[tempCount].productName  = d.productName;
                temp[tempCount].totalQuantity = d.quantity;
                temp[tempCount].totalRevenue  = d.lineTotal;
                tempCount++;
            }
        }
    }

    // Bước 2: Selection sort giảm dần theo totalQuantity (tự viết)
    for (int i = 0; i < tempCount - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < tempCount; j++) {
            if (temp[j].totalQuantity > temp[maxIdx].totalQuantity) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            ProductSales swap = temp[i];
            temp[i]    = temp[maxIdx];
            temp[maxIdx] = swap;
        }
    }

    // Bước 3: Lấy tối đa maxTop phần tử
    int resultCount = (tempCount < maxTop) ? tempCount : maxTop;
    for (int i = 0; i < resultCount; i++) {
        result[i] = temp[i];
    }
    return resultCount;
}

// ===== Hiển thị báo cáo doanh thu =====
void displayRevenueReport(std::string keys[], double revenues[],
                           int count, const std::string& title) {
    std::cout << "===== " << title << " =====" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    double total = 0.0;
    for (int i = 0; i < count; i++) {
        std::cout << keys[i] << " : " << revenues[i] << std::endl;
        total += revenues[i];
    }
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "TONG DOANH THU : " << total << std::endl;
    std::cout << "=============================================" << std::endl;
}

// ===== Hiển thị top sản phẩm bán chạy =====
void displayTopProducts(ProductSales topProducts[], int count) {
    std::cout << "===== TOP " << count << " SAN PHAM BAN CHAY =====" << std::endl;
    std::cout << std::left
              << std::setw(10) << "Ma SP"
              << std::setw(22) << "Ten SP"
              << std::setw(10) << "SL ban"
              << "Doanh thu" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    for (int i = 0; i < count; i++) {
        std::cout << std::left
                  << std::setw(10) << topProducts[i].productID
                  << std::setw(22) << topProducts[i].productName
                  << std::setw(10) << topProducts[i].totalQuantity
                  << topProducts[i].totalRevenue << std::endl;
    }
    std::cout << "=============================================" << std::endl;
}