#ifndef INVOICE_HPP
#define INVOICE_HPP

#include <string>
#include <vector>
#include "invoicedetail.hpp"

class Invoice {
private:
    std::string invoiceID;
    std::string customerID;
    std::string purchaseDate; // Định dạng YYYY-MM-DD
    std::vector<InvoiceDetail> details; // Danh sách các dòng sản phẩm trong hóa đơn

    double subTotal;       // Tổng lineTotal của tất cả các dòng
    double discountRate;   // Tỷ lệ chiết khấu tổng của hóa đơn (nếu có)
    double discountAmount; // Số tiền chiết khấu tổng
    double vatAmount;      // Tổng lineVAT của tất cả các dòng
    double finalTotal;     // Tổng số tiền cuối cùng khách phải trả

public:
    // Constructor
    Invoice();
    Invoice(const std::string& invoiceID, const std::string& customerID,
            const std::string& purchaseDate);

    // Các hàm Getter và Setter cơ bản
    std::string getInvoiceID() const;
    void setInvoiceID(const std::string& id);

    std::string getCustomerID() const;
    void setCustomerID(const std::string& id);

    std::string getPurchaseDate() const;
    void setPurchaseDate(const std::string& date);

    void setDiscountRate(double rate);
    double getDiscountRate() const;

    const std::vector<InvoiceDetail>& getDetails() const;
    void addProductDetail(const InvoiceDetail& detail);

    // Getter cho các giá trị đã tính toán
    double getSubTotal() const;
    double getDiscountAmount() const;
    double getVatAmount() const;
    double getFinalTotal() const;

    // Hàm tính toán toàn bộ tiền nong cho hóa đơn theo công thức mục 2.3
    void calculateTotal();

    // Hàm hiển thị thông tin hóa đơn (phục vụ việc xuất/in dữ liệu)
    void displayInfo() const;
};

#endif