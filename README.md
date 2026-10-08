# Platform IO: OneButton Two LED Demo

By Phan Thành Đạt



## Mục đích

Dự án được phát triển dựa trên dự án điều khiển LED bằng nút nhấn sử dụng thư viện OneButton. Mục tiêu của bài là mở rộng chương trình để sử dụng một nút nhấn ngoài để điều khiển hai LED, trong đó một LED là LED tích hợp trên ESP32 DevKit V1 và một LED được mắc thêm trên test board.

Dự án minh họa cách sử dụng thư viện OneButton để nhận biết các thao tác single click, double click và long press, đồng thời sử dụng thư viện LED để điều khiển trạng thái của từng LED.

## Phần cứng

Trong dự án sử dụng board phát triển ESP32 DevKit V1, một LED ngoài và một nút nhấn ngoài.

### ESP32 DevKit V1

- LED1 là LED tích hợp sẵn trên board.
- LED1 được kết nối với GPIO2.
- LED1 có active level = HIGH.
- Không sử dụng nút BOOT tích hợp trên board.
- Nút nhấn ngoài được kết nối với GPIO5.
- Nút nhấn sử dụng active level = LOW.

### LED2 ngoài

LED2 được mắc thêm trên test board và kết nối với GPIO4.
LED2 có active level = HIGH.

### Nút nhấn ngoài

Nút nhấn được kết nối với GPIO5.
Nút nhấn sử dụng mức tác động LOW và sử dụng điện trở kéo lên nội của ESP32.



## Yêu cầu chức năng

Chương trình chỉ sử dụng nút nhấn ngoài tại GPIO5 để điều khiển cả hai LED.

### Double click

Khi double click nút nhấn:

- Chuyển chế độ điều khiển từ LED1 sang LED2.
- Hoặc chuyển từ LED2 về LED1.
- LED không được chọn không bị thay đổi trạng thái.

Ban đầu LED1 được chọn.

### Single click

Khi single click:

- Nếu LED1 đang được chọn thì bật/tắt LED1.
- Nếu LED2 đang được chọn thì bật/tắt LED2.

### Giữ nút nhấn

Khi giữ nút nhấn:

- LED đang được chọn chuyển sang chế độ nhấp nháy.
- LED thay đổi trạng thái sau mỗi 200 ms.
- LED còn lại không bị ảnh hưởng.

## Nguyên lý hoạt động

Chương trình tạo hai đối tượng LED:

- `led1` điều khiển LED built-in tại GPIO2.
- `led2` điều khiển LED ngoài tại GPIO4.

Một con trỏ được sử dụng để xác định LED đang được điều khiển:

    LED *selectedLED = &led1;

Ban đầu `selectedLED` trỏ tới `led1`.

Khi double click, chương trình chuyển con trỏ giữa hai LED:

    LED1 ←→ LED2

Khi single click, chương trình gọi:

    selectedLED->flip();

để bật hoặc tắt LED đang được chọn.

Khi giữ nút, chương trình gọi:

    selectedLED->blink(200);

để LED đang được chọn nhấp nháy với thời gian 200 ms.

## Xử lý nút nhấn bằng OneButton

Thư viện OneButton được sử dụng để nhận biết các thao tác của nút nhấn:

    button.attachClick(btnPush);
    button.attachDoubleClick(btnDoubleClick);
    button.attachLongPressStart(btnHold);

Trong đó:

- `attachClick()` xử lý single click.
- `attachDoubleClick()` xử lý double click.
- `attachLongPressStart()` xử lý thao tác giữ nút.

Trong vòng lặp chính, hàm `button.tick()` được gọi liên tục để OneButton phát hiện thao tác của nút nhấn.

## Cấu hình GPIO

Đối với ESP32 DevKit V1:

    BTN_PIN  = GPIO5
    LED1_PIN = GPIO2
    LED2_PIN = GPIO4

Cấu hình trong `platformio.ini`:

    '-D BTN_PIN=5U'
    '-D BTN_ACT=LOW'
    '-D LED1_PIN=2U'
    '-D LED1_ACT=HIGH'
    '-D LED2_PIN=4U'
    '-D LED2_ACT=HIGH'

## Thư viện sử dụng

### OneButton

Dự án sử dụng thư viện OneButton để xử lý các thao tác của nút nhấn:

- Single click.
- Double click.
- Long press.
- Khử rung và nhận biết thao tác nút nhấn.

Thư viện được khai báo trong `platformio.ini`:

    lib_deps =
        mathertel/OneButton @ ^2.6.1

### LED

Dự án sử dụng thư viện LED tự phát triển nằm trong:

    lib/LED/LED.h

Thư viện cung cấp các chức năng:

- `on()` - bật LED.
- `off()` - tắt LED.
- `flip()` - đảo trạng thái LED.
- `blink()` - chuyển LED sang chế độ nhấp nháy.
- `loop()` - cập nhật trạng thái LED.

## Kết quả

Sau khi hoàn thành, hệ thống hoạt động như sau:

- Ban đầu LED1 được chọn.
- Single click → bật/tắt LED1.
- Double click → chuyển sang điều khiển LED2.
- Single click → bật/tắt LED2.
- Double click → quay lại điều khiển LED1.
- Giữ nút → LED đang được chọn nhấp nháy với chu kỳ 200 ms.

Như vậy, chỉ với một nút nhấn ngoài tại GPIO5, người dùng có thể chuyển đổi và điều khiển độc lập hai LED.

## Git và GitHub

Dự án được clone từ dự án mẫu sử dụng thư viện OneButton, sau đó được chỉnh sửa và phát triển thêm chức năng điều khiển hai LED.

Các bước quản lý mã nguồn:

- Clone dự án mẫu bằng `git clone`.
- Chỉnh sửa mã nguồn và cấu hình phần cứng.
- Khởi tạo Git repository riêng cho dự án.
- Sử dụng `git add` để thêm các file vào Git.
- Sử dụng `git commit` để lưu phiên bản.
- Kết nối repository local với GitHub bằng `git remote add origin`.
- Push mã nguồn lên GitHub bằng `git push`.
- Repository được đặt ở chế độ Public.

## Repository

https://github.com/thanhdatphan263/OneButton_TwoLED
