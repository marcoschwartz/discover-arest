if (Meteor.isServer) {
  Meteor.startup(function () {

    // Add device
    aREST.addDevice('http', '192.168.115.104');

  });
}

if (Meteor.isClient) {

  // Main route
  Router.route('/', {name: 'home'});

  // Events
  Template.home.events({

    'click #on': function() {
      Meteor.call('digitalWrite', 1, 4, 1);
    },
    'click #off': function() {
      Meteor.call('digitalWrite', 1, 4, 0);
    }

  });

  // Rendered
  Template.home.rendered = function() {

    // Set pin
    Meteor.call('pinMode', 1, 4, 'o');

  }

}
