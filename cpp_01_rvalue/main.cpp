#include <iostream>
#include <string>
#include <utility>

template<typename T>
void print_type_ref(T& value) {  // 左值引用
    std::cout << "左值引用: " << __PRETTY_FUNCTION__ << std::endl;
}

template<typename T>
void print_type_forward_inner(T&& value, const std::string expr) {  // 万能引用
    std::cout << expr << " : " << __PRETTY_FUNCTION__ << std::endl;
}

template<typename T>
void print_type_forward(T&& value) {  // 万能引用
    std::cout << "万能引用2:                          " << __PRETTY_FUNCTION__ << std::endl;
    print_type_forward_inner(static_cast<T&&>(value), "cast   "); // 模拟 std::forward
    print_type_forward_inner(std::forward<T>(value), "forward");
    //  std::forward, 如果 T 被推断成 std::string, 说明传入为右值, 此时 std::string&& && 引用折叠为 std::string&&
    //                如果 T 被推断成 std::string&, 说明传入为左值, 此时 std::string& && 引用折叠为 std::string&
    print_type_forward_inner(value, "直接传值"); // 直接传值，T 被推导为左值引用类型
    print_type_forward_inner(std::forward<T&>(value), "error forward");
    // 注意: std::forward 是依赖传入的泛型的, 如果传成 T&, 引用折叠的结果就统一是 std::string&, 这样与直接传值就没有区别了
    std::cout << "-----------------------------" << std::endl;
}

template<typename T>
void print_type_value(T value) {  // 按值传递
    std::cout << "按值传递: " << __PRETTY_FUNCTION__ << std::endl;
}

int main() {
    int a = 1;
    int &b = a;
    int&& c = std::move(a); // 虽然 int&& c 这个变量本身是左值，但它所引用的对象是右值，这使得 C++ 能够实现高效的资源管理和移动语义。
    int& d = c;  // c 本质上就是左值引用
    // int&& e = c; // 编译报错: Rvalue reference to type 'int' cannot bind to lvalue of type 'int'
    std::string str = "hello";
    std::string& str2 = str;
    const std::string& const_str = "hello";

    std::cout << "=== 按值传递 ===\n";
    print_type_value(1);              // T: int
    print_type_value(a);              // T: int
    print_type_value(b);              // T: int
    print_type_value(c);              // T: int
    print_type_value(std::string("str")); // T: std::string
    print_type_value(str);            // T: std::string
    print_type_value(const_str);      // T: std::string

    std::cout << "\n=== 左值引用 ===\n";
    print_type_ref(a);                  // T: int
    print_type_ref(b);                  // T: int
    print_type_ref(c);                  // T: int
    print_type_ref(str);                // T: std::string
    print_type_ref(const_str);       // T: const std::string

    std::cout << "\n=== 万能引用 ===\n";
    print_type_forward(1);                  // T: int
    print_type_forward(a);                     // T: int&
    print_type_forward(std::move(a));       // T: int
    print_type_forward(c);                     // T: int &
    print_type_forward(str);                   // T: std::string&
    print_type_forward(std::move(str));     // T: std::string
    print_type_forward(std::move(str2));    // T: std::string
    print_type_forward(const_str);          // T: const std::string&

    return 0;
}

/*
如果传入左值，T 被推导为左值引用类型 (T&)
如果传入右值，T 被推导为非引用类型 (T)
T 永远不会被推导为 && 类型

在 print_type_forward 中调用 print_type_forward_inner(value) 时：
1. value 是一个有名字的变量，无论它原来是什么引用类型，它现在是一个左值
2. 因此 print_type_forward_inner 的 T 会被推导为左值引用类型

行为上, 二者等价:
std::forward<T>(value);
static_cast<T&&>(value);
*/

// 输出:
/*
=== 按值传递 ===
按值传递: void print_type_value(T) [T = int]
按值传递: void print_type_value(T) [T = int]
按值传递: void print_type_value(T) [T = int]
按值传递: void print_type_value(T) [T = int]
按值传递: void print_type_value(T) [T = std::string]
按值传递: void print_type_value(T) [T = std::string]
按值传递: void print_type_value(T) [T = std::string]

=== 左值引用 ===
左值引用: void print_type_ref(T &) [T = int]
左值引用: void print_type_ref(T &) [T = int]
左值引用: void print_type_ref(T &) [T = int]
左值引用: void print_type_ref(T &) [T = std::string]
左值引用: void print_type_ref(T &) [T = const std::string]

=== 万能引用 ===
万能引用2:                          void print_type_forward(T &&) [T = int]
cast    : void print_type_forward_inner(T &&, const std::string) [T = int]
forward : void print_type_forward_inner(T &&, const std::string) [T = int]
直接传值 : void print_type_forward_inner(T &&, const std::string) [T = int &]
error forward : void print_type_forward_inner(T &&, const std::string) [T = int &]
-----------------------------
万能引用2:                          void print_type_forward(T &&) [T = int &]
cast    : void print_type_forward_inner(T &&, const std::string) [T = int &]
forward : void print_type_forward_inner(T &&, const std::string) [T = int &]
直接传值 : void print_type_forward_inner(T &&, const std::string) [T = int &]
error forward : void print_type_forward_inner(T &&, const std::string) [T = int &]
-----------------------------
万能引用2:                          void print_type_forward(T &&) [T = int]
cast    : void print_type_forward_inner(T &&, const std::string) [T = int]
forward : void print_type_forward_inner(T &&, const std::string) [T = int]
直接传值 : void print_type_forward_inner(T &&, const std::string) [T = int &]
error forward : void print_type_forward_inner(T &&, const std::string) [T = int &]
-----------------------------
万能引用2:                          void print_type_forward(T &&) [T = int &]
cast    : void print_type_forward_inner(T &&, const std::string) [T = int &]
forward : void print_type_forward_inner(T &&, const std::string) [T = int &]
直接传值 : void print_type_forward_inner(T &&, const std::string) [T = int &]
error forward : void print_type_forward_inner(T &&, const std::string) [T = int &]
-----------------------------
万能引用2:                          void print_type_forward(T &&) [T = std::string &]
cast    : void print_type_forward_inner(T &&, const std::string) [T = std::string &]
forward : void print_type_forward_inner(T &&, const std::string) [T = std::string &]
直接传值 : void print_type_forward_inner(T &&, const std::string) [T = std::string &]
error forward : void print_type_forward_inner(T &&, const std::string) [T = std::string &]
-----------------------------
万能引用2:                          void print_type_forward(T &&) [T = std::string]
cast    : void print_type_forward_inner(T &&, const std::string) [T = std::string]
forward : void print_type_forward_inner(T &&, const std::string) [T = std::string]
直接传值 : void print_type_forward_inner(T &&, const std::string) [T = std::string &]
error forward : void print_type_forward_inner(T &&, const std::string) [T = std::string &]
-----------------------------
万能引用2:                          void print_type_forward(T &&) [T = std::string]
cast    : void print_type_forward_inner(T &&, const std::string) [T = std::string]
forward : void print_type_forward_inner(T &&, const std::string) [T = std::string]
直接传值 : void print_type_forward_inner(T &&, const std::string) [T = std::string &]
error forward : void print_type_forward_inner(T &&, const std::string) [T = std::string &]
-----------------------------
万能引用2:                          void print_type_forward(T &&) [T = const std::string &]
cast    : void print_type_forward_inner(T &&, const std::string) [T = const std::string &]
forward : void print_type_forward_inner(T &&, const std::string) [T = const std::string &]
直接传值 : void print_type_forward_inner(T &&, const std::string) [T = const std::string &]
error forward : void print_type_forward_inner(T &&, const std::string) [T = const std::string &]
-----------------------------
 */