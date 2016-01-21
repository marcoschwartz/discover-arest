if (Meteor.isServer) {
  Meteor.startup(function () {

    // Add device
    aREST.addDevice('http', '192.168.115.107');

  });
}

if (Meteor.isClient) {

  // Main route
  Router.route('/', {name: 'home'});

  // Events
  Template.home.events({

    'click #on': function() {
      Meteor.call('digitalWrite', "34f5eQ", 7, 1);
    },
    'click #off': function() {
      Meteor.call('digitalWrite', "34f5eQ", 7, 0);
    }

  });

}
