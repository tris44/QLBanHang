#include "../include/invoice.hpp"
#include <iostream>
#include <iomanip>

// Sử dụng Member Initializer List rất tốt
Invoice::Invoice()
    : invoiceID(""), customerID(""), purchaseDate(""),
      subTotal(0.0), discountRate(0.0), discountAmount(0.0),
      vatAmount(0.0), finalTotal(0.0) {}

Invoice::Invoice(const std::string& invoiceID, const std::string& customerID,
                 const std::string& purchaseDate)
    : invoiceID(invoiceID), customerID(customerID), purchaseDate(purchaseDate),
      subTotal(0.0), discountRate(0.0), discountAmount(0.0),
      vatAmount(0.0), finalTotal(0.0) {}

// ---- Getter / Setter ----
std::string Invoice::getInvoiceID() const { return invoiceID; }
void Invoice::setInvoiceID(const std::string& id) { invoiceID = id; }

std::string Invoice::getCustomerID() const { return customerID; }
void Invoice::setCustomerID(const std::string& id) { customerID = id; }

std::string Invoice::getPurchaseDate() const { return purchaseDate; }
void Invoice::setPurchaseDate(const std::string& date) { purchaseDate = date; }

void Invoice::setDiscountRate(double rate) { discountRate = rate; }
double Invoice::getDiscountRate() const { return discountRate; }

const std::vector<InvoiceDetail>& Invoice::getDetails() const { return details; }

void Invoice::addProductDetail(const InvoiceDetail& detail) {
    details.push_back(detail);
}

double Invoice::getSubTotal() const { return subTotal; }
double Invoice::getDiscountAmount() const { return discountAmount; }
double Invoice::getVatAmount() const { return vatAmount; }
double Invoice::getFinalTotal() const { return finalTotal; }

// ---- Tính toán theo công thức mục 2.3 ----
void Invoice::calculateTotal() {
    subTotal = 0.0;
    vatAmount = 0.0;

    // Bỏ const_cast thừa, dùng & để thay đổi trực tiếp giá trị lineTotal, lineVAT trong details
    for (auto& detail : details) {
        detail.calculateLineTotal();
        subTotal += detail.lineTotal;
        vatAmount += detail.lineVAT;
    }

    // Công thức tính chiết khấu và tổng thanh toán chuẩn theo yêu cầu
    discountAmount = subTotal * discountRate;
    finalTotal = subTotal - discountAmount + vatAmount;
}

// ---- Hiển thị thông tin hóa đơn ----
void Invoice::displayInfo() const {
    std::cout << "===== HOA DON: " << invoiceID << " =====" << std::endl;
    std::cout << "Khach hang : " << customerID << std::endl;
    std::cout << "Ngay mua   : " << purchaseDate << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << std::left << std::setw(12) << "Ma SP" 
              << std::setw(8) << "SL" 
              << std::setw(12) << "Don Gia" 
              << std::setw(10) << "Thanh Tien" << std::endl;

    // Tự in chi tiết dòng sản phẩm để tránh phụ thuộc hàm của Người 1 chưa viết
    std::cout << std::fixed << std::setprecision(2);
    for (const auto& detail : details) {
        std::cout << std::left << std::setw(12) << detail.productID 
                  << std::setw(8) << detail.quantity 
                  << std::setw(12) << detail.unitPrice 
                  << std::setw(10) << detail.lineTotal << std::endl;
    }

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Tam tinh (subTotal)    : " << subTotal << std::endl;
    std::cout << "Chiet khau (" << (discountRate * 100) << "%)     : -" << discountAmount << std::endl;
    std::cout << "Tien VAT               : +" << vatAmount << std::endl;
    std::cout << "TONG CONG (finalTotal) : " << finalTotal << std::endl;
    std::cout << "=============================================" << std::endl;
}