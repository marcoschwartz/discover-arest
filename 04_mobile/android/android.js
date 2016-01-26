if (Meteor.isClient) {

  // Events
  Template.home.events({
    'click #on': function() {
      Meteor.call('digitalWrite', "192.168.115.105", 5, 1);
    },
    'click #off': function() {
      Meteor.call('digitalWrite', "192.168.115.105", 5, 0);
    }
  });
}

if (Meteor.isServer) {

  Meteor.methods({

    digitalWrite: function(ipAddress, pin, state) {
      HTTP.get('http://' + ipAddress + '/digital/' + pin + '/' + state);
    }

  });

}
