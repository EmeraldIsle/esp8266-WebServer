﻿const char MAIN_page[] PROGMEM = R"=====(
<HTML>
  <HEAD>
      <TITLE>ESP8266 Main Page</TITLE>
     <link href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u" crossorigin="anonymous">
 <script src="https://code.jquery.com/jquery-3.2.1.min.js"
  integrity="sha256-hwg4gsxgFZhOsEEamdOYGBf13FyQuiTwlAQgxVSNgt4="
  crossorigin="anonymous"></script>
     <meta name="viewport" content="width=device-width, initial-scale=1">
  </HEAD>
  

<BODY>
<div class="text-center">
<img src="http://www.cnx-software.com/wp-content/uploads/2016/02/Wemos_D1_mini.jpg" class="img-thumbnail">
<label>
This page is being served by an ESP8266
</label>
</div>
<div class="text-center">

<div class="checkbox">
    <label>
      <input type="checkbox" id="led1"><b id="LED">Turn LED ON</b>
    </label>
    <label>
      <input type="checkbox" id="flash" name="led" class="ledState"> Flash
    </label>
  </div>
   <button type="submit" class="btn btn-primary" id="btnSubmit">Send</button>
   <p class="help-block">This button sends a JSON Request to the ESP8266</p>

</div>

</BODY>

<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js" integrity="sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa" crossorigin="anonymous"></script>
<script>

$(document).ready(function() {

    $("#btnSubmit").click(function(){

  var values = [$('#led1').is(":checked"),$('#flash').is(":checked")];
if(values[0] == true){
  $('#LED').text('LED: ON');
   }
   else
   {
  $('#LED').text('LED: OFF');
   }
  var data = JSON.stringify({led1:values[0],flash:values[1]});
  console.log(data);
      
        $.ajax({
    url: '/api/',
    type: 'POST',
    data: data,
    //data: JSON.stringify(LedState),
    contentType: 'application/json; charset=utf-8',
    dataType: 'json',
    async: false,
    success: function(msg) {
        alert(msg);
    }
});
 $(this).addClass('active');
    }); 
});
</script>
</HTML>
)=====";

