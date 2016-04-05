void ProcessMsg() {
String smscontent;
char* SMSreplytxt;
char* SMSreplynum;

    smscontent = cell.Message();
    SMSreplynum = cell.Sender();

    if (smscontent == "Mergozzo OFF" or smscontent == "Mergozzo off") {
      set_heat_prog(0);
      mainUI(0);
      SMSreplytxt = "Status: \"OFF\"\nTemp: ";
    }
    else if (smscontent == "Mergozzo T1" or smscontent == "Mergozzo t1") {
      set_heat_prog(1);
      mainUI(1);
      SMSreplytxt = "Status: \"T1\"\nTemp: ";
    }
    else if (smscontent == "Mergozzo T2" or smscontent == "Mergozzo t2") {
      set_heat_prog(2);
      SMSreplytxt = "Status: \"T2\"\nTemp: ";
      mainUI(2);
    }
    else if (smscontent == "Mergozzo T3" or smscontent == "Mergozzo t3") {
      set_heat_prog(3);
      mainUI(3);
      SMSreplytxt = "Status: \"T3\"\nTemp: ";
    }
    else if (smscontent == "Mergozzo AUTO" or smscontent == "Mergozzo auto") {
      set_heat_prog(9);
      mainUI(9);
      SMSreplytxt = "Status: \"AUTO\"\nTemp: ";
    }
    else {
      SMSreplytxt = "Errore!  (es. Mergozzo T2)";
    }

  char curTemp[6];
  char fullSMS[70];
  dtostrf(tempC, 4, 1, curTemp);
  strcpy(fullSMS,SMSreplytxt);
  strcat(fullSMS,curTemp);
  Serial.println(fullSMS);

    delay(2000);

    //send sms confirmation to sender number
    cell.Rcpt(SMSreplynum);
    cell.Message(fullSMS);
    cell.SendSMS();
    
    //delay(2000);
    cell.DeleteAllSMS();
}
