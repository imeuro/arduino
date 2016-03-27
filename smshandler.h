void ProcessMsg() {
    smscontent = cell.Message();
    SMSreplynum = cell.Sender();
    SMSreplytxt = "";
    GetTemp();
    if (smscontent == prefix+" OFF" || smscontent == prefix+" off") {
      set_heat_prog(0);
      mainUI(0);
      SMSreplytxt = "Caldaia Mergozzo impostata su \"OFF\".";
    }
    else if (smscontent == prefix+" T1" || smscontent == prefix+" t1") {
      set_heat_prog(1);
      mainUI(1);
      SMSreplytxt = "Caldaia Mergozzo impostata su \"T1\".";
    }
    else if (smscontent == prefix+" T2" || smscontent == prefix+" t2") {
      set_heat_prog(2);
      SMSreplytxt = "Caldaia Mergozzo impostata su \"T2\".";
      mainUI(2);
    }
    else if (smscontent == prefix+" T3" || smscontent == prefix+" t3") {
      set_heat_prog(3);
      mainUI(3);
      SMSreplytxt = "Caldaia Mergozzo impostata su \"T3\".";
    }
    else if (smscontent == prefix+" AUTO" || smscontent == prefix+" auto") {
      set_heat_prog(9);
      mainUI(9);
      SMSreplytxt = "Caldaia Mergozzo impostata su \"AUTO\".";
    }
    else {
      SMSreplytxt = "Comando non riconosciuto (es. \"Mergozzo T2\" per impostare a T2 il termostato).";
      // Temperatura attuale: "+Clock.getTemperature()+" C";
    }
    delay(2000);

    cell.DeleteAllSMS();

    //send sms confirmation to sender number
    cell.Rcpt(SMSreplynum);
    cell.Message(SMSreplytxt);
    cell.SendSMS();

}

