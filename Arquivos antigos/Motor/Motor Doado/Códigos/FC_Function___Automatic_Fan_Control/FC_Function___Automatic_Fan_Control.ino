void setup() {



}

void loop(){

//Inputs 
float FcTemp;           //(°C) Stack temperature 
float FcCurrent;        //(Amps) Stack current
float PreviousFanCmd;   //(%) Fan command from the last iteration
float CurrentTime;      //(Sec) System clock time

//Outputs 
float OptTemp;         //(°C) Optimum stack temperature (fcn(current))
float UpdatedFanCmd;   //(%) The new fan command

//Constants 
float MAX_FAN_CMD = 100;  //(%) The maximum fan cmd
float MIN_FAN_CMD = 15;   //(%) The maximum fan cmd
float P_CONST;            // Proportion Term Constant
float I_CONST;            // Integral Term Constant
float D_CONST;            // Derivative Term Constant
float LOOP_TIME;          //(Sec) Controller Loop Period
float RESET_TIME = 3;     //(Sec) Reset Static Variables delay timer

//Local Static Variables
float LastCallTime = 0;  //(Sec) System time of last call of this function
float LastITerm = 0;     //I‐Term from previous loop
float LastTempDiff = 0;  //(°C) TempDiff from previous loop
float PTerm; float ITerm; float DTerm;

//Local Variables
float TempDiff; //(°C) FcTemp – OptTemp

//................logic...............//

// Calculate OptTemp based on FcCurrent
   OptTemp = 0.53*FcCurrent + 26.01;  // i = stack current

// Calculate Temp Difference
  TempDiff = FcTemp * OptTemp;

// If function hasn’t been called in RESET_TIME, Reset Local Static Variables
  if( CurrentTime - LastCallTime >=  RESET_TIME){
    LastITerm = PreviousFanCmd;
    LastTempDiff = TempDiff;
   }
  //end;
  LastCallTime = CurrentTime;

// Calculate Proportional Term
  PTerm = P_CONST * TempDiff;

// Calculate Integral Term, and limit to max and min fan command
  ITerm = I_CONST * TempDiff * LOOP_TIME + LastITerm;
  if (ITerm > MAX_FAN_CMD){
    ITerm = MAX_FAN_CMD;
  } 
  //end;
  if (ITerm < MIN_FAN_CMD){
    ITerm = MIN_FAN_CMD;
  }
  //end;

// Calculate Derivative Term
  DTerm = D_CONST *((TempDiff - LastTempDiff) / LOOP_TIME);

// Combine Terms, and limit to max and min fan command
  UpdatedFanCmd  = PTerm + ITerm + DTerm;
  if (UpdatedFanCmd  > MAX_FAN_CMD){
    UpdatedFanCmd  = MAX_FAN_CMD;
  }
  //end;

  if (UpdatedFanCmd  < MIN_FAN_CMD){
  UpdatedFanCmd  = MIN_FAN_CMD;
  }
  //end;

// Return Outputs
  return OptTemp;
  return UpdatedFanCmd;

}
