#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include <string>

/*
 * Module kiểm tra tính hợp lệ của dữ liệu đầu vào
 * Tất cả hàm trả về true nếu hợp lệ, false nếu không hợp lệ
 */

// Kiểm tra mã sản phẩm: đúng định dạng SP + 3 chữ số 
bool isValidProductID(const std::string& id);

// Kiểm tra mã khách hàng: đúng định dạng KH + 3 chữ số 
bool isValidCustomerID(const std::string& id);

// Kiểm tra mã hóa đơn: đúng định dạng HD + 3 chữ số 
bool isValidInvoiceID(const std::string& id);

// Kiểm tra số lượng: phải là số nguyên dương
bool isValidQuantity(int quantity);

// Kiểm tra đơn giá: phải là số thực dương
bool isValidPrice(double price);

// Kiểm tra tỉ lệ VAT: thuộc [0.0, 1.0]
bool isValidVATRate(double vatRate);

// Kiểm tra tỉ lệ chiết khấu: thuộc [0.0, 1.0]
bool isValidDiscountRate(double discountRate);

// Kiểm tra số điện thoại: đúng 10 chữ số
bool isValidPhoneNumber(const std::string& phone);

#endif