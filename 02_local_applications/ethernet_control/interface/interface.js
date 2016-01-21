if (Meteor.isServer) {
  Meteor.startup(function () {

    // Add device
    aREST.addDevice('http', '192.168.115.104');

  });
}

if (Meteor.isClient) {

  // Main route
  Router.route('/', {name: 'home'});

  // Rendered
  Template.home.rendered = function() {

    // Refresh temperature & humidity
    Meteor.call('getVariable', 1, 'temperature', function(err, data) {
      console.log(data);
      $('#temperature').text(data.temperature);
    });

    Meteor.call('getVariable', 1, 'humidity', function(err, data) {
      $('#humidity').text(data.humidity);
    });

  }

}
