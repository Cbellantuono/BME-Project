int const order = 3; //average filter order
unsigned int val[order]; //store & read in values
unsigned long sum = 0; //temp sum for filter
float filt_val = 0; //stored filter value

int analogPin = A4;
unsigned long t0, t1,  t; //time tracking
int flag = 0; //stops printing
int i, j; //interval counters
int pinNumber = 8;
double volt = 0;

unsigned long baud = 9600; //baud rate


void setup() {
  // put your setup code here, to run once:
  Serial.begin(baud);
  flag = 0;
 
  pinMode(pinNumber, OUTPUT); //This will set a specific pin on the
                              //Arduino to supply an output.
  for (i=0; i < order - i; i++) {
    val[i] = 0; //initializes val[i] to 0
    }
  Serial.println("Start!");
  sum = 0;
  t0 = micros(); //initializes t0
  }
 

void loop() {
  // put your main code here, to run repeatedly:
  if(flag == 0) {
    t = micros();

    for(i = 0; i < order -1; i++) {
      val[i] = analogRead(A1);
      delayMicroseconds(1000);
      sum+= val[i];
      }
    while (t-t0 < 30000000) {
      t1 = micros();
     
      // moving average (filter) calculation
      val[i] = analogRead(analogPin);      // read input pin in last filter spot
      sum += val[i++];
      filt_val = (float)sum / order;       // filtered value
      i = order - i;                       // reset counter (point to replace)
      sum -= val[i];  
           
      Serial.println(val[i]);
      if(val[i] > 553) { //find value for val[i] where arm is flexed

          digitalWrite(pinNumber, HIGH);//This will output a voltage to the
                                        //specified pin. “HIGH” will supply 5 volts,
      }
      else
      {
          digitalWrite(pinNumber, LOW); //stops output when input is below desired filtered value.
      }
     
      t = micros();
      delayMicroseconds(1000 - (t - t1));  // 1 msec delay
     
     
    }
  }
}