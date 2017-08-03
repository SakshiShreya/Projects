int a = 0;
int b = 1;
int c = 2;
int d = 3;
int e = 4;
int f = 5;
int g = 6;
int h = 7;

int en0 = 11;
int en1 = 12;

void setup() {
    pinMode(a, OUTPUT);
    pinMode(b, OUTPUT);
    pinMode(c, OUTPUT);
    pinMode(d, OUTPUT);
    pinMode(e, OUTPUT);
    pinMode(f, OUTPUT);
    pinMode(g, OUTPUT);
    pinMode(h, OUTPUT);
    pinMode(en0, OUTPUT);
    pinMode(en1, OUTPUT);
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
    digitalWrite(h, HIGH);
}

void loop() {
    for(int i = 0; i <= 9; i++)
    {
        for(int j = 0; j <= 9; j++)
        {
            for(int k = 0; k <= 100; k++){
                digitalWrite(en0, LOW);
                digitalWrite(en1, HIGH);
                seven(j);
                delay(10);
                digitalWrite(en0, HIGH);
                digitalWrite(en1, LOW);
                seven(i);
                delay(10);
            }
            digitalWrite(a, HIGH);  
            digitalWrite(b, HIGH);
            digitalWrite(c, HIGH);
            digitalWrite(d, HIGH);
            digitalWrite(e, HIGH);
            digitalWrite(f, HIGH);
            digitalWrite(g, HIGH);
        }
    }
}

void  seven(int i)  {
    if(i == 0 || i == 2 || i == 3 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9)
        digitalWrite(a, 0);
    if(i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 7 || i == 8 || i == 9)
        digitalWrite(b, 0);
    if(i == 0 || i == 1 || i == 3 || i == 4 || i == 5 || i == 6 || i == 7 || i == 8 || i == 9)
        digitalWrite(c, 0);
    if(i == 0 || i == 2 || i == 3 || i == 5 || i == 6 || i == 8)
        digitalWrite(d, 0);
    if(i == 0 || i == 2 || i == 6 || i == 8)
        digitalWrite(e, 0);
    if(i == 0 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9)
        digitalWrite(f, 0);
    if(i == 2 || i == 3 || i == 4 || i == 5 || i == 6 || i == 8 || i == 9)
        digitalWrite(g, 0);
}
