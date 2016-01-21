// Function to control lamp
$(document).ready(function() {

  // Click on buttons
  $("#on").click(function() {
    $.get('/digital/7/1');
  });

  $("#off").click(function() {
    $.get('/digital/7/0');
  });

  // Refresh sensor data
  refreshSensors();
  setInterval(refreshSensors, 5000);

  // Refresh camera picture
  setInterval(function() {

    // Take picture
    $.get("/camera/snapshot");

  }, 10000);

  setInterval(function() {

    // Reload picture
    d = new Date();
    $("#camera").attr("src","/pictures/image.jpg?" + d.getTime());

  }, 1000);

});

function refreshSensors() {

  $.get('/temperature', function(json_data) {
    $("#temperature").text('Temperature: ' + json_data.temperature + ' C');

	$.get('/humidity', function(json_data) {
      $("#humidity").text('Humidity: ' + json_data.humidity + ' %');
    });
  });

}
