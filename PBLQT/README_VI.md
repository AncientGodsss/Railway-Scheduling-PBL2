# PBL 2 - Hệ thống điều phối lịch chạy tàu hỏa (Qt)

Đây là phiên bản giao diện đồ họa. Model, cấu trúc dữ liệu và nghiệp vụ được giữ độc lập; Qt Widgets chỉ được dùng cho tầng giao diện.

## Chức năng

- Dashboard thống kê tàu, ga, tuyến và lịch chạy.
- Thêm, sửa, xóa và xem dữ liệu bằng bảng và hộp thoại.
- BFS, DFS, Dijkstra; phát hiện xung đột và điều phối lịch.
- Hai chiến lược đa hình: ưu tiên cao và khởi hành sớm.
- Đọc/ghi năm file TXT trong thư mục `data/`.

## Mở bằng Qt Creator

1. Mở `PBLQT.pro`.
2. Chọn kit **Desktop Qt 6.11.1 MinGW 64-bit**.
3. Đặt working directory là thư mục `PBLQT` để đọc được `data/`.
4. Chọn **Build** rồi **Run**.

## Build bằng terminal

```powershell
E:\Qt\6.11.1\mingw_64\bin\qmake.exe PBLQT.pro
E:\Qt\Tools\mingw1310_64\bin\mingw32-make.exe
```

Nếu máy có nhiều bản `g++`, đưa `E:\Qt\Tools\mingw1310_64\bin` lên đầu `PATH` trước khi build để tránh trộn compiler.

## Lưu ý khi trình bày

Qt chỉ hiển thị và nhận thao tác. Thuật toán và cấu trúc dữ liệu tự cài đặt vẫn nằm trong `data_structure/`, `service/` và `system/`, nên phần cốt lõi của PBL 2 không phụ thuộc thư viện giao diện.
