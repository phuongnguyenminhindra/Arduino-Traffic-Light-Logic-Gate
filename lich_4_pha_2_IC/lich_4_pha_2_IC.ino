// DAY 18 - 2 IC - LICH 4 PHA CHUAN
// Quy luật lắp IC7400HC
/*
NOT A = NAND(A,A) - Nối 2 chân vào với nhau
A VÀ B = NOT(NAND(A,B)) = NAND(NAND(A,B), NAND(A,B))
A HOẶC B = NAND(NOT A, NOT B)
NOT_D8: 1 cổng
NOT_D10: 1 cổng
Xanh: 2 cổng (1 NAND + 1 NOT)
Vàng: 3 cổng (A,B và NAND(A,B))
Tổng = 7 cổng.
Đỏ: Nhìn cột Đỏ, nó sáng đúng khi D8=1, không quan tâm D10.
=> Đỏ = D8 (quá dễ!)
Xanh: Xanh chỉ sáng 1 dòng duy nhất là D8=0 và D10=1
=> Xanh = (KHÔNG D8) VÀ D10
Vàng: Vàng sáng khi D8==D10 (cùng 0 hoặc cùng 1)
=> Đây chính là cổng XNOR, công thức là Vàng = (D8 VÀ D10) HOẶC ((KHÔNG D8) VÀ (KHÔNG D10))
*/
#define PIN_DO_THO 8
#define PIN_XANH_THO 10

enum Phase { P_DO, P_DO_VANG, P_XANH, P_VANG };
Phase phase = P_DO;
unsigned long last = 0;

void setup() {
  pinMode(PIN_DO_THO, OUTPUT);
  pinMode(PIN_XANH_THO, OUTPUT);
  Serial.begin(9600);
  Serial.println("Day18 - 2 IC - Bat dau chay lich");
}

void loop() {
  unsigned long now = millis();
  
  if (phase == P_DO && now - last >= 5000) {
    phase = P_DO_VANG; last = now;
    Serial.println("-> DO+VANG 2s");
  } else if (phase == P_DO_VANG && now - last >= 2000) {
    phase = P_XANH; last = now;
    Serial.println("-> XANH 5s");
  } else if (phase == P_XANH && now - last >= 5000) {
    phase = P_VANG; last = now;
    Serial.println("-> VANG 2s");
  } else if (phase == P_VANG && now - last >= 2000) {
    phase = P_DO; last = now;
    Serial.println("-> DO 5s");
  }

  // Giai ma 2 chan ra 4 pha
  if (phase == P_DO) {
    digitalWrite(PIN_DO_THO, HIGH); digitalWrite(PIN_XANH_THO, LOW);
  } else if (phase == P_DO_VANG) {
    digitalWrite(PIN_DO_THO, HIGH); digitalWrite(PIN_XANH_THO, HIGH);
  } else if (phase == P_XANH) {
    digitalWrite(PIN_DO_THO, LOW); digitalWrite(PIN_XANH_THO, HIGH);
  } else { // P_VANG
    digitalWrite(PIN_DO_THO, LOW); digitalWrite(PIN_XANH_THO, LOW);
  }
}
