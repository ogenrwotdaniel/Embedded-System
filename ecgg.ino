void ecg(){
  if((digitalRead(LO_PINN) == 1)||(digitalRead(LO_PINP) == 1)){
Serial.println('!');
}
else{
// send the value of analog input 0:
Serial.println(analogRead(A0));
}}