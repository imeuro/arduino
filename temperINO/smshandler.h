void ProcessMsg() {
String smscontent;
char* SMSreplytxt;
char* SMSreplynum;

    smscontent = cell.Message();
    SMSreplynum = cell.Sender();
    SMSreplytxt = "";

    if (smscontent == "Mergozzo OFF" or smscontent == "Mergozzo off") {
      set_heat_prog(0);
      mainUI(0);
      SMSreplytxt = "Caldaia impostata su \"OFF\".\nTemp: ";
    }
    else if (smscontent == "Mergozzo T1" or smscontent == "Mergozzo t1") {
      set_heat_prog(1);
      mainUI(1);
      SMSreplytxt = "Caldaia impostata su \"T1\".\nTemp: ";
    }
    else if (smscontent == "Mergozzo T2" or smscontent == "Mergozzo t2") {
      set_heat_prog(2);
      SMSreplytxt = "Caldaia impostata su \"T2\".\nTemp: ";
      mainUI(2);
    }
    else if (smscontent == "Mergozzo T3" or smscontent == "Mergozzo t3") {
      set_heat_prog(3);
      mainUI(3);
      SMSreplytxt = "Caldaia impostata su \"T3\".\nTemp: ";
    }
    else if (smscontent == "Mergozzo AUTO" or smscontent == "Mergozzo auto") {
      set_heat_prog(9);
      mainUI(9);
      SMSreplytxt = "Caldaia impostata su \"AUTO\".\nTemp: ";
    }
    else {
      SMSreplytxt = "Comando non riconosciuto (es. \"Mergozzo T2\").";
    }

    Serial.println(tempC);
    dtostrf(tempC, 4, 1, &SMSreplytxt[50]);
    delay(2000);

    //send sms confirmation to sender number
    cell.Rcpt(SMSreplynum);
    cell.Message(SMSreplytxt);
    cell.SendSMS();
    
    delay(2000);
    cell.DeleteAllSMS();
}
