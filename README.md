Hướng dẫn cài đặt và chạy chương trình giải bài toán Quy hoạch tuyến tính

1. Yêu cầu hệ thống
Máy tính có cài đặt trình biên dịch C (gcc, clang, hoặc tương đương)
Hệ điều hành: Linux, macOS, hoặc Windows (có MinGW hoặc WSL)

2. Dùng Dev-C++
Bước 1: Cài đặt
Tải Dev-C++ tại: https://sourceforge.net/projects/orwelldevcpp/

Cài đặt bình thường, chạy được luôn (đã có sẵn trình biên dịch MinGW)

Bước 2: Mở và chạy chương trình
Mở Dev-C++

Chọn File → Open 

Mở file .c hoặc .cpp có sẵn

Nhấn F9 hoặc Execute → Compile & Run để biên dịch và chạy chương trình

Xem kết quả trên cửa sổ console hiện ra

3. Dùng Vscode
Bước 1: Cài đặt
Tải VS Code tại: https://code.visualstudio.com/

Cài đặt và mở VS Code

Cài đặt extension C/C++ của Microsoft

Cài đặt MinGW (chứa gcc/g++) nếu chưa có:

Tải MinGW từ https://osdn.net/projects/mingw/releases/

Cài đặt và thêm đường dẫn bin của MinGW vào biến môi trường PATH
Bước 2: Biên dịch và chạy
Mở file .c hoặc .cpp muốn chạy

Nhấn Ctrl+Shift+B để biên dịch

Mở terminal (Terminal → New Terminal)

Nhấn run C/C++ file để chạy chương trình

Xem kết quả trên terminal

4. Hướng dẫn nhập dữ liệu
Chọn phương pháp giải:

Nhập 1 để giải bằng phương pháp hình học (2 biến)

Nhập 2 để giải bằng phương pháp đơn hình (nhiều biến)
Chọn cách nhập dữ liệu:

Nhập 1 để nhập từ bàn phím

Nhập 2 để nhập từ file 

-Đối với phương pháp hình học:
Nhập số ràng buộc M (số hàng)
Sau đó nhập hệ số ràng buộc từng hàng
Rồi nhập hệ số hàm mục tiêu
Ví dụ:
Nhập số ràng buộc M: 3
Nhập hệ số ràng buộc 1: 1 1 4
Nhập hệ số ràng buộc 2: 1 -1 1
Nhập hệ số ràng buộc 3: -1 0 0
Nhập hệ số hàm mục tiêu: 3 2

-Đối với phương pháp đơn hình:
Nhập số ràng buộc M (số hàng)
Nhập số biến N (số cột)
Nhập vào các hệ số của ma trận ràng buộc (kèm vế phải)
Sau đó nhập hệ số hàm mục tiêu
Ví dụ:
Nhập số ràng buộc M: 2
Nhập số biến N: 2
Nhập hệ số ràng buộc và RHS(vế phải):
1 1 4
1 -1 1
Nhập hệ số hàm mục tiêu:
3 2

Lưu ý
Chương trình chỉ áp dụng với bài toán tối đa hóa hàm mục tiêu.

Biến số phải luôn không âm.

Với phương pháp hình học, số biến phải là 2.

Với phương pháp đơn hình, dữ liệu phải ở dạng chuẩn (ràng buộc dạng <=).

