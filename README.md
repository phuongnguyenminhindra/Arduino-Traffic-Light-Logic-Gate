# Arduino-Traffic-Light-Logic-Gate
Đèn giao thông 4 pha chỉ dùng 2 chân Arduino + 2 IC 74HC00. Giải mã logic NAND: Đỏ=D8, Xanh=/D8&amp;D10, Vàng=XNOR
# 🚦 Đèn Giao Thông 4 Pha - Chỉ Dùng 2 Chân Arduino + 2 IC 74HC00
> **Day 18 - LỊCH 4 PHA CHUẨN**

Dự án giải mã 4 trạng thái đèn giao thông chỉ từ 2 tín hiệu D8, D10 của Arduino bằng logic thuần túy cổng NAND 74HC00.

### 🎯 Ý tưởng cốt lõi
Thay vì dùng 3 chân Arduino cho 3 đèn, mình chỉ dùng **2 chân (D8, D10)** để mã hóa 4 pha:
- `00` -> Vàng
- `01` -> Xanh
- `10` -> Đỏ
- `11` -> Đỏ + Vàng

### 🧠 Công thức Logic (Chỉ dùng cổng NAND)
> NOT A = NAND(A,A)

- **ĐỎ = D8** (Quá dễ!)
- **XANH = (NOT D8) AND D10** -> Sáng duy nhất khi D8=0, D10=1
- **VÀNG = D8 XNOR D10** -> Sáng khi D8 == D10 (cùng 0 hoặc cùng 1)
  `Vàng = (D8 & D10) OR ((NOT D8) & (NOT D10))`

Tổng cộng chỉ tốn **7 cổng NAND** -> Vừa đủ 2 IC 74HC00.

| D8 | D10 | Đỏ (D8) | Xanh (/D8 & D10) | Vàng (XNOR) | Pha |
| --- | --- | --- | --- | --- | --- |
| 0 | 0 | TẮT | TẮT | **BẬT** | Vàng 2s |
| 0 | 1 | TẮT | **BẬT** | TẮT | Xanh 5s |
| 1 | 0 | **BẬT** | TẮT | TẮT | Đỏ 5s |
| 1 | 1 | **BẬT** | TẮT | **BẬT** | Đỏ+Vàng 2s |

### 🔧 Phần cứng
- 1x Arduino Uno
- 2x IC 74HC00 (Quad NAND)
- 3x LED: Đỏ, Vàng, Xanh + 3x điện trở 220Ω
- Breadboard + dây nối

### 🔌 Sơ đồ nối dây chốt hạ

**IC1 (làm XANH + tạo NOT):**
- Chân 14->5V, Chân 7->GND
- Chân 1,2 = D8 -> Chân 3 = /D8
- Chân 4,5 = D10 -> Chân 6 = /D10
- Chân 9 = /D8 (từ chân 3), Chân 10 = D10 -> Chân 8 = NAND(/D8,D10)
- Chân 12,13 = Chân 8 -> **Chân 11 = XANH** -> 220Ω -> LED Xanh -> GND

**IC2 (chỉ làm VÀNG):**
- Chân 1 = D8, Chân 2 = D10 -> Chân 3 = NAND(D8,D10)
- Chân 4 = /D8 (từ IC1-3), Chân 5 = /D10 (từ IC1-6) -> Chân 6 = NAND(/D8,/D10)
- Chân 9 = Chân 3, Chân 10 = Chân 6 -> **Chân 8 = VÀNG** -> 220Ω -> LED Vàng -> GND

**ĐÈN ĐỎ:**
- D8 -> 220Ω -> LED Đỏ -> GND

### 💻 Code
Xem file `lich_4_pha_2_IC/lich_4_pha_2_IC.ino`
Chu kỳ: Đỏ 5s -> Đỏ+Vàng 2s -> Xanh 5s -> Vàng 2s (đúng luật giao thông VN)

### 🎥 Demo
- Ảnh mạch thực tế: `/images/`
- Video full: (https://drive.google.com/file/d/1Ui5PWTadafHPtjFwM5EM-tDFJA1YyXQn/view?usp=drive_link)

---
**Author:** Phương Nguyễn - Day 18 Project
