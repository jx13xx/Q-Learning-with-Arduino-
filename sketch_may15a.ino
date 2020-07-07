// PATTERN:

//Reward Matrice
float Q[8][8];
// setting all to zeros 


// Mapping Matrice -1's are walls, 0's are possibility and 100 is target

float R[8][8] = {
  {-1,0,0,0,-1 ,-1 ,-1, -1},  // For 0
  {0,-1, -1, -1, 0, -1, -1, -1}, // For 1
  {0, -1 , -1,-1, 0, 0, -1, -1}, // For 2
  {0, -1, -1, -1, -1, -1, 100,-1}, // For 3
  {-1, 0, 0, -1, -1, -1, -1, 0}, // For 4
  {-1, -1, 0, -1, -1, -1, -1, 0}, // For 5 
  {-1, -1, -1, 0, -1, -1, -1, -1}, // For 6
  {-1, -1, -1, -1, 0, 0, -1, -1} // For 7
};

int M[8][3] = { {1,2,3}, {0, 4}, {0, 4, 5}, {0 ,6}, {1,2,7}, {2 ,7}, {3}, {5,4}  };
// write possibilites 

//Arduino Pins 
int pins[] = {2, 3, 4, 5, 6, 7, 8, 9};

//random selected action on the current state (oe next state)
int action;

//current position 
int state;
int GOAL_STATE = 6;
int Start = 2;

int i, j,l, m;
int k = 0;
int r; 
// defining the gamma factor 
float gamma = 0.8;
float Qmax; 

float a;
float b; 

// set all pins to output
void setup() {
  // put your setup code here, to run once:
  for (int i =1; i<8; i++){
    for (int j = 0; j<8; j++) {
      Q[i][j] = 0;
    }
  }

  for (i = 0; i<8; i ++) {
    pinMode(pins[i],OUTPUT);
    Serial.begin(9600);
    Serial.println("begin");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  while (k <10 ){
    //initital state
    state = Start;
    j = state +2;
    digitalWrite(j, HIGH);
    delay(100);
    digitalWrite(j,LOW);
    delay(50);


    while (state != GOAL_STATE) {
      // Select the next possible action randomly
      switch(state){
        case 0:
          r = rand() % 3;
          break;
        case 1:
          r = rand() % 2;
          break;
        case 2:
          r = rand() % 3;
          break;
        case 3:
          r = rand() % 2;
          break;
        case 4:
         r = rand() % 3;
         break;
        case 5:
         r = rand() % 2;
         break;
        case 6:
         r = rand() % 1;
         break;
        case 7:
         r = rand() % 2;
         break;
      }

      action = M[state][r];

      a = -10;
      for (i =0; i<8; i++) {
        if( a < Q[action][i]) {
          a = Q[action][i];
        }
      }

      // Compute the Qmax and rewards for the action 
      Qmax = a* gamma;
      Q[state][action] = R[state][action] + Qmax;
      state = action;


      //Light up the led at the postion 
      j = state +2;
      digitalWrite(j,HIGH); // turn the LED On
      delay(40);
      digitalWrite(j,LOW); // turn the LED OFF
      delay(15);
    }
    Serial.println(k);
    // increment the k value 
    k++;
  }


Serial.println("***PROGRAM DONE****");

  while(1) {
    // another infinite loop to light up the correct path

    state = Start;
    j = state +2;

    digitalWrite(j,HIGH); // turn the LED on 
    delay(300); // wait time 
    digitalWrite(j, LOW); // turn the LED off
    delay(100); // wate for a second 

    // Finds the action with the highest score and performance
    b = -10;
    // do the while loop until you reach the final destination 
    while (state != GOAL_STATE) {
      for (i = 0; i<8; i++) {
        if(b <= Q[state][i]) {
          b = Q[state][i];
          l = i;
        }
      }
      state = l;

      // light up the leds at that position 
      j = state + 2;
      digitalWrite(j, HIGH); // turn the LED ON
      delay(300);
      digitalWrite(j, LOW); // turn the LED off
      delay(100);
    }
  }


}
