#include "../include/invoice.hpp"
#include <iostream>
#include <iomanip>

Invoice::Invoice()
    : invoiceID(""), customerID(""), purchaseDate(""),
      detailCount(0), subTotal(0.0), discountRate(0.0),
      discountAmount(0.0), vatAmount(0.0), finalTotal(0.0) {}

Invoice::Invoice(const std::string& invoiceID, const std::string& customerID,
                  const std::string& purchaseDate)
    : invoiceID(invoiceID), customerID(customerID), purchaseDate(purchaseDate),
      detailCount(0), subTotal(0.0), discountRate(0.0),
      discountAmount(0.0), vatAmount(0.0), finalTotal(0.0) {}

// ---- Getter ----
std::string Invoice::getInvoiceID()      const { return invoiceID; }
std::string Invoice::getCustomerID()     const { return customerID; }
std::string Invoice::getPurchaseDate()   const { return purchaseDate; }
double      Invoice::getDiscountRate()   const { return discountRate; }
double      Invoice::getSubTotal()       const { return subTotal; }
double      Invoice::getDiscountAmount() const { return discountAmount; }
double      Invoice::getVatAmount()      const { return vatAmount; }
double      Invoice::getFinalTotal()     const { return finalTotal; }
int         Invoice::getDetailCount()    const { return detailCount; }

// ---- Setter ----
void Invoice::setInvoiceID(const std::string& id)     { invoiceID = id; }
void Invoice::setCustomerID(const std::string& id)    { customerID = id; }
void Invoice::setPurchaseDate(const std::string& date) { purchaseDate = date; }
void Invoice::setDiscountRate(double rate)              { discountRate = rate; }

// ---- Lấy dòng chi tiết theo chỉ số ----
const InvoiceDetail& Invoice::getDetail(int index) const {
    return details[index];
}

// ---- Thêm dòng chi tiết ----
bool Invoice::addProductDetail(const InvoiceDetail& detail) {
    if (detailCount >= MAX_DETAILS) {
        std::cout << "Khong the them: da day mang chi tiet hoa don!" << std::endl;
        return false;
    }
    details[detailCount] = detail;
    detailCount++;
    return true;
}

// ---- Tính toán theo công thức mục 2.3 ----
void Invoice::calculateTotal() {
    subTotal  = 0.0;
    vatAmount = 0.0;

    for (int i = 0; i < detailCount; i++) {
        details[i].calculateLineTotal();
        subTotal  += details[i].lineTotal;
        vatAmount += details[i].lineVAT;
    }

    discountAmount = subTotal * discountRate;
    finalTotal     = subTotal - discountAmount + vatAmount;
}

// ---- Hiển thị hóa đơn ----
void Invoice::displayInfo() const {
    std::cout << "===== HOA DON: " << invoiceID << " =====" << std::endl;
    std::cout << "Khach hang : " << customerID  << std::endl;
    std::cout << "Ngay mua   : " << purchaseDate << std::endl;
    std::cout << "-------------------------------------------" << std::endl;

    for (int i = 0; i < detailCount; i++) {
        details[i].displayInfo();
    }

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Tam tinh (subTotal)    : " << subTotal      << std::endl;
    std::cout << "Chiet khau ("
              << (discountRate * 100) << "%)   : -" << discountAmount << std::endl;
    std::cout << "Tien VAT               : +" << vatAmount    << std::endl;
    std::cout << "TONG CONG (finalTotal) : "  << finalTotal   << std::endl;
    std::cout << "=============================================" << std::endl;
}