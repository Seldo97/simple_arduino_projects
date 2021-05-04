const char charTable[37] = { //tablica z literami i cyframi
  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'w', 'v', 'x', 'y', 'z',
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0'
};

const short morseTable[37][7] = { //dwuwymiarowa tablica, pierwszy wymiar odpowiada za dany znak z tablicy liter i cyfr,
  //a drugi zawiera przetworzony ciąg kropek i kresek - zrozumiały w kodzie morse'a.
  //0 - dot, 1 - dash, 2 - end //jako kropkę oznaczamy 0, kreska to 1, a koniec ciągu to 2
  {0, 1, 2},//a
  {1, 0, 0, 0, 2},//b
  {1, 0, 1, 0, 2},//c
  {1, 0, 0, 2},//f
  {0, 2},//e
  {0, 0, 1, 0, 2},//f
  {1, 0, 0, 2},//g
  {0, 0, 0, 0, 2},//h
  {0, 0, 2},//i
  {0, 1, 1, 1, 2},//j
  {1, 0, 1, 2},//k
  {0, 1, 0, 0, 2},//l
  {1, 1, 2},//m
  {1, 0, 2},//n
  {1, 1, 1, 2},//o
  {0, 1, 1, 0, 2},//p
  {1, 1, 0, 1, 2},//q
  {0, 1, 0, 2},//r
  {0, 0, 0, 2},//s
  {1, 2},//t
  {0, 0, 1, 2},//u
  {0, 1, 1, 2},//w
  {0, 0, 0, 1, 2},//v
  {1, 0, 0, 1, 2},//x
  {1, 0, 1, 2},//y
  {1, 1, 0, 0, 2},//z
  {0, 1, 1, 1, 1, 2},//1
  {0, 0, 1, 1, 1, 2},//2
  {0, 0, 0, 1, 1, 2},//3
  {0, 0, 0, 0, 1, 2},//4
  {0, 0, 0, 0, 0, 2},//5
  {1, 0, 0, 0, 0, 2},//6
  {1, 1, 0, 0, 0, 2},//7
  {1, 1, 1, 0, 0, 2},//8
  {1, 1, 1, 1, 0, 2},//9
  {1, 1, 1, 1, 1, 2}//0
  //0 - dot, 1 - dash, 2 - end
};

const int dotLength = 300; //długość trwania kropki w milisekundach
String slowo;

int ledPinOne = 8;
int ledPinTwo = 9;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Podaj słowo:");
  pinMode(ledPinOne, OUTPUT);
  pinMode(ledPinTwo, OUTPUT);

}

void loop() {
  if (Serial.available() > 0) {
    slowo = Serial.readString();
    Serial.println(slowo);

    for (int i = 0; i < slowo.length(); i++) {
      for (int j = 0; j < 37; j++) {
        if (slowo[i] == charTable[j]) {
          displayLetter(j);
        }
      }
    }

    breakAfterWord();
  }
}

void displayLetter(int wordPosition) {
  Serial.println();
  Serial.println(charTable[wordPosition]);

  int k = 0;
  while (morseTable[wordPosition][k] != 2) {
    if (morseTable[wordPosition][k] == 0) {
      blinkDot();
    }
    else {
      blinkDash();
    }
    k++;
  }
  pauseAfterLetter();
}

void blinkDot() {
  Serial.print(".");
  digitalWrite(ledPinOne, HIGH);
  delay(dotLength);
  digitalWrite(ledPinOne, LOW);
  delay(dotLength);
}

void blinkDash() {
  Serial.print("-");
  digitalWrite(ledPinOne, HIGH);
  delay(3 * dotLength);
  digitalWrite(ledPinOne, LOW);
  delay(dotLength);
}

void pauseAfterLetter() {
  delay(dotLength * 2);
}

void breakAfterWord() {
  Serial.println("\nbreak");
  digitalWrite(ledPinTwo, HIGH);
  delay(dotLength * 6);
  digitalWrite(ledPinTwo, LOW);
  delay(dotLength);
}
