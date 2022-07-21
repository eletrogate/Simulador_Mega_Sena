#include <LiquidCrystal_I2C.h> // Biblioteca do LCD I2C
#include <Wire.h>  // Biblioteca para ativar o I2C

#define QntdNum 6 // Quantidade de numeros sorteados

LiquidCrystal_I2C lcd(0x27,20,4); 

void setup() {
  randomSeed(analogRead(A0)); // Usando o pino A0 para embaralhar os numeros para ficarem aleatórios
  criaCaracteres(); // Chamando a função para criar os caracteres
  desenhaLogo(0,1); // Chamando a função para desenhar o logo com base na posição passada por parametro
  lcd.setCursor(6,1); // Setando o cursor para a posição para escrever a mensagem
  lcd.print("Simulador");
  lcd.setCursor(6,2);
  lcd.print("Mega Sena");
  desenhaLogo(16,1); // Chamando a função para desenhar o logo com base na posição passada por parametro
  Serial.begin(9600); // Inicia a comunicação serial para receber a informação também na comunicação serial.
  delay(4000); // Espera 4 segundos na tela inicial
  lcd.clear();
  Serial.println("Numeros da sorte: ");
  lcd.print(" Numeros da sorte: ");
  delay(50);
  
  
}

void loop() {
  int NumSorte[QntdNum], i = 0; // Inicia o vetor que irá receber os números aleatórios e uma variável para pular para o próximo espaço do vetor
  lcd.setCursor(1, 2);
  while (1) {
    do {
      NumSorte[i] = random(1, 60); // Recebe um numero aleatório no range definido.
    } while (VerificaRepetidos(NumSorte, i)); // Chama a função para verificar se existe numero repetido, e passa também quantos numeros existem no vetor
    //Caso o numero seja repetido, ele recebe outro numero e verifica de novo se é repetido, e repete até que não seja repetido.
    i++; // Pula para o próximo espaço do vetor.
    if (i == QntdNum) { // Verifica se o vetor está completo com a quantidade de numeros definidos
      insertionSort(NumSorte, QntdNum); //Chama a função para ordenar o vetor.
      for (int j = 0; j < QntdNum; j++) { // Imprime no LCD e serial cada numero individualmente separando por espaço
        Serial.print(NumSorte[j]);
        Serial.print(" ");
        lcd.print(NumSorte[j]);
        lcd.print(" ");
        delay(50);
      }
      Serial.println();   
      while(1){}; //Trava o programa
    }
  }
}



bool VerificaRepetidos(int* Numeros, int k) {  // Função que verifica se o número passado é repetido em relação aos outros
  for (int i = 0; i < k; i++) {
    if (Numeros[k] == Numeros[i]) return (true);
  }
  return (false);
}

void insertionSort(int arr[], int n) // O algoritmo de ordenação por inserção, que funciona como visto na vídeo.
{
  int aux, i, j;
  for (i = 1; i < n; i++) {
    aux = arr[i];
    j = i - 1;
    while (j >= 0 && arr[j] > aux) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = aux;
  }
}

void criaCaracteres(){ // Função que cria os caracteres com base nos desenhos que fizemos
  byte c1[] = {
  0x00,
  0x00,
  0x00,
  0x01,
  0x03,
  0x07,
  0x03,
  0x00
};
byte c2[] = {
  0x04,
  0x0E,
  0x0E,
  0x1E,
  0x1E,
  0x1E,
  0x1E,
  0x00
};
byte c3[] = {
  0x04,
  0x0E,
  0x0A,
  0x0B,
  0x0B,
  0x08,
  0x0F,
  0x00
};
byte c4[] = {
  0x00,
  0x00,
  0x00,
  0x10,
  0x1C,
  0x06,
  0x1C,
  0x00
};
byte c5[] = {
  0x00,
  0x03,
  0x06,
  0x03,
  0x00,
  0x00,
  0x00,
  0x00
};
byte c6[] = {
  0x00,
  0x1E,
  0x02,
  0x12,
  0x1A,
  0x0A,
  0x0E,
  0x00
};
byte c7[] = {
  0x00,
  0x0F,
  0x0F,
  0x0F,
  0x0F,
  0x0E,
  0x0E,
  0x04
};
byte c8[] = {
  0x00,
  0x18,
  0x1C,
  0x18,
  0x10,
  0x00,
  0x00,
  0x00
};
lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.createChar(0, c1);
  lcd.createChar(1, c2);
  lcd.createChar(2, c3);
  lcd.createChar(3, c4);
  lcd.createChar(4, c5);
  lcd.createChar(5, c6);
  lcd.createChar(6, c7);
  lcd.createChar(7, c8);
  
}

void desenhaLogo(int linha, int coluna){ // Função para desenhar a logo com base nos caracteres personalizados.
  lcd.setCursor(linha,coluna);
  lcd.write(0);
  lcd.write(1);
  lcd.write(2);
  lcd.write(3);
  lcd.setCursor(linha,coluna+1);
  lcd.write(4);
  lcd.write(5);
  lcd.write(6);
  lcd.write(7);
}