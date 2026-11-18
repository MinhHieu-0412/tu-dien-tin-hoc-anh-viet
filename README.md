# Từ điển tin học Anh–Việt

Bài tập lớn môn Cấu trúc dữ liệu và giải thuật (Đề tài 9), viết bằng C++.

Từ điển được cài đặt bằng **bảng băm 27 nhóm** (26 chữ cái a–z và 1 nhóm "khác") kết hợp **danh sách liên kết đơn tự cài đặt**. Mỗi nhóm giữ các từ theo thứ tự alphabet. Không dùng `std::list`, `std::map` hay `std::unordered_map`.

## Chức năng

Thêm từ, tra cứu, sửa nghĩa, xóa từ, hiển thị theo nhóm hoặc tất cả, nạp từ file và lưu ra file. Khi mở chương trình tự nạp `dictionary.txt`; khi thoát bằng lựa chọn 0 tự lưu lại.

Tra cứu không phân biệt chữ hoa, chữ thường. Từ được lưu đúng dạng người dùng nhập.

## Cấu trúc thư mục

| File | Nhiệm vụ |
|---|---|
| `dictionary.h`, `dictionary.cpp` | Lớp `Dictionary`: bảng băm, danh sách liên kết, các thao tác, nạp và lưu file |
| `menu.h`, `menu.cpp` | Giao diện dòng lệnh |
| `main.cpp` | Chương trình chính |
| `bench.cpp` | Chương trình đo hiệu năng, xuất `bench_result.csv` |
| `bench_result.csv` | Kết quả đo hiệu năng |
| `dictionary.txt` | Dữ liệu mẫu, mỗi dòng có dạng `english\|vietnamese`, mã hóa UTF-8 |
| `test.txt`, `rong.txt` | File dùng để kiểm thử chức năng nạp file (có dòng sai, file rỗng) |

## Biên dịch và chạy

Cần trình biên dịch g++ (đã thử với g++ 15.2.0 trên Windows 11).

```
g++ main.cpp menu.cpp dictionary.cpp -o dict
.\dict
```

Trên Linux hoặc macOS: `./dict`. Trên Windows, chương trình tự đặt bảng mã UTF-8 cho console để hiển thị tiếng Việt có dấu.

Chương trình đo hiệu năng:

```
g++ -O2 bench.cpp dictionary.cpp -o bench
.\bench
```

## Định dạng file dữ liệu

Mỗi dòng là một cặp `từ tiếng Anh|nghĩa tiếng Việt`, mã hóa UTF-8. Dòng trống, dòng thiếu dấu `|`, dòng có từ rỗng hoặc từ trùng sẽ bị bỏ qua khi nạp.
