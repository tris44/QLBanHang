#include "../include/validator.hpp"

// Kiểm tra mã sản phẩm: đúng định dạng SP + 3 chữ số 
bool isValidProductID(const std::string& id) {
    // Độ dài phải đúng 5 ký tự
    if (id.length() != 5) return false;
    // 2 ký tự đầu phải là "SP"
    if (id.substr(0, 2) != "SP") return false;
    // 3 ký tự cuối phải là chữ số
    for (int i = 2; i < 5; i++) {
        if (!isdigit(id[i])) return false;
    }
    return true;
}

// Kiểm tra mã khách hàng: đúng định dạng KH + 3 chữ số 
bool isValidCustomerID(const std::string& id) {
    if (id.length() != 5) return false;
    if (id.substr(0, 2) != "KH") return false;
    for (int i = 2; i < 5; i++) {
        if (!isdigit(id[i])) return false;
    }
    return true;
}

// Kiểm tra mã hóa đơn: đúng định dạng HD + 3 chữ số 
bool isValidInvoiceID(const std::string& id) {
    if (id.length() != 5) return false;
    if (id.substr(0, 2) != "HD") return false;
    for (int i = 2; i < 5; i++) {
        if (!isdigit(id[i])) return false;
    }
    return true;
}

// Kiểm tra số lượng: phải là số nguyên dương
bool isValidQuantity(int quantity) {
    return quantity > 0;
}

// Kiểm tra đơn giá: phải là số thực dương
bool isValidPrice(double price) {
    return price > 0.0;
}

// Kiểm tra tỉ lệ VAT: thuộc [0.0, 1.0]
bool isValidVATRate(double vatRate) {
    return vatRate >= 0.0 && vatRate <= 1.0;
}

// Kiểm tra tỉ lệ chiết khấu: thuộc [0.0, 1.0]
bool isValidDiscountRate(double discountRate) {
    return discountRate >= 0.0 && discountRate <= 1.0;
}

// Kiểm tra số điện thoại: đúng 10 chữ số, không chứa ký tự khác
bool isValidPhoneNumber(const std::string& phone) {
    if (phone.length() != 10) return false;
    for (char c : phone) {
        if (!isdigit(c)) return false;
    }
    return true;
}