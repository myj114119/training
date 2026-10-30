// password_checker.cpp 修复说明
//
// 修复点 1（数字判断）：
//   原代码 contains_between(password, 0, 9) 把整数 0 和 9 传给 char 参数，
//   被解释成 ASCII 控制字符（码值 0~9），而不是数字字符 '0'~'9'（码值 48~57），
//   导致密码里的数字永远检测不到。改为 contains_between(password, '0', '9')。
//
// 修复点 2（长度判断）：
//   原代码 password.size() <= 10 方向反了，刚好 10 位的密码也被拒绝。
//   题目要求至少 10 位，改为 password.size() >= 10。
//
// 修复点 3（范围边界）：
//   原代码 lower < ch && ch < upper 是严格小于，端点字符（如 A、Z、a、z、0、9）
//   恰好等于 lower 或 upper 时被漏掉。改为 lower <= ch && ch <= upper。
//
// 自设测试组：
//   输入：Li Wang Bb12345678   → 预期：VALID    （10 位达标，含大小写与数字，不含名字）
//   输入：Li Wang Bb1234567    → 预期：INVALID  （9 位，长度不足）
//   输入：Li Wang Bb123456789  → 预期：VALID    （11 位，超过下限仍合法）
//   输入：Li Wang bb12345678   → 预期：INVALID  （10 位但无大写字母）
//   输入：Li Wang Bb1234Li56   → 预期：INVALID  （密码含名字 Li）
#include <iostream>
#include <string>

bool contains_between(const std::string& text, char lower, char upper) {
    for (char ch : text) {
        if (lower <= ch && ch <= upper) {
            return true;
        }
    }
    return false;
}

bool check_password(const std::string& first_name,
                    const std::string& last_name,
                    const std::string& password) {
    bool length_ok = password.size() >= 10;
    bool upper_ok = contains_between(password, 'A', 'Z');
    bool lower_ok = contains_between(password, 'a', 'z');
    bool digit_ok = contains_between(password, '0', '9');
    bool name_ok = password.find(first_name) == std::string::npos &&
                   password.find(last_name) == std::string::npos;
    return length_ok && upper_ok && lower_ok && digit_ok && name_ok;
}

int main() {
    std::string first_name, last_name, password;
    if (!(std::cin >> first_name >> last_name >> password)) {
        std::cerr << "请输入：名 姓 密码\n";
        return 1;
    }
    std::cout << (check_password(first_name, last_name, password)
                      ? "VALID" : "INVALID") << '\n';
    return 0;
}
