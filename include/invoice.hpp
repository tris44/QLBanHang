#ifndef INVOICE_HPP
#define INVOICE_HPP

#include <string>
#include "invoicedetail.hpp"
#include "utilities.hpp"

class Invoice {
private:
    std::string invoiceID;
    std::string customerID;
    std::string purchaseDate;

    InvoiceDetail details[MAX_DETAILS]; // Mảng cố định
    int detailCount;                    // Số dòng chi tiết hiện có

    double subTotal;
    double discountRate;
    double discountAmount;
    double vatAmount;
    double finalTotal;

public:
    Invoice();
    Invoice(const std::string& invoiceID, const std::string& customerID,
            const std::string& purchaseDate);

    // Getter / Setter
    std::string getInvoiceID()    const;
    std::string getCustomerID()   const;
    std::string getPurchaseDate() const;
    double      getDiscountRate() const;
    double      getSubTotal()     const;
    double      getDiscountAmount() const;
    double      getVatAmount()    const;
    double      getFinalTotal()   const;
    int         getDetailCount()  const;

    void setInvoiceID(const std::string& id);
    void setCustomerID(const std::string& id);
    void setPurchaseDate(const std::string& date);
    void setDiscountRate(double rate);

    // Lấy dòng chi tiết theo chỉ số
    const InvoiceDetail& getDetail(int index) const;

    // Thêm dòng chi tiết vào mảng
    bool addProductDetail(const InvoiceDetail& detail);

   
    void calculateTotal();

    // Hiển thị thông tin hóa đơn
    void displayInfo() const;
};

#endif