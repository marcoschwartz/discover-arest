if (Meteor.isServer) {
  Meteor.startup(function () {

    // Add device
    aREST.addDevice('http', '192.168.115.104');
    aREST.addDevice('http', '192.168.115.105');
    aREST.addDevice('http', '192.168.115.106');

  });
}

if (Meteor.isClient) {

  // Main route
  Router.route('/', {name: 'home'});

  // Init
  Template.home.rendered = function() {

    // Set pin
    Meteor.call('pinMode', 2, 4, 'o');

    // Refresh temperature & humidity
    Meteor.call('getVariable', 1, 'temperature', function(err, data) {
      console.log(data);
      $('#temperature').text(data.temperature);
    });

    Meteor.call('getVariable', 1, 'humidity', function(err, data) {
      $('#humidity').text(data.humidity);
    });

  }

  // Helpers
  Template.home.helpers({

    motionStatus: function() {

      // Motion sensor
      var sensorState = Events.find({}, {sort: {timestamp: -1}}).fetch()[0];
      console.log(sensorState);

      if (sensorState.value == '1') {
        return 'Motion detected';
      }
      if (sensorState.value == '0') {
        return 'No motion';
      }

    }

  });

  // Events
  Template.home.events({

    'click #on': function() {
      Meteor.call('digitalWrite', "2", 4, 1);
    },
    'click #off': function() {
      Meteor.call('digitalWrite', "2", 4, 0);
    }

  });

}
