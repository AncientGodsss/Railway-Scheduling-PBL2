# Giải thích chi tiết `RailwaySystem.cpp`

Tài liệu này giải thích theo đúng thứ tự code trong `PBLQT/system/RailwaySystem.cpp` và giữ nguyên tên biến của chương trình.

## Phần 1: Khởi tạo hệ thống và quản lý tàu (dòng 1–98)

### 1. Các file được sử dụng

```cpp
#include "RailwaySystem.h"
```

Nạp file khai báo lớp `RailwaySystem`. File `.h` khai báo các thuộc tính như `trains`, `stations`, `routes`, `schedules`, `graph`, `dispatcher`, `strategy`; còn file `.cpp` viết hoạt động cụ thể của các hàm đó.

```cpp
#include "../service/FileManager.h"
```

Nạp lớp `FileManager`, dùng để đọc dữ liệu từ các file `.dat` và ghi dữ liệu hiện tại ra các file `.dat`. Dấu `../` có nghĩa là đi lên một thư mục rồi vào thư mục `service`.

```cpp
#include "../service/PriorityStrategy.h"
```

Nạp chiến lược điều phối tàu theo độ ưu tiên. Ví dụ tàu có độ ưu tiên `90` sẽ được xét trước tàu có độ ưu tiên `50`.

```cpp
#include "../service/EarliestStrategy.h"
```

Nạp chiến lược điều phối theo thời gian sớm nhất. Chiến lược này so sánh ngày và giờ xuất phát để lịch chạy sớm hơn được xử lý trước.

```cpp
#include "../data_structure/BST.h"
```

Nạp cây tìm kiếm nhị phân `BST`. Trong các phần phía sau, cây này được dùng để sắp xếp hoặc tổ chức dữ liệu lịch chạy.

### 2. Hàm khởi tạo `RailwaySystem`

```cpp
RailwaySystem::RailwaySystem()
```

Đây là constructor của lớp `RailwaySystem`. Constructor tự động chạy khi tạo một đối tượng như sau:

```cpp
RailwaySystem system;
```

Dấu `::` có nghĩa là hàm `RailwaySystem()` thuộc lớp `RailwaySystem`.

```cpp
{
```

Bắt đầu thân constructor.

```cpp
strategy = new PriorityStrategy();
```

Dòng này tạo một đối tượng `PriorityStrategy` trong vùng nhớ động bằng `new`, rồi lưu địa chỉ của đối tượng vào con trỏ `strategy`. Như vậy hệ thống mặc định chọn cách điều phối theo độ ưu tiên.

```text
strategy
   ↓
đối tượng PriorityStrategy
```

```cpp
dispatcher.setStrategy(strategy);
```

Truyền chiến lược vừa tạo cho `dispatcher`. Khi `dispatcher` điều phối tàu, nó sẽ sử dụng quy tắc chứa trong `strategy`.

```text
RailwaySystem
    └── dispatcher
            └── sử dụng PriorityStrategy
```

```cpp
}
```

Kết thúc constructor.

### 3. Hàm hủy `RailwaySystem`

```cpp
RailwaySystem::~RailwaySystem()
```

Đây là destructor của lớp `RailwaySystem`. Destructor tự động chạy khi đối tượng hệ thống bị hủy, chẳng hạn lúc chương trình kết thúc. Dấu `~` cho biết đây là hàm hủy.

```cpp
{
```

Bắt đầu thân destructor.

```cpp
clearData();
```

Gọi `clearData()` để giải phóng các đối tượng tàu, ga, tuyến đường, lịch chạy và xóa dữ liệu trong đồ thị. Việc này giúp tránh rò rỉ bộ nhớ.

```cpp
delete strategy;
```

Giải phóng đối tượng chiến lược đã được tạo bằng `new` trong constructor.

```text
new    → cấp phát bộ nhớ
delete → giải phóng bộ nhớ
```

```cpp
}
```

Kết thúc destructor.

### 4. Hàm xóa toàn bộ dữ liệu

```cpp
void RailwaySystem::clearData()
```

Khai báo hàm `clearData()` của lớp `RailwaySystem`. `void` nghĩa là hàm không trả về kết quả.

```cpp
{
```

Bắt đầu thân hàm.

```cpp
for (int i = 0; i < trains.getSize(); ++i)
    delete trains.getAt(i);
```

Dùng biến `i` chạy từ `0` đến trước số lượng tàu. `trains.getAt(i)` lấy con trỏ tàu ở vị trí `i`; `delete` giải phóng đối tượng tàu đó khỏi bộ nhớ.

```cpp
for (int i = 0; i < stations.getSize(); ++i)
    delete stations.getAt(i);
```

Duyệt từng vị trí trong bảng `stations` và giải phóng từng đối tượng `Station`.

```cpp
for (int i = 0; i < routes.getSize(); ++i)
    delete routes.getAt(i);
```

Duyệt từng vị trí trong bảng `routes` và giải phóng từng đối tượng `Route`.

```cpp
for (int i = 0; i < schedules.getSize(); ++i)
    delete schedules.getAt(i);
```

Duyệt từng vị trí trong bảng `schedules` và giải phóng từng đối tượng `Schedule`.

Bốn vòng lặp trên giải phóng các đối tượng mà con trỏ đang trỏ tới. Các phần tử trong bảng vẫn phải được xóa ở các dòng tiếp theo.

```cpp
trains.clear();
```

Xóa tất cả phần tử trong bảng tàu.

```cpp
stations.clear();
```

Xóa tất cả phần tử trong bảng ga.

```cpp
routes.clear();
```

Xóa tất cả phần tử trong bảng tuyến đường.

```cpp
schedules.clear();
```

Xóa tất cả phần tử trong bảng lịch chạy.

```cpp
graph.clear();
```

Xóa toàn bộ đỉnh đại diện cho ga và cạnh đại diện cho tuyến đường trong đồ thị.

```cpp
}
```

Kết thúc hàm `clearData()`.

Thứ tự xử lý:

```text
Giải phóng các đối tượng
        ↓
Xóa các bảng chứa con trỏ
        ↓
Xóa đồ thị
```

### 5. Hàm thêm tàu

```cpp
bool RailwaySystem::addTrain(Train* x)
```

Hàm nhận con trỏ `Train* x` và trả về `true` nếu thêm tàu thành công, `false` nếu dữ liệu không hợp lệ hoặc mã tàu đã tồn tại.

```cpp
{
```

Bắt đầu thân hàm.

```cpp
if (!x || x->getTrainId().empty() || x->getTrainName().empty() || x->getTrainType().empty() ||
    x->getCapacity() <= 0 || x->getMaxSpeed() <= 0 || x->getStatus().empty() || trains.contains(x->getTrainId()))
```

Các điều kiện được nối bằng `||`, nghĩa là chỉ cần một điều kiện đúng thì tàu không hợp lệ:

- `!x`: `x` là con trỏ rỗng, tương đương `x == nullptr`.
- `x->getTrainId().empty()`: mã tàu rỗng.
- `x->getTrainName().empty()`: tên tàu rỗng.
- `x->getTrainType().empty()`: loại tàu rỗng.
- `x->getCapacity() <= 0`: sức chứa bằng `0` hoặc âm.
- `x->getMaxSpeed() <= 0`: tốc độ tối đa bằng `0` hoặc âm.
- `x->getStatus().empty()`: trạng thái tàu rỗng.
- `trains.contains(x->getTrainId())`: mã tàu đã tồn tại trong bảng `trains`.

```cpp
return false;
```

Nếu có ít nhất một điều kiện không hợp lệ thì kết thúc hàm và báo thêm thất bại.

```cpp
return trains.insert(x->getTrainId(), x);
```

Nếu dữ liệu hợp lệ, thêm tàu vào bảng `trains`. Khóa là `x->getTrainId()` và giá trị là con trỏ `x`. `insert()` trả về `true` nếu thêm thành công và `false` nếu không thể thêm.

```cpp
}
```

Kết thúc hàm `addTrain()`.

### 6. Kiểm tra tàu có đang được lịch chạy sử dụng không

```cpp
bool RailwaySystem::trainUsed(const string& id) const
```

Hàm kiểm tra tàu có mã `id` có được lịch chạy nào sử dụng không. `const string&` giúp nhận chuỗi mà không sao chép và không cho sửa chuỗi; `const` cuối hàm đảm bảo hàm không thay đổi dữ liệu của `RailwaySystem`.

```cpp
{
```

Bắt đầu thân hàm.

```cpp
for (int i = 0; i < schedules.getSize(); ++i)
```

Dùng vòng `for` duyệt lần lượt các vị trí từ `0` đến trước số lượng lịch chạy.

```cpp
{
    Schedule* s = schedules.getAt(i);
```

Lấy lịch chạy ở vị trí `i` và lưu đúng vào biến `Schedule* s`.

```cpp
if (s && s->getTrainId() == id)
```

Kiểm tra `s` không rỗng và mã tàu của lịch `s` bằng mã `id` cần tìm.

```cpp
return true;
```

Nếu tìm thấy một lịch sử dụng tàu có mã `id`, hàm trả về `true` ngay vì không cần kiểm tra các lịch còn lại.

```cpp
}
```

Kết thúc vòng `for`.

```cpp
return false;
```

Nếu đã duyệt hết mà không tìm thấy lịch nào sử dụng tàu thì trả về `false`.

```cpp
}
```

Kết thúc hàm `trainUsed()`.

### 7. Tìm tàu — phiên bản cho phép sửa

```cpp
Train* RailwaySystem::findTrain(const string& id)
```

Tìm tàu theo mã. Hàm trả về `Train*`, vì vậy nơi gọi có thể sửa đối tượng tàu tìm được.

```cpp
{
    return trains.search(id);
}
```

Tìm khóa `id` trong bảng `trains`. Nếu tìm thấy thì trả về con trỏ `Train*`; nếu không tìm thấy thì trả về `nullptr`.

### 8. Tìm tàu — phiên bản chỉ đọc

```cpp
const Train* RailwaySystem::findTrain(const string& id) const
```

Đây là phiên bản chỉ đọc. `const Train*` không cho phép sửa tàu thông qua con trỏ trả về, còn `const` cuối hàm đảm bảo hàm không thay đổi hệ thống.

```cpp
{
    return trains.search(id);
}
```

Tìm và trả về tàu tương ứng. Hai hàm `findTrain()` cùng tên nhưng khác trạng thái `const` là hai phiên bản nạp chồng.

### 9. Xóa tàu

```cpp
bool RailwaySystem::removeTrain(const string& id)
```

Xóa tàu có mã `id`. Hàm trả về `true` nếu xóa thành công và `false` nếu không tìm thấy tàu hoặc tàu đang được sử dụng.

```cpp
{
```

Bắt đầu thân hàm.

```cpp
Train* value = trains.search(id);
```

Tìm tàu theo mã `id` và lưu kết quả vào đúng biến `Train* value`. Nếu không tìm thấy thì `value == nullptr`.

```cpp
if (!value || trainUsed(id))
```

Không cho xóa nếu không tìm thấy tàu (`!value`) hoặc tàu đang được ít nhất một lịch chạy sử dụng (`trainUsed(id)`). Việc kiểm tra này tránh để lịch chạy tham chiếu đến một tàu đã bị xóa.

```cpp
return false;
```

Báo xóa thất bại.

```cpp
delete value;
```

Giải phóng đối tượng `Train` khỏi bộ nhớ.

```cpp
return trains.remove(id);
```

Xóa phần tử có khóa `id` khỏi bảng `trains` và trả về kết quả của `remove()`.

```cpp
}
```

Kết thúc hàm `removeTrain()`.

### 10. Cập nhật thông tin tàu

```cpp
bool RailwaySystem::updateTrain(const string& id, const string& name, const string& type, int cap, double speed,
                                const string& status)
```

Hàm cập nhật tàu đã tồn tại:

- `id`: mã tàu cần cập nhật.
- `name`: tên mới.
- `type`: loại tàu mới.
- `cap`: sức chứa mới.
- `speed`: tốc độ tối đa mới.
- `status`: trạng thái mới.

`status` nằm ở dòng tiếp theo chỉ vì khai báo dài; đây vẫn là một hàm duy nhất.

```cpp
{
```

Bắt đầu thân hàm.

```cpp
Train* x = findTrain(id);
```

Tìm tàu có mã `id` và lưu kết quả vào đúng biến `Train* x`.

```cpp
if (!x || name.empty() || type.empty() || cap <= 0 || speed <= 0 || status.empty())
```

Kiểm tra không tìm thấy tàu, tên rỗng, loại rỗng, sức chứa không dương, tốc độ không dương hoặc trạng thái rỗng.

```cpp
return false;
```

Nếu có dữ liệu không hợp lệ thì không cập nhật.

```cpp
x->setTrainName(name);
```

Đổi tên tàu thành `name`.

```cpp
x->setTrainType(type);
```

Đổi loại tàu thành `type`.

```cpp
x->setCapacity(cap);
```

Đổi sức chứa thành `cap`.

```cpp
x->setMaxSpeed(speed);
```

Đổi tốc độ tối đa thành `speed`.

```cpp
x->setStatus(status);
```

Đổi trạng thái thành `status`.

```cpp
return true;
```

Thông báo cập nhật thành công.

```cpp
}
```

Kết thúc hàm `updateTrain()`. Hàm không sửa `id` vì mã tàu đang được dùng làm khóa trong bảng băm.

### 11. Hiển thị danh sách tàu

```cpp
void RailwaySystem::displayTrains() const
```

Hàm hiển thị toàn bộ tàu. `void` nghĩa là không trả về kết quả; `const` nghĩa là không thay đổi dữ liệu hệ thống.

```cpp
{
```

Bắt đầu thân hàm.

```cpp
cout << "\n===== DANH SACH TAU =====\n";
```

In tiêu đề danh sách tàu ra console. `\n` là ký tự xuống dòng.

```cpp
for (int i = 0; i < trains.getSize(); ++i)
```

Dùng vòng `for` duyệt toàn bộ các vị trí trong bảng `trains`.

```cpp
{
    Train* x = trains.getAt(i);
```

Lấy con trỏ tàu ở vị trí `i` và lưu vào đúng biến `Train* x`.

```cpp
if (x)
```

Kiểm tra `x` là con trỏ hợp lệ, tương đương `x != nullptr`.

```cpp
x->displayInfo();
```

Gọi `displayInfo()` của đúng đối tượng tàu `x` để in thông tin tàu.

```cpp
}
```

Kết thúc vòng `for`.

```cpp
}
```

Kết thúc hàm `displayTrains()`.

Luồng quản lý tàu trong phần này:

```text
addTrain()
    ↓
kiểm tra dữ liệu
    ↓
lưu vào trains

findTrain()
    ↓
tìm tàu theo mã

updateTrain()
    ↓
tìm tàu rồi sửa thông tin

removeTrain()
    ↓
kiểm tra tàu có được lịch sử dụng không
    ↓
giải phóng đối tượng và xóa khỏi bảng
```

Phần tiếp theo cần bổ sung là nhóm quản lý ga: `addStation()`, `stationUsed()`, `findStation()`, `removeStation()`, `updateStation()` và `displayStations()`.
