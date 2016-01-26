$( document ).ready(function() {

  // Create new aREST device when button is clicked
    var device = new Device("192.168.115.105");

    // Set device pins
    device.pinMode(6, "OUTPUT");

    // Button
    $('#on').click(function() {
      device.digitalWrite(6, 1);
    });

    $('#off').click(function() {
      device.digitalWrite(6, 0);
    });

    // Analog write
    $('#slider').mouseup(function() {
      var val = $('#slider').val();
      device.analogWrite(6, val);
    });

    //Analog read every 5 seconds
    device.analogRead(0, function(data) {
      $("#A0").html(data.return_value);
    });
    setInterval(function() {
      device.analogRead(0, function(data) {
        $("#A0").html(data.return_value);
      });
    }, 5000);

});
