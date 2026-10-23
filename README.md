# Railway Scheduling PBL2

Đồ án PBL2 quản lý và điều phối lịch chạy tàu hỏa, được xây dựng bằng C++17 và Qt Widgets.

## Chức năng chính

- Quản lý tàu, nhà ga, tuyến đường và lịch chạy.
- Quản lý các điểm dừng của lịch trình.
- Tìm đường bằng BFS, DFS và Dijkstra.
- Phát hiện xung đột lịch chạy.
- Điều phối theo độ ưu tiên hoặc giờ xuất phát.
- Lưu và đọc dữ liệu từ file văn bản.
- Giao diện đồ họa được thiết kế bằng Qt Designer.

## Cấu trúc dự án

Mã nguồn ứng dụng nằm trong thư mục `PBLQT`. Các thành phần chính gồm:

```text
model/             Các lớp dữ liệu
data_structure/    Các cấu trúc dữ liệu tự xây dựng
service/           Đọc file, phát hiện xung đột và điều phối
system/            Lớp RailwaySystem quản lý toàn hệ thống
```

## Cấu trúc dữ liệu được sử dụng

- Doubly Linked List
- Queue
- Stack
- Hash Table
- Binary Search Tree
- Heap
- Graph

## Chạy dự án

Mở file `PBLQT/PBLQT.pro` bằng Qt Creator, chọn Qt 6 với MinGW, sau đó nhấn Build và Run.

