#include <Servo.h>

//初期設定
const int potm_pin = A0; //ポテンショメータ接続ピン
const int servo_pin = 6; //サーボモーター接続ピン
Servo servo;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(servo_pin);
}

void loop() {
  // put your main code here, to run repeatedly:
  int angle = 0;
  angle = read_potm();

  wind_dir_m(angle);

}


//ポテンショメータから値を読み取り、角度を返す
int read_potm() {
  int i;
  int potm_value = 0; //ポテンショメータの生の値
  //計測値の5回平均をとる
  for (i = 0; i < 5; i++){
    potm_value = potm_value + analogRead(potm_pin);
  }
  potm_value = potm_value / 5; //平均を求める

  int result;
  result = map(potm_value, 0, 1023, 0, 360); // 角度に変換
  
  //デバッグ用シリアル出力
  Serial.print("angle = ");
  Serial.println(result);
  
  delay(2);

  return result;
}

//サーボ制御部分
void wind_dir_m(int angle){
  
  if(angle <= 180){
    //角度が180度以下のとき
    servo.write(angle);
    delay(10);
  }else{
    //角度が181度以上360度以下のよき
    servo.write(angle - 180);
    delay(10);
  }
  
}
