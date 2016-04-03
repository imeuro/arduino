void ProcessMsg() {
char* smscontent;
char* SMSreplytxt;
char* SMSreplynum;
//String fullSMS;

    smscontent = cell.Message();
    SMSreplynum = cell.Sender();
    SMSreplytxt = "";

    if (smscontent == "Mergozzo OFF" || smscontent == "Mergozzo off") {
      set_heat_prog(0);
      mainUI(0);
      SMSreplytxt = "Caldaia Mergozzo impostata su \"OFF\". \nTemp: ";
    }
    else if (smscontent == "Mergozzo T1" || smscontent == "Mergozzo t1") {
      set_heat_prog(1);
      mainUI(1);
      SMSreplytxt = "Caldaia Mergozzo impostata su \"T1\". \nTemp: ";
    }
    else if (smscontent == "Mergozzo T2" || smscontent == "Mergozzo t2") {
      set_heat_prog(2);
      SMSreplytxt = "Caldaia Mergozzo impostata su \"T2\". \nTemp: ";
      mainUI(2);
    }
    else if (smscontent == "Mergozzo T3" || smscontent == "Mergozzo t3") {
      set_heat_prog(3);
      mainUI(3);
      SMSreplytxt = "Caldaia Mergozzo impostata su \"T3\". \nTemp: ";
    }
    else if (smscontent == "Mergozzo AUTO" || smscontent == "Mergozzo auto") {
      set_heat_prog(9);
      mainUI(9);
      SMSreplytxt = "Caldaia Mergozzo impostata su \"AUTO\". \nTemp: ";
    }
    else {
      SMSreplytxt = "Comando non riconosciuto (es. \"Mergozzo T2\" per impostare a T2 il termostato).";
    }

    dtostrf(tempC, 4, 1, &SMSreplytxt[80]);

    //send sms confirmation to sender number
    cell.Rcpt(SMSreplynum);
    cell.Message(SMSreplytxt);
    cell.SendSMS();
    
    delay(2000);
     cell.DeleteAllSMS();
}
