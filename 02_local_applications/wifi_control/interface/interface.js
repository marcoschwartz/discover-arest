if (Meteor.isServer) {
  Meteor.startup(function () {

    // Add device
    aREST.addDevice('http', '192.168.115.105');

    // Regularly check temperature
    SyncedCron.add({
      name: 'Check temperature',
      schedule: function(parser) {
        return parser.text('every 1 minute');
      },
      job: function() {
        Meteor.call('getVariable', 1, 'temperature', function(err, data) {

          // Check temperature value
          if (data.temperature < 20) {

            // Activate relay
            Meteor.call('digitalWrite', 1, 7, 1);
          }
        });
      }
    });

  });
}

if (Meteor.isClient) {

  // Main route
  Router.route('/', {name: 'home'});

  // Events
  Template.home.events({

    'click #on': function() {
      Meteor.call('digitalWrite', 1, 7, 1);
    },
    'click #off': function() {
      Meteor.call('digitalWrite', 1, 7, 0);
    }

  });

  // Rendered
  Template.home.rendered = function() {

    // Set pin
    Meteor.call('pinMode', 1, 7, 'o');

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
