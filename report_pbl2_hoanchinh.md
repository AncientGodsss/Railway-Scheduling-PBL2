# ĐẠI HỌC ĐÀ NẴNG
# TRƯỜNG ĐẠI HỌC BÁCH KHOA
# KHOA CÔNG NGHỆ THÔNG TIN

---

## PBL2: DỰ ÁN CƠ SỞ LẬP TRÌNH

### ĐỀ TÀI: HỆ THỐNG QUẢN LÝ VÀ ĐIỀU PHỐI LỊCH CHẠY TÀU HỎA

**GIẢNG VIÊN HƯỚNG DẪN:** GVC.ThS. Trần Hồ Thuỷ Tiên  
**SINH VIÊN THỰC HIỆN:**  
1. Hoàng Phan Bảo Trang - Lớp: 25T_DT2 - Nhóm: 25.11A  
2. Phan Phú Quân - Lớp: 25T_DT2 - Nhóm: 25.11A  

*Đà Nẵng, Tháng 12 Năm 2026*

---

# LỜI MỞ ĐẦU

Trong xu thế phát triển mạnh mẽ của khoa học kỹ thuật và chuyển đổi số, ngành giao thông vận tải đóng vai trò huyết mạch kết nối các trung tâm kinh tế, xã hội và văn hóa trên phạm vi toàn quốc. Trong đó, vận tải đường sắt là một phương thức vận chuyển chủ lực, an toàn, có khối lượng vận chuyển lớn và tính ổn định cao. Tuy nhiên, đặc thù kỹ thuật của mạng lưới đường sắt là các đoàn tàu đều phải chia sẻ chung cơ sở hạ tầng nhà ga và các đoạn đường ray đơn/đôi trên các cung đường liên tỉnh. Do đó, bài toán lập lịch, quản lý hành trình và điều phối tránh vượt khi xảy ra xung đột thời gian là một thách thức kỹ thuật phức tạp, đòi hỏi sự chính xác tuyệt đối nhằm đảm bảo an toàn vận hành và hiệu quả khai thác.

Trước đây và tại nhiều đơn vị quản lý vận tải, công tác theo dõi tàu và giải quyết xung đột vẫn mang tính bán thủ công hoặc dựa vào kinh nghiệm cá nhân của nhân viên điều độ. Cách tiếp cận này bộc lộ nhiều hạn chế khi mật độ tàu tăng cao: thời gian phản hồi chậm, khó phát hiện sớm các nguy cơ chồng lấn thời gian trên các cung đường hẹp và dễ dẫn đến sai sót. Xuất phát từ nhu cầu thực tiễn đó, nhóm chúng em đã lựa chọn đề tài **“Hệ thống quản lý và điều phối lịch chạy tàu hỏa”** cho đồ án môn học **Dự án cơ sở lập trình (PBL2)**.

Đồ án là cơ hội quý báu giúp chúng em vận dụng tổng hợp và thực chứng những kiến thức nền tảng cốt lõi được đào tạo tại Khoa Công nghệ Thông tin - Trường Đại học Bách Khoa, Đại học Đà Nẵng, bao gồm phương pháp **Lập trình hướng đối tượng (OOP)**, thiết kế **Cấu trúc dữ liệu và Giải thuật (DSA)** chuyên sâu và xây dựng giao diện người dùng trực quan trên thư viện **Qt C++**. Điểm đặc biệt của đề tài là toàn bộ các cấu trúc dữ liệu phục vụ quản lý (Bảng băm, Đồ thị, Cây nhị phân tìm kiếm, Hàng đợi ưu tiên, Hàng đợi, Ngăn xếp, Danh sách liên kết đôi) đều được nhóm **tự cài đặt từ đầu bằng kỹ thuật Template trong C++**, không sử dụng các thư viện vùng chứa có sẵn của STL.

Trong suốt quá trình triển khai đồ án, nhóm chúng em đã nhận được sự hướng dẫn tận tình, những định hướng học thuật quý báu và sự chỉ dẫn sâu sát từ cô **GVC.ThS. Trần Hồ Thuỷ Tiên**. Nhóm xin bày tỏ lòng biết ơn chân thành và sâu sắc nhất đến Cô.

Dù đã nỗ lực hết mình với tinh thần nghiên cứu nghiêm túc, đồ án khó tránh khỏi những thiếu sót nhất định. Nhóm chúng em rất mong nhận được những góp ý, chỉ bảo của quý Thầy Cô để hoàn thiện sản phẩm và nâng cao năng lực chuyên môn cho các đồ án tiếp theo.

*Trân trọng cảm ơn!*

---

# MỤC LỤC

- **LỜI MỞ ĐẦU**
- **DANH MỤC HÌNH VẼ**
- **DANH MỤC BẢNG BIỂU**
- **1. GIỚI THIỆU ĐỀ TÀI**
  - 1.1. Đặt vấn đề
  - 1.2. Giới thiệu đề tài
  - 1.3. Mục đích và mục tiêu thực hiện đề tài
    - 1.3.1. Mục đích
    - 1.3.2. Mục tiêu
  - 1.4. Đối tượng và phạm vi nghiên cứu
    - 1.4.1. Phạm vi chức năng
    - 1.4.2. Phạm vi dữ liệu
    - 1.4.3. Đối tượng sử dụng
- **2. PHÂN TÍCH CHỨC NĂNG HỆ THỐNG**
  - 2.1. Sơ đồ chức năng hệ thống
  - 2.2. Các vai trò trong hệ thống
  - 2.3. Chi tiết các chức năng chính
    - 2.3.1. Quản lý danh mục đoàn tàu
    - 2.3.2. Quản lý danh mục nhà ga
    - 2.3.3. Quản lý mạng lưới tuyến đường (Chặng ray)
    - 2.3.4. Quản lý lịch chạy tàu và điểm dừng trung gian
    - 2.3.5. Tìm đường đi ngắn nhất (Dijkstra)
    - 2.3.6. Kiểm tra phát hiện xung đột lịch chạy
    - 2.3.7. Điều phối tự động giải quyết xung đột
    - 2.3.8. Quản lý hàng chờ điều phối và lịch sử thao tác
    - 2.3.9. Lưu trữ và đồng bộ dữ liệu
- **3. THIẾT KẾ CẤU TRÚC DỮ LIỆU**
  - 3.1. Phát biểu bài toán
    - 3.1.1. Dữ liệu đầu vào (Input)
    - 3.1.2. Dữ liệu đầu ra (Output)
    - 3.1.3. Mô hình quan hệ thực thể (ERD) và Từ điển dữ liệu
  - 3.2. Phân tích và ứng dụng cấu trúc dữ liệu trong hệ thống
    - 3.2.1. Phân tích các cấu trúc dữ liệu tự cài đặt
    - 3.2.2. Phân tích các thuật toán cốt lõi và độ phức tạp
    - 3.2.3. Bảng tổng hợp độ phức tạp thuật toán toàn hệ thống
- **4. PHÂN TÍCH HƯỚNG ĐỐI TƯỢNG VÀ TRIỂN KHAI HỆ THỐNG**
  - 4.1. Cấu trúc hệ thống hướng đối tượng (class, object, relation)
    - 4.1.1. Kiến trúc phân tầng và lập trình tổng quát (Template)
    - 4.1.2. Ứng dụng các nguyên lý lập trình hướng đối tượng
    - 4.1.3. Thiết kế quan hệ thực thể giữa các lớp
    - 4.1.4. Chi tiết các lớp trong hệ thống
  - 4.2. Kết quả
    - 4.2.1. Giao diện chính của chương trình
    - 4.2.2. Kết quả thực thi các chức năng
    - 4.2.3. Nhận xét đánh giá
- **5. KẾT LUẬN VÀ HƯỚNG PHÁT TRIỂN**
  - 5.1. Kết luận
    - 5.1.1. Những điều đã đạt được
    - 5.1.2. Những hạn chế còn tồn tại
  - 5.2. Hướng phát triển
- **TÀI LIỆU THAM KHẢO**

---

# DANH MỤC HÌNH VẼ

- Hình 2.1: Sơ đồ chức năng tổng thể của hệ thống điều phối lịch chạy tàu
- Hình 3.1: Sơ đồ lược đồ cơ sở dữ liệu quan hệ (ERD - Database Diagram)
- Hình 3.2: Cấu trúc bảng băm giải quyết đụng độ bằng phương pháp xâu chuỗi (Separate Chaining)
- Hình 3.3: Minh họa đồ thị vô hướng biểu diễn mạng lưới đường sắt
- Hình 3.4: Cây nhị phân tìm kiếm (BST) phục vụ sắp xếp lịch chạy
- Hình 3.5: Cấu trúc Cây đống cực đại (Max-Heap) cho hàng đợi ưu tiên
- Hình 4.1: Sơ đồ kiến trúc phân tầng của hệ thống (Model - Service - Data Structure - UI)
- Hình 4.2: Sơ đồ thiết kế mẫu chiến lược (Strategy Pattern) cho giải thuật điều phối
- Hình 4.3: Giao diện bảng điều khiển trung tâm (Dashboard)
- Hình 4.4: Giao diện quản lý danh sách đoàn tàu
- Hình 4.5: Giao diện quản lý danh sách nhà ga
- Hình 4.6: Giao diện quản lý tuyến đường nối các ga
- Hình 4.7: Giao diện lập lịch chạy tàu và tự động tính giờ đến bằng Dijkstra
- Hình 4.8: Giao diện tìm đường đi ngắn nhất giữa hai ga
- Hình 4.9: Giao diện kiểm tra phát hiện xung đột lịch trình có tiếng Việt và chi tiết giờ
- Hình 4.10: Giao diện điều phối tự động dời giờ lịch ưu tiên thấp
- Hình 4.11: Giao diện hàng chờ tránh tàu và lịch sử thao tác điều phối

---

# DANH MỤC BẢNG BIỂU

- Bảng 3.1: Từ điển dữ liệu bảng TRAINS (Đoàn tàu)
- Bảng 3.2: Từ điển dữ liệu bảng STATIONS (Nhà ga)
- Bảng 3.3: Từ điển dữ liệu bảng ROUTES (Tuyến đường)
- Bảng 3.4: Từ điển dữ liệu bảng SCHEDULES (Lịch chạy tàu)
- Bảng 3.5: Từ điển dữ liệu bảng STOPS (Điểm dừng trung gian)
- Bảng 3.6: Tổng hợp cấu trúc dữ liệu và bài toán áp dụng trong hệ thống
- Bảng 3.7: Bảng đánh giá độ phức tạp thời gian của các cấu trúc dữ liệu tự cài đặt

---

# 1. GIỚI THIỆU ĐỀ TÀI

## 1.1. Đặt vấn đề

Đường sắt Việt Nam là một trong những hệ thống giao thông xương sống nối liền các vùng kinh tế trọng điểm từ Bắc vào Nam. Điểm đặc thù của mạng lưới đường sắt nước ta là phần lớn cự ly vẫn là mạng ray đơn khổ 1000mm, các đoàn tàu chạy ngược chiều hoặc cùng chiều với vận tốc khác nhau bắt buộc phải sử dụng các ga trung gian làm điểm dừng tránh hoặc đón trả khách. 

Trong thực tiễn vận hành, công tác lập lịch và điều phối tàu hỏa gặp phải những bài toán hóc búa:
- **Tài nguyên dùng chung bị giới hạn:** Mỗi nhà ga chỉ có số lượng đường ray (ke ga) nhất định; mỗi chặng đường nối giữa hai ga kề nhau tại một thời điểm chỉ cho phép duy nhất một đoàn tàu chiếm dụng để đảm bảo an toàn khu gian.
- **Xung đột thời gian:** Rất dễ phát sinh các tình huống hai đoàn tàu được phân công cùng chạy trên một đoạn ray đơn trong cùng khoảng thời gian, hoặc cùng đến dừng đỗ tại một ga vượt quá sức chứa số đường ray của ga đó.
- **Tính toán hành trình tối ưu:** Hành khách và các đơn vị vận tải hàng hóa luôn có nhu cầu tìm lộ trình nhanh nhất hoặc cự ly ngắn nhất giữa hai địa phương bất kỳ, đồng thời cần dự báo chính xác thời gian tàu đến ga đích.

Nếu chỉ sử dụng bảng tính Excel hoặc sổ ghi chép điều độ truyền thống, người quản lý rất khó phát hiện sớm các điểm xung đột tiềm ẩn trên toàn mạng lưới và mất nhiều giờ đồng hồ để tính toán phương án dời giờ thủ công. Do đó, việc xây dựng một phần mềm tự động hóa quản lý dữ liệu, tìm đường tối ưu và tự động điều phối khi phát hiện xung đột là một đòi hỏi cấp thiết và có ý nghĩa ứng dụng thực tiễn cao.

## 1.2. Giới thiệu đề tài

Đề tài **“Hệ thống quản lý và điều phối lịch chạy tàu hỏa”** là một ứng dụng máy tính (Desktop Application) được xây dựng trên ngôn ngữ **C++** kết hợp với bộ công cụ đồ họa chuyên nghiệp **Qt Framework (Qt 6 / C++17)**. 

Phần mềm mô phỏng toàn diện hoạt động của trung tâm điều hành vận tải đường sắt với các khả năng nổi bật:
- Số hóa và quản lý đầy đủ các thực thể mạng lưới: Đoàn tàu, Nhà ga, Tuyến ray nối trực tiếp, Lịch chạy tàu và các Điểm dừng trung gian.
- Ứng dụng thuật toán **Dijkstra** trên cấu trúc Đồ thị (Graph) để tìm lộ trình tối ưu theo khoảng cách địa lý (km) hoặc thời gian di chuyển (phút).
- Tích hợp động cơ kiểm tra xung đột (**Conflict Detector**) đa tầng: phát hiện trùng tàu, trùng tuyến xuất phát - kết thúc, trùng chặng trung gian và trùng giờ chiếm dụng đường ray tại ga dừng.
- Cơ chế điều phối xung đột (**Dispatcher**) thông minh áp dụng mẫu thiết kế **Strategy Pattern**: linh hoạt lựa chọn chiến lược ưu tiên đoàn tàu theo mức độ ưu tiên hoặc theo giờ xuất phát sớm để lùi lịch tàu ưu tiên thấp hơn một khoảng an toàn (Buffer Time = 30 phút).
- Hệ thống hàng chờ tránh tàu và ngăn xếp lịch sử thao tác giúp kiểm soát chặt chẽ quy trình điều độ.

Toàn bộ hệ thống được xây dựng tuân thủ nguyên tắc lập trình hướng đối tượng vững chắc và **100% các cấu trúc dữ liệu đều được sinh viên tự lập trình từ đầu** để làm chủ thuật toán và tối ưu hóa bộ nhớ.

## 1.3. Mục đích và mục tiêu thực hiện đề tài

### 1.3.1. Mục đích
- Làm chủ và vận dụng thành thạo tư duy Lập trình hướng đối tượng (OOP) vào việc phân tích, thiết kế và hiện thực hóa một hệ thống phần mềm nghiệp vụ có độ phức tạp cao.
- Nâng cao năng lực tư duy thuật toán thông qua việc tự nghiên cứu, cài đặt và phân tích độ phức tạp của các cấu trúc dữ liệu kinh điển: Bảng băm, Đồ thị, Cây nhị phân tìm kiếm, Đống cực đại, Hàng đợi, Ngăn xếp, Danh sách liên kết.
- Tiếp cận quy trình phát triển ứng dụng giao diện trực quan (GUI) hiện đại với Qt Creator, nâng cao kỹ năng kiểm thử và xử lý dữ liệu nhất quán.

### 1.3.2. Mục tiêu
- **Về cấu trúc dữ liệu:** Xây dựng thư viện các cấu trúc dữ liệu dạng tổng quát (`template <typename T>`) độc lập, tái sử dụng cao, không rò rỉ bộ nhớ (Memory Leak).
- **Về thuật toán:** Hiện thực thành công thuật toán tìm đường ngắn nhất Dijkstra, thuật toán sắp xếp bằng cây BST và cơ chế phát hiện chồng lấn thời gian đoạn giao nhau.
- **Về chức năng ứng dụng:** Cung cấp đầy đủ các thao tác Thêm, Sửa, Xóa, Tra cứu, Lưu/Nạp dữ liệu bền vững từ file và cơ sở dữ liệu.
- **Về trải nghiệm người dùng:** Giao diện Qt thân thiện, hỗ trợ tiếng Việt có dấu chuẩn UTF-8, cảnh báo lỗi chi tiết, trực quan hóa tiến trình điều phối.

## 1.4. Đối tượng và phạm vi nghiên cứu

### 1.4.1. Phạm vi chức năng
Hệ thống tập trung giải quyết trọn vẹn chu trình nghiệp vụ quản lý và điều hành giao thông đường sắt:
- Nhóm chức năng Quản lý danh mục: Tàu (Train), Nhà ga (Station), Tuyến đường (Route).
- Nhóm chức năng Lập lịch: Quản lý lịch chạy (Schedule), thêm bớt điểm dừng (Stop), tự động tính giờ đến dự kiến dựa trên đồ thị đường đi thực tế.
- Nhóm chức năng Thuật toán & Tối ưu: Tìm đường ngắn nhất giữa 2 nhà ga bất kỳ.
- Nhóm chức năng Điều phối an toàn: Kiểm tra xung đột giữa 2 lịch trình và giải quyết xung đột bằng thuật toán dời giờ tự động.
- Nhóm chức năng Giám sát: Quản lý hàng chờ tàu tránh, ngăn xếp lưu vết lịch sử điều phối.

### 1.4.2. Phạm vi dữ liệu
Hệ thống xử lý mô hình hóa mạng lưới đường sắt Việt Nam với 15 nhà ga tiêu biểu trải dài từ Bắc vào Nam (Hà Nội, Lào Cai, Hải Phòng, Thanh Hóa, Vinh, Đồng Hới, Huế, Đà Nẵng, Quy Nhơn, Khánh Hòa, Đà Lạt, Đắk Lắk, Bình Thuận, Biên Hòa, Sài Gòn), 14 cung đường kết nối thực tế, cùng đội tàu khách (SE, TN) và tàu hàng (HH). Dữ liệu được lưu trữ dạng file văn bản định dạng cấu trúc và lược đồ cơ sở dữ liệu quan hệ SQL Server.

### 1.4.3. Đối tượng sử dụng
Hệ thống hướng tới đối tượng người dùng chính là **Nhân viên điều độ đường sắt (Train Dispatcher)** và **Quản lý trung tâm vận hành**, giúp họ có công cụ trực quan để giám sát mạng lưới, duyệt lịch chạy và ra quyết định xử lý tình huống nhanh chóng, chính xác.

---

# 2. PHÂN TÍCH CHỨC NĂNG HỆ THỐNG

## 2.1. Sơ đồ chức năng hệ thống

Hệ thống được tổ chức thành các phân hệ chức năng logic, liên kết chặt chẽ với nhau theo mô hình hình cây phân rã chức năng:

- **1. Quản lý danh mục cơ sở:**
  - 1.1. Quản lý đoàn tàu (Thêm, Sửa, Xóa, Tra cứu, Xem danh sách)
  - 1.2. Quản lý nhà ga (Thêm, Sửa, Xóa, Xem danh sách, Cập nhật số ray)
  - 1.3. Quản lý tuyến đường (Thêm chặng ray, Sửa khoảng cách/thời gian, Xóa)
- **2. Quản lý lịch chạy tàu:**
  - 2.1. Tạo lịch chạy mới (Tự động tính giờ đến bằng Dijkstra, chọn ngày khởi hành)
  - 2.2. Cập nhật và Xóa lịch chạy
  - 2.3. Quản lý điểm dừng trung gian (Thêm ga dừng, Cập nhật giờ đỗ, Xóa điểm dừng)
  - 2.4. Hiển thị lịch sắp xếp (Sắp xếp theo giờ xuất phát hoặc theo mức ưu tiên)
- **3. Tìm đường đi tối ưu:**
  - 3.1. Tìm đường theo Khoảng cách ngắn nhất (km)
  - 3.2. Tìm đường theo Thời gian di chuyển nhanh nhất (phút)
- **4. Phát hiện xung đột & Điều phối:**
  - 4.1. Kiểm tra xung đột đa tầng (Trùng tàu, trùng tuyến, trùng chặng, trùng giờ ga)
  - 4.2. Lựa chọn chiến lược điều phối (Theo mức ưu tiên / Theo giờ đi sớm)
  - 4.3. Tự động điều phối (Dời giờ lịch chạy, bảo toàn khoảng cách an toàn Buffer)
- **5. Hàng chờ & Lịch sử thao tác:**
  - 5.1. Xem hàng chờ tàu dừng tránh (Queue)
  - 5.2. Xem hàng ưu tiên điều phối (Max-Heap)
  - 5.3. Xem nhật ký lịch sử điều phối (Stack)
- **6. Lưu trữ và đồng bộ dữ liệu:**
  - 6.1. Đọc nạp dữ liệu từ file văn bản / CSDL
  - 6.2. Lưu trữ dữ liệu an toàn khi kết thúc phiên làm việc

*Hình 2.1: Sơ đồ chức năng tổng thể của hệ thống điều phối lịch chạy tàu*

## 2.2. Các vai trò trong hệ thống

Hệ thống phân định rõ trách nhiệm của người vận hành:
- **Người quản trị hệ thống (System Administrator):** Phụ trách cấu hình hạ tầng mạng lưới đường sắt, thêm bớt nhà ga, cập nhật thông số đường ray và các chặng liên kết vật lý.
- **Điều độ viên lập lịch (Schedule Planner):** Phụ trách xây dựng kế hoạch chạy tàu hằng ngày, phân bổ đầu máy, thiết lập các điểm đón trả khách tại ga trung gian.
- **Điều độ viên trực ban (Real-time Train Dispatcher):** Sử dụng các công cụ tìm đường, quét xung đột thời gian thực giữa các chuyến tàu và áp dụng giải thuật điều phối khi có sự cố trùng lịch.

## 2.3. Chi tiết các chức năng chính

### 2.3.1. Quản lý danh mục đoàn tàu
Cho phép quản lý thông tin các đầu máy/đoàn tàu gồm: Mã tàu, Tên tàu (SE1, SE3,...), Loại tàu (Tàu khách Passenger, Tàu hàng Freight), Sức chứa (số chỗ ngồi/tấn hàng), Vận tốc thiết kế tối đa (km/h) và Trạng thái hoạt động (ACTIVE, MAINTENANCE).
- *Ràng buộc toàn vẹn:* Không cho phép xóa đoàn tàu nếu tàu đó đang được phân công trong ít nhất một lịch chạy đang hoạt động.

### 2.3.2. Quản lý danh mục nhà ga
Quản lý các điểm nút giao thông: Mã ga (HANOI, DANANG,...), Tên ga, Vị trí địa lý (Miền Bắc, Miền Trung, Miền Nam, Tây Nguyên) và Số lượng đường ray (số ke ga có thể tiếp nhận tàu cùng lúc).
- *Ràng buộc toàn vẹn:* Mỗi khi thêm nhà ga mới, hệ thống tự động bổ sung một đỉnh (Vertex) tương ứng vào đồ thị mạng lưới. Không cho phép xóa nhà ga nếu ga đó đang thuộc về một tuyến đường hoặc một lịch trình đang tồn tại.

### 2.3.3. Quản lý mạng lưới tuyến đường (Chặng ray)
Quản lý các cạnh nối trực tiếp giữa 2 nhà ga kế cận: Mã tuyến, Ga xuất phát, Ga đích, Khoảng cách thực tế (km), Thời gian chạy chuẩn (phút) và Trạng thái thông tuyến.
- Khi một tuyến đường được thêm/sửa/xóa, hệ thống đồng bộ cập nhật cạnh vô hướng tương ứng trong Đồ thị mạng lưới (`Graph`).

### 2.3.4. Quản lý lịch chạy tàu và điểm dừng trung gian
Quản lý toàn bộ thông tin chuyến đi: Mã lịch, Mã đoàn tàu phụ trách, Ga khởi hành, Ga kết thúc, Ngày khởi hành (dd/MM/yyyy), Giờ xuất phát, Giờ đến dự kiến, Mức độ ưu tiên (0 - 100) và Trạng thái (SCHEDULED, DELAYED).
- **Tính toán giờ đến tự động:** Khi người dùng nhập Ga đi, Ga đến và Giờ xuất phát, hệ thống tự động kích hoạt thuật toán Dijkstra để tính tổng thời gian di chuyển ngắn nhất qua mạng ray và tự điền Giờ đến dự kiến.
- **Điểm dừng trung gian:** Cho phép bổ sung danh sách các ga dừng dọc đường với thứ tự tăng dần, giờ tàu vào ga và giờ rời ga. Hệ thống tự động tính toán thời gian dừng đỗ (Dwell Time) và đẩy giờ đến cuối cùng tịnh tiến tương ứng.

### 2.3.5. Tìm đường đi ngắn nhất (Dijkstra)
Người dùng chọn Ga đi và Ga đến trên danh sách trực quan, lựa chọn tiêu chí tối ưu:
- **Tối ưu theo khoảng cách:** Tìm hành trình có tổng số km ngắn nhất.
- **Tối ưu theo thời gian:** Tìm hành trình có tổng thời gian chạy ray ngắn nhất.
- *Kết quả trả về:* Dãy danh sách các ga cần đi qua theo thứ tự, tổng cự ly và tổng thời gian hành trình.

### 2.3.6. Kiểm tra phát hiện xung đột lịch chạy
Công cụ phân tích an toàn cho phép chọn 2 lịch chạy bất kỳ để kiểm tra. Động cơ phân tích thực hiện 4 cấp độ kiểm tra:
1. **Xung đột cùng tàu (Same Train Conflict):** Cùng một đầu máy nhưng bị xếp 2 chuyến chạy có khoảng thời gian bị chồng lấn.
2. **Xung đột cùng tuyến (Same End-to-End Route Conflict):** Hai tàu cùng chạy trên một tuyến (cùng chiều hoặc ngược chiều) trong cùng khoảng thời gian chiếm dụng ray.
3. **Xung đột cùng đoạn đường trung gian (Segment Conflict):** Hai lịch chạy có lộ trình khác nhau nhưng có một chặng ray trung gian đi chung bị trùng thời điểm chiếm dụng.
4. **Xung đột dừng tại ga (Station Stop Conflict):** Hai tàu cùng đỗ tại một ga trung gian trong cùng một khoảng thời gian.
- *Đặc điểm cải tiến:* Kết quả hiển thị tiếng Việt có dấu rõ ràng, chỉ đích danh tuyến bị trùng và khoảng giờ cụ thể của từng lịch trình.

### 2.3.7. Điều phối tự động giải quyết xung đột
Khi phát hiện xung đột, hệ thống áp dụng cơ chế giải quyết tự động:
- Dựa trên **Chiến lược điều phối** được chọn:
  - *Chiến lược 1 (Mức ưu tiên):* Chuyến tàu có độ ưu tiên cao hơn được giữ nguyên quyền chạy trước.
  - *Chiến lược 2 (Khởi hành sớm):* Chuyến tàu xuất phát sớm hơn được ưu tiên đi trước.
- Chuyến tàu có quyền ưu tiên thấp hơn sẽ được tính toán lùi giờ (`shiftSchedule`) sao cho giờ xuất phát mới cách giờ tàu kia giải phóng tuyến một khoảng đệm an toàn tối thiểu (**Buffer = 30 phút**).
- Đồng thời tịnh tiến toàn bộ giờ đến của chuyến đi và giờ của các điểm dừng trung gian.

### 2.3.8. Quản lý hàng chờ điều phối và lịch sử thao tác
- **Hàng chờ tránh tàu (`waitingQueue`):** Lưu trữ các mã tàu đang phải tạm dừng chờ giải phóng ray.
- **Hàng đợi ưu tiên (`priorityQueue`):** Quản lý các tàu chờ điều phối theo cơ chế Heap cực đại dựa trên điểm ưu tiên.
- **Lịch sử thao tác (`history`):** Hoạt động theo cơ chế Ngăn xếp (LIFO), ghi lại từng bước điều phối (Lùi giờ bao nhiêu phút, chuyển hàng chờ,...) giúp người điều hành xem lại nhật ký hoặc phục vụ đối soát.

### 2.3.9. Lưu trữ và đồng bộ dữ liệu
Hệ thống cung cấp cơ chế lưu trữ bền vững:
- Nạp và ghi dữ liệu ra các file văn bản có cấu trúc: `trains.txt`, `stations.txt`, `routes.txt`, `schedules.txt`, `stops.txt`.
- Đồng thời tương thích hoàn toàn với cơ sở dữ liệu quan hệ SQL Server (`Railway_PBL2`) thông qua các tập lệnh SQL chuẩn hóa.

---

# 3. THIẾT KẾ CẤU TRÚC DỮ LIỆU

## 3.1. Phát biểu bài toán

Hệ thống quản lý và điều phối đường sắt là một bài toán xử lý dữ liệu phức hợp với khối lượng bản ghi lớn, có mối quan hệ đa chiều và yêu cầu tính toán tối ưu theo thời gian thực.

### 3.1.1. Dữ liệu đầu vào (Input)
- Danh sách thông tin kỹ thuật của các đoàn tàu (Mã, Tên, Loại, Sức chứa, Tốc độ, Trạng thái).
- Danh sách các nhà ga địa phương và thông số số lượng đường ray vật lý.
- Mạng lưới các chặng ray liên kết trực tiếp giữa các cặp ga (Cự ly km, thời gian chuẩn).
- Kế hoạch lịch trình chạy tàu hàng ngày (Mã tàu, Ga đi, Ga đến, Ngày đi, Giờ đi, Giờ đến, Mức ưu tiên).
- Thông tin chi tiết các điểm dừng đỗ trung gian trên từng lịch trình.

### 3.1.2. Dữ liệu đầu ra (Output)
- Danh sách các thực thể được hiển thị trực quan trên bảng dữ liệu với các bộ lọc tìm kiếm.
- Danh sách lịch trình đã được sắp xếp tăng dần theo Giờ xuất phát hoặc giảm dần theo Mức ưu tiên.
- Lộ trình di chuyển ngắn nhất giữa hai ga bất kỳ (Danh sách thứ tự các ga, tổng quãng đường km, tổng thời gian phút).
- Báo cáo kết quả kiểm tra xung đột: Phán đoán Có/Không, phân loại nguyên nhân xung đột, chỉ ra tuyến và khung giờ bị chồng lấn.
- Lịch trình mới sau điều phối (đã tịnh tiến lùi giờ an toàn) và nhật ký lịch sử các bước xử lý.

### 3.1.3. Mô hình quan hệ thực thể (ERD) và Từ điển dữ liệu

Để mô hình hóa chuẩn xác bài toán theo nguyên lý cơ sở dữ liệu quan hệ, nhóm thiết kế mô hình ERD gồm **5 thực thể nghiệp vụ cốt lõi**, tạo thành một chu trình quan hệ khép kín và không tồn tại thực thể cô lập.

*Hình 3.1: Sơ đồ lược đồ cơ sở dữ liệu quan hệ (ERD - Database Diagram)*

#### Chi tiết Từ điển dữ liệu (Data Dictionary):

**Bảng 3.1: Từ điển dữ liệu bảng TRAINS (Đoàn tàu)**
| Tên cột | Kiểu dữ liệu | Ràng buộc | Ý nghĩa / Mô tả |
| :--- | :--- | :--- | :--- |
| `train_id` | VARCHAR(20) | PRIMARY KEY | Mã định danh duy nhất của đoàn tàu (VD: KH1, HH1) |
| `train_name` | NVARCHAR(100) | NOT NULL | Tên thương mại của tàu (VD: SE1, TN2, HH01) |
| `train_type` | NVARCHAR(50) | NOT NULL | Phân loại: Tàu khách (Passenger), Tàu hàng (Freight) |
| `capacity` | INT | CHECK (> 0) | Sức chứa tối đa (số chỗ ngồi hoặc tải trọng tấn) |
| `max_speed` | FLOAT | CHECK (> 0) | Vận tốc thiết kế tối đa cho phép (km/h) |
| `status` | NVARCHAR(30) | DEFAULT 'ACTIVE' | Trạng thái kỹ thuật: ACTIVE (Đang chạy), MAINTENANCE |

**Bảng 3.2: Từ điển dữ liệu bảng STATIONS (Nhà ga)**
| Tên cột | Kiểu dữ liệu | Ràng buộc | Ý nghĩa / Mô tả |
| :--- | :--- | :--- | :--- |
| `station_id` | VARCHAR(20) | PRIMARY KEY | Mã ký hiệu ga viết hoa không dấu (VD: HANOI, DANANG) |
| `station_name` | NVARCHAR(100) | NOT NULL | Tên đầy đủ có dấu của nhà ga (VD: Hà Nội, Đà Nẵng) |
| `location` | NVARCHAR(100) | NOT NULL | Vị trí địa lý / Miền (Miền Bắc, Miền Trung, Miền Nam) |
| `number_of_tracks`| INT | CHECK (> 0) | Số lượng đường ray đón gửi tàu đồng thời của nhà ga |

**Bảng 3.3: Từ điển dữ liệu bảng ROUTES (Tuyến đường nối trực tiếp)**
| Tên cột | Kiểu dữ liệu | Ràng buộc | Ý nghĩa / Mô tả |
| :--- | :--- | :--- | :--- |
| `route_id` | VARCHAR(20) | PRIMARY KEY | Mã tuyến ray nối liền 2 ga kề nhau (VD: R01, R02) |
| `from_station_id` | VARCHAR(20) | FOREIGN KEY | Mã ga đầu của chặng ray (tham chiếu `stations`) |
| `to_station_id` | VARCHAR(20) | FOREIGN KEY | Mã ga cuối của chặng ray (tham chiếu `stations`) |
| `distance` | FLOAT | CHECK (> 0) | Cự ly chiều dài thực tế của chặng (km) |
| `travel_time` | INT | CHECK (> 0) | Thời gian chạy tàu tiêu chuẩn qua chặng (phút) |
| `status` | NVARCHAR(30) | DEFAULT 'ACTIVE' | Trạng thái cung đường: ACTIVE (Thông tuyến), BLOCKED |

**Bảng 3.4: Từ điển dữ liệu bảng SCHEDULES (Lịch chạy tàu)**
| Tên cột | Kiểu dữ liệu | Ràng buộc | Ý nghĩa / Mô tả |
| :--- | :--- | :--- | :--- |
| `schedule_id` | VARCHAR(20) | PRIMARY KEY | Mã lịch trình duy nhất (VD: SC01, SC02) |
| `train_id` | VARCHAR(20) | FOREIGN KEY | Mã tàu được phân công (tham chiếu `trains`) |
| `departure_station_id` | VARCHAR(20) | FOREIGN KEY | Ga xuất phát đầu hành trình (tham chiếu `stations`) |
| `destination_station_id`| VARCHAR(20) | FOREIGN KEY | Ga đích cuối hành trình (tham chiếu `stations`) |
| `departure_date` | VARCHAR(20) | NOT NULL | Ngày khởi hành (định dạng chuỗi dd/MM/yyyy) |
| `departure_time` | INT | CHECK (>= 0) | Giờ xuất phát tính theo phút từ 00:00 (VD: 480 = 08:00) |
| `arrival_time` | INT | CHECK (>= 0) | Giờ đến tính theo phút (có thể vượt 1440 nếu qua ngày) |
| `priority` | INT | DEFAULT 50 | Điểm ưu tiên điều phối của chuyến tàu (0 - 100) |
| `status` | NVARCHAR(30) | DEFAULT 'SCHEDULED' | Trạng thái lịch: SCHEDULED, DELAYED, CANCELLED |

**Bảng 3.5: Từ điển dữ liệu bảng STOPS (Điểm dừng trung gian)**
| Tên cột | Kiểu dữ liệu | Ràng buộc | Ý nghĩa / Mô tả |
| :--- | :--- | :--- | :--- |
| `schedule_id` | VARCHAR(20) | PK, FOREIGN KEY | Mã lịch trình sở hữu điểm dừng (tham chiếu `schedules`) |
| `stop_order` | INT | PK, CHECK (> 0) | Số thứ tự điểm dừng trên hành trình (1, 2, 3...) |
| `station_id` | VARCHAR(20) | FOREIGN KEY | Mã nhà ga đón/trả khách (tham chiếu `stations`) |
| `arrival_time` | INT | CHECK (>= 0) | Thời điểm tàu cập ke ga (tính bằng phút) |
| `departure_time`| INT | CHECK (>= 0) | Thời điểm tàu rời ga tiếp tục chạy (tính bằng phút) |

*Phân tích ý nghĩa quan hệ liên kết:*
1. **Quan hệ 1 - N giữa `TRAINS` và `SCHEDULES`:** Một đoàn tàu vật lý có thể phục vụ nhiều lịch chạy khác nhau ở các mốc thời gian không trùng lặp.
2. **Quan hệ 1 - N đúp giữa `STATIONS` và `ROUTES`:** Một nhà ga là đầu mối kết nối nhiều chặng đường ray tỏa đi các hướng. Mỗi chặng liên kết 2 ga qua 2 khóa ngoại `from_station_id` và `to_station_id`.
3. **Quan hệ 1 - N đúp giữa `STATIONS` và `SCHEDULES`:** Xác định điểm bắt đầu và điểm kết thúc của một chuyến tàu.
4. **Quan hệ N - M giữa `SCHEDULES` và `STATIONS` qua bảng trung gian `STOPS`:** Một chuyến tàu dừng tại nhiều ga trung gian, và một ga đón nhiều chuyến tàu ghé đỗ. Bảng `STOPS` đóng vai trò là bảng cầu nối (Bridge Table) lưu trữ thông tin thời gian dừng đỗ tương ứng với từng thứ tự ghé ga.

---

## 3.2. Phân tích và ứng dụng cấu trúc dữ liệu trong hệ thống

Một yêu cầu bắt buộc và là điểm sáng học thuật của đề tài PBL2 này là **không sử dụng các vùng chứa STL của C++ (`std::vector`, `std::map`, `std::list`, `std::queue`, `std::stack`)**. Thay vào đó, nhóm chúng em đã tự thiết kế và cài đặt toàn bộ các cấu trúc dữ liệu theo dạng tổng quát hóa (Template).

**Bảng 3.6: Tổng hợp cấu trúc dữ liệu và bài toán áp dụng trong hệ thống**
| STT | Cấu trúc dữ liệu tự cài đặt | Lớp lưu trữ trong hệ thống | Bài toán và Vai trò trong đề tài |
| :---: | :--- | :--- | :--- |
| 1 | **Bảng băm (HashTable)** | `HashTable<T>` | Lưu trữ và tra cứu tức thời O(1) các thực thể Tàu, Ga, Tuyến, Lịch trình theo khóa chuỗi ID. |
| 2 | **Đồ thị (Graph)** | `Graph` | Biểu diễn mạng lưới đường ray vật lý toàn quốc bằng danh sách kề trọng số kép (khoảng cách & thời gian). |
| 3 | **Cây nhị phân tìm kiếm (BST)** | `BST<Key, Value>` | Tổ chức và sắp xếp danh sách lịch chạy tàu theo Giờ khởi hành hoặc theo Mức độ ưu tiên. |
| 4 | **Cây đống cực đại (Max-Heap)** | `MaxHeap` | Cài đặt Hàng đợi ưu tiên (`PriorityQueue`) phục vụ chọn chuyến tàu có độ ưu tiên cao nhất khi điều phối. |
| 5 | **Hàng đợi (Queue)** | `Queue<T>` | Cài đặt Hàng chờ các đoàn tàu tạm thời dừng tại đường tránh để nhường đường cho tàu khác. |
| 6 | **Ngăn xếp (Stack)** | `Stack<T>` | Quản lý Lịch sử thao tác điều phối theo cơ chế LIFO, hỗ trợ truy vấn nhật ký đảo ngược thời gian. |
| 7 | **Danh sách liên kết đôi (DoublyLinkedList)** | `DoublyLinkedList<T>` | Quản lý danh sách các điểm dừng đỗ (`StopList`) của từng lịch trình, cho phép chèn xóa ga dừng linh hoạt. |

### 3.2.1. Phân tích các cấu trúc dữ liệu tự cài đặt

#### 1. Bảng băm (Hash Table)
- **Cơ chế băm chuỗi:** Áp dụng thuật toán băm đa thức Horner với số nguyên tố 31: `hash = (hash * 31 + c) % capacity`.
- **Giải quyết xung đột:** Áp dụng phương pháp xâu chuỗi ngoài (Separate Chaining). Mỗi ô trong mảng băm là đầu một danh sách liên kết đơn các nút `HashNode<K, V>`.
- **Ứng dụng:** Lớp `RailwaySystem` sở hữu 4 bảng băm: `trains`, `stations`, `routes`, `schedules`. Thao tác tìm kiếm phần tử theo mã ID đạt tốc độ trung bình O(1).

#### 2. Đồ thị vô hướng (Graph)
- **Tổ chức:** Sử dụng danh sách kề (`AdjList`). Mỗi đỉnh là một nhà ga (`stationId`), mỗi cạnh lưu trữ trọng số kép gồm: Khoảng cách cự ly (`distance` - km) và Thời gian chạy ray (`travelTime` - phút).
- **Ứng dụng:** Mô hình hóa toàn bộ mạng lưới đường sắt. Cung cấp nền tảng cấu trúc dữ liệu để thuật toán Dijkstra vận hành.

#### 3. Cây nhị phân tìm kiếm (Binary Search Tree - BST)
- **Tổ chức:** Mỗi nút gồm Khóa (`Key`), Dữ liệu con trỏ (`Value*`), cùng hai con trỏ `left` và `right`.
- **Ứng dụng:** 
  - Khi cần xuất danh sách lịch chạy theo giờ xuất phát từ sớm đến muộn, hệ thống duyệt trung thứ tự (In-order Traversal: Left -> Root -> Right) để trích xuất mảng tăng dần mà không cần thuật toán sắp xếp phụ trợ.
  - Khi cần xuất danh sách theo mức ưu tiên từ cao xuống thấp, hệ thống duyệt đảo (Reverse In-order: Right -> Root -> Left).

#### 4. Cây đống cực đại (Max-Heap)
- **Tổ chức:** Mảng một chiều lưu cây nhị phân gần hoàn chỉnh, với nút cha tại chỉ số `i` luôn có giá trị lớn hơn hoặc bằng các nút con tại `2*i + 1` và `2*i + 2`.
- **Thao tác:** Vun đống lên (`heapifyUp`) khi thêm phần tử và vun đống xuống (`heapifyDown`) khi lấy phần tử có mức ưu tiên cao nhất (`popMax`). Đảm bảo độ phức tạp O(log N).

#### 5. Hàng đợi (Queue) và Ngăn xếp (Stack)
- **Hàng đợi:** Cài đặt bằng danh sách liên kết đơn có 2 con trỏ `front` và `rear`. Hoạt động theo nguyên tắc FIFO (Vào trước - Ra trước). Ứng dụng quản lý hàng chờ tàu tránh.
- **Ngăn xếp:** Cài đặt bằng danh sách liên kết đơn với con trỏ `top`. Hoạt động theo nguyên tắc LIFO (Vào sau - Ra trước). Ứng dụng lưu các bản ghi `Operation` trong lịch sử điều phối.

#### 6. Danh sách liên kết đôi (Doubly Linked List)
- **Tổ chức:** Mỗi phần tử chứa con trỏ `prev` và `next`.
- **Ứng dụng:** Quản lý danh sách `StopList` trong mỗi `Schedule`. Điểm dừng trên hành trình tàu có thứ tự nghiêm ngặt, việc thêm điểm dừng vào giữa hành trình hoặc xóa một ga dừng được thực hiện bằng cách hoán đổi liên kết con trỏ mà không phải dồn mảng.

### 3.2.2. Phân tích các thuật toán cốt lõi và độ phức tạp

#### 1. Thuật toán Dijkstra tìm đường đi ngắn nhất
- **Ý tưởng:** Tìm đường đi ngắn nhất từ đỉnh nguồn `start` đến đỉnh đích `target` trên đồ thị trọng số không âm.
- **Hiện thực:** Duy trì mảng `bestCost` (theo km hoặc theo phút), mảng đánh dấu đỉnh đã chốt `visited`, và mảng lưu vết đường đi `parent`. Ở mỗi bước, thuật toán chọn đỉnh chưa thăm có chi phí nhỏ nhất, sau đó tiến hành thư giãn (relax) các cạnh kề.
- **Cải tiến kỹ thuật:** Thuật toán được thiết kế đặc biệt để **theo dõi đồng thời cả hai thông số (Khoảng cách km và Thời gian phút)** trong cùng một lượt chạy, giúp người dùng nắm bắt đầy đủ cả hai thông số của hành trình.
- **Độ phức tạp:** Với V đỉnh (ga) và E cạnh (tuyến), do sử dụng duyệt tìm đỉnh nhỏ nhất trên danh sách đỉnh, độ phức tạp thời gian đạt **O(V^2 + E)**. Với mạng lưới 15 ga hiện tại, thuật toán thực thi tức thời dưới 1 mili-giây.

#### 2. Thuật toán kiểm tra xung đột lịch trình đa tầng
- **Tầng 1 (Cùng tàu):** So sánh `first.getTrainId() == second.getTrainId()`. Nếu trùng mã tàu, kiểm tra khoảng giao nhau giữa `[dep1, arr1]` và `[dep2, arr2]`. Độ phức tạp: **O(1)**.
- **Tầng 2 (Cùng tuyến):** Kiểm tra trùng cả ga đi và ga đến (cùng chiều hoặc ngược chiều). Độ phức tạp: **O(1)**.
- **Tầng 3 (Cùng chặng ray trung gian):** Duyệt từng cặp chặng con `(i, i+1)` của lịch 1 và `(j, j+1)` của lịch 2. Với S1 điểm dừng và S2 điểm dừng, số đoạn ray là (S1 + 1) và (S2 + 1). Độ phức tạp: **O(S1 * S2)**.
- **Tầng 4 (Trùng giờ đỗ tại ga):** Duyệt so khớp từng cặp điểm dừng trung gian có cùng `stationId` và chồng lấn thời gian đỗ. Độ phức tạp: **O(S1 * S2)**.

#### 3. Thuật toán điều phối dời lịch (Dispatching Algorithm)
- **Bước 1:** Xác định lịch có quyền ưu tiên cao hơn (`higher`) và lịch ưu tiên thấp hơn (`lower`) thông qua con trỏ chiến lược `strategy->higher(x, y)`.
- **Bước 2:** Tính khoảng dịch chuyển thời gian cần thiết:
  `shift = higher->getArrivalTime() + BUFFER - lower->getDepartureTime()`
  với hằng số khoảng đệm an toàn `BUFFER = 30` phút.
- **Bước 3:** Gọi hàm `shiftSchedule(shift)` trên lịch ưu tiên thấp hơn để dịch chuyển toàn bộ giờ đi, giờ đến và giờ của tất cả các điểm dừng trung gian.
- **Bước 4:** Ghi bản ghi `Operation` vào ngăn xếp lịch sử. Độ phức tạp toàn bộ quá trình: **O(S)** với S là số điểm dừng của lịch bị dời.

### 3.2.3. Bảng tổng hợp độ phức tạp thuật toán toàn hệ thống

**Bảng 3.7: Bảng đánh giá độ phức tạp thời gian của các cấu trúc dữ liệu tự cài đặt**
| Cấu trúc / Thao tác | Thêm (Insert) | Xóa (Delete) | Tìm kiếm (Search) | Duyệt (Traversal) |
| :--- | :---: | :---: | :---: | :---: |
| **Bảng băm (HashTable)** | O(1) trung bình / O(N) xấu nhất | O(1) trung bình / O(N) xấu nhất | O(1) trung bình / O(N) xấu nhất | O(N + Capacity) |
| **Cây BST (Sắp xếp lịch)** | O(log N) trung bình / O(N) xấu nhất | O(log N) trung bình / O(N) xấu nhất | O(log N) trung bình / O(N) xấu nhất | O(N) (In-order) |
| **Cây đống (Max-Heap)** | O(log N) | O(log N) (Xóa gốc) | O(N) | O(N log N) (Heap Sort) |
| **Hàng đợi (Queue)** | O(1) (Enqueue ở cuối) | O(1) (Dequeue ở đầu) | O(N) | O(N) |
| **Ngăn xếp (Stack)** | O(1) (Push ở đỉnh) | O(1) (Pop ở đỉnh) | O(N) | O(N) |
| **DSLK đôi (DoublyLinkedList)**| O(1) ở hai đầu / O(N) chèn theo vị trí | O(1) ở hai đầu / O(N) xóa theo vị trí | O(N) | O(N) |
| **Đồ thị (Dijkstra)** | Thêm đỉnh: O(1) / Thêm cạnh: O(1) | Tìm đường ngắn nhất: **O(V^2 + E)** | Tra cứu kề: O(deg(V)) | BFS/DFS: O(V + E) |

---

# 4. PHÂN TÍCH HƯỚNG ĐỐI TƯỢNG VÀ TRIỂN KHAI HỆ THỐNG

## 4.1. Cấu trúc hệ thống hướng đối tượng (class, object, relation)

### 4.1.1. Kiến trúc phân tầng và lập trình tổng quát (Template)

Kiến trúc phần mềm được phân tách thành 4 tầng rành mạch, bảo đảm nguyên tắc phân tách mối quan tâm (Separation of Concerns):
1. **Tầng Giao diện người dùng (Presentation Layer - Qt UI):** `MainWindow`, `TrainDialog`, `StationDialog`, `RouteDialog`, `ScheduleDialog`. Tầng này chỉ tương tác với lớp điều khiển trung tâm `RailwaySystem`, không trực tiếp can thiệp vào cấu trúc lưu trữ nội tại.
2. **Tầng Nghiệp vụ và Điều phối (Service & Controller Layer):** `RailwaySystem`, `Dispatcher`, `ConflictDetector`, `SchedulingStrategy`.
3. **Tầng Mô hình thực thể (Model/Domain Layer):** `Train`, `Station`, `Route`, `Schedule`, `Stop`, `Operation`.
4. **Tầng Cấu trúc dữ liệu nền tảng (Data Structure Layer):** `HashTable`, `Graph`, `BST`, `MaxHeap`, `Queue`, `Stack`, `DoublyLinkedList`.

*Ứng dụng kỹ thuật Template:*
Tất cả các cấu trúc dữ liệu đều được trừu tượng hóa bằng từ khóa `template <typename T>` hoặc `template <typename Key, typename Value>`. Nhờ đó, một lớp `Queue<T>` duy nhất có thể vừa sử dụng để chứa chuỗi mã tàu `Queue<string>`, vừa có thể mở rộng để chứa con trỏ đối tượng mà không phải sao chép mã nguồn.

### 4.1.2. Ứng dụng các nguyên lý lập trình hướng đối tượng

#### a. Tính đóng gói (Encapsulation)
- Toàn bộ thuộc tính của các lớp thực thể (`Train`, `Station`, `Route`, `Schedule`, `Stop`) đều được khai báo ở phạm vi `private`.
- Mọi truy cập hoặc hiệu chỉnh dữ liệu từ bên ngoài đều phải thông qua các phương thức `public` (Getters và Setters).
- Bên trong các phương thức Setters, hệ thống tích hợp chặt chẽ logic kiểm tra tính hợp lệ dữ liệu (Data Validation): Sức chứa và vận tốc tàu phải lớn hơn 0; khoảng cách và thời gian tuyến đường phải dương; giờ xuất phát và giờ đến không được mang giá trị âm.

#### b. Tính kế thừa (Inheritance - Quan hệ "is-a")
- Hệ thống áp dụng quan hệ kế thừa trong module chiến lược điều phối:
  - Lớp cơ sở trừu tượng: `SchedulingStrategy`.
  - Hai lớp con dẫn xuất: `PriorityStrategy` và `EarliestStrategy`. Cả hai lớp con đều kế thừa và định nghĩa lại phương thức đánh giá mức độ ưu tiên của chuyến tàu.

#### c. Tính đa hình (Polymorphism)
- **Đa hình lúc chạy (Runtime Polymorphism):** 
  Lớp `SchedulingStrategy` khai báo hàm ảo thuần túy:
  `virtual bool higher(const Schedule& first, const Schedule& second) const = 0;`
  Lớp `Dispatcher` nắm giữ con trỏ thuộc kiểu lớp cơ sở `SchedulingStrategy* strategy`. Trong quá trình chương trình đang chạy, người dùng có thể đổi chiến lược qua giao diện (`setSchedulingStrategy(1)` hoặc `(2)`). Khi hàm `dispatcher.compare(*x, *y)` được gọi, chương trình sẽ tự động kích hoạt phiên bản hàm `higher()` tương ứng của lớp con tại thời điểm chạy thông qua bảng phương thức ảo (V-Table).
- **Đa hình lúc biên dịch (Compile-time Polymorphism):** 
  Thể hiện qua cơ chế nạp chồng hàm (Function Overloading) trong các hàm khởi tạo (Constructors) của các lớp và thông qua kỹ thuật hàm mẫu Template.

#### d. Tính trừu tượng (Abstraction)
- Lớp trung tâm `RailwaySystem` đóng vai trò là một giao diện mặt tiền (Facade Pattern) che giấu toàn bộ sự phức tạp của 4 bảng băm, đồ thị và các thuật toán bên dưới. Giao diện người dùng Qt chỉ cần gọi các phương thức mức cao như `system.shortestPath(...)`, `system.hasConflict(...)`, `system.dispatch(...)`.

### 4.1.3. Thiết kế quan hệ thực thể giữa các lớp

Hệ thống thể hiện đầy đủ các mô hình quan hệ hướng đối tượng chuẩn mực:
1. **Quan hệ Hợp thành mạnh (Composition - "Has-a" mạnh):**
   - Lớp `Schedule` sở hữu một đối tượng `StopList` (`DoublyLinkedList<Stop>`). Vòng đời của danh sách điểm dừng gắn liền trực tiếp với vòng đời của đối tượng lịch trình. Khi đối tượng `Schedule` bị hủy, danh sách `stops` bên trong cũng tự động bị giải phóng.
   - Lớp `RailwaySystem` sở hữu các đối tượng thành phần `Graph graph`, `Dispatcher dispatcher`, `ConflictDetector detector`.
2. **Quan hệ Tập hợp yếu (Aggregation - "Has-a" yếu):**
   - Lớp `RailwaySystem` quản lý các con trỏ `Train*`, `Station*`, `Route*`, `Schedule*` thông qua các bảng băm `HashTable<Train*>`. Các đối tượng thực thể được cấp phát động trên vùng nhớ Heap, `RailwaySystem` nắm giữ địa chỉ để quản lý vòng đời và thu hồi bộ nhớ qua phương thức `clearData()`.
3. **Quan hệ Phụ thuộc / Sử dụng (Dependency):**
   - Lớp `ConflictDetector` phụ thuộc vào lớp `TimeUtils` để chuyển đổi thời gian chuỗi ngày giờ sang số phút tuyệt đối (`toAbsoluteMinutes`).
4. **Quan hệ Lớp bạn (Friend Class):**
   - Lớp `FileManager` được thiết kế có quan hệ mật thiết với `RailwaySystem` để thực hiện việc đọc nạp và tuần tự hóa ghi dữ liệu ra các tập tin đĩa.

### 4.1.4. Chi tiết các lớp trong hệ thống

#### 1. Lớp Train (Đoàn tàu)
- **Thuộc tính (private):** `id : string`, `name : string`, `type : string`, `capacity : int`, `maxSpeed : double`, `status : string`.
- **Phương thức (public):** Constructors, Getters/Setters kèm kiểm tra ràng buộc, `displayInfo()`.

#### 2. Lớp Station (Nhà ga)
- **Thuộc tính (private):** `stationId : string`, `stationName : string`, `location : string`, `numberOfTracks : int`.
- **Phương thức (public):** Constructors, Getters/Setters kèm kiểm tra số đường ray >= 0, `displayInfo()`.

#### 3. Lớp Route (Tuyến đường nối 2 ga)
- **Thuộc tính (private):** `routeId : string`, `fromStationId : string`, `toStationId : string`, `distance : double`, `travelTime : int`, `status : string`.
- **Phương thức (public):** Constructors, Getters/Setters, `displayInfo()`.

#### 4. Lớp Stop (Điểm dừng trung gian)
- **Thuộc tính (private):** `stationId : string`, `order : int`, `arrivalTime : int`, `departureTime : int`.
- **Phương thức (public):** Constructors, Getters/Setters, `isValidTime()`, `displayInfo()`.

#### 5. Lớp Schedule (Lịch chạy tàu)
- **Thuộc tính (private):** `scheduleId : string`, `trainId : string`, `departureStationId : string`, `destinationStationId : string`, `departureTime : int`, `arrivalTime : int`, `priority : int`, `status : string`, `departureDate : string`, `stops : StopList`.
- **Phương thức (public):** Constructors, Getters/Setters, `addStop()`, `removeStopByOrder()`, `shiftSchedule(minutes)`, `isValidTime()`, `displaySchedule()`, `displayScheduleWithStops()`.

#### 6. Lớp RailwaySystem (Lớp điều khiển trung tâm)
- **Thuộc tính (private):** `trains : HashTable<Train*>`, `stations : HashTable<Station*>`, `routes : HashTable<Route*>`, `schedules : HashTable<Schedule*>`, `graph : Graph`, `dispatcher : Dispatcher`, `detector : ConflictDetector`, `strategy : SchedulingStrategy*`.
- **Phương thức (public):** Các bộ hàm CRUD cho Tàu, Ga, Tuyến, Lịch, Điểm dừng; `displaySchedulesSortedByTime()`, `displaySchedulesSortedByPriority()`, `shortestPath(...)`, `hasConflict(...)`, `dispatch(...)`, `setSchedulingStrategy(...)`, `loadAllData()`, `saveAllData()`.

#### 7. Lớp Dispatcher (Điều phối viên)
- **Thuộc tính (private):** `waitingQueue : Queue<string>`, `priorityQueue : MaxHeap`, `history : Stack<Operation>`, `strategy : SchedulingStrategy*`.
- **Phương thức (public):** `setStrategy()`, `addWaiting()`, `addPriority()`, `nextTrain()`, `showQueues()`, `showHistory()`, `compare()`, `shiftSchedule()`.

#### 8. Lớp ConflictDetector (Động cơ kiểm tra xung đột)
- **Phương thức (public):** `sameTrain()`, `sameEndToEndRoute()`, `segmentConflict()`, `stationStopConflict()`, `any()`.

#### 9. Lớp SchedulingStrategy và các lớp dẫn xuất
- Lớp cơ sở trừu tượng `SchedulingStrategy` với hàm ảo thuần túy `higher()`.
- Hai lớp con cụ thể: `PriorityStrategy` và `EarliestStrategy`.

---

## 4.2. Kết quả

### 4.2.1. Giao diện chính của chương trình
Giao diện ứng dụng được thiết kế trên Qt Creator với phong cách hiện đại, thanh điều hướng trực quan gồm 7 phân hệ chính: Dashboard tổng quan, Quản lý đoàn tàu, Quản lý nhà ga, Quản lý tuyến đường, Quản lý lịch chạy, Tìm đường đi ngắn nhất, Kiểm tra xung đột & Điều phối, Hàng chờ & Lịch sử thao tác.

### 4.2.2. Kết quả thực thi các chức năng

#### a. Quản lý danh mục Tàu, Ga, Tuyến
- Cho phép thêm, sửa, xóa, hiển thị danh sách các bản ghi. Dữ liệu hiển thị dạng bảng có căn lề, lọc tìm kiếm.
- Các hộp thoại nhập liệu đều tích hợp kiểm tra dữ liệu và chặn các trường hợp nhập rỗng hoặc vi phạm ràng buộc khóa ngoại.

#### b. Lập lịch chạy tàu và Tự động tính giờ đến
- Người dùng chọn Ga đi, Ga đến và Giờ xuất phát. Hệ thống tự động kích hoạt Dijkstra để tìm lộ trình thực tế qua các ga trung gian và điền giờ đến chính xác.

#### c. Tìm đường đi ngắn nhất giữa hai nhà ga
- Thử nghiệm tìm đường từ **Huế (HUE) đến Đắk Lắk (DAKLAK)**:
  - Lộ trình: `HUE -> DANANG -> QUYNHON -> KHANHHOA -> DAKLAK`.
  - Tổng chiều dài khoảng cách: 813 km.
  - Tổng thời gian di chuyển: 930 phút.

#### d. Kiểm tra phát hiện xung đột lịch chạy (Đã nâng cấp tiếng Việt có dấu chi tiết)
- Thử nghiệm kiểm tra giữa hai lịch trình **SC02** và **SC05**:
  - Lịch SC02: Tàu SE3, lộ trình Huế -> Đà Nẵng, khung giờ 08:00 - 10:30, mức ưu tiên 85.
  - Lịch SC05: Tàu SE7, lộ trình Huế -> Đà Nẵng, khung giờ 08:30 - 11:00, mức ưu tiên 75.
- Hệ thống phát hiện và hiển thị kết quả trực quan trên giao diện:
  - Xung đột: Cùng tuyến HUE -> DANANG
  - Thời gian chồng lấn!
  - Lịch SC02: 08:00 - 10:30
  - Lịch SC05: 08:30 - 11:00
- Thử nghiệm với hai lịch không xung đột (SC01 Hà Nội -> Hải Phòng lúc 06:00 và SC04 Hải Phòng -> Hà Nội lúc 14:00): Hệ thống hiển thị thông báo an toàn màu xanh: Không có xung đột giữa 2 lịch trình này.

#### e. Điều phối giải quyết xung đột
- Khi bấm nút **“Điều phối”** giữa SC02 và SC05 theo chiến lược mức ưu tiên:
  - Do SC02 có ưu tiên 85 > SC05 (75), hệ thống giữ nguyên lịch SC02.
  - Lịch SC05 bị tự động dời giờ lùi 150 phút (chờ SC02 giải phóng ray lúc 10:30 + 30 phút khoảng đệm an toàn Buffer = xuất phát mới lúc 11:00).
  - Khung giờ mới của SC05: 11:00 - 13:30.
  - Bấm kiểm tra lại: Hệ thống báo hai lịch đã an toàn và không còn xung đột.

#### f. Giám sát hàng chờ và Lịch sử
- Màn hình Hàng chờ hiển thị chi tiết các thao tác vừa thực hiện: Ghi nhận sự kiện `DELAY` của lịch SC05 được đẩy lên đỉnh ngăn xếp với đầy đủ mốc thời gian và lý do điều phối.

### 4.2.3. Nhận xét đánh giá
- Chương trình chạy ổn định, tốc độ xử lý nhanh, không có hiện tượng giật lag hay treo ứng dụng khi thao tác trên dữ liệu.
- Tính toàn vẹn của dữ liệu được bảo vệ nghiêm ngặt: không xảy ra tình trạng xóa nhầm ga đang có tàu chạy hay lập lịch với dữ liệu thời gian không hợp lệ.
- Giao diện người dùng thân thiện, trực quan, hỗ trợ tiếng Việt có dấu hoàn chỉnh và giải phóng hoàn toàn bộ nhớ khi tắt ứng dụng.

---

# 5. KẾT LUẬN VÀ HƯỚNG PHÁT TRIỂN

## 5.1. Kết luận

### 5.1.1. Những điều đã đạt được
1. **Hoàn thành xuất sắc mục tiêu đề tài:** Xây dựng thành công ứng dụng máy tính hoàn chỉnh cho bài toán Quản lý và Điều phối lịch chạy tàu hỏa với giao diện Qt GUI chuyên nghiệp.
2. **Làm chủ cấu trúc dữ liệu:** Cài đặt độc lập 100% các cấu trúc dữ liệu tổng quát (Bảng băm, Đồ thị, BST, Heap, Queue, Stack, DSLK đôi) với thuật toán tối ưu, không phụ thuộc vào thư viện ngoài.
3. **Áp dụng toàn diện tư duy OOP:** Thiết kế kiến trúc phân tầng rõ ràng, đóng gói dữ liệu chặt chẽ, áp dụng thành công mẫu thiết kế hướng đối tượng Strategy Pattern cho cơ chế điều phối đa chiến lược.
4. **Giải quyết bài toán thực tế:** Thuật toán Dijkstra tìm đường nhanh chóng; thuật toán quét xung đột 4 tầng phát hiện chính xác các nguy cơ mất an toàn chạy tàu và tự động dời lịch an toàn.

### 5.1.2. Những hạn chế còn tồn tại
- Cây nhị phân tìm kiếm (BST) hiện tại là cây nhị phân cơ bản, chưa tự cân bằng dạng cây AVL hay Red-Black Tree nên trong trường hợp dữ liệu chèn vào có thứ tự đơn điệu, cây có thể bị suy thoái.
- Cơ chế điều phối hiện tại thực hiện theo từng cặp lịch do người dùng chọn, chưa tự động quét toàn cục trên hàng trăm chuyến tàu đồng thời để đưa ra ma trận điều phối tối ưu toàn phần.
- Dữ liệu lưu trữ chính hiện tại vẫn là hệ thống tệp tin văn bản phân tách ký tự, mặc dù đã chuẩn bị sẵn lược đồ CSDL SQL Server.

## 5.2. Hướng phát triển
1. **Nâng cấp cấu trúc dữ liệu:** Thay thế BST bằng cây tự cân bằng AVL Tree hoặc Red-Black Tree để đảm bảo thời gian tìm kiếm luôn ổn định O(log N) trong mọi tình huống.
2. **Tích hợp sâu Cơ sở dữ liệu:** Kết nối trực tiếp hệ thống với SQL Server / SQLite thông qua module `QSqlDatabase` của Qt để hỗ trợ quản trị dữ liệu lớn và phân quyền nhiều người dùng đồng thời.
3. **Mở rộng thuật toán điều phối thông minh:** Nghiên cứu áp dụng giải thuật di truyền (Genetic Algorithm) hoặc quy hoạch động để tự động tối ưu hóa biểu đồ chạy tàu toàn mạng lưới khi xảy ra sự cố đột xuất.
4. **Trực quan hóa đồ họa bản đồ:** Phát triển tính năng vẽ sơ đồ mạng lưới đường ray động trên canvas của Qt, hiển thị vị trí các đoàn tàu di chuyển theo thời gian thực mô phỏng.

---

# TÀI LIỆU THAM KHẢO

[1] Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, Clifford Stein, *Introduction to Algorithms (3rd Edition)*, MIT Press, 2009.  
[2] Robert Sedgewick, Kevin Wayne, *Algorithms (4th Edition)*, Addison-Wesley Professional, 2011.  
[3] PGS. TS. Hoàng Nghĩa Tý, *Giáo trình Cấu trúc dữ liệu và Giải thuật*, NXB Xây Dựng, Hà Nội, 2014.  
[4] GS. Phạm Văn Ất, *Giáo trình C++ & Lập trình hướng đối tượng*, NXB Bách Khoa Hà Nội, 2008.  
[5] The Qt Company, *Qt 6 Documentation (Qt Widgets, Signals and Slots, Model/View Programming)*, [Online]. Available: https://doc.qt.io/qt-6/.  
[6] Microsoft Corporation, *SQL Server Database Documentation & T-SQL Reference*, [Online]. Available: https://learn.microsoft.com/en-us/sql/.  
